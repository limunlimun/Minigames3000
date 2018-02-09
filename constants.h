#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

HBITMAP nemesisWhite=(HBITMAP)LoadImage(NULL,"nemesis1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP nemesisBlack=(HBITMAP)LoadImage(NULL,"nemesis1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP _ammoWhite=(HBITMAP)LoadImage(NULL,"laserBeamWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP _ammoBlack=(HBITMAP)LoadImage(NULL,"laserBeamBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP _nemAmmoBlack=(HBITMAP)LoadImage(NULL,"nemLasBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
HBITMAP _nemAmmoWhite=(HBITMAP)LoadImage(NULL,"nemLasWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
//HBITMAP background=(HBITMAP)LoadImage(NULL,"background1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
int correction=5;
BITMAP _ammoInfo;
BITMAP player;
BITMAP bmp;
BITMAP nemesisAmmo;
BITMAP back;

RECT clientRect;
int numNem=0;
int kills=0;
int nem=50;

void draw(HWND);
void runSetup();
void drawBackground(HDC hdc);
void drawHealthBar(HDC hdc);
void update();
void generateNewNemesii();
HBRUSH gr=CreateSolidBrush(RGB(0,255,0));

//BITNO ZA LEVEL UP
bool l1=true;
bool l2=true;
bool l3=true;
bool l4=true;


#endif // CONSTANTS_H_INCLUDED
