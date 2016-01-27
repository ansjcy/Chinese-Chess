#include "model.h"
#include <vector>
#include <iostream>
#include <math.h>
#include "../../alg/alg.h"

using namespace std;
bool Handler::isInArray(int ways,const short array[], int size)
{
    for(int i = 0; i < size; i++)
        if(array[i] == ways)
            return true;
    return false;
}
bool Handler::canMove(int startPos, int endPos, bool flag)
{
    if(startPos < 0 || startPos > 99 || endPos < 0 || endPos > 99)
        return false;
    short chessCode = board[startPos];
    if(board[startPos] == 0)
    {
        return false;
    }
    else if((chessCode&tag) == tag                                      //Tag is 16 or 32
            && (chessCode&tag) != (board[endPos]&tag)                   //not same side
            && legalPos[chessCode][endPos]                              //The destination is reachable
            && isLegalMoveWays(chessCode, startPos, endPos)             //The way of movements is legal
            && isNotBlocked(chessCode, startPos, endPos)                //There is no blocks
            && (flag || !isStillInDanger(startPos, endPos))
           )
    {
        return true;
    }
    return false;
}



bool Handler::isStillInDanger(short startPos, short endPos)
{
    //in this function, the movements must be legal
    //whether the general is still in danger or not
    //will be checked here.
    bool flag = false;
    short genPos = piece[tag];
    short chess1, chess2;
    short tag1 = tag;
    short tag2 = tag == 16? 32: 16;
    bool isGen = false;
    chess1 = board[startPos];
    chess2 = board[endPos];
    board[startPos] = 0;
    board[endPos] = chess1;
    if(chess1 == tag)
    {
        isGen = true;
        genPos = endPos;
        piece[tag] = endPos;
    }
    tag = tag2;
    if(  piece[16]%10 == piece[32]%10)  //is Gen_red and Gen_black are face to face ?
    {
        flag = true;
        for(int i = 1; i < piece[16]/10 - piece[32]/10; i++)
        {
            if(board[i*10 + piece[32]] != 0)
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            tag = tag1;
            board[startPos] = chess1;
            board[endPos] = chess2;
            if(isGen) piece[tag1] = startPos;
            return true;
        }
        else
        {
            if(isGen) piece[tag1] = startPos;
            flag = false;
        }

    }

    for(int i = tag2; i < tag2 + 16; i++)
    {
        if(canMove(piece[i], genPos, true))
        {
            flag = true;
            break;
        }
    }
    tag = tag1;
    board[startPos] = chess1;
    board[endPos] = chess2;
    if(isGen) piece[tag] = startPos;
    return flag;
}

vector<mov>* Handler::allMoveWays()
{
    vector<mov>* moveWays = new vector<mov>();
    short startPos, endPos, capture;
    for(int i = tag; i < tag + 16; i++)
    {
        if(piece[i] != -1)
        {
            vector<short>* vec = searcher->getWays(i);
            vector<short>::iterator p;
            //cout << "chess:" << " " << i << endl;
            for(p = vec->begin(); p != vec->end(); p++)
            {
                startPos = piece[i];
                endPos = startPos + *p;
                if(canMove(startPos, endPos))
                {
                    capture = board[endPos];
                    //cout << "from: " << startPos << " to: " << endPos << " eat: " << capture << endl;
                    moveWays->push_back(*new mov(startPos, endPos, capture));
                }
            }
            delete vec;
        }
    }
    return moveWays;
}



bool Handler::isEnd()
{
    short pos1, pos2;
    for(int i = 0; i < 16; i++)
    {
        pos1 = piece[tag + i];
        vector<short>* vec = searcher->getWays(tag + i);
        vector<short>::iterator position;
        for(position = vec->begin(); position != vec->end(); position++)
        {
            pos2 = pos1 + *position;
            //cout << pos1 << " " << pos2 << endl;
            if(canMove(pos1, pos2))       //current plaer can move in this way
                return false;
        }
        delete vec;
    }
    return true;
}

