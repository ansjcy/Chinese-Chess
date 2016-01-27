#ifndef MOVEABLE
#define MOVEABLE
#include <vector>
#include <../../common/global.h>
#include "model.h"
using namespace std;
extern const short genMov[4];
extern const short servantMov[4];
extern const short advisorMov[4];
extern const short horseMov[8];
extern const short carMov[34];
extern const short cannonMov[34];
extern const short soldierRed[3];
extern const short soldierBlack[3];
class moveWaysSearcher
{
private:
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
public:
    void arrayToVector(const short array[], vector<short>& vec, int size)
    {
        for(int i = 0; i < size; i++)
            vec.push_back(array[i]);
    }

    vector<short>* getWays(short chessCode)
    {
        vector<short>* vec = new vector<short>;
        switch(chessCode)
        {
            case GEN_BLACK:
            case GEN_RED:
                arrayToVector(genMov, *vec, 4);
                return vec;
            case SERVANT1_BLACK:
            case SERVANT2_BLACK:
            case SERVANT1_RED:
            case SERVANT2_RED:
                arrayToVector(servantMov, *vec, 4);
                return vec;
            case ADVISOR1_BLACK:
            case ADVISOR2_BLACK:
            case ADVISOR1_RED:
            case ADVISOR2_RED:
                 arrayToVector(advisorMov, *vec, 4);
                 return vec;
            case HORSE1_BLACK:
            case HORSE2_BLACK:
            case HORSE1_RED:
            case HORSE2_RED:
                 arrayToVector( horseMov, *vec, 8);
                 return vec;
            case CAR1_BLACK:
            case CAR2_BLACK:
            case CAR1_RED:
            case CAR2_RED:
                arrayToVector( carMov, *vec, 34);
                return vec;
            case CANNON1_BLACK:
            case CANNON2_BLACK:
            case CANNON1_RED:
            case CANNON2_RED:
                arrayToVector( cannonMov, *vec, 34);
                return vec;
            case SOLIDER1_BLACK:
            case SOLIDER2_BLACK:
            case SOLIDER3_BLACK:
            case SOLIDER4_BLACK:
            case SOLIDER5_BLACK:
                arrayToVector( soldierBlack, *vec, 3);
                return vec;
            case SOLIDER1_RED:
            case SOLIDER2_RED:
            case SOLIDER3_RED:
            case SOLIDER4_RED:
            case SOLIDER5_RED:
                arrayToVector( soldierRed, *vec, 3);
                return vec;
            default:
                return vec;
        }
    }
};

#endif // MOVEABLE

