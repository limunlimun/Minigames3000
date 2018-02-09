static HBITMAP hbmhilopoz,hbmhi,hbmlo,hbmhimask,hbmlomask;
static BITMAP bitmaphilopoz,bitmaphi,bitmaplo;
static HBITMAP hbmcards,hbmback,hbmbackmask;
static BITMAP bitmapcards,bitmapback;
static int sirina,visina;
static int x=0,y=0;
static int starox,staroy;
static bool tacno=true;
static int pogodaka=0;
static int ukupanscore=1;

void odaberiKartu(){
    starox=x;
    staroy=y;
    x=rand()%13;
    y=rand()%4;
}

bool vecamanja(int xk,int yk){
    if(xk>=316&&xk<=316+bitmaphi.bmWidth && yk>=150 && yk<=150+bitmaphi.bmHeight){
        if(starox<=x){
            pogodaka+=1;
            ukupanscore*=2;
            odaberiKartu();
            return true;
        }else return false;
    }else if(xk>=500&&xk<=500+bitmaplo.bmWidth && yk>=150 && yk<=150+bitmaplo.bmHeight){
        if(starox>=x){
            pogodaka+=1;
            ukupanscore*=2;
            odaberiKartu();
            return true;
        }else return false;
    }else return true;
}

void initializeHilo(){
    pogodaka=0;
    ukupanscore=1;
    tacno=true;
    hbmhilopoz=(HBITMAP) LoadImage(NULL,"hilopoz.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmhilopoz,sizeof(BITMAP),&bitmaphilopoz);

    hbmhi=(HBITMAP) LoadImage(NULL,"highblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmhi,sizeof(BITMAP),&bitmaphi);
    hbmhimask=(HBITMAP) LoadImage(NULL,"high.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmlo=(HBITMAP) LoadImage(NULL,"lowblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmlo,sizeof(BITMAP),&bitmaplo);
    hbmlomask=(HBITMAP) LoadImage(NULL,"low.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmback=(HBITMAP) LoadImage(NULL,"cardbackblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmback,sizeof(BITMAP),&bitmapback);
    hbmbackmask=(HBITMAP) LoadImage(NULL,"cardback.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmcards=(HBITMAP) LoadImage(NULL,"cards.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmcards,sizeof(BITMAP),&bitmapcards);
    sirina=bitmapcards.bmWidth/13;
    visina=bitmapcards.bmHeight/4;
    odaberiKartu();
}

void renderHilo(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);
    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmhilopoz);
    BitBlt(hdcBuffer,0,0,bitmaphilopoz.bmWidth,bitmaphilopoz.bmHeight,hdcMem,0,0,SRCCOPY);

    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmhimask);
    BitBlt(hdcBuffer, 316,150,bitmaphi.bmWidth,bitmaphi.bmHeight, hdcMem, 0,0, SRCAND);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmhi);
    BitBlt(hdcBuffer, 316,150,bitmaphi.bmWidth,bitmaphi.bmHeight, hdcMem, 0,0, SRCPAINT);

    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmlomask);
    BitBlt(hdcBuffer, 500,150,bitmaplo.bmWidth,bitmaplo.bmHeight, hdcMem, 0,0, SRCAND);
    hbmOld = (HBITMAP)SelectObject(hdcMem, hbmlo);
    BitBlt(hdcBuffer, 500,150,bitmaplo.bmWidth,bitmaplo.bmHeight, hdcMem, 0,0, SRCPAINT);

    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmcards);
    BitBlt(hdcBuffer,80,170,sirina,visina,hdcMem,starox*sirina,staroy*visina,SRCCOPY);
    if(tacno){
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmbackmask);
        BitBlt(hdcBuffer, 736,150,bitmapback.bmWidth,bitmapback.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmback);
        BitBlt(hdcBuffer, 736,150,bitmapback.bmWidth,bitmapback.bmHeight, hdcMem, 0,0, SRCPAINT);
    }else{
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmcards);
        BitBlt(hdcBuffer,736,150,sirina,visina,hdcMem,x*sirina,y*visina,SRCCOPY);
    }

    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}
