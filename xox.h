#ifndef _XOX_H
#define _XOX_H
#include <vector>
using namespace std;
static bool prviIgrac=TRUE;
static bool drugiIgrac=FALSE;
static bool singlePlayer=FALSE;
static bool twoPlayer=TRUE;

static HBITMAP hbmxoxpoz;
static BITMAP bitmapxoxpoz;

int pronadjiPolje(int,int);
static int polje=0;
static bool slobodnaPolja[9]={TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE};
static int odigranaPolja[9]={0,0,0,0,0,0,0,0,0};
int provjeriIgru();
void potezKompjuter();
static bool kompjuter=FALSE;
static bool gotovaPartija=FALSE;
struct Objekat{
    int x1;
    int y1;
    int x2;
    int y2;
    int oblik;
    Objekat();
    Objekat(int a,int b,int c,int d,int o){
        x1=a; y1=b; x2=c; y2=d; oblik=o;
    }
};
static vector<Objekat> potezi;
static const int polja[9][4]={//x1 x2 y1 y2
    {250,390,50,120},{390,545,50,120},{550,690,50,120},
    {250,390,125,225},{390,545,125,225},{550,690,125,225},
    {250,390,235,330},{390,545,235,330},{550,690,235,330}
};
static const int coordPoteza[9][4]={//x1 y1 x2 y2
    {260,380,60,110},{400,535,60,110},{560,680,60,110},
    {260,380,135,215},{400,535,135,215},{560,680,135,215},
    {260,380,245,320},{400,535,245,320},{560,680,245,320}
};

void renderXOX(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);

    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);

    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;

    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmxoxpoz);
    BitBlt(hdcBuffer,0,0,bitmapxoxpoz.bmWidth,bitmapxoxpoz.bmHeight,hdcMem,0,0,SRCCOPY);

    for(int i=0;i<potezi.size();++i){
            HPEN kreda=CreatePen(PS_SOLID,5,RGB(255,255,255));
            SelectObject(hdcBuffer,GetStockObject(HOLLOW_BRUSH));
            SelectObject(hdcBuffer,kreda);
            if(potezi.at(i).oblik==XOBLIK){
                MoveToEx(hdcBuffer,potezi.at(i).x1,potezi.at(i).y1,NULL);
                LineTo(hdcBuffer,potezi.at(i).x2,potezi.at(i).y2);
                MoveToEx(hdcBuffer,potezi.at(i).x1,potezi.at(i).y2,NULL);
                LineTo(hdcBuffer,potezi.at(i).x2,potezi.at(i).y1);
            }else{
                Ellipse(hdcBuffer,potezi.at(i).x1,potezi.at(i).y1,potezi.at(i).x2,potezi.at(i).y2);
            }
            DeleteObject(kreda);
        }
    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}

void initializeXOX(){
    hbmxoxpoz=(HBITMAP) LoadImage(NULL,"xoxpoz.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmxoxpoz,sizeof(BITMAP),&bitmapxoxpoz);
}

int pronadjiPolje(int xklik,int yklik){
    int pov=0;
    for(int i=0;i<9;++i){
            if(xklik>=polja[i][0]&&xklik<=polja[i][1]&&
               yklik>=polja[i][2]&&yklik<=polja[i][3]){
                   if(!slobodnaPolja[i]){//zauzeto polje
                        return 0;
                   }
                   if(prviIgrac){
                        prviIgrac=FALSE;
                        potezi.push_back(Objekat(coordPoteza[i][0],coordPoteza[i][2],coordPoteza[i][1],coordPoteza[i][3],XOBLIK));
                        odigranaPolja[i]=1;
                   }
                   else{
                        prviIgrac=TRUE;
                        potezi.push_back(Objekat(coordPoteza[i][0],coordPoteza[i][2],coordPoteza[i][1],coordPoteza[i][3],OXOBLIK));
                        odigranaPolja[i]=2;
                   }
                   pov=i+1;
                   slobodnaPolja[i]=FALSE;
            }

    }
    int temp=provjeriIgru();
    if(temp!=0){
        gotovaPartija=true;
        return pov;}
    /* single player nije jos u funkciji, bug na zadnjem potezu*/
     if(singlePlayer&&kompjuter){
        if(potezi.size()==8) return pov;
        kompjuter=FALSE;
        potezKompjuter();
    }
    return pov;
}

int provjeriIgru(){
    int pov=0;
    //provjera vodoravno
    if(odigranaPolja[0]==odigranaPolja[1]&&odigranaPolja[1]==odigranaPolja[2]&&(odigranaPolja[2]==1||odigranaPolja[2]==2)) pov=odigranaPolja[2];
    if(odigranaPolja[3]==odigranaPolja[4]&&odigranaPolja[4]==odigranaPolja[5]&&(odigranaPolja[5]==1||odigranaPolja[5]==2)) pov=odigranaPolja[5];
    if(odigranaPolja[6]==odigranaPolja[7]&&odigranaPolja[7]==odigranaPolja[8]&&(odigranaPolja[8]==1||odigranaPolja[8]==2)) pov=odigranaPolja[8];
    //provjera uspravno
    if(odigranaPolja[0]==odigranaPolja[3]&&odigranaPolja[3]==odigranaPolja[6]&&(odigranaPolja[6]==1||odigranaPolja[6]==2)) pov=odigranaPolja[6];
    if(odigranaPolja[1]==odigranaPolja[4]&&odigranaPolja[4]==odigranaPolja[7]&&(odigranaPolja[7]==1||odigranaPolja[7]==2)) pov=odigranaPolja[7];
    if(odigranaPolja[2]==odigranaPolja[5]&&odigranaPolja[5]==odigranaPolja[8]&&(odigranaPolja[8]==1||odigranaPolja[8]==2)) pov=odigranaPolja[8];
    //provjera dijagonala
    if(odigranaPolja[0]==odigranaPolja[4]&&odigranaPolja[4]==odigranaPolja[8]&&(odigranaPolja[8]==1||odigranaPolja[8]==2)) pov=odigranaPolja[8];
    if(odigranaPolja[2]==odigranaPolja[4]&&odigranaPolja[4]==odigranaPolja[6]&&(odigranaPolja[6]==1||odigranaPolja[6]==2)) pov=odigranaPolja[6];

    if(pov!=0) gotovaPartija=true;
    return pov;
}
void resetujXOX(){
    prviIgrac=TRUE;
    drugiIgrac=FALSE;
    potezi.clear();
    polje=0;
    gotovaPartija=false;
    for(int i=0;i<9;++i){
        slobodnaPolja[i]=TRUE;
        odigranaPolja[i]=0;
    }
}

void potezKompjuter(){
    int i=rand()%8;
    while(!pronadjiPolje(coordPoteza[i][0],coordPoteza[i][2])){
        i=rand()%8;
    }
    kompjuter=TRUE;
}
#endif // _XOX_H
