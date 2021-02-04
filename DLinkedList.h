#include<string>
using namespace std;
class Node{
    public:
    char val;
    Node* next;
    Node* prev;
    Node(char inVal);
};
class LinkedList{

    public:
    Node* tail;
    Node* head;
    LinkedList();
    void insert_head(char val);
    Node* remove_head();
    void insert_tail(char val);
    Node* remove_tail();
    void insert(Node* cursor,char val);
    Node* remove(Node* nodeToRemove);
    void convertStrToList(string str);
    void printList();
};