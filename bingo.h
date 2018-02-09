#include <string>
#include <vector>
using namespace std;
static bool prvopokretanje=true;
static bool zavrsenKrug=false;
static bool ostvarenDobitak=false;
static HBITMAP hbmbingopoz,hbmloptice,hbmlopticemask,hbmbubanj,hbmbubanjmask,hbmizvlacenje,hbmpobjeda;
static BITMAP bitmapbingopoz,bitmaploptice,bitmapbubanj,bitmapizvlacenje,bitmappobjeda;
static int sirinaloptice,visinaloptice;
static int odabranax,odabranay;
static int brojacb,sirinabubnja,visinabubnja;
static int ii=0;
static int counter,counter2=0;
static bool zapocni=false;
static int prizemoney=0;

class Loptica{
public:
    int ind;
    int xl;
    int yg;
    bool oznacena;
    Loptica()=default;
    Loptica(int a,int b,int i){
        xl=a;
        yg=b;
        ind=i;
        oznacena=false;
    }
    bool pripada(int a,int b){
        if(ind==50){
            if(a>=755&&a<=920&&y>=475&&y<=475+70) return true;
            else return false;
        }else {
            if(a>=xl&&a<=xl+70&&b>=yg&&b<=yg+70) return true;
            else return false;
        }
    }
    void oznaci(){
        if(oznacena){
                oznacena=false;
        }else {
                oznacena=true;
        }
    }
};
static vector<Loptica> oznaceneLoptice;
static vector<Loptica> loptice;

void popuniLoptice(){
    loptice.clear();
    loptice.push_back(Loptica(15,100,0));
    loptice.push_back(Loptica(108,100,1));
    loptice.push_back(Loptica(202,100,2));
    loptice.push_back(Loptica(295,100,3));
    loptice.push_back(Loptica(388,100,4));
    loptice.push_back(Loptica(480,100,5));
    loptice.push_back(Loptica(570,100,6));
    loptice.push_back(Loptica(664,100,7));
    loptice.push_back(Loptica(759,100,8));
    loptice.push_back(Loptica(850,100,9));

    loptice.push_back(Loptica(15,195,10));
    loptice.push_back(Loptica(108,195,11));
    loptice.push_back(Loptica(202,195,12));
    loptice.push_back(Loptica(295,195,13));
    loptice.push_back(Loptica(388,195,14));
    loptice.push_back(Loptica(480,195,15));
    loptice.push_back(Loptica(570,195,16));
    loptice.push_back(Loptica(664,195,17));
    loptice.push_back(Loptica(759,195,18));
    loptice.push_back(Loptica(850,195,19));

    loptice.push_back(Loptica(15,290,20));
    loptice.push_back(Loptica(108,290,21));
    loptice.push_back(Loptica(202,290,22));
    loptice.push_back(Loptica(295,290,23));
    loptice.push_back(Loptica(388,290,24));
    loptice.push_back(Loptica(480,290,25));
    loptice.push_back(Loptica(570,290,26));
    loptice.push_back(Loptica(664,290,27));
    loptice.push_back(Loptica(759,290,28));
    loptice.push_back(Loptica(850,290,29));

    loptice.push_back(Loptica(15,380,30));
    loptice.push_back(Loptica(108,380,31));
    loptice.push_back(Loptica(202,380,32));
    loptice.push_back(Loptica(295,380,33));
    loptice.push_back(Loptica(388,380,34));
    loptice.push_back(Loptica(480,380,35));
    loptice.push_back(Loptica(570,380,36));
    loptice.push_back(Loptica(664,380,37));
    loptice.push_back(Loptica(759,380,38));
    loptice.push_back(Loptica(850,380,39));

    loptice.push_back(Loptica(15,475,40));
    loptice.push_back(Loptica(108,475,41));
    loptice.push_back(Loptica(202,475,42));
    loptice.push_back(Loptica(295,475,43));
    loptice.push_back(Loptica(388,475,44));
    loptice.push_back(Loptica(480,475,45));
    loptice.push_back(Loptica(570,475,46));
    loptice.push_back(Loptica(664,475,47));

    loptice.push_back(Loptica(0,0,50));
}

