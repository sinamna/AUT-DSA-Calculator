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
    void insert(Node* cursor,char val){        
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
    Node* remove(Node* nodeToRemove){
        if(nodeToRemove==head)return remove_head();
        if(nodeToRemove==tail)return remove_tail();
        nodeToRemove->prev->next=nodeToRemove->next;
        nodeToRemove->next->prev=nodeToRemove->prev;
        return nodeToRemove;
    }
    //convert string to linkedList
};