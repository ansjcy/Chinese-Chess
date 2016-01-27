#ifndef ALG_H
#define ALG_H
#include<iostream>
#include "../../model/node.h"
using namespace std;
class alg
{
private:
    static int getPosValue(short pieceNum);
    static int weightValue();
    static int search(short depth, int alpha, int beta);
    static int PVS(short depth, int alpha, int beta);
    static void makeMove(mov& mv);
    static void unMove(mov& mv);
public:
    static mov& compute();
};

#endif // ALG_H
