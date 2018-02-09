
HBITMAP hbmminepoz,hbmmina,hbmexp,hbmvic;
BITMAP bitmapminepoz,bitmapmina,bitmapexp,bitmapvic;
static int minepolja[10][10];
static int otvorenapolja[10][10];
static int pozicijepolja[10][10][2];
static bool eksplozija=false;
static bool victory=false;

void initializeMine(){
    hbmminepoz=(HBITMAP) LoadImage(NULL,"minepoz.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmminepoz,sizeof(BITMAP),&bitmapminepoz);

    hbmmina=(HBITMAP) LoadImage(NULL,"mina.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmmina,sizeof(BITMAP),&bitmapmina);

    hbmexp=(HBITMAP) LoadImage(NULL,"minaexp.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmexp,sizeof(BITMAP),&bitmapexp);

    hbmvic=(HBITMAP) LoadImage(NULL,"minevictory.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmvic,sizeof(BITMAP),&bitmapvic);

    int x=245,y=50;
    int dx=50,dy=50;

    for(int i=0;i<10;++i){
        for(int j=0;j<10;++j){
            pozicijepolja[i][j][0]=x+j*dx;
            pozicijepolja[i][j][1]=y+i*dy;
            minepolja[i][j]=0;
            otvorenapolja[i][j]=0;
        }
    }

    for(int i=0;i<10;++i){
        int a=rand()%10;
        int b=rand()%10;
        minepolja[a][b]=-1;
    }
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++){
            if(minepolja[i][j]==-1){
                if(i!=0){
                    if(j!=0 && minepolja[i-1][j-1]!=-1) minepolja[i-1][j-1]++;
                    if(minepolja[i-1][j]!=-1) minepolja[i-1][j]++;
                    if(j+1<10 && minepolja[i-1][j+1]!=-1) minepolja[i-1][j+1]++;
                }
                if(j!=0 && minepolja[i][j-1]!=-1) minepolja[i][j-1]++;
                if(j+1<10 && minepolja[i][j+1]!=-1) minepolja[i][j+1]++;

                if(i+1<10){
                    if(j!=0 && minepolja[i+1][j-1]!=-1) minepolja[i+1][j-1]++;
                    if(minepolja[i+1][j]!=-1) minepolja[i+1][j]++;
                    if(j+1<10 && minepolja[i+1][j+1]!=-1) minepolja[i+1][j+1]++;
                }
            }
        }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(minepolja[i][j]==-1) std::cout<<"* ";
            else std::cout<<minepolja[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    eksplozija=false;
    victory=false;
}

void provjeriPolja(){
    int temp=0;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++){
            if(otvorenapolja[i][j]==0) temp++;
    }
    if(temp==0) victory=true;
}

void renderMine(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);

    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;
    provjeriPolja();
    if(eksplozija||victory){
        if(eksplozija){
            hbmOld1=(HBITMAP)SelectObject(hdcMem,hbmexp);
            BitBlt(hdcBuffer,0,0,bitmapexp.bmWidth,bitmapexp.bmHeight,hdcMem,0,0,SRCCOPY);
        }else{
            hbmOld1=(HBITMAP)SelectObject(hdcMem,hbmvic);
            BitBlt(hdcBuffer,0,0,bitmapvic.bmWidth,bitmapvic.bmHeight,hdcMem,0,0,SRCCOPY);
        }
        BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
        DeleteObject(hdcMem);
        DeleteObject(hbmBuffer);
        SelectObject(hdcBuffer, hbmOldBuffer);
        DeleteObject(hdcBuffer);
        DeleteObject(hbmOldBuffer);
        return;
    }
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmminepoz);
    BitBlt(hdcBuffer,0,0,bitmapminepoz.bmWidth,bitmapminepoz.bmHeight,hdcMem,0,0,SRCCOPY);
    HFONT hFont=CreateFont(-48, 0, 0, 0, FW_BOLD, FALSE,
                                FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,"Broadway");
    string broj;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            Rectangle(hdcBuffer,pozicijepolja[i][j][0],pozicijepolja[i][j][1],pozicijepolja[i][j][0]+50,pozicijepolja[i][j][1]+50);
            if(otvorenapolja[i][j]==1){
                    SelectObject(hdcBuffer,hFont);
                    broj=std::to_string(minepolja[i][j]);
                    TextOut(hdcBuffer,pozicijepolja[i][j][0],pozicijepolja[i][j][1],broj.c_str(),1);
                }
            else if(otvorenapolja[i][j]==2){
                    hbmOld1=(HBITMAP)SelectObject(hdcMem,hbmmina);
                    BitBlt(hdcBuffer,pozicijepolja[i][j][0],pozicijepolja[i][j][1],bitmapminepoz.bmWidth,bitmapminepoz.bmHeight,hdcMem,0,0,SRCCOPY);
            }
        }
    }

    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}

void otvoriPoljeMine(int x,int y,int klik){
    //klik=1 za lijevi taster; klik=2 za desni taster
    int a,b;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(x>pozicijepolja[i][j][0]&&x<pozicijepolja[i][j][0]+50 &&
               y>pozicijepolja[i][j][1]&&y<pozicijepolja[i][j][1]+50){
                if(klik==1){
                        if(minepolja[i][j]==-1) eksplozija=true;
                        otvorenapolja[i][j]=1;
                }
                else {
                        if(otvorenapolja[i][j]==2)otvorenapolja[i][j]=0;
                        else otvorenapolja[i][j]=2;
               }
            }
        }
    }
}
