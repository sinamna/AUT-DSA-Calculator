#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <unordered_map> 
#include <cmath>
// #include "DLinkedList.h"
// #include "Node.h"
#define LIMIT (int(pow(10,9))+7)
using namespace std;
class Node{
    public:
    char val;
    Node* next;
    Node* prev;
    Node(char inVal){
        val=inVal;
        next=NULL;
        prev=NULL;    
    }
};
class LinkedList{
    private:
    //create Node
    Node* create_node(char val){
        Node* newNode= new Node(val);
        newNode->next=NULL;
        newNode->prev=NULL;
        return newNode;
    }
    public:
    Node* tail;
    Node* head;
    Node* cursor;
    //constructor
    LinkedList(){
        head=NULL;
        tail=NULL;
        cursor=create_node('c');
        head=tail=cursor;
    }
    //size
    //return cursor
    Node* get_cursor(){
        return cursor;
    }
    //insert_head
    void insert_head(char val){
        Node* newNode=create_node(val);
        if (head==NULL) head=tail=newNode;
        else{
            newNode->next=head;
            head->prev=newNode;
            head=newNode;
        }
    }
    //remove_head
    Node* remove_head(){
        if(head==NULL) return NULL;
        Node* removedHead=head;
        if(head->next==NULL){
            head=tail=NULL;
        }else{
            head->next->prev=NULL;
            head=head->next;
        }
        return removedHead;
    }
    //insert_tail
    void insert_tail(char val){
        Node* newNode=create_node(val);
        if (tail==NULL) head=tail=newNode;
        else{
            tail->next=newNode;
            newNode->prev=tail;
            tail=newNode;
        }
    }
    //remove_tail
    Node* remove_tail(){
        if(tail==NULL)return NULL;
        Node* removedNode=tail;
        if(tail->prev==NULL){
            head=tail=NULL;
        }else{
            tail->prev->next=NULL;
            tail=tail->prev;
        }
        return removedNode;
    }

