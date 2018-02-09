#include <vector>
using namespace std;

static RECT rect;

static HBITMAP hbmsnakepoz;
static BITMAP bitmapsnakepoz;
//pomjeraj zmije
static int dx=10;
static int dy=10;

static int rezultat=0;
static bool gotovaIgra=FALSE;
static bool poslano=TRUE;
int brzina=100;

static int tezinaSnake=0;

struct Mamac{
    int x;
    int y;
    Mamac(int a, int b){x=a;y=b;}
};
struct Glava{
    int x;
    int y;
    int smjer;
    int sljsmjer;
    Glava(int a,int b,int s,int slj){
        x=a;y=b;smjer=s;sljsmjer=slj;}
};

static Mamac mam(0,0);
static vector<Glava> glave;

void kreirajMamac(){
    int x1=(rand()%80)*10+100;
    int y1=(rand()%40)*10+80;
    mam.x=x1;
    mam.y=y1;
}

void updateKretanje(){
    int x=glave.at(0).x;
    int y=glave.at(0).y;
    if(glave.at(0).smjer==DESNO){
        glave.at(0).x+=dx;
    }else if(glave.at(0).smjer==LIJEVO){
        glave.at(0).x-=dx;
    }else if(glave.at(0).smjer==GORE){
        glave.at(0).y-=dy;
    }else if(glave.at(0).smjer==DOLE){
        glave.at(0).y+=dy;
    }
    int px,py;
    for(int i=1;i<glave.size();++i){
        px=glave.at(i).x;
        py=glave.at(i).y;
        glave.at(i).x=x;
        glave.at(i).y=y;
        x=px;
        y=py;
    }
}

void provjeriSnake(){
    if(glave.at(0).x<=rect.left || glave.at(0).x>=rect.right
       || glave.at(0).y<=rect.top || glave.at(0).y>=rect.bottom) {gotovaIgra=TRUE; return;}
    if(glave.at(0).x==mam.x && glave.at(0).y==mam.y){
        rezultat++;
        glave.push_back(Glava(glave.at(glave.size()-1).x,glave.at(glave.size()-1).y,
                              glave.at(glave.size()-1).smjer,glave.at(glave.size()-1).sljsmjer));
        kreirajMamac();
    }
}

void provjeriSudar(){
    int refx=glave.at(0).x;
    int refy=glave.at(0).y;
    for(int i=2;i<glave.size();++i){
        if(glave.at(i).x==refx && glave.at(i).y==refy)
            gotovaIgra=true;
    }
}

void pripremiKretanje(){
    glave.at(0).smjer=glave.at(0).sljsmjer;
    provjeriSudar();
}

void initializeSnake(){
    hbmsnakepoz=(HBITMAP) LoadImage(NULL,"snakepoz.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmsnakepoz,sizeof(BITMAP),&bitmapsnakepoz);
    glave.clear();
    glave.push_back(Glava(100,100,DESNO,DESNO));
    kreirajMamac();
    rezultat=0;
    gotovaIgra=false;
    poslano=false;
    if(tezinaSnake==0) brzina=100;
    else if(tezinaSnake==1) brzina=80;
    else brzina=50;
}

void renderSnake(HWND hwnd){
    pripremiKretanje();

    RECT crect;
    GetClientRect(hwnd, &crect);
    rect=crect;
    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmsnakepoz);
    BitBlt(hdcBuffer,0,0,bitmapsnakepoz.bmWidth,bitmapsnakepoz.bmHeight,hdcMem,0,0,SRCCOPY);

    if(gotovaIgra){
            HFONT hFont=CreateFont(-48, 0, 0, 0, FW_BOLD, FALSE,
                            FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
                            "Broadway");
            string rez="Rezultat: "+std::to_string(rezultat);
            SelectObject(hdcBuffer,hFont);
            TextOut(hdcBuffer,400,400,rez.c_str(),rez.length());
            BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
            DeleteObject(hdcMem);
            DeleteObject(hbmBuffer);
            SelectObject(hdcBuffer, hbmOldBuffer);
            DeleteObject(hdcBuffer);
            DeleteObject(hbmOldBuffer);
            return;
    }
    HBRUSH crvena=CreateSolidBrush(RGB(255,0,0));
    SelectObject(hdcBuffer,crvena);
    Ellipse(hdcBuffer,mam.x-10,mam.y-10,mam.x+10,mam.y+10);
    DeleteObject(crvena);
    SelectObject(hdcBuffer,GetStockObject(BLACK_BRUSH));
    for(int i=0;i<glave.size();++i){
        Ellipse(hdcBuffer,glave.at(i).x-10,glave.at(i).y-10,glave.at(i).x+10,glave.at(i).y+10);
    }
    updateKretanje();
    provjeriSnake();

    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
    Sleep(brzina);
}
