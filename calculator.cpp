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
        // string expr;
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
        return 0;
    }
    string convertToPostfix(){
        string operators="()*+-";
        string result="";
        stack<char> opstack;
        Node* current=list->head;
        while(current!=NULL){
            char ch = current->val;
            size_t operand_found=operators.find(ch);
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
            current=current->next;
        }
        while(!opstack.empty()){
            result.push_back(opstack.top());
            opstack.pop();
        }
        return result;
    }
    public:
    Calculator(string expr){
        list= new LinkedList();
        list->convertStrToList(expr);
    }
    //hashing 
    
    //calculating 
    long evalPostfix(){
        string postExpr= convertToPostfix();
        stack<long> operands;
        string operators="()*+-";

        for(int i=0;i<postExpr.length();i++){
            char ch = postExpr.at(i);
            size_t is_operand=operators.find(ch);
            if(is_operand!=string::npos){
                long op1=operands.top();
                operands.pop();
                long op2= operands.top();
                operands.pop();
                long result=0;
                switch(ch){
                    case '*':
                        result=op1*op2;
                        break;
                    case '+':
                        result=op1+op2;
                        break;
                    case '-':
                        result=op2-op1;
                        break;
                }
                operands.push(result%(10^9+7));
            }else{
                int num = ch - '0';
                operands.push(num);
            }
        }
        long result = operands.top();
        operands.pop();
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