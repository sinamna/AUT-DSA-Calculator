#include <iostream>
#include <string>
#include "Node.h"
using namespace std;
//class based linked list
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
                nextNode->next->prev=cursor;
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