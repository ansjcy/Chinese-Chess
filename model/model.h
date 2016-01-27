//
//  main.cpp
//  test
//
//  Created by Ah on 7/17/15.
//  Copyright (c) 2015 Ah. All rights reserved.
//


#ifndef MODEL
#define MODEL
#include "../common/global.h"
#include "recorder.h"
#include "moveable.h"
#include "node.h"
enum
{
    GEN_RED        = 16,
    SERVANT1_RED   = 17,
    SERVANT2_RED   = 18,
    ADVISOR1_RED   = 19,
    ADVISOR2_RED   = 20,
    HORSE1_RED     = 21,
    HORSE2_RED     = 22,
    CAR1_RED       = 23,
    CAR2_RED       = 24,
    CANNON1_RED    = 25,
    CANNON2_RED    = 26,
    SOLIDER1_RED   = 27,
    SOLIDER2_RED   = 28,
    SOLIDER3_RED   = 29,
    SOLIDER4_RED   = 30,
    SOLIDER5_RED   = 31,

    GEN_BLACK      = 32,
    SERVANT1_BLACK = 33,
    SERVANT2_BLACK = 34,
    ADVISOR1_BLACK = 35,
    ADVISOR2_BLACK = 36,
    HORSE1_BLACK   = 37,
    HORSE2_BLACK   = 38,
    CAR1_BLACK     = 39,
    CAR2_BLACK     = 40,
    CANNON1_BLACK  = 41,
    CANNON2_BLACK  = 42,
    SOLIDER1_BLACK = 43,
    SOLIDER2_BLACK = 44,
    SOLIDER3_BLACK = 45,
    SOLIDER4_BLACK = 46,
    SOLIDER5_BLACK = 47
};
extern short piece[48];
extern short board[100];
//extern short legalPos[48][100];
extern const short genMov[4];
extern const short servantMov[4];
extern const short advisorMov[4];
extern const short horseMov[8];
extern const short carMov[34];
extern const short cannonMov[34];
extern const short soldierBlack[3];
extern const short soldierRed[3];




/////////////////////////////////
class Handler
{
/**************************************************************
 *This class is a base class of Player or computer.           *
 *when you initial a handler (such as player or computer?),   *
 *you should initialize the tag, which is used when deciding  *
 *wheter your insrtucion is valid or not.                     *
 **************************************************************/
protected:
    short tag;
    moveWaysSearcher* searcher;
public:
    Handler(short tag):tag(tag),searcher(new moveWaysSearcher()){}
    virtual bool isInArray(int ways,const short array[], int size);
    virtual bool canMove(int startPos, int endPos, bool flag = false);
    virtual bool isLegalMoveWays(short chessCode, int startPos, int endPos);
    virtual bool isNotBlocked(short chessCode, int startPos, int endPos);
    virtual bool executeInstruction(int& startPos, int& endPos) = 0;
    virtual bool isEnd();
    virtual ~Handler() {delete searcher;};
    virtual std::vector<mov>* allMoveWays();
    virtual bool isStillInDanger(short startPos, short endPos);
};

///////////////////////////////////////////////



class modelDirector
{
/*************************************************
 *This class is the leader in this model,it will *
 *distribute the instruction to the handler      *
 *according to the current. example: 0-A 1-B.    *
 *Besides, when you initialize the object, you   *
 *should bind the handler and the event recorder.*
 *************************************************/
private:
    Handler* PlayerHandlerA;
    //Handler to exectue the instruction of player A
    Handler* PlayerHandlerB;
    //Handler to execute the instructon of player B
    RecordStack* recorder;

    
public:
    enum
    {
        TURNS_OF_A = true,
        TURNS_OF_B = false
    };
    modelDirector(Handler* PA, Handler* PB, int turns = TURNS_OF_A)
        :PlayerHandlerA(PA),PlayerHandlerB(PB), recorder(new RecordStack()){}
    ~modelDirector();
    void updatePiece(int sp, short sc, int ep, short ec);
    bool MovementsExectionDistributer(int startPos, int endPos, bool turns);
    bool regret();
    void restart();
    int getRecordSize(){return recorder->size();}
    virtual std::vector<mov>* allMoveWays(bool turns);
    bool isStillInDanger( short startPos , short endPos,bool turns);
    bool isEnd(bool turns);
    short getLastMove();
};


/////////////////////////////////////////////

class playerHandler:public Handler
{
public:
    playerHandler(short tag):Handler(tag){}
    virtual bool executeInstruction(int& startPos, int& endPos);
    ~playerHandler(){}
};

class computerHandler:public Handler
{
public:
    computerHandler(short tag):Handler(tag){}
    virtual bool executeInstruction(int& startPos, int& endPos);
};






#endif // MODEL

