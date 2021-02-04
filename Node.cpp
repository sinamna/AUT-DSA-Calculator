#include<iostream>
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
