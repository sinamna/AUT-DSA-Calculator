#include <iostream>
#include <string>
#include <stack>
#include <unordered_map> 
#include "DLinkedList.h"
#include "Node.h"
using namespace std;

class Calculator{
    private:
        LinkedList* list;
        //unordered_map for hashing
        unordered_map<string,long> savedEval;
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
    //calculating and hashing
    long evalPostfix(){
        long result;
        string postExpr= convertToPostfix();
        if (savedEval.find(postExpr)==savedEval.end()){
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
            result = operands.top();
            operands.pop();
            savedEval[postExpr]=result;
        }else{
            result =savedEval.at(postExpr);
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
    void printExpr(){
        list->printList();
    }
};

int main(){
    int orderCount;
    cin>>orderCount;
    string expression;
    // getline(cin,expression);
    cin>>expression;

    Calculator cal(expression);
    for (int i=0;i<orderCount;i++){
        string order;
        getline(cin,order);
        switch(order.at(0)){
            case '>':
                cal.moveCurserToRight();
                break;
            case '<':
                cal.moveCurserToLeft();
                break;
            case '?':
                cal.printExpr();
                break;
            case '-':
                cal.removeChar();
                break;
            case '!':
                cout<<cal.evalPostfix();
                break;
            default:
                char toBeAdded= order.at(0);
                cal.addCharacter(toBeAdded);
        }
    }
}