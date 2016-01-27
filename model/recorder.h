#ifndef RECORDER
#define RECORDER
#include "../common/global.h"
extern short piece[48];
extern short board[100];
class Node
{
    friend class RecordStack;
private:
    Node * pre;
    Node * next;
    short chessStart;
    short chessEnd;
    int startPos; 
    int endPos;
public:
    Node(short startPos, int chessStart, short endPos, int chessEnd)
        :pre(NULL),next(NULL),startPos(startPos),endPos(endPos),chessStart(chessStart),chessEnd(chessEnd){}
    ~Node()
    {
        //delete next;
    }
};

class RecordStack
{
    friend class modelDirector;
private:
    int N;
    Node * head;
    Node * tail;
public:
    RecordStack():head(NULL),tail(NULL),N(0){}
    int size(){return N;}
    bool isEmpty(){return N==0;}
    void push(Node * node)
    {
        if(N == 0)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            node->pre = tail;
            tail = node;
        }
        N++;
    }
    short lastElementDetails()
    {
        if(N != 0)
        {
            return tail->startPos + tail->endPos*100;
        }
        else
        {
            return -1;
        }
    }

    void pop()
    {
        if(N != 0)
        {
            Node * temp;
            temp = tail;
            board[tail->startPos] = tail->chessStart;
            board[tail->endPos] = tail->chessEnd;
            piece[tail->chessStart] = tail->startPos;
            piece[tail->chessEnd] = tail->endPos;
            if(N > 1)
                tail = tail->pre;
            delete temp;
            N = N - 1;
        }
    }
    ~RecordStack()
    {
        while(N != 0)
        {
            pop();
        }
    }
    
};

//////////////////////////////////////////////////////////
#endif
