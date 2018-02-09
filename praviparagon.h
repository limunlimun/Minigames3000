#include "par.h"

void runSetup(){
    nemesisWhite=(HBITMAP)LoadImage(NULL,"nemesis1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    nemesisBlack=(HBITMAP)LoadImage(NULL,"nemesis1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(nemesisBlack,sizeof(BITMAP),&bmp);

    spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(spaceshipBlack,sizeof(BITMAP),&player);

    _ammoWhite=(HBITMAP)LoadImage(NULL,"laserBeamWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    _ammoBlack=(HBITMAP)LoadImage(NULL,"laserBeamBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(_ammoBlack,sizeof(BITMAP),&_ammoInfo);

    _nemAmmoBlack=(HBITMAP)LoadImage(NULL,"nemLasBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    _nemAmmoWhite=(HBITMAP)LoadImage(NULL,"nemLasWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    GetObject(spaceshipWhite,sizeof(BITMAP),&player);
    play.setPosition((clientRect.right-player.bmWidth)/2,clientRect.bottom-player.bmHeight);

    nemAmmoBlack=(HBITMAP)LoadImage(NULL,"nemLasBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(_nemAmmoBlack,sizeof(BITMAP),&nemesisAmmo);

    background=(HBITMAP)LoadImage(NULL,"background1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(background,sizeof(BITMAP),&bitmapbackground);

}
static int playerx=100,playery;
struct Shot{
    int x;
    int y;
    Shot(int a,int b) : x(a),y(b){};
};
static vector<Shot> shots;

void updateShots(RECT rec){
    for(int i=0;i<shots.size();++i){
        shots.at(i).y-=5;
        if(shots.at(i).y<rec.top) shots.erase(shots.begin()+i);
    }
}
void draw(HWND hwnd){
    RECT rect;
    GetClientRect(hwnd, &rect);
    updateShots(rect);
    playery=rect.bottom-player.bmHeight;
    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,rect.right,rect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1,hbmOld;

    hbmOld1=(HBITMAP) SelectObject(hdcMem,background);
    BitBlt(hdcBuffer, 0,0,bitmapbackground.bmWidth,bitmapbackground.bmHeight, hdcMem, 0,0, SRCCOPY);

    if(kills==50){
        TextOut(hdcBuffer,rect.right/2,rect.bottom/2,"-------Victory!------",strlen("-------Victory!------"));
        TextOut(hdcBuffer,rect.right/2,rect.bottom/2+20,"------We are once more safe from the horde!-------",strlen("------We are once more safe from the horde!-------"));
    }else if(play.getHitpoints()>0){
        for(int i=0;i<numNem;i++){
            if(nemesii[i].getHitPoints()>0)
                nemesii[i].render(hdcBuffer);
            }
        SelectObject(hdcMem,spaceshipBlack);
        BitBlt(hdcBuffer,playerx,playery,player.bmWidth,player.bmHeight,hdcMem,0,0,SRCPAINT);
        SelectObject(hdcMem,spaceshipWhite);
        BitBlt(hdcBuffer,playerx,playery,player.bmWidth,player.bmHeight,hdcMem,0,0,SRCAND);

        for(int i=0;i<shots.size();i++){
           SelectObject(hdcMem,_ammoBlack);
            BitBlt(hdcBuffer,shots.at(i).x,shots.at(i).y,_ammoInfo.bmWidth,_ammoInfo.bmHeight,hdcMem,0,0,SRCPAINT);
            SelectObject(hdcMem,_ammoWhite);
            BitBlt(hdcBuffer,shots.at(i).x,shots.at(i).y,_ammoInfo.bmWidth,_ammoInfo.bmHeight,hdcMem,0,0,SRCAND);
        }
//NE RADIIIII HEALTHHH!!!!!!!!!!!!!!!!
        //drawHealthBar(hdcBuffer);
        int i=play.getHitpoints();
        while(i>0){
            SelectObject(hdcBuffer,gr);
            TextOut(hdcBuffer,10,rect.bottom-70,"Health:",strlen("Health:"));
            Rectangle(hdcBuffer,i*30,600,(i+1)*30,630);
            i--;
        }
        std::stringstream ss;
        ss<<kills;
        std::string disp;
        disp="Kills: "+ss.str();
        int slen=strlen(disp.c_str());
        TextOut(hdcBuffer,rect.right-slen*9,rect.bottom-70,disp.c_str(),slen);
    }else{
            std::stringstream ss;
            ss<<kills;
            std::string ender;
            ender="You have been overrun commander!";
            TextOut(hdc,(clientRect.right-8*ender.size())/2,clientRect.bottom/2,ender.c_str(),ender.size());
            ender="Your men are soon to follow.";
            TextOut(hdc,(clientRect.right-8*ender.size())/2,clientRect.bottom/2+20,ender.c_str(),ender.size());
            ender="You took with you:"+ss.str()+" of their warriors\n";
            TextOut(hdc,(clientRect.right-8*ender.size())/2,clientRect.bottom/2+40,ender.c_str(),ender.size());
            ender="Game over!";
            TextOut(hdc,(clientRect.right-8*ender.size())/2,clientRect.bottom/2+60,ender.c_str(),ender.size());
    }
    nemesii[0].render(hdcBuffer);
    BitBlt(hdc,0,0,rect.right,rect.bottom,hdcBuffer,0,0,SRCCOPY);

    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);

}

