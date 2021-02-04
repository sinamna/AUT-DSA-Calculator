#include <iostream>
//class based linked list
class Node{
    public:
    char val;
    Node* next;
    Node* prev;
    Node(char inVal){
        val=inVal;
        next=NULL;
        prev=NULL;    }
};

class LinkedList{
    private:
        Node* head;
        Node* tail;
    //create Node
    Node* create_node(char val){
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
    void insert_head(char val){
        Node* newNode=create_node(val);
        if (head==NULL) head=tail=newNode;
        else{
            newNode->next=head;
            head=newNode;
        }
    }
    //remove_head
    Node* remove_head(){
        if(head==NULL) return NULL;
        if(head->next==NULL){
            Node* removedHead=head;
            head=NULL;
            return removedHead;
        }else{
            Node* removedHead=head;
            head=head->next;
            return removedHead;
        }
    }
    //insert_tail
    void insert_tail(char val){
        Node* newNode=create_node(val);
        if (tail==NULL) head=tail=newNode;
        else{
            tail->next=newNode;
            tail=newNode;
        }
    }
    //remove_tail
    Node* remove_tail(){
        if(tail==NULL)return NULL;
        Node* removedNode=tail;
        if(tail->prev==NULL){
            tail=NULL;
        }else{
            tail=tail->prev;
        }
        return removedNode;
    }

    //insert
    void insert(Node* cursor,char val){        
        if(cursor==head)insert_head(val);
        else if(cursor==tail)insert_tail(val);
        else{
            Node* newNode=create_node(val);
            cursor->prev->next=newNode;
            newNode->next=cursor;
        }
    }
    //remove

    //convert string to linkedList
};