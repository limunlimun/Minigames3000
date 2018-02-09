#ifndef _MEMORY_H
#define _MEMORY_H

#include <vector>
#include <algorithm>
#include <array>
#include <random>
using namespace std;

static HBITMAP hbmmempoz;
static BITMAP bitmapmempoz;
//flagovi za tezinu
static bool start=TRUE;
static bool easy=TRUE;
static bool middle=FALSE;
static bool hard=FALSE;

static int MAXK=4;//broj karti odredjen tezinom
static bool prviklik=FALSE;
static bool drugiklik=FALSE;
static int odabranoPolje[2]={-1,-1};

static HBITMAP hbmslika;
static BITMAP bitmapslika;
static int sirinakarte;
static int visinakarte;
static int brojacx=0;
static int brojacy=0;

//varijable za score
static int uspjesnih=0;
static int pokusaja=0;
//pobjeda
static bool pobjeda=FALSE;

void pripremiIgru();
void provjeriPar(int,int);

static int pozicije[24][2]={
    {200,100},{300,100},{400,100},{500,100},{600,100},{700,100},
    {200,200},{300,200},{400,200},{500,200},{600,200},{700,200},
    {200,300},{300,300},{400,300},{500,300},{600,300},{700,300},
    {200,400},{300,400},{400,400},{500,400},{600,400},{700,400}
};

static vector<int> postavljenekarte;
static vector<int> parovi;
void initializeMemory(){
    hbmmempoz=(HBITMAP) LoadImage(NULL,"memorypoz.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmmempoz,sizeof(BITMAP),&bitmapmempoz);

    hbmslika=(HBITMAP) LoadImage(NULL,"memorycards.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmslika,sizeof(BITMAP),&bitmapslika);
    sirinakarte=bitmapslika.bmWidth/4;
    visinakarte=bitmapslika.bmHeight/6;
    postavljenekarte.clear();
    parovi.clear();
    pripremiIgru();
    prviklik=FALSE;
    drugiklik=FALSE;
    pobjeda=FALSE;
    odabranoPolje[0]=-1;
    odabranoPolje[1]=-1;
    brojacx=0;
    brojacy=0;
    uspjesnih=0;
    pokusaja=0;
}

void pripremiIgru(){
    random_shuffle(begin(pozicije),end(pozicije));
    if(easy) MAXK=4;
    else if(middle) MAXK=8;
    else MAXK=12;
    for(int i=0;i<MAXK;++i){
        postavljenekarte.push_back(pozicije[2*i][0]);
        postavljenekarte.push_back(pozicije[2*i][1]);
        postavljenekarte.push_back(pozicije[2*i+1][0]);
        postavljenekarte.push_back(pozicije[2*i+1][1]);
    }
}

void renderMemory(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);

    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmmempoz);
    BitBlt(hdcBuffer,0,0,bitmapmempoz.bmWidth,bitmapmempoz.bmHeight,hdcMem,0,0,SRCCOPY);

    for(int i=0;i<MAXK;i++){
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmslika);
        BitBlt(hdcBuffer,pozicije[2*i][0],pozicije[2*i][1],sirinakarte,visinakarte, hdcMem, brojacx*sirinakarte,brojacy*visinakarte, SRCCOPY);
        BitBlt(hdcBuffer,pozicije[2*i+1][0],pozicije[2*i+1][1],sirinakarte,visinakarte, hdcMem, brojacx*sirinakarte,brojacy*visinakarte, SRCCOPY);
        brojacx++;
        if(brojacx==4){
            brojacx=0;
            brojacy++;
        }
        if(easy&&brojacy==1) brojacy=0;
        else if(middle&&brojacy==2) brojacy=0;
        else if(hard&&brojacy==3) brojacy=0;
    }
    for(int i=0;i<postavljenekarte.size()/2;++i){
            if(i==odabranoPolje[0]||i==odabranoPolje[1]) SelectObject(hdcBuffer,GetStockObject(HOLLOW_BRUSH));
            else SelectObject(hdcBuffer,GetStockObject(WHITE_BRUSH));
            if(parovi.size()!=0 && (find(parovi.begin(),parovi.end(),i)!=parovi.end()))
                SelectObject(hdcBuffer,GetStockObject(HOLLOW_BRUSH));
            //else SelectObject(hdcBuffer,GetStockObject(WHITE_BRUSH));
        Rectangle(hdcBuffer,postavljenekarte.at(2*i),postavljenekarte.at(2*i+1),postavljenekarte.at(2*i)+100,postavljenekarte.at(2*i+1)+100);
    }

    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}

void otvoriPolje(int x,int y){
    int temp;
    for(int i=0;i<postavljenekarte.size()/2;++i){
        if(x>postavljenekarte.at(2*i)&&x<(postavljenekarte.at(2*i)+100)&&y>postavljenekarte.at(2*i+1)&&y<(postavljenekarte.at(2*i+1)+100))
            if(!prviklik) {prviklik=TRUE;odabranoPolje[0]=i;}
            else {
                if(odabranoPolje[0]==i) return;
                odabranoPolje[1]=i;
                drugiklik=TRUE;
                if(odabranoPolje[0]>odabranoPolje[1]){
                    temp=odabranoPolje[0];
                    odabranoPolje[0]=odabranoPolje[1];
                    odabranoPolje[1]=temp;
                }
                provjeriPar(odabranoPolje[0],odabranoPolje[1]);
            }
    }
}

void provjeriPar(int p, int d){
    if(p+1==d)
        if(p%2==0){
                parovi.push_back(p);
                parovi.push_back(d);
                uspjesnih++;
        }
    pokusaja++;
    if(parovi.size()==MAXK*2){
        pobjeda=TRUE;
        string poruka="Pogodjenih "+std::to_string(uspjesnih)+" od "+std::to_string(pokusaja)+" pokusaja!";
        MessageBox(NULL,poruka.c_str(),"Zavrsena igra",MB_OK);
    }
}

void zatvoriPolja(){
    prviklik=FALSE;
    drugiklik=FALSE;
    odabranoPolje[0]=-1;
    odabranoPolje[1]=-1;
}



#endif // _MEMORY_H
