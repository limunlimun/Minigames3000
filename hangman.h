#include "gdiplus.h"

static HBITMAP hbmhangvic,hbmhanglose;
static BITMAP bitmaphangvic,bitmaphanglose;

static int greska=0;
static int tezinaHang=0;
static string rijeci[]={"METOD","KOD","ERROR","KLASA","MOTOR","HANDLE","THREAD","KAFA","LAMPA","MIS",
                        "ENERGIJA","WINDOWS","NESANICA","TASTATURA","FIREWALL","DIZAJNER","DIPLOMAT","KOMPAJLER","PROFESOR","RAČUNAR",
                        "APLAUDIRATI","ARHITEKTURA","KONDENZATOR","KREATIVNOST","EKSPERIMENT","INSTRUKCIJA","INVESTICIJA","LABORATORIJ","ENKAPSULACIJA","PROGRAMIRANJE"
};
static bool victoryHang=false;
static bool hanged=false;
int indeks;


class Slovo{
public:
    int ind;
    char karakter;
    bool pog;
    Slovo();
    Slovo(int a,char b){
        ind=a;karakter=b;
    }
};

static vector<Slovo> pogodjeni;
void NacrtajSlovo(HDC);
void NacrtajCrtice(HDC);

void initializeHangman(){
    hbmhanglose=(HBITMAP) LoadImage(NULL,"hanglose.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmhanglose,sizeof(BITMAP),&bitmaphanglose);
    hbmhangvic=(HBITMAP) LoadImage(NULL,"hangvic.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmhangvic,sizeof(BITMAP),&bitmaphangvic);

    pogodjeni.clear();
    greska=0;
    indeks=rand()%10+tezinaHang*10;;
    victoryHang=false;
    hanged=false;
}

void renderHangman(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);

    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;

    if(victoryHang||hanged){
        if(victoryHang){
            hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmhangvic);
            BitBlt(hdcBuffer,0,0,bitmaphangvic.bmWidth,bitmaphangvic.bmHeight,hdcMem,0,0,SRCCOPY);
        }else{
            hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmhanglose);
            BitBlt(hdcBuffer,0,0,bitmaphanglose.bmWidth,bitmaphanglose.bmHeight,hdcMem,0,0,SRCCOPY);
        }

        BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
        DeleteObject(hdcMem);
        DeleteObject(hbmBuffer);
        SelectObject(hdcBuffer, hbmOldBuffer);
        DeleteObject(hdcBuffer);
        DeleteObject(hbmOldBuffer);
        return;
    }

    //vjesalo
    SelectObject(hdcBuffer,GetStockObject(WHITE_BRUSH));
    Rectangle(hdcBuffer,crect.left,crect.top,crect.right,crect.bottom);
    SelectObject(hdcBuffer,GetStockObject(BLACK_BRUSH));
    Rectangle(hdcBuffer,crect.left,crect.bottom-120,crect.right,crect.bottom);
    Rectangle(hdcBuffer,crect.left+50,crect.top+100,crect.left+60,crect.bottom-120);
    Rectangle(hdcBuffer,crect.left+50,crect.top+100,crect.left+180,crect.top+90);
    Rectangle(hdcBuffer,crect.left+170,crect.top+100,crect.left+180,crect.top+180);
    //kraj vjesala
    HPEN olovka=CreatePen(PS_SOLID,7,RGB(0,0,0));
    if(greska>0)
        Ellipse(hdcBuffer,crect.left+155,crect.top+170,crect.left+195,crect.top+210);
    if(greska>1)
        Rectangle(hdcBuffer,crect.left+170,crect.top+180,crect.left+180,crect.top+280);
    if(greska>2){
        SelectObject(hdcBuffer,olovka);
        MoveToEx(hdcBuffer,crect.left+170,crect.top+280,NULL);
        LineTo(hdcBuffer,crect.left+150,crect.top+350);
    }
    if(greska>3){
        SelectObject(hdcBuffer,olovka);
        MoveToEx(hdcBuffer,crect.left+180,crect.top+280,NULL);
        LineTo(hdcBuffer,crect.left+200,crect.top+350);
    }
    if(greska>4){
        SelectObject(hdcBuffer,olovka);
        MoveToEx(hdcBuffer,crect.left+170,crect.top+220,NULL);
        LineTo(hdcBuffer,crect.left+150,crect.top+270);
    }
    if(greska>5){
        SelectObject(hdcBuffer,olovka);
        MoveToEx(hdcBuffer,crect.left+180,crect.top+220,NULL);
        LineTo(hdcBuffer,crect.left+200,crect.top+270);
        hanged=true;
    }
    NacrtajCrtice(hdcBuffer);
    NacrtajSlovo(hdcBuffer);

    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(olovka);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}

void provjeriSlovo(WPARAM slovo){
    int provjera=0;
    cout<<rijeci[indeks]<<endl;
    for(int i=0;i<rijeci[indeks].length();++i)
        if(slovo!=rijeci[indeks][i]) provjera++;
        else pogodjeni.push_back(Slovo(i,rijeci[indeks][i]));
    if(provjera==rijeci[indeks].length()) greska++;
    if(pogodjeni.size()==rijeci[indeks].length()) victoryHang=TRUE;

}

void NacrtajCrtice(HDC hdc){
    int x=300;
    int y=460;
    int dx=60;
    for(int i=0;i<rijeci[indeks].length();++i){
        Rectangle(hdc,x+i*dx,y,x+i*dx+35,y+10);
    }
}

void NacrtajSlovo(HDC hdc){
    int x=300,y=400;
    int dx=60;
    HFONT hFont=CreateFont(-48, 0, 0, 0, FW_BOLD, FALSE,
    FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
    "Broadway");
    SelectObject(hdc,hFont);
    for(int i=0;i<pogodjeni.size();++i){
            TextOut(hdc,x+pogodjeni[i].ind*dx,y,&rijeci[indeks][pogodjeni[i].ind],1);
    }
}
