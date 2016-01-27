#ifndef GLOBAL_H
#define GLOBAL_H
#include <iostream>
#include "../../model/model.h"
void initialize();
using namespace std;
extern short piece[48];
extern short board[100];
extern const short pieceWeight[48];
extern const short legalPos[48][100];
extern const short genMov[4];
extern const short servantMov[4];
extern const short advisorMov[4];
extern const short advisorLeg[4];
extern const short horseMov[8];
extern const short horseLeg[8];
extern const short carMov[34];
extern const short cannonMov[34];
extern const short soldierRed[3];
extern const short soldierBlack[3];
//the value for chesses in each position
extern const short genValue[100];
extern const short servantValue[100];
extern const short advisorValue[100];
extern const short horseValueRed[100];
extern const short horseValueBlack[100];
extern const short carValueRed[100];
extern const short carValueBlack[100];
extern const short cannonValueRed[100];
extern const short cannonValueBlack[100];
extern const short soldierValueRed[100];
extern const short soldierValueBlack[100];



#endif // GLOBAL_H