bool Handler::isLegalMoveWays(short chessCode, int startPos, int endPos)
{
    int ways = endPos - startPos;
    switch(chessCode)
    {
        case GEN_BLACK:
        case GEN_RED:
            return isInArray(ways, genMov, 4);
        case SERVANT1_BLACK:
        case SERVANT2_BLACK:
        case SERVANT1_RED:
        case SERVANT2_RED:
            return isInArray(ways, servantMov, 4);
        case ADVISOR1_BLACK:
        case ADVISOR2_BLACK:
        case ADVISOR1_RED:
        case ADVISOR2_RED:
             return isInArray(ways, advisorMov, 4);
        case HORSE1_BLACK:
        case HORSE2_BLACK:
        case HORSE1_RED:
        case HORSE2_RED:
             return abs(endPos/10 - startPos/10) == 2
                     && abs(endPos%10 - startPos%10) == 1
                     || abs (endPos/10 - startPos/10) ==1
                     && abs(endPos%10 - startPos%10) == 2;
                     ///isInArray(ways, horseMov, 8);
        case CAR1_BLACK:
        case CAR2_BLACK:
        case CAR1_RED:
        case CAR2_RED:
            return endPos/10==startPos/10||startPos%10==endPos%10;//isInArray(ways, carMov, 34);
        case CANNON1_BLACK:
        case CANNON2_BLACK:
        case CANNON1_RED:
        case CANNON2_RED:
            return endPos/10==startPos/10||startPos%10==endPos%10;//isInArray(ways, cannonMov, 34);
        case SOLIDER1_BLACK:
        case SOLIDER2_BLACK:
        case SOLIDER3_BLACK:
        case SOLIDER4_BLACK:
        case SOLIDER5_BLACK:
            return isInArray(ways, soldierBlack, 3);
        case SOLIDER1_RED:
        case SOLIDER2_RED:
        case SOLIDER3_RED:
        case SOLIDER4_RED:
        case SOLIDER5_RED:
            return isInArray(ways, soldierRed, 3);
        default:
            return false;
    }
}

bool Handler::isNotBlocked(short chessCode, int startPos, int endPos)
{
    int ways = endPos - startPos;                       //it's similar to vector
    int sign = ways < 0? -1: 1;                         //sign
    switch(chessCode)
    {
        case GEN_BLACK:
        case GEN_RED:
            return true;
        case SERVANT1_BLACK:
        case SERVANT2_BLACK:
        case SERVANT1_RED:
        case SERVANT2_RED:
            return true;
        case ADVISOR1_BLACK:
        case ADVISOR2_BLACK:
        case ADVISOR1_RED:
        case ADVISOR2_RED:
            return board[startPos + ways/2] == 0;
        case HORSE1_BLACK:
        case HORSE2_BLACK:
        case HORSE1_RED:
        case HORSE2_RED:
        {
           // ways = ways < 0? -ways:ways;
            int x_val = endPos%10 - startPos%10;                            //as the gap between columns is 1
            int y_val = endPos/10 - startPos/10;                            //the gap between rows is 10
            //if(x_val < 0) x_val = - x_val;                  //be positive
            //if(y_val < 0) y_val = - y_val;                  //be positive
            if(y_val == 2 || y_val == -2)                               //if exist a chess in the front, then blocked
                return board[startPos + sign*10] == 0;
            else
                return board[startPos + x_val/2] == 0;
        }
        case CAR1_BLACK:
        case CAR2_BLACK:
        case CAR1_RED:
        case CAR2_RED:
        {
            if((startPos - endPos)/10 == 0)                             //just go somewhere in the row
            {
               for(int i = startPos + sign; i != endPos; i += sign)
                   if(board[i] != 0)
                        return false;
            }
            else
            {
                for(int i = startPos + sign*10; i != endPos; i = i + sign*10)
                    if(board[i] != 0)                                 // go somewhere in the column
                        return false;
            }
            return true;
        }
        case CANNON1_BLACK:
        case CANNON2_BLACK:
        case CANNON1_RED:
        case CANNON2_RED:
        {
            if(board[endPos] == 0)                                  //just go somewhere
            {
                if((startPos - endPos)/10 == 0)
                {
                    for(int i = startPos + sign; i != endPos; i += sign)
                        if(board[i] != 0)
                            return false;
                }
                else
                {
                    for(int i = startPos + sign*10; i != endPos; i = i + sign*10)
                        if(board[i] != 0)
                            return false;
                }
                return true;
            }
            else                                                    //attack the enemy, there should be
            {                                                       //only one chess in the way
                int count = 0;
                if((startPos - endPos)/10 == 0)
                {
                    for(int i = startPos + sign; i != endPos; i += sign)
                        if(board[i] != 0)
                            count++;
                }
                else
                {
                    for(int i = startPos + sign*10; i != endPos; i = i + sign*10)
                        if(board[i] != 0)
                            count++;
                }
                return count == 1;
            }
        }
        case SOLIDER1_BLACK:
        case SOLIDER2_BLACK:
        case SOLIDER3_BLACK:
        case SOLIDER4_BLACK:
        case SOLIDER5_BLACK:
        case SOLIDER1_RED:
        case SOLIDER2_RED:
        case SOLIDER3_RED:
        case SOLIDER4_RED:
        case SOLIDER5_RED:
            return true;
        default:
            return false;
    }
}


