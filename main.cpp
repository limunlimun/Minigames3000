#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include<sstream>
#include <fstream>

#include "resource.h"
#include "const.h"
#include "xox.h"
#include "memory.h"
#include "snake.h"
#include "simons.h"
#include "hangman.h"
#include "minesweeper.h"
#include "box.h"
#include "hilo.h"
#include "con4.h"
#include "bingo.h"
#include "paragon.h"
#include "frankTheLovingTank.h"
//#include "praviparagon.h"

void CheckInput(void);
//void Update(HWND);
void Render(HWND);
BOOL initializeStart(void);
void initialize(int,HWND);
int odrediIgru(int,int);

const int PAUZA = 20;
static HBITMAP hbmlogo,hbmpoc,hbmxox,hbmxoxmask,hbmbingologo,hbmbingologomask;
static HBITMAP hbmmemory,hbmmemorymask,hbmhilo,hbmhilomask;
static HBITMAP hbmspinv,hbmspinvmask,hbmboxlogo,hbmcon4;
static HBITMAP hbmsnlogo,hbmsimonlogo,hbmsimonlogomask;
static HBITMAP hbmhanglogo,hbmhanglogomask,hbmminelogo,hbmhelp;
static BITMAP bitmaplogo,bitmappoc,bitmapxox,bitmapmemory,bitmapspinv,bitmapsnlogo;
static BITMAP bitmapsimonlogo,bitmaphangmanlogo,bitmapminelogo,bitmapboxlogo;
static BITMAP bitmaphilo,bitmapcon4,bitmapbingologo,bitmaphelp;
static int zvuk=50;

static int xklik,yklik;//za odabir igrice na pocetnom ekranu
static int opcija;//za igricu, konstante definirati u const.h
static RECT crect;//za klijentsko podrucje

static HMENU hMenu;
void omoguciIgru(HMENU,BOOL);
void omoguciModove(HMENU,BOOL);
void omoguciTezinu(HMENU,BOOL);