    //insert in calculator
    void insert(char val){        
        if(cursor==head)insert_head(val);
        else if(cursor==tail){
            Node* newNode=create_node(val);
            tail->prev->next=newNode;
            newNode->prev=tail->prev;
            newNode->next=tail;
            tail->prev=newNode;
        }
        else{
            Node* newNode=create_node(val);
            cursor->prev->next=newNode;
            newNode->prev=cursor->prev;
            newNode->next=cursor;
            cursor->prev=newNode;
        }
    }
    //remove in calculator
    Node* remove(){
        Node* nodeToRemove=cursor->prev;
        if(nodeToRemove==NULL) return NULL;
        if(nodeToRemove==head)return remove_head();
        if(nodeToRemove==tail)return remove_tail();
        nodeToRemove->prev->next=nodeToRemove->next;
        nodeToRemove->next->prev=nodeToRemove->prev;
        return nodeToRemove;
    }
    //convert string to linkedList
    void convertStrToList(string str){
        for(int i=0;i<str.length();i++){
            insert_tail(str.at(i));
        }
    }
    void printList(){
        Node* current=head;
        while(current!=NULL){
            if(current->val == 'c') cout<<'|';
            else
                cout<<current->val;
            current=current->next;
        }
        cout<<endl;
    }
    void movecursorToRight(){
        if(cursor==tail)return;
        if(cursor==head){
            Node* nextNode=cursor->next;
            cursor->next=nextNode->next;
            nextNode->next=cursor;
            cursor->prev=nextNode;
            head=nextNode;
            if(cursor->next!=NULL)
                cursor->next->prev=cursor;
            else
                tail=cursor;
            
        }else{
            cursor->prev->next=cursor->next;
            cursor->next->prev=cursor->prev;

            Node* nextNode= cursor->next;
            cursor->prev=nextNode;
            cursor->next=nextNode->next;

            nextNode->next=cursor;
            if(cursor->next!=NULL)
                cursor->next->prev=cursor;
            else
                tail=cursor;
            // :"") PARE
        }
    }
    void movecursorToLeft(){
            if(cursor==head) return;
            if(cursor==tail){
                Node* prevNode=cursor->prev;
                cursor->prev=prevNode->prev;
                prevNode->next=cursor->next;
                cursor->next=prevNode;
                prevNode->prev=cursor;
                tail=prevNode;
                if(cursor->prev!=NULL)
                    cursor->prev->next=cursor;
                else
                    head=cursor;  
            }else{
                cursor->next->prev=cursor->prev;
                cursor->prev->next=cursor->next;

                Node* prevNode=cursor->prev;
                cursor->prev=prevNode->prev;
                cursor->next=prevNode;
                prevNode->prev=cursor;

                if(cursor->prev!=NULL)
                    cursor->prev->next=cursor;
                else
                    head=cursor;
            }
        }
};
class Calculator{
    private:
        LinkedList* list;
        //unordered_map for hashing
        unordered_map<string,long> savedEval;
        // string expr;
    int precLevel(char str){
        if (str == '+')return 2;
        if(str == '-')return 2;
        if(str == '*')return 3;
        if(str =='(')return 1;
        return 0;
    }
    string convertToPostfix(){
        string operators="()*+-";
        stringstream result;
        stringstream temp;
        stack<char> opstack;
        bool flag=false;
        bool negflag=false;
        Node* current=list->head;
        while(current!=NULL){
            char nextVal=current->next!=NULL?current->next->val:'n';
            char currentVal= current->val;
            if(isdigit(currentVal)){
                temp<<currentVal;
                if(operators.find(nextVal) != string::npos || nextVal =='n'||nextVal =='c'){
                    if(negflag){
                        result<<"-";
                        negflag=false;
                        }
                    result<<temp.str()<<" ";
                    if(flag){
                        result<<"* ";
                        flag=false;
                    }
                    temp.str("");
                }
            }else{
                if(nextVal == '-' && currentVal!=')') {
                    negflag=true;
                }
                if(currentVal== '(')
                    opstack.push(currentVal);
                else if(currentVal == ')'){
                    char top =opstack.top();
                    opstack.pop();
                    while(top!= '('){
                        result<<top<<" ";
                        top=opstack.top();
                        opstack.pop();
                    }
                    if(flag){
                        result<<"* ";
                        flag=false;
                    }
                    if(nextVal=='('|| isdigit(nextVal))flag=true;
                }else{
                    if(currentVal!='c' && (!negflag || currentVal!='-')){
                        while(!opstack.empty() && (precLevel(opstack.top()) >= precLevel(currentVal))){
                            result<<opstack.top()<<" ";
                            opstack.pop();
                        }
                        opstack.push(currentVal);
                    }                
                }
                
            }
            current=current->next;
        }
        while(!opstack.empty()){
            result<<opstack.top()<<" ";
            opstack.pop();
        }
        return result.str();
    }
    public:
    Calculator(string expr){
        list= new LinkedList();
        list->convertStrToList(expr);
    }
    long strToLongMod(string bigNum){
        long result=0;
        for(int i=0;i<bigNum.length();i++){
            char el= bigNum.at(i);
            if(el!='-' && el!='+'){
                result=(result*10 + (int)el-(int)'0')% LIMIT;
            }
        }
        return result;

    }

    //calculating and hashing
    long evalPostfix(){
        int result;
        string postExpr= convertToPostfix();
        stringstream ss(postExpr);
        string tokenStr;
        if (savedEval.find(postExpr)==savedEval.end()){
            stack<string> operands;
            string operators="()*+-";
            while(ss>>tokenStr){
                if(operators.find(tokenStr)!=string::npos){
                    long op1=operands.top();
                    operands.pop();
                    long op2= operands.top();
                    operands.pop();
                    long result=0;
                    if(tokenStr=="+")result=(op1+op2)%LIMIT;
                    else if(tokenStr=="-")result=(op2-op1)%LIMIT;
                    else if(tokenStr=="*")result=(op1*op2)%LIMIT;
                    operands.push(strToLongMod());
                }else{
                    long token;
                    if(tokenStr.length()>=9)token=strToLongMod(tokenStr);
                    else token =stoi(tokenStr);
                    operands.push(token);
                }
            }
            result = operands.top();
            operands.pop();
            while(result<0)result+=LIMIT;
            savedEval[postExpr]=result%LIMIT;
        }else{
            result =savedEval.at(postExpr);
        }
        return result%LIMIT;
    }
    
    //move cursor to right
    void moveCurserToRight(){
        list->movecursorToRight();
    }
    //move cursor to the left
    void moveCurserToLeft(){
        list->movecursorToLeft();
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
    getline(cin>>ws,expression);
    // cin>>expression;

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
                cout<<cal.evalPostfix()<<endl;
                break;
            case '+':
                char toBeAdded= order.at(2);
                cal.addCharacter(toBeAdded);
        }
    }
}