short modelDirector::getLastMove()
{
    return recorder->lastElementDetails();
}

modelDirector::~modelDirector()
{
    delete PlayerHandlerA;
    delete PlayerHandlerB;
    delete recorder;
}
bool modelDirector::isStillInDanger(short startPos , short endPos ,bool turns)
{
    if(turns == TURNS_OF_A)
        return  PlayerHandlerA->canMove(startPos, endPos, true) && PlayerHandlerA->isStillInDanger(startPos, endPos);
    else
        return  PlayerHandlerB->canMove(startPos, endPos, true) && PlayerHandlerB->isStillInDanger(startPos, endPos);
    
}
bool modelDirector::isEnd(bool turns)
{
    if(turns == true)
    {
        return PlayerHandlerA->isEnd();
    }
    else
    {
        return PlayerHandlerB->isEnd();
    }
}
void modelDirector::updatePiece(int sp, short sc, int ep, short ec)
{
    piece[sc] = ep;
    piece[ec] = -1;
}    
bool modelDirector::MovementsExectionDistributer(int startPos, int endPos, bool turns)
{
    short startChess = board[startPos];
    short endChess = board[endPos];
    if(turns == TURNS_OF_A)//turns of A, executed by PlayerA handler
    {
        if(PlayerHandlerA->executeInstruction(startPos, endPos))
        {
            startChess = board[startPos];
            endChess = board[endPos];
            board[startPos] = 0;
            board[endPos] = startChess;
            recorder->push(new Node(startPos, startChess, endPos, endChess));
            updatePiece(startPos, startChess, endPos, endChess);
            return true;
        }
        return false;
    }
    else
    {
        if(PlayerHandlerB->executeInstruction(startPos, endPos))
        {
            startChess = board[startPos];
            endChess = board[endPos];
            board[startPos] = 0;
            board[endPos] = startChess;
            recorder->push(new Node(startPos, startChess, endPos, endChess));
            updatePiece(startPos, startChess, endPos, endChess);
            return true;
        }
        return false;
    }
}
bool modelDirector::regret()
{
    if(!recorder->isEmpty())
    {
        recorder->pop();
        return true;
    }
    else
    {
        return false;
    }
    //if recorder is empty, pop is okay, it just do nothing.
}
void modelDirector::restart()
{
    while(!recorder->isEmpty())
    {
        recorder->pop();
    }
}
vector<mov>* modelDirector::allMoveWays(bool turns)
{
    if(turns == TURNS_OF_A)
        return PlayerHandlerA->allMoveWays();
    else
        return PlayerHandlerB->allMoveWays();
}

bool playerHandler::executeInstruction(int& startPos, int& endPos)
{
    if(canMove(startPos, endPos))
    {
       // board[endPos] = board[startPos];
       // board[startPos] = 0;
        return true;
    }
    return false;
}
bool computerHandler::executeInstruction(int& startPos, int& endPos)
{
    mov& pos = alg::compute();
    startPos = pos.from;
    endPos = pos.to;
    return true;
    //unfinshed, it will apply the algorithm here.
}
