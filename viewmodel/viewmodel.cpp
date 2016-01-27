#include "viewmodel.h"

int ViewModel::PixelX=0;
int ViewModel::PixelY=0;
int ViewModel::chosenX=0;
int ViewModel::chosenY=0;
int ViewModel::StartOrEnd=0;
bool ViewModel::turns=true; //red
int ViewModel::startPos=0;
int ViewModel::endPos=0;
int ViewModel::chosenPos=0;
bool ViewModel::legal=false;
modelDirector* ViewModel::mD = new modelDirector(new playerHandler(16),new playerHandler(32),true);
ViewModel::ViewModel()
{

}
void ViewModel::ChosenMode(int stateChosen)
{
    delete mD;
    if(stateChosen==2)
        mD=new modelDirector(new playerHandler(16),new computerHandler(32),true);
    else
        mD=new modelDirector(new playerHandler(16),new playerHandler(32),true);
}

void ViewModel::Restart()
{
    PixelX=0;
    PixelY=0;
    chosenX=0;
    chosenY=0;
    StartOrEnd=0;
    turns=true;
    startPos=0;
    endPos=0;
    chosenPos=0;
    legal=false;
    mD->restart();
}

void ViewModel::ArrayToPixel(int i, int stateChosen, bool setSide)
{
    int code=piece[i];
    if(stateChosen==1&&!setSide)
    {
        code=98-code;
    }
    if(piece[i]==-1)
    {
        PixelY=-9999;
        PixelX=-9999;
    }
    else
    {
    int raw=code/10;
    int col=code%10;
    PixelY=10+raw*63;
    PixelX=40+col*63;
    }
}
void ViewModel::ChosenToPixel()
{
    int raw=chosenPos/10;
    int col=chosenPos%10;
    chosenY=10+raw*63;
    chosenX=40+col*63;
}

int ViewModel::GetPixelX()
{
    return PixelX;
}
int ViewModel::GetPixelY()
{
    return PixelY;
}

void ViewModel::PixelToArray(int x, int y, int stateChosen, bool enableFlag, bool setSide)
{
    int col,raw,code,ori;
    col=(x-40)/63;
    raw=(y-25)/63;
    code=raw*10+col;
    ori=code;
    if(stateChosen==1&&!setSide)
        code=98-code;
    if(StartOrEnd==0)
    {
        startPos=code;
        chosenPos=ori;
        if(board[code]>0)
            StartOrEnd++;
    }
    else
    {
        endPos=code;
        chosenPos=ori;
        if((stateChosen==2||enableFlag==true)&&mD->MovementsExectionDistributer(startPos,endPos,turns))
        {
            turns=!turns;
            legal=true;
            StartOrEnd--;
        }
        else
        {
            if(board[code]/32!=turns&&board[code]!=0)
            {
                startPos=code;
            }
            else
                StartOrEnd--;
            legal=false;
        }
    }
}

bool ViewModel::alarm()
{
    return mD->isStillInDanger(startPos,endPos,turns);
}