void initializeHelp(){;}
void renderHelp(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);
    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBRUSH bijela=CreateSolidBrush(RGB(255,255,255));
    SelectObject(hdcBuffer,bijela);
    Rectangle(hdcBuffer,crect.left,crect.top,crect.right,crect.bottom);
    SelectObject(hdcBuffer,GetStockObject(BLACK_PEN));
    ifstream infile;
    string STRING;
	infile.open ("help.txt");
	int i=0;
        while(!infile.eof()) // To get you all the lines.
        {
	        getline(infile,STRING); // Saves the line in STRING.
	        TextOut(hdcBuffer,20,20+i*20,STRING.c_str(),STRING.length());
	        //cout<<STRING; // Prints our STRING.
	        ++i;
        }
	infile.close();
	BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
	DeleteObject(bijela);
	DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = "MENI";                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Minigames 3000"),       /* Title Text */
           WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           990,                 /* The programs width */
           650,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

     if(initializeStart())
    {
        while(TRUE)
        {
            DWORD vrijeme_pocetak;

            if(PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
            {
                if(messages.message == WM_QUIT)
                {
                    break;
                }
                TranslateMessage(&messages);
                DispatchMessage(&messages);
            }
            vrijeme_pocetak = GetTickCount();
//            CheckInput();
  //          Update(hwnd);
            if(opcija==SPACEINVADER){
                update();
            }else if(opcija==FRANKIE){
                updateFrankie();
            }
            Render(hwnd);
            while((GetTickCount() - vrijeme_pocetak) < PAUZA)
            {
                Sleep(PAUZA);
            }
        }
    }
    /* Run the message loop. It will run until GetMessage() returns 0 */
/*    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
/*        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
/*        DispatchMessage(&messages);
    }*/

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            {
                initializeStart();
                runSetup(hwnd);
                HINSTANCE hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
                HICON hIcon = LoadIcon (hInstance, MAKEINTRESOURCE (IDI_ICON1));
                SendMessage (hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

                hMenu=LoadMenu(hInstance,"MENI");
                SetMenu(hwnd,hMenu);
                omoguciIgru(hMenu,FALSE);
                omoguciModove(hMenu,FALSE);
                omoguciTezinu(hMenu,FALSE);
                break;
            }
            case WM_LBUTTONDOWN:
            {
                xklik=LOWORD(lParam);
                yklik=HIWORD(lParam);
                if(opcija==0){//klik na pocetnom screen-u
                        opcija=odrediIgru(xklik,yklik);
                        initialize(opcija,hwnd);
                }else if(opcija==XOX){
                    polje=pronadjiPolje(xklik,yklik);
                    int pobjednik=provjeriIgru();
                    if(pobjednik==1)
                        MessageBoxA(NULL,"Pobjednik je X","Zavrsena igra",MB_OK);
                    else if(pobjednik==2)
                        MessageBoxA(NULL,"Pobjednik je O","Zavrsena igra",MB_OK);
                    else if(potezi.size()==9)
                        MessageBoxA(NULL,"Nerijeseno!","Zavrsena igra",MB_OK);

                }else if(opcija==MEMORY){
                    if(pobjeda) break;
                    if(drugiklik){
                        zatvoriPolja();
                    }
                    otvoriPolje(xklik,yklik);
                }else if(opcija==SIMONS){
                    dodajKlik(xklik,yklik);
                }else if(opcija==MINE){
                    otvoriPoljeMine(xklik,yklik,1);
                }else if(opcija==BOX){
                    if(pogodikutiju) provjeriKlik(hwnd,xklik,yklik);
                }else if(opcija==HILO){
                    if(!vecamanja(xklik,yklik)){
                        tacno=false;
                        string rez=std::to_string(pogodaka);
                        string scr=std::to_string(ukupanscore);
                        string t="Pogodili ste: "+rez+" puta! ("+scr+" poena)";
                        MessageBox(hwnd,t.c_str(),"Gotova igra",MB_OK);
                    }
                }else if(opcija==CON4){
                    if(player1) odigrajPotez(hwnd,xklik,yklik,1);
                    else odigrajPotez(hwnd,xklik,yklik,2);
                }else if(opcija==BINGO){
                    if(zapocni) break;
                    else odaberiBroj(xklik,yklik);
                }
                break;
            }
            case WM_COMMAND:
            {
                if(LOWORD(wParam)==VRATINAZAD) {opcija=0;zvuk=1;}
                else if(opcija==XOX){
                    if(LOWORD(wParam)==RESET) resetujXOX();
                    else if(LOWORD(wParam)==SINGLE){
                        resetujXOX();
                        singlePlayer=TRUE;
                        twoPlayer=FALSE;
                        kompjuter=TRUE;
                    }else if(LOWORD(wParam)==VERSUS){
                        resetujXOX();
                        singlePlayer=FALSE;
                        twoPlayer=TRUE;
                        kompjuter=FALSE;
                    }
                }else if(opcija==MEMORY){
                        if(LOWORD(wParam)==LAGANO) {easy=TRUE;middle=FALSE;hard=FALSE;initializeMemory();}
                        else if(LOWORD(wParam)==SREDNJE) {easy=FALSE;middle=TRUE;hard=FALSE;initializeMemory();}
                        else if(LOWORD(wParam)==TESKO) {easy=FALSE;middle=FALSE;hard=TRUE;initializeMemory();}
                        else if(LOWORD(wParam)==RESET) {initializeMemory();}
                }else if(opcija==SNAKE){
                        if(LOWORD(wParam)==LAGANO){tezinaSnake=0;initializeSnake();}
                        else if(LOWORD(wParam)==SREDNJE){tezinaSnake=1;initializeSnake();}
                        else if(LOWORD(wParam)==TESKO){tezinaSnake=2;initializeSnake();}
                        else if(LOWORD(wParam)==RESET){initializeSnake();}
                }else if(opcija==MINE){
                    if(LOWORD(wParam)==RESET){initializeMine();}
                }else if(opcija==HANGMAN){
                    if(LOWORD(wParam)==LAGANO){tezinaHang=0;initializeHangman();}
                    else if(LOWORD(wParam)==SREDNJE){tezinaHang=1;initializeHangman();}
                    else if(LOWORD(wParam)==TESKO){tezinaHang=2;initializeHangman();}
                    else if(LOWORD(wParam)==RESET){initializeHangman();}
                }else if(opcija==SIMONS){
                    if(LOWORD(wParam)==RESET){initializeSimon(hwnd);}
                }else if(opcija==BOX){
                    if(LOWORD(wParam)==LAGANO){level=0;initializeBox();}
                    else if(LOWORD(wParam)==SREDNJE){level=1;initializeBox();}
                    else if(LOWORD(wParam)==TESKO){level=2;initializeBox();}
                    else if(LOWORD(wParam)==RESET){initializeBox();}
                }else if(opcija==HILO){
                    if(LOWORD(wParam)==RESET){initializeHilo();}
                }else if(opcija==CON4){
                    if(LOWORD(wParam)==RESET){initializeCon4();}
                }else if(opcija==BINGO){
                    if(LOWORD(wParam)==RESET){initializeBingo();}
                }
                break;
            }
            case WM_RBUTTONDOWN:
            {
                xklik=LOWORD(lParam);
                yklik=HIWORD(lParam);
                if(opcija==MINE){
                    otvoriPoljeMine(xklik,yklik,2);
                }
                break;
            }
            case WM_KEYDOWN:
            {
                if(opcija==SPACEINVADER){
                    play.checkInput(wParam);
                    break;
                }else if(opcija==FRANKIE){
                    checkInput(wParam);
                    break;
                }
                switch(wParam)
                {
                    case VK_RIGHT:
                    {
                        if(opcija==SNAKE){
                            if(tezinaSnake>=1 && glave.at(0).smjer==LIJEVO) break;
                            glave.at(0).sljsmjer=DESNO;
                        }
                        break;
                    }
                case VK_LEFT:
                    {
                        if(opcija==SNAKE){
                            if(tezinaSnake>=1 && glave.at(0).smjer==DESNO) break;
                            glave.at(0).sljsmjer=LIJEVO;
                        }
                        break;
                    }
                case VK_UP:
                    {
                        if(opcija==SNAKE){
                            if(tezinaSnake>=1 && glave.at(0).smjer==DOLE) break;
                            glave.at(0).sljsmjer=GORE;
                        }
                        break;
                    }
                case VK_DOWN:
                    {
                        if(opcija==SNAKE){
                            if(tezinaSnake>=1 && glave.at(0).smjer==GORE) break;
                            glave.at(0).sljsmjer=DOLE;
                        }
                        break;
                    }
                }
            break;
            }
        case WM_CHAR:
            {
                if(opcija==HANGMAN)
                    provjeriSlovo(wParam);
                break;
            }
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

BOOL initializeStart(){
    srand((int) time(0));

    hbmpoc=(HBITMAP) LoadImage(NULL,"pocetna.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmpoc,sizeof(BITMAP),&bitmappoc);

    hbmlogo=(HBITMAP) LoadImage(NULL,"hblogo.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmlogo,sizeof(BITMAP),&bitmaplogo);

    hbmxox=(HBITMAP) LoadImage(NULL,"xoxblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmxox,sizeof(BITMAP),&bitmapxox);
    hbmxoxmask=(HBITMAP) LoadImage(NULL,"xox.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmmemory=(HBITMAP) LoadImage(NULL,"memoryblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmmemory,sizeof(BITMAP),&bitmapmemory);
    hbmmemorymask=(HBITMAP) LoadImage(NULL,"memory.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmspinv=(HBITMAP) LoadImage(NULL,"spinvblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmspinv,sizeof(BITMAP),&bitmapspinv);
    hbmspinvmask=(HBITMAP) LoadImage(NULL,"spinv.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmsnlogo=(HBITMAP) LoadImage(NULL,"snakelogo.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmsnlogo,sizeof(BITMAP),&bitmapsnlogo);

    hbmsimonlogo=(HBITMAP) LoadImage(NULL,"simonsayslogoblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmsimonlogo,sizeof(BITMAP),&bitmapsimonlogo);
    hbmsimonlogomask=(HBITMAP) LoadImage(NULL,"simonsayslogo.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmhanglogo=(HBITMAP) LoadImage(NULL,"hanglogoblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmhanglogo,sizeof(BITMAP),&bitmaphangmanlogo);
    hbmhanglogomask=(HBITMAP) LoadImage(NULL,"hanglogo.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmminelogo=(HBITMAP) LoadImage(NULL,"minelogo.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmminelogo,sizeof(BITMAP),&bitmapminelogo);

    hbmboxlogo=(HBITMAP) LoadImage(NULL,"boxlogo.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmboxlogo,sizeof(BITMAP),&bitmapboxlogo);

    hbmhilo=(HBITMAP) LoadImage(NULL,"hilologoblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmhilo,sizeof(BITMAP),&bitmaphilo);
    hbmhilomask=(HBITMAP) LoadImage(NULL,"hilologo.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmcon4=(HBITMAP) LoadImage(NULL,"con4.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmcon4,sizeof(BITMAP),&bitmapcon4);

    hbmbingologo=(HBITMAP) LoadImage(NULL,"bingologoblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmbingologo,sizeof(BITMAP),&bitmapbingologo);
    hbmbingologomask=(HBITMAP) LoadImage(NULL,"bingologo.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmhelp=(HBITMAP) LoadImage(NULL,"helpabout.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmhelp,sizeof(BITMAP),&bitmaphelp);
    return true;
}

void initialize(int o,HWND hwnd){
    if(o==0){
        initializeStart();
    }else if(o==XOX){
        initializeXOX();
    }else if(o==MEMORY){
        initializeMemory();
    }else if(o==SPACEINVADER){
        runSetup(hwnd);
    }else if(o==SNAKE){
        initializeSnake();
    }else if(o==SIMONS){
        initializeSimon(hwnd);
    }else if(o==HANGMAN){
        initializeHangman();
    }else if(o==MINE){
        initializeMine();
    }else if(o==BOX){
        initializeBox();
    }else if(o==HILO){
        initializeHilo();
    }else if(o==CON4){
        initializeCon4();
    }else if(o==BINGO){
        initializeBingo();
    }else if(o==HELP){
        initializeHelp();
    }else if(o==FRANKIE){
        runSetupFrankie(hwnd);
    }
}

int odrediIgru(int x,int y){
    if(x>=100 && x<100+bitmapxox.bmWidth && y>=400 && y<400+bitmapxox.bmHeight){
            omoguciIgru(hMenu,TRUE);
            omoguciModove(hMenu,TRUE);
            omoguciTezinu(hMenu,FALSE);
            return XOX;
    }
    if(x>=220 && x<220+bitmapmemory.bmWidth && y>=400 && y<400+bitmapmemory.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,TRUE);
        omoguciModove(hMenu,FALSE);
        return MEMORY;
    }
    if(x>=330 && x<330+bitmapspinv.bmWidth && y>=400 && y<400+bitmapspinv.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,TRUE);
        return SPACEINVADER;
    }
    if(x>=500 && x<500+bitmapsnlogo.bmWidth && y>=400 & y<400+bitmapsnlogo.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,TRUE);
        omoguciModove(hMenu,FALSE);
        return SNAKE;
    }
    if(x>=620 && x<620+bitmapsimonlogo.bmWidth && y>=400 && y<400+bitmapsimonlogo.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,TRUE);
        omoguciModove(hMenu,FALSE);
        return SIMONS;
    }

    if(x>=770 && x<770+bitmaphangmanlogo.bmWidth && y>=400 && y<400+bitmaphangmanlogo.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,TRUE);
        omoguciModove(hMenu,FALSE);
        return HANGMAN;
    }
    if(x>=100 && x<100+bitmapminelogo.bmWidth && y>=500 && y<500+bitmapminelogo.bmHeight){
            omoguciIgru(hMenu,TRUE);
            omoguciTezinu(hMenu,TRUE);
            omoguciModove(hMenu,FALSE);
            return MINE;
    }
     if(x>=220 && x<220+bitmapboxlogo.bmWidth && y>=500 && y<500+bitmapboxlogo.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,TRUE);
        omoguciModove(hMenu,FALSE);
        return BOX;
    }
    if(x>=330 && x<330+bitmaphilo.bmWidth && y>=500 && y<500+bitmaphilo.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,FALSE);
        omoguciModove(hMenu,FALSE);
        return HILO;
    }
    if(x>=480 && x<480+bitmapbingologo.bmWidth && y>=500 && y<500+bitmapbingologo.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,FALSE);
        omoguciModove(hMenu,FALSE);
        return BINGO;
    }
    if(x>=620 && x<620+bitmapcon4.bmWidth && y>=500 & y<500+bitmapcon4.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,FALSE);
        omoguciModove(hMenu,FALSE);
        return CON4;
    }
    if(x>=770 && x<770+bitmaphelp.bmWidth && y>=500 && y<500+bitmaphelp.bmHeight){
        omoguciIgru(hMenu,TRUE);
        omoguciTezinu(hMenu,FALSE);
        omoguciModove(hMenu,FALSE);
        return HELP;
    }
    omoguciIgru(hMenu,TRUE);
    omoguciTezinu(hMenu,FALSE);
    omoguciModove(hMenu,FALSE);
    return FRANKIE;

}
int mojint=50;
void Render(HWND hwnd){
    if(opcija==XOX){
        renderXOX(hwnd);
        return;
    }else if(opcija==MEMORY){
        renderMemory(hwnd);
        return;
    }else if(opcija==SPACEINVADER){
//        renderSpaceInvader(hwnd);
//        start_time = GetTickCount();
  //   	update();
     	drawParagon(hwnd);
     //	DWORD frame_time = GetTickCount() - start_time;
       // if(frame_time < _frameDelay){
         //   Sleep(_frameDelay - frame_time);
           // nem--;
    //    }
//        if(nem==0){
  //          generateNewNemesii();
          //  nem=50;
        //}
        return;
    }else if(opcija==SNAKE){
        renderSnake(hwnd);
        return;
    }else if(opcija==SIMONS){
        renderSimon(hwnd);
        return;
    }else if(opcija==HANGMAN){
        renderHangman(hwnd);
        return;
    }else if(opcija==MINE){
        renderMine(hwnd);
        return;
    }else if(opcija==BOX){
        renderBox(hwnd);
        return;
    }else if(opcija==HILO){
        renderHilo(hwnd);
        return;
    }else if(opcija==CON4){
        renderCon4(hwnd);
        return;
    }else if(opcija==BINGO){
        renderBingo(hwnd);
        return;
    }else if(opcija==HELP){
        renderHelp(hwnd);
        return;
    }else if(opcija==FRANKIE){
        drawFrankie(hwnd);
        return;
    }
    //PlaySound("sound.wav",NULL,SND_LOOP|SND_LOOP);

    RECT crect;
    GetClientRect(hwnd, &crect);

    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;
    if(mojint>0){//logo
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmlogo);
        BitBlt(hdcBuffer,0,0,bitmaplogo.bmWidth,bitmaplogo.bmHeight,hdcMem,0,0,SRCCOPY);
        mojint--;
    }else if(opcija==0){//pocetni
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmpoc);
        BitBlt(hdcBuffer,0,0,bitmappoc.bmWidth,bitmappoc.bmHeight,hdcMem,0,0,SRCCOPY);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmxoxmask);
        BitBlt(hdcBuffer, 100,400,bitmapxox.bmWidth,bitmapxox.bmHeight, hdcMem, 0,0, SRCAND);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmxox);
        BitBlt(hdcBuffer, 100,400,bitmapxox.bmWidth,bitmapxox.bmHeight, hdcMem, 0,0, SRCPAINT);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmmemorymask);
        BitBlt(hdcBuffer, 220,400,bitmapmemory.bmWidth,bitmapmemory.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmmemory);
        BitBlt(hdcBuffer, 220,400,bitmapmemory.bmWidth,bitmapmemory.bmHeight, hdcMem, 0,0, SRCPAINT);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmspinvmask);
        BitBlt(hdcBuffer, 330,400,bitmapspinv.bmWidth,bitmapspinv.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmspinv);
        BitBlt(hdcBuffer, 330,400,bitmapspinv.bmWidth,bitmapspinv.bmHeight, hdcMem, 0,0, SRCPAINT);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmsnlogo);
        BitBlt(hdcBuffer,500,400,bitmapsnlogo.bmWidth,bitmapsnlogo.bmHeight,hdcMem,0,0,SRCCOPY);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmsimonlogomask);
        BitBlt(hdcBuffer, 620,400,bitmapsimonlogo.bmWidth,bitmapsimonlogo.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmsimonlogo);
        BitBlt(hdcBuffer, 620,400,bitmapsimonlogo.bmWidth,bitmapsimonlogo.bmHeight, hdcMem, 0,0, SRCPAINT);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmhanglogomask);
        BitBlt(hdcBuffer, 770,400,bitmapsimonlogo.bmWidth,bitmaphangmanlogo.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmhanglogo);
        BitBlt(hdcBuffer, 770,400,bitmapsimonlogo.bmWidth,bitmaphangmanlogo.bmHeight, hdcMem, 0,0, SRCPAINT);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmminelogo);
        BitBlt(hdcBuffer,100,500,bitmapminelogo.bmWidth,bitmapminelogo.bmHeight,hdcMem,0,0,SRCCOPY);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmboxlogo);
        BitBlt(hdcBuffer,220,500,bitmapboxlogo.bmWidth,bitmapboxlogo.bmHeight,hdcMem,0,0,SRCCOPY);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmhilomask);
        BitBlt(hdcBuffer, 330,500,bitmaphilo.bmWidth,bitmaphilo.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmhilo);
        BitBlt(hdcBuffer, 330,500,bitmaphilo.bmWidth,bitmaphilo.bmHeight, hdcMem, 0,0, SRCPAINT);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmbingologomask);
        BitBlt(hdcBuffer, 480,500,bitmapbingologo.bmWidth,bitmapbingologo.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmbingologo);
        BitBlt(hdcBuffer, 480,500,bitmapbingologo.bmWidth,bitmapbingologo.bmHeight, hdcMem, 0,0, SRCPAINT);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmcon4);
        BitBlt(hdcBuffer,620,500,bitmapcon4.bmWidth,bitmapcon4.bmHeight,hdcMem,0,0,SRCCOPY);

        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmhelp);
        BitBlt(hdcBuffer,770,500,bitmaphelp.bmWidth,bitmaphelp.bmHeight,hdcMem,0,0,SRCCOPY);
    }

    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
    if(zvuk>0){
            PlaySound("sound.wav",NULL,SND_LOOP|SND_LOOP);
            //mciSendString("sound.wav",NULL,0,NULL);
            zvuk=0;
    }
}