static string nagrade[]={"10000","7500","5000","2500","1000","500","300","200",
                                "150","100","90","80","70","60","50","40","30","25","20","15","10",
                                "9","8","7","6","5","4","3","2","1"};

static string nagradetext[]={"TEN THOUSAND","SEVEN THOUSAND FIVE HUNDRED","FIVE THOUSAND","TWO THOUSAND FIVE HUNDRED",
                            "ONE THOUSAND","FIVE HUNDRED","THREE HUNDRED","TWO HUNDRED","ONE HUNDRED FIFTY","ONE HUNDRED",
                            "NINETY","EIGHTY","SEVENTY","SIXTY","FIFTY","FORTY","THIRTY","TWENTY FIVE","TWENTY","FIFTEEN",
                            "TEN","NINE","EIGHT","SEVEN","SIX","FIVE","FOUR","THREE","TWO","ONE"};

static const int koordinate[][2]={  {560,60},{580,105},{600,150},{580,195},{560,240},
                                    {50,90},{50,135},{50,180},{50,225},{50,270},{50,315},{50,360},{50,405},{50,450},
                                    {210,360},{210,405},{210,450},
                                    {370,360},{370,405},{370,450},
                                    {530,360},{530,405},{530,450},
                                    {690,360},{690,405},{690,450},
                                    {850,90},{850,135},{850,180},{850,225},{850,270},{850,315},{850,360},{850,405},{850,450},
};

static int tiketbrojevi[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
                            20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
                            36,37,38,39,40,41,42,43,44,45,46,47
};

