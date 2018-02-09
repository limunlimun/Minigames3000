
static HBITMAP hbmpoz,hbmpoz2,hbmpoz2mask,hbmbox,hbmboxmask;
static BITMAP bitmappoz,bitmappoz2,bitmapbox;

static HBITMAP hbmitem1,hbmitem2,hbmitem3,hbmitem4,hbmitem5;
static HBITMAP hbmitem1mask,hbmitem2mask,hbmitem3mask,hbmitem4mask,hbmitem5mask;
static BITMAP bitmapitem1,bitmapitem2,bitmapitem3,bitmapitem4,bitmapitem5;

static HBITMAP hbmprize,hbmprizemask;
static BITMAP bitmapprize;

static bool pogodikutiju=true;
static int tacnih=0;
static int level=0;
static int xt;
static int position[]={30,190,400,620,820};

void zatvoriKutiju(){
    pogodikutiju=true;
    random_shuffle(begin(position),end(position));
    int i;
    if(level==0) i=rand()%2;
    else if(level==1) i=rand()%3;
    else i=rand()%4;
    if(i==0){
        hbmprize=hbmitem1;
        hbmprizemask=hbmitem1mask;
        bitmapprize=bitmapitem1;
        xt=position[0];
    }else if(i==1){
        hbmprize=hbmitem2;
        hbmprizemask=hbmitem2mask;
        xt=position[1];
        bitmapprize=bitmapitem2;
    }else if(i==2){
        hbmprize=hbmitem3;
        hbmprizemask=hbmitem3mask;
        xt=position[2];
        bitmapprize=bitmapitem3;
    }else if(i==3){
        hbmprize=hbmitem4;
        hbmprizemask=hbmitem4mask;
        xt=position[3];
        bitmapprize=bitmapitem4;
    }else{
        hbmprize=hbmitem5;
        hbmprizemask=hbmitem5mask;
        xt=position[4];
        bitmapprize=bitmapitem5;
    }
}

void provjeriKlik(HWND hwnd,int x,int y){
    int temp=0;

    if(x>=position[0]&&x<position[0]+bitmapitem1.bmWidth && y>200 && y<200+bitmapitem1.bmHeight && xt==position[0]){
        tacnih++;
        temp++;
    }else if(x>=position[1]&&x<position[1]+bitmapitem2.bmWidth && y>200 && y<200+bitmapitem2.bmHeight && xt==position[1]){
        tacnih++;
        temp++;
    }else if(x>=position[2]&&x<position[2]+bitmapitem3.bmWidth && y>200 && y<200+bitmapitem3.bmHeight && xt==position[2]){
        tacnih++;
        temp++;
    }else if(x>=position[3]&&x<position[3]+bitmapitem4.bmWidth && y>200 && y<200+bitmapitem4.bmHeight && xt==position[3]){
        tacnih++;
        temp++;
    }else if(x>=position[4]&&x<position[4]+bitmapitem5.bmWidth && y>200 && y<200+bitmapitem5.bmHeight && xt==position[4]){
        tacnih++;
        temp++;
    }else temp==-1;

    if(temp==-1) return;
    else if(temp==0){
            string t=std::to_string(tacnih);
            t="Pogodili ste: "+t+" puta";
            pogodikutiju=false;
            MessageBox(hwnd,t.c_str(),"Gotova igra",MB_OK);
    }else zatvoriKutiju();
}

