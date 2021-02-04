#include <iostream>
//class based linked list
class Node{
    public:
    int val;
    Node* next;
    Node* prev;
    Node(int inVal){
        val=inVal;
        next=NULL;
        prev=NULL;    }
};

class LinkedList{
    private:
        Node* head;
        Node* tail;
    //create Node
    Node* create_node(int val){
        Node* newNode= new Node(val);
        newNode->next=NULL;
        newNode->prev=NULL;
        return newNode;
    }
    public:
    //constructor
    LinkedList(){
        head=NULL;
        tail=NULL;
    }
    //size

    //insert_head
    void insert_head(int val){
        Node* newNode=create_node(val);
        if (head==NULL) head=tail=newNode;
        else{
            newNode->next=head;
            head=newNode;
        }
    }
    //remove_head

    //insert_tail
    void insert_tail(int val){
        Node* newNode=create_node(val);
        if (tail==NULL) head=tail=newNode;
        else{
            tail->next=newNode;
            tail=newNode;
        }
    }
    //remove_tail

    //insert

    //remove

    //convert string to linkedList
};