static int brojevi[][2]={{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},
                        {0,1},{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},
                        {0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},
                        {0,3},{1,3},{2,3},{3,3},{4,3},{5,3},{6,3},{7,3},
                        {0,4},{1,4},{2,4},{3,4},{4,4},{5,4},{6,4},{7,4},
                        {0,5},{1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{7,5},
};
static int brojevi1[][2]={{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},
                        {0,1},{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},
                        {0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},
                        {0,3},{1,3},{2,3},{3,3},{4,3},{5,3},{6,3},{7,3},
                        {0,4},{1,4},{2,4},{3,4},{4,4},{5,4},{6,4},{7,4},
                        {0,5},{1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{7,5},
};
static bool izvucenibubanj[6]={false,false,false,false,false,false};
static bool izvuceni[6]={false,false,false,false,false,false};
static int odabrani[6][2]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

void slucajniIzbor(){
    random_shuffle(begin(tiketbrojevi),end(tiketbrojevi));
    random_shuffle(begin(tiketbrojevi),end(tiketbrojevi));
    random_shuffle(begin(tiketbrojevi),end(tiketbrojevi));
    random_shuffle(begin(tiketbrojevi),end(tiketbrojevi));
    random_shuffle(begin(tiketbrojevi),end(tiketbrojevi));
    int a=3;
    for(int i=0;i<6;++i){
        izvuceni[i]=true;
        odabrani[i][0]=brojevi[tiketbrojevi[a]][0];
        odabrani[i][1]=brojevi[tiketbrojevi[a]][1];
        a+=3;
    }
    zapocni=true;
}

void pokreniBubanj(){
    random_shuffle(begin(brojevi),end(brojevi));
    random_shuffle(begin(brojevi),end(brojevi));
    random_shuffle(begin(brojevi),end(brojevi));
    random_shuffle(begin(brojevi),end(brojevi));
    random_shuffle(begin(brojevi),end(brojevi));
    random_shuffle(begin(brojevi),end(brojevi));
    random_shuffle(begin(brojevi),end(brojevi));
    random_shuffle(begin(brojevi),end(brojevi));
    random_shuffle(begin(brojevi),end(brojevi));
    random_shuffle(begin(brojevi),end(brojevi));
}

void initializeBingo(){
    zavrsenKrug=false;
    prvopokretanje=true;
    ostvarenDobitak=false;
    hbmizvlacenje=(HBITMAP) LoadImage(NULL,"izvlacenjescreen.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmizvlacenje,sizeof(BITMAP),&bitmapizvlacenje);

    hbmbingopoz=(HBITMAP) LoadImage(NULL,"bingopoz.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmbingopoz,sizeof(BITMAP),&bitmapbingopoz);

    hbmpobjeda=(HBITMAP) LoadImage(NULL,"bingowinner.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmpobjeda,sizeof(BITMAP),&bitmappobjeda);

    hbmloptice=(HBITMAP) LoadImage(NULL,"lopticeblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmloptice,sizeof(BITMAP),&bitmaploptice);
    hbmlopticemask=(HBITMAP) LoadImage(NULL,"loptice.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    sirinaloptice=bitmaploptice.bmWidth/8;
    visinaloptice=bitmaploptice.bmHeight/6;
    //pokreniBubanj();

    hbmbubanj=(HBITMAP) LoadImage(NULL,"bubanjblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmbubanj,sizeof(BITMAP),&bitmapbubanj);
    hbmbubanjmask=(HBITMAP) LoadImage(NULL,"bubanj.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    sirinabubnja=bitmapbubanj.bmWidth/4;
    visinabubnja=bitmapbubanj.bmHeight;
    brojacb=0;
    ii=0;
    counter=0;
    counter2=0;
    zapocni=false;
    prvopokretanje=true;
    popuniLoptice();
    for(int i=0;i<48;++i){
        brojevi[i][0]=brojevi1[i][0];
        brojevi[i][1]=brojevi1[i][1];
    }
    for(int i=0;i<6;i++){
        izvuceni[i]=false;
        izvucenibubanj[i]=false;
    }
    prizemoney=0;
}

void odaberiBoju(int boja){
    if(boja==CRVENAB){
        for(int i=0;i<6;++i){
            izvuceni[i]=true;
            odabrani[i][0]=0;
            odabrani[i][1]=i;
        }
    }else if(boja==ZELENAB){
        for(int i=0;i<6;++i){
            izvuceni[i]=true;
            odabrani[i][0]=1;
            odabrani[i][1]=i;
        }
    }else if(boja==PLAVAB){
        for(int i=0;i<6;++i){
            izvuceni[i]=true;
            odabrani[i][0]=2;
            odabrani[i][1]=i;
        }
    }else if(boja==LJUBICASTAB){
        for(int i=0;i<6;++i){
            izvuceni[i]=true;
            odabrani[i][0]=3;
            odabrani[i][1]=i;
        }
    }else if(boja==SMEDJAB){
        for(int i=0;i<6;++i){
            izvuceni[i]=true;
            odabrani[i][0]=4;
            odabrani[i][1]=i;
        }
    }else if(boja==ZUTAB){
        for(int i=0;i<6;++i){
            izvuceni[i]=true;
            odabrani[i][0]=5;
            odabrani[i][1]=i;
        }
    }else if(boja==NARANDZASTAB){
        for(int i=0;i<6;++i){
            izvuceni[i]=true;
            odabrani[i][0]=6;
            odabrani[i][1]=i;
        }
    }else if(boja==CRNAB){
        for(int i=0;i<6;++i){
            izvuceni[i]=true;
            odabrani[i][0]=7;
            odabrani[i][1]=i;
        }
    }
}

void odaberiBroj(int xk,int yk){
    if(xk>=755&&xk<=920&&yk>=475&&yk<=475+70){
        slucajniIzbor();
        return;
    }
    if(xk>=15&&xk<=85&&yk>=0&&yk<=80){
        odaberiBoju(CRVENAB);
        return;
    }
    if(xk>=108&&xk<=180&&yk>=0&&yk<=80){
        odaberiBoju(ZELENAB);
        return;
    }
    if(xk>=202&&xk<=272&&yk>=0&&yk<=80){
        odaberiBoju(PLAVAB);
        return;
    }
    if(xk>=295&&xk<=363&&yk>=0&&yk<=80){
        odaberiBoju(LJUBICASTAB);
        return;
    }
    if(xk>=388&&xk<=456&&yk>=0&&yk<=80){
        odaberiBoju(SMEDJAB);
        return;
    }
    if(xk>=480&&xk<=550&&yk>=0&&yk<=80){
        odaberiBoju(ZUTAB);
        return;
    }
    if(xk>=570&&xk<=640&&yk>=0&&yk<=80){
        odaberiBoju(NARANDZASTAB);
        return;
    }
    if(xk>=664&&xk<=734&&yk>=0&&yk<=80){
        odaberiBoju(CRNAB);
        return;
    }
    if(xk>=755&&xk<=920&&yk>=0&&yk<=80){
        int a=rand()%7+12;
        odaberiBoju(a);
        return;
    }
    for(int i=0;i<loptice.size();++i){
        if(loptice.at(i).pripada(xk,yk)){
            if(!loptice[i].oznacena){
                for(int j=0;j<6;++j){
                    if(izvuceni[j]) continue;
                    else{
                        izvuceni[j]=true;
                        odabrani[j][0]=brojevi[loptice[i].ind][0];
                        odabrani[j][1]=brojevi[loptice[i].ind][1];
                        loptice.at(i).oznaci();
                        return;
                    }
                }
            }else{
                for(int j=0;j<6;++j){
                    if(odabrani[j][0]==brojevi[loptice[i].ind][0]&&odabrani[j][1]==brojevi[loptice[i].ind][1]){
                        loptice[i].oznaci();
                        izvuceni[j]=false;
                        return;
                    }
                }
            }

        }

    }
}

void renderIzvlacenje(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);
    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1,hbmOld;
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmizvlacenje);
    BitBlt(hdcBuffer, 0,0,bitmapizvlacenje.bmWidth,bitmapizvlacenje.bmHeight, hdcMem, 0,0, SRCCOPY);

    HBRUSH green=CreateSolidBrush(RGB(0,200,0));
    HPEN gr=CreatePen(PS_SOLID,10,RGB(0,200,0));
    SelectObject(hdcBuffer,green);
    SelectObject(hdcBuffer,gr);
    SelectObject(hdcBuffer,GetStockObject(HOLLOW_BRUSH));
    for(int i=0;i<loptice.size();++i){
        if(loptice[i].oznacena)
            Ellipse(hdcBuffer,loptice[i].xl,loptice[i].yg,loptice[i].xl+70,loptice[i].yg+70);
    }
    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(green);
    DeleteObject(gr);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}

bool provjeriDobitak(){
    for(int i=0;i<6;++i){
        if(izvucenibubanj[i]) continue;
        else return false;
    }
    return true;
}

void renderIgra(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);
    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1,hbmOld;
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmbingopoz);
    BitBlt(hdcBuffer, 0,0,bitmapbingopoz.bmWidth,bitmapbingopoz.bmHeight, hdcMem, 0,0, SRCCOPY);

    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmbubanjmask);
    BitBlt(hdcBuffer, 330,50,sirinabubnja,visinabubnja, hdcMem, brojacb*sirinabubnja,0, SRCAND);
    hbmOld = (HBITMAP)SelectObject(hdcMem, hbmbubanj);
    BitBlt(hdcBuffer, 330,50,sirinabubnja,visinabubnja, hdcMem, brojacb*sirinabubnja,0, SRCPAINT);
    if(ii++%5==0) brojacb++;
    if(brojacb==4) brojacb=0;

    int x=700,y=20;
    for(int i=0;i<6;i++){
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmlopticemask);
        BitBlt(hdcBuffer, x+i*45,y,sirinaloptice,visinaloptice, hdcMem, odabrani[i][0]*sirinaloptice,odabrani[i][1]*visinaloptice, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmloptice);
        BitBlt(hdcBuffer, x+i*45,y,sirinaloptice,visinaloptice, hdcMem, odabrani[i][0]*sirinaloptice,odabrani[i][1]*visinaloptice, SRCPAINT);
    }

    SelectObject(hdcBuffer,GetStockObject(BLACK_PEN));
    string ispis;
    for(int i=0;i<35;++i){
        if(i>4) {
            ispis=nagrade[i-5];
            TextOut(hdcBuffer,koordinate[i][0]+50,koordinate[i][1]+15,ispis.c_str(),ispis.length());
        }
    }

    counter2++;
    if(counter2==100&&counter==35) zavrsenKrug=true;
    if(counter2==100){
        counter++;
        counter2=0;
        if(counter>=35) {counter=35;}
    }
    vector<int> nagrada;
    int i;
    for(i=0;i<counter;++i){
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmlopticemask);
        BitBlt(hdcBuffer, koordinate[i][0],koordinate[i][1],sirinaloptice,visinaloptice, hdcMem, brojevi[i][0]*sirinaloptice,brojevi[i][1]*visinaloptice, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmloptice);
        BitBlt(hdcBuffer, koordinate[i][0],koordinate[i][1],sirinaloptice,visinaloptice, hdcMem, brojevi[i][0]*sirinaloptice,brojevi[i][1]*visinaloptice, SRCPAINT);
        for(int j=0;j<6;++j){
            if(brojevi[i][0]==odabrani[j][0]&&brojevi[i][1]==odabrani[j][1])
                izvucenibubanj[j]=true;
        }
    }
    if(!ostvarenDobitak){
        if(provjeriDobitak()) {nagrada.push_back(i);ostvarenDobitak=true;}
        if(nagrada.size()>0) prizemoney=nagrada.at(0);
    }

    HPEN zelena=CreatePen(PS_SOLID,5,RGB(0,255,0));
    SelectObject(hdcBuffer,zelena);
    for(int j=0;j<6;++j){
        if(izvucenibubanj[j]){
            MoveToEx(hdcBuffer,x+j*45,y,NULL);
            LineTo(hdcBuffer,x+j*45+sirinaloptice,y+visinaloptice);
        }
    }

    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(zelena);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
    //Sleep(5);
}

void poredajBrojeve(){
    int flag=1;
    for(int i=1;i<=6&&flag;++i){
        flag=0;
        for(int j=0;j<5;++j){
            if(odabrani[j+1][0]<odabrani[j][0]){
                int temp=odabrani[j][0];
                int temp2=odabrani[j][1];
                odabrani[j][0]=odabrani[j+1][0];
                odabrani[j][1]=odabrani[j+1][1];
                odabrani[j+1][0]=temp;
                odabrani[j+1][1]=temp2;
                flag=1;
            }
            if(odabrani[j+1][1]<odabrani[j][1]){
                int temp=odabrani[j][0];
                int temp2=odabrani[j][1];
                odabrani[j][0]=odabrani[j+1][0];
                odabrani[j][1]=odabrani[j+1][1];
                odabrani[j+1][0]=temp;
                odabrani[j+1][1]=temp2;
                flag=1;
            }
        }
    }
}

bool spremnaIgra(){
    for(int i=0;i<6;++i){
        if(!izvuceni[i]) return false;
    }
    poredajBrojeve();
    return true;
}

void renderPobjeda(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);
    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1,hbmOld;
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmpobjeda);
    BitBlt(hdcBuffer, 0,0,bitmappobjeda.bmWidth,bitmappobjeda.bmHeight, hdcMem, 0,0, SRCCOPY);

    HFONT hFont=CreateFont(-30, 0, 0, 0, FW_BOLD, FALSE,
                            FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,"Broadway");

    if(prizemoney>0){
        SelectObject(hdcBuffer,hFont);
        string ispis=nagrade[prizemoney-6];
        SetBkMode( hdcBuffer, TRANSPARENT );
        TextOut(hdcBuffer,220,225,nagradetext[prizemoney-6].c_str(),nagradetext[prizemoney-6].length());
        TextOut(hdcBuffer,790,185,ispis.c_str(),ispis.length());
    }else{
        SelectObject(hdcBuffer,hFont);
        SetBkMode( hdcBuffer, TRANSPARENT );
        TextOut(hdcBuffer,300,225,"ZERO",4);
        TextOut(hdcBuffer,790,185,"0",1);
    }
    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hFont);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}

void renderBingo(HWND hwnd){
    if(zavrsenKrug)
        renderPobjeda(hwnd);
    else if(zapocni)
        renderIgra(hwnd);
    else
        renderIzvlacenje(hwnd);
    if(spremnaIgra()) {
        zapocni=true;
        if(prvopokretanje) {pokreniBubanj();prvopokretanje=false;}
    }
}
