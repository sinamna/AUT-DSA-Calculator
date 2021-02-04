#include <iostream>
#include <string>
#include <stack>
#include "DLinkedList.h"
#include "Node.h"
using namespace std;

class Calculator{
    private:
        LinkedList* list;

        //unordered_map for hashing
        string expr;
    int precLevel(char ch){
        switch (ch){
            case '+':
                return 2;
            case '-':
                return 2;
            case '*':
                return 3;
            case '(':
                return 1;
        }
    }
    public:

    Calculator(string expr){
        list= new LinkedList();
        this->expr=expr;
    }
    //hashing 

    //calculating 

    //converting infix to postfix
    string convertToPostfix(){
        string operands="()*+-";
        string result="";
        stack<char> opstack;
        for (int i=0;i<expr.length();i++){
            char ch = expr.at(i);
            size_t operand_found=operands.find(ch);
            if(operand_found != string::npos){
                if(ch == '(')
                    opstack.push(ch);
                else if(ch == ')'){
                    char top = opstack.top();
                    opstack.pop();
                    while(top!= '('){
                        result.push_back(top);
                        top =opstack.top();
                        opstack.pop();
                    }
                }else{
                    while(!opstack.empty() && (precLevel(opstack.top()) >= precLevel(ch))){
                        result.push_back(opstack.top());
                        opstack.pop();
                    }
                    opstack.push(ch);
                }

            }else{
                result.push_back(ch);
            }
        }
        while(!opstack.empty()){
            result.push_back(opstack.top());
            opstack.pop();
        }
        return result;
    }
    //move cursor to right
    void moveCurserToRight(){
        list->moveCursorToRight();
    }
    //move cursor to the left
    void moveCurserToLeft(){
        list->moveCursorToLeft();
    }
    void addCharacter(char c){
        list->insert(c);
    }
    void removeChar(){
        list->remove();
    }
};

int main(){

}