void omoguciTezinu(HMENU hmenu,BOOL on){
    if(on){
        EnableMenuItem(hmenu,LAGANO,MF_ENABLED);
        EnableMenuItem(hmenu,SREDNJE,MF_ENABLED);
        EnableMenuItem(hmenu,TESKO,MF_ENABLED);
    }
    else{
        EnableMenuItem(hmenu,LAGANO,MF_DISABLED|MF_GRAYED);
        EnableMenuItem(hmenu,SREDNJE,MF_DISABLED|MF_GRAYED);
        EnableMenuItem(hmenu,TESKO,MF_DISABLED|MF_GRAYED);
    }
}

void omoguciModove(HMENU hmenu,BOOL on){
    if(on){
        EnableMenuItem(hmenu,SINGLE,MF_ENABLED);
        EnableMenuItem(hmenu,VERSUS,MF_ENABLED);
    }
    else {
        EnableMenuItem(hmenu,SINGLE,MF_DISABLED|MF_GRAYED);
        EnableMenuItem(hmenu,VERSUS,MF_DISABLED|MF_GRAYED);
    }
}

void omoguciIgru(HMENU hmenu,BOOL on){
    if(on){
        EnableMenuItem(hmenu,RESET,MF_ENABLED);
        EnableMenuItem(hmenu,VRATINAZAD,MF_ENABLED);
    }
    else {
    EnableMenuItem(hmenu,RESET,MF_DISABLED|MF_GRAYED);
    EnableMenuItem(hmenu,VRATINAZAD,MF_DISABLED|MF_GRAYED);
    }
}
