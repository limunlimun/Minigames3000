#ifndef CONSTANTSTANK_H_INCLUDED
#define CONSTANTSTANK_H_INCLUDED
#include<iostream>
#include"tankObject.h"
#include"ft/vector2D.h"
#include"obstacle.h"
#include<vector>

//NOTE TO SELF: STEP UP YOUR HEADER NAMING SKILLS, IT IS EMBARASSING HOW GENERIC THIS NAME IS.
void drawFrankie(HWND);
void updateFrankie();
void checkInput(int);
void runSetup(HWND);
void checkForObstacles();
void renderObstacle(HDC);
int i=0;
int j=0;
int init=0;
int shootingTime=50;
//RECT clientRect2;
int amInc=0;
bool moveForward=true;
void drawOilField(HDC);
void drawBackground(HDC);
int shooter=0;

BITMAP bmp2,scene,oil,rock,soldier,heart,flower,smile;
HBITMAP tankWhite=(HBITMAP)LoadImage(NULL,"tankWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP tankBlack=(HBITMAP)LoadImage(NULL,"tankBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP oilWhite=(HBITMAP)LoadImage(NULL,"oilRigWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP oilBlack=(HBITMAP)LoadImage(NULL,"oilRigBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP rockWhite=(HBITMAP)LoadImage(NULL,"rockWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP rockBlack=(HBITMAP)LoadImage(NULL,"rockBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP background=(HBITMAP)LoadImage(NULL,"land.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP soldierWhite=(HBITMAP)LoadImage(NULL,"soldierWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP soldierBlack=(HBITMAP)LoadImage(NULL,"soldierBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP heartWhite=(HBITMAP)LoadImage(NULL,"heartWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP heartBlack=(HBITMAP)LoadImage(NULL,"heartBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP flowerWhite=(HBITMAP)LoadImage(NULL,"flowerWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP flowerBlack=(HBITMAP)LoadImage(NULL,"flowerBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP rockSmileWhite=(HBITMAP)LoadImage(NULL,"rockSmileWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP rockSmileBlack=(HBITMAP)LoadImage(NULL,"rockSmileBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBRUSH br=(HBRUSH)GetStockObject(BLACK_BRUSH);
HBRUSH red=(HBRUSH)CreateSolidBrush(RGB(255,0,0));
int rigLocation=0;



#endif // CONSTANTSTANK_H_INCLUDED