void initializeBox(){
    tacnih=0;
    hbmpoz=(HBITMAP) LoadImage(NULL,"boxpoz.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmpoz,sizeof(BITMAP),&bitmappoz);

    hbmpoz2=(HBITMAP) LoadImage(NULL,"boxpoz2black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmpoz2,sizeof(BITMAP),&bitmappoz2);
    hbmpoz2mask=(HBITMAP) LoadImage(NULL,"boxpoz2.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmbox=(HBITMAP) LoadImage(NULL,"boxblack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmbox,sizeof(BITMAP),&bitmapbox);
    hbmboxmask=(HBITMAP) LoadImage(NULL,"box.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmitem1=(HBITMAP) LoadImage(NULL,"item1black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmitem1,sizeof(BITMAP),&bitmapitem1);
    hbmitem1mask=(HBITMAP) LoadImage(NULL,"item1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmitem2=(HBITMAP) LoadImage(NULL,"item2black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmitem2,sizeof(BITMAP),&bitmapitem2);
    hbmitem2mask=(HBITMAP) LoadImage(NULL,"item2.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmitem3=(HBITMAP) LoadImage(NULL,"item3black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmitem3,sizeof(BITMAP),&bitmapitem3);
    hbmitem3mask=(HBITMAP) LoadImage(NULL,"item3.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmitem4=(HBITMAP) LoadImage(NULL,"item4black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmitem4,sizeof(BITMAP),&bitmapitem4);
    hbmitem4mask=(HBITMAP) LoadImage(NULL,"item4.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    hbmitem5=(HBITMAP) LoadImage(NULL,"item5black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(hbmitem5,sizeof(BITMAP),&bitmapitem5);
    hbmitem5mask=(HBITMAP) LoadImage(NULL,"item5.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    pogodikutiju=true;
    zatvoriKutiju();
}



void renderBox(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd, &crect);

    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;
    //pozadina
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmpoz);
    BitBlt(hdcBuffer,0,0,bitmappoz.bmWidth,bitmappoz.bmHeight,hdcMem,0,0,SRCCOPY);
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmpoz2mask);
    BitBlt(hdcBuffer, 220,25,bitmappoz2.bmWidth,bitmappoz2.bmHeight, hdcMem, 0,0, SRCAND);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmpoz2);
    BitBlt(hdcBuffer, 220,25,bitmappoz2.bmWidth,bitmappoz2.bmHeight, hdcMem, 0,0, SRCPAINT);
    //kraj pozadine
    if(pogodikutiju){
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmboxmask);
        BitBlt(hdcBuffer, 400,400,bitmapbox.bmWidth,bitmapbox.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmbox);
        BitBlt(hdcBuffer, 400,400,bitmapbox.bmWidth,bitmapbox.bmHeight, hdcMem, 0,0, SRCPAINT);
    }else{
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmprizemask);
        BitBlt(hdcBuffer, 400,400,bitmapprize.bmWidth,bitmapprize.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmprize);
        BitBlt(hdcBuffer, 400,400,bitmapprize.bmWidth,bitmapprize.bmHeight, hdcMem, 0,0, SRCPAINT);
    }

    //itemi
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmitem1mask);
    BitBlt(hdcBuffer, position[0],200,bitmapitem1.bmWidth,bitmapitem1.bmHeight, hdcMem, 0,0, SRCAND);
    hbmOld = (HBITMAP)SelectObject(hdcMem, hbmitem1);
    BitBlt(hdcBuffer, position[0],200,bitmapitem1.bmWidth,bitmapitem1.bmHeight, hdcMem, 0,0, SRCPAINT);

    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmitem2mask);
    BitBlt(hdcBuffer, position[1],200,bitmapitem2.bmWidth,bitmapitem2.bmHeight, hdcMem, 0,0, SRCAND);
    hbmOld = (HBITMAP)SelectObject(hdcMem, hbmitem2);
    BitBlt(hdcBuffer, position[1],200,bitmapitem2.bmWidth,bitmapitem2.bmHeight, hdcMem, 0,0, SRCPAINT);

    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmitem3mask);
    BitBlt(hdcBuffer, position[2],200,bitmapitem3.bmWidth,bitmapitem3.bmHeight, hdcMem, 0,0, SRCAND);
    hbmOld = (HBITMAP)SelectObject(hdcMem, hbmitem3);
    BitBlt(hdcBuffer, position[2],200,bitmapitem3.bmWidth,bitmapitem3.bmHeight, hdcMem, 0,0, SRCPAINT);

    if(level>0){
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmitem4mask);
        BitBlt(hdcBuffer, position[3],200,bitmapitem4.bmWidth,bitmapitem4.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmitem4);
        BitBlt(hdcBuffer, position[3],200,bitmapitem4.bmWidth,bitmapitem4.bmHeight, hdcMem, 0,0, SRCPAINT);
    }
    if(level>1){
        hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmitem5mask);
        BitBlt(hdcBuffer, position[4],200,bitmapitem5.bmWidth,bitmapitem5.bmHeight, hdcMem, 0,0, SRCAND);
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmitem5);
        BitBlt(hdcBuffer, position[4],200,bitmapitem5.bmWidth,bitmapitem5.bmHeight, hdcMem, 0,0, SRCPAINT);
    }
    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}
