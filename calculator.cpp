#include <iostream>
#include <string>
#include "DLinkedList.h"
#include "Node.h"
using namespace std;

class Calculator{
    private:
        LinkedList* list;
        //unordered_map for hashing
        string expr;

    public:

    Calculator(string expr){
        list= new LinkedList();
        this->expr=expr;
    }
    //hashing 

    //calculating 

    //converting infix to postfix
    
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