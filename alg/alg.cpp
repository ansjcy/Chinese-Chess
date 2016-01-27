#include <algorithm>
#include "alg.h"
#include "../../model/model.h"
#include "../../common/global.h"
#include "../../viewmodel/viewmodel.h"
const int maxValue = 20000;
short maxDepth;
mov bestMove(0,0,0);
int value;

mov& alg::compute(){
    maxDepth = 4;   //4
    if(10<ViewModel::mD->getRecordSize()&&ViewModel::mD->getRecordSize()<=50)
        maxDepth = 5; //4
    if(ViewModel::mD->getRecordSize() > 50)
        maxDepth = 5;  //5
    value = PVS(maxDepth, -maxValue, maxValue);
    return bestMove;
}
int alg::getPosValue(short pieceNum){
    short pos = piece[pieceNum];

/*****the number for piece******
red:    gen-16 servant-17,18
        advisor-19,20 horse:21,22
        car-23,24 cannon-25,26
        soldier-27,28,29,30,31
 black: gen-32 servant-33,34
        advisor-35,36 horse:37,38
        car-39,40 cannon-41,42
        soldier-43,44,45,46,47
 *******************************/
    switch (pieceNum) {
        case 0:
            return 0;
        case 16:
        case 32:
            return genValue[pos];
        case 17:
        case 18:
        case 33:
        case 34:
            return servantValue[pos];
        case 19:
        case 20:
        case 35:
        case 36:
            return advisorValue[pos];
        case 21:
        case 22:
            return horseValueRed[pos];
        case 37:
        case 38:
            return horseValueBlack[pos];
        case 23:
        case 24:
            return carValueRed[pos];
        case 39:
        case 40:
            return carValueBlack[pos];
        case 25:
        case 26:
            return cannonValueRed[pos];
        case 41:
        case 42:
            return cannonValueBlack[pos];
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
            return soldierValueRed[pos];
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
            return soldierValueBlack[pos];
        default:
            return 0;
    }
}
int alg::weightValue(){
    short i = 0;
    int redValue = 0, blackValue = 0;
    for(i = 0; i < 16; i++){
        short red = i + 16;
        short black = i + 32;
        if(piece[red] != -1){
            redValue += pieceWeight[red] + getPosValue(red);
        }                               //no piece = -1????
        if (piece[black]) {
            blackValue += pieceWeight[black] + getPosValue(black);
        }
    }
    if (ViewModel::turns) {                    //side = 0, red turn??
        return (redValue - blackValue);
    }
    return (blackValue - redValue);
}
int alg::search(short depth, int alpha, int beta){
    int value;
    vector<mov> *tmp;
    vector<mov>moveArray;
    if(depth == 0)
        return weightValue();

    tmp = ViewModel::mD->allMoveWays(ViewModel::turns);
    moveArray = *tmp;
    sort(moveArray.begin(),moveArray.end(),greater<mov>());

    if(moveArray.size() == 0)
        return -maxValue;
    for(short i = 0; i < moveArray.size(); i++){
        makeMove(moveArray[i]);
        value = -search(depth-1, -beta, -alpha);
        unMove(moveArray[i]);
        if(value >= beta)
            return beta;
        if(value > alpha)
            alpha = value;
    }
    delete tmp;
    return alpha;
}

int alg::PVS(short depth, int alpha, int beta){
    int value = 0;
    vector<mov> *tmp;
    vector<mov> MoveArray;
    bool flag = false;

    if(depth == 0)
        return weightValue();

    tmp = ViewModel::mD->allMoveWays(ViewModel::turns);
    MoveArray = *tmp;
    sort(MoveArray.begin(),MoveArray.end(),greater<mov>());

    if(MoveArray.size() == 0)
        return -maxValue;
    bestMove = MoveArray[0];
    for(short i = 0; i < MoveArray.size(); i++){
        mov mv = MoveArray[i];
        makeMove(mv);
        if(flag){
            value = -search(depth-1, -alpha-1, -alpha);
            if(value > alpha && value < beta)
                value = -search(depth-1, -beta, -alpha);
        }
        else{
            value = -search(depth-1, -beta, -alpha);
        }
        unMove(mv);
        if(value >= beta){
            if(beta == maxValue){
                bestMove = mv;
            }
            return value;
        }
        if(value > alpha){
            alpha = value;
            flag = true;
            if(depth == maxDepth)
                bestMove = mv;
        }
    }
    delete tmp;
    return value;
}
void alg::makeMove(mov& mv){
    short from = mv.from;
    short to = mv.to;
    short capture = mv.capture;
    piece[board[from]] = to;
    piece[capture] = 0;
    board[to] = board[from];
    board[from] = 0;
    ViewModel::turns = !ViewModel::turns;
}
void alg::unMove(mov& mv){
    short from = mv.from;
    short to = mv.to;
    short capture = mv.capture;
    board[from]=board[to];
    board[to]=capture;
    piece[capture]=to;
    piece[board[from]]=from;
    ViewModel::turns = !ViewModel::turns;
}




