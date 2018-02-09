#include <iostream>
static bool player1=true;
static bool player2=false;
static bool finishedprvi=false;
static bool finisheddrugi=false;

class Krug{
public:
    int xl,yg,xd,yd;
    Krug()=default;
    Krug(int a,int b,int c,int d){
        xl=a;yg=b;xd=c;yd=d;
    }
    Krug(Krug g,int i){
        xl=g.xl;yg=g.yg;xd=g.xd;yd=g.yd;igrac=i;
    }
    int igrac=0;//1 za crveni krug 2 za tamno plavi
};

Krug krugovi[6][7];
Krug odigranipotezi[6][7];
int nizpolja[6][7];

bool provjeriCon4(int red,int kol,int igrac){
    int uspravno=1,vodoravno=1,dijagonala1=1,dijagonala2=1;
    int i;//brojac uspravno
    int j;//brojac vodoravno
    //provjera uspravno
    for(i = red+1;nizpolja[i][kol] == igrac && i <= 5;i++,uspravno++);
	for(i = red-1;nizpolja[i][kol] == igrac && i >= 0;i--,uspravno++);
	if(uspravno>=4)return true;
	//provjera vodoravno
	for(j = kol-1;nizpolja[red][j] == igrac && j >= 0;j--,vodoravno++);
	for(j = kol+1;nizpolja[red][j] == igrac && j <= 6;j++,vodoravno++);
	if(vodoravno>=4) return true;
	//provjera prve dijagonale
	for(i = red-1, j= kol-1;nizpolja[i][j] == igrac&& i>=0 && j >=0; dijagonala1++, i --, j --);
	for(i = red+1, j = kol+1;nizpolja[i][j] == igrac && i<=5 && j <=6;dijagonala1++, i ++, j ++);
	if(dijagonala1>=4) return true;
	//provjera druge dijagonale
	for(i = red-1, j= kol+1;nizpolja[i][j] == igrac && i>=0 && j <= 6; dijagonala2++, i --, j ++);
	for(i = red+1, j= kol-1;nizpolja[i][j] == igrac&& i<=5 && j >=0; dijagonala2 ++, i ++, j --);
	if(dijagonala2>=4) return true;
	return false;
}

void odigrajPotez(HWND hwnd,int xk,int yk,int igrac){
    int kolona=-1;
    for(int j=0;j<7;++j){
        if(xk>=krugovi[0][j].xl&&xk<=krugovi[0][j].xd){
            kolona=j;
        }
    }
    bool tt=false;
    if(kolona>=0){
        int temp=-1;
        for(int i=5;i>=0;--i){
            if(nizpolja[i][kolona]==0){
                nizpolja[i][kolona]=igrac;
                temp++;
                odigranipotezi[i][kolona]=Krug(krugovi[i][kolona],igrac);
                tt=provjeriCon4(i,kolona,igrac);
                break;
            }
        }
        if(temp==-1) return;
    }else return;
    if(igrac==1){
        player1=false;
        player2=true;
    }else{
        player1=true;
        player2=false;
    }
    if(tt){
        if(igrac==1) {finishedprvi=true;}
        else {finisheddrugi=true;}
    }
}

void initializeCon4(){
    player1=true;
    player2=false;
    int x=220,y=80;
    int dx=40,dy=40;
    for(int i=0;i<6;++i){
        for(int j=0;j<7;j++){
            krugovi[i][j]=Krug((x+j*2*dx)-dx,(y+i*2*dy)-dy,(x+j*2*dx)+dx,(y+i*2*dy)+dy);
            nizpolja[i][j]=0;
            memset(odigranipotezi, 0, sizeof(odigranipotezi));
        }
    }
    finisheddrugi=false;
    finishedprvi=false;
}

void renderCon4(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);
    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;
    HBRUSH crvena=CreateSolidBrush(RGB(255,0,0));
    HBRUSH plava=CreateSolidBrush(RGB(25,25,112));

    if(finishedprvi){
        SelectObject(hdcBuffer,GetStockObject(WHITE_BRUSH));
        Rectangle(hdcBuffer,crect.left,crect.top,crect.right,crect.bottom);
        SelectObject(hdcBuffer,crvena);
        Ellipse(hdcBuffer,300,100,700,500);
    }else if(finisheddrugi){
        SelectObject(hdcBuffer,GetStockObject(WHITE_BRUSH));
        Rectangle(hdcBuffer,crect.left,crect.top,crect.right,crect.bottom);
        SelectObject(hdcBuffer,plava);
        Ellipse(hdcBuffer,300,100,700,500);
    }else{
        SelectObject(hdcBuffer,CreateSolidBrush(RGB(0,0,255)));
        Rectangle(hdcBuffer,crect.left,crect.top,crect.right,crect.bottom);
        SelectObject(hdcBuffer,GetStockObject(WHITE_BRUSH));
        for(int i=0;i<6;++i)
            for(int j=0;j<7;++j)
                Ellipse(hdcBuffer,krugovi[i][j].xl,krugovi[i][j].yg,krugovi[i][j].xd,krugovi[i][j].yd);

        for(int i=0;i<6;++i){
            for(int j=0;j<7;++j){
                if(nizpolja[i][j]==1){
                    SelectObject(hdcBuffer,crvena);
                    Ellipse(hdcBuffer,krugovi[i][j].xl,krugovi[i][j].yg,krugovi[i][j].xd,krugovi[i][j].yd);
                }else if(nizpolja[i][j]==2){
                    SelectObject(hdcBuffer,plava);
                    Ellipse(hdcBuffer,krugovi[i][j].xl,krugovi[i][j].yg,krugovi[i][j].xd,krugovi[i][j].yd);
                }else continue;
            }
        }
    }
    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
    DeleteObject(crvena);
    DeleteObject(plava);
}
