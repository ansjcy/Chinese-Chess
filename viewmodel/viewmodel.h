#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "../../common/global.h"
#include "../../model/model.h"
#include <QMessageBox>

class ViewModel
{
public:
    ViewModel();

    static void ArrayToPixel(int i,int stateChosen,bool setSide);
    static void PixelToArray(int x,int y,int stateChosen,bool enableFlag,bool setSide);
    static void ChosenToPixel();
    static void ChosenMode(int stateChosen);
    static void Restart();
    static int GetPixelX();
    static int GetPixelY();
    static int chosenX;
    static int chosenY;
    static bool legal;
    static int startPos;
    static int endPos;
    static bool turns;
	static bool alarm();
    static int StartOrEnd;
    static modelDirector* mD;
private:
    static int chosenPos;
    static int PixelX;
    static int PixelY;
};

#endif // VIEWMODEL_H
