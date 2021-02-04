#include<string>
#include "Node.h"
using namespace std;
class LinkedList{
    public:
    Node* tail;
    Node* head;
    Node* cursor;
    LinkedList();
    void insert_head(char val);
    Node* remove_head();
    void insert_tail(char val);
    Node* remove_tail();
    void insert(Node* cursor,char val);
    Node* remove(Node* nodeToRemove);
    void convertStrToList(string str);
    void printList();
    void moveCursorToLeft();
    void moveCursorToRight();
};