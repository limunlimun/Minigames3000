#ifndef PARAGON_H_INCLUDED
#define PARAGON_H_INCLUDED
#include <tchar.h>
#include <windows.h>
#include "nemesisObject.h"
#include"playerObject.h"
#include"constants.h"
#include<sstream>

Nemesis nemesii[200];
Player play;

void runSetup(HWND hwnd){
    HBITMAP spaceshipWhite,nemAmmo;
    GetClientRect(hwnd,&clientRect);
    spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(spaceshipWhite,sizeof(BITMAP),&player);
    play.setPosition((clientRect.right-player.bmWidth)/2,clientRect.bottom-player.bmHeight);
    HBITMAP nemAmmoBlack;
    nemAmmoBlack=(HBITMAP)LoadImage(NULL,"nemLasBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(_nemAmmoBlack,sizeof(BITMAP),&nemesisAmmo);
    DeleteObject(spaceshipWhite);

}

void drawHealthBar(HDC hdc){
    int i=play.getHitpoints();
    while(i>0){
        SelectObject(hdc,gr);
        TextOut(hdc,10,clientRect.bottom-70,"Health:",strlen("Health:"));
        Rectangle(hdc,i*30,clientRect.bottom-50,(i+1)*30,clientRect.bottom-25);
        i--;
    }
    std::stringstream ss;
    ss<<kills;
    std::string disp;
    disp="Kills: "+ss.str();
    int slen=strlen(disp.c_str());
    TextOut(hdc,clientRect.right-slen*9,clientRect.bottom-70,disp.c_str(),slen);


}

void drawParagon(HWND hwnd){
    HDC hdc,hdcTransient,hdcMem;
    PAINTSTRUCT ps;
    HBITMAP hbmold,hbmMem;
    HBITMAP background=(HBITMAP)LoadImage(NULL,"background1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);;
             hdc=GetDC(hwnd);


                hdcMem=CreateCompatibleDC(hdc);
                hdcTransient=CreateCompatibleDC(hdc);
                //ZASTO DOUBLE BUFFERING NE RADI!!!!!!!!!!
                // SAD RADI, VALJDA ZATO STO SE BOG SMILOVO.
                hbmMem=CreateCompatibleBitmap(hdc,clientRect.right,clientRect.bottom);
                hbmold=(HBITMAP)SelectObject(hdcMem,hbmMem);

                if(kills==50){
                    TextOut(hdc,clientRect.right/2,clientRect.bottom/2,"-------Victory!------",strlen("-------Victory!------"));
                    TextOut(hdc,clientRect.right/2,clientRect.bottom/2+20,"------We are once more safe from the horde!-------",strlen("------We are once more safe from the horde!-------"));
                }
               else if(play.getHitpoints()>0){
               hbmold=(HBITMAP)SelectObject(hdcMem,background);
               BitBlt(hdc,0,0,back.bmWidth,back.bmHeight,hdcMem,0,0,SRCCOPY);
               for(int i=0;i<numNem;i++){

                    if(nemesii[i].getHitPoints()>0)

                    nemesii[i].render(hdcMem);
                }
                play.render(hdcMem);
                drawHealthBar(hdcMem);


                BitBlt(hdc,0,0,clientRect.right,clientRect.bottom,hdcMem,0,0,SRCCOPY);
                }

                else{
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

                SelectObject(hdcMem,hbmold);
                DeleteObject(hbmMem);
                DeleteObject(hdcMem);
                DeleteObject(hdcTransient);
                DeleteObject(background);
             ReleaseDC(hwnd,hdc);
            DeleteObject(hdc);

}

void update(){

    int x=play.getPosition().getX();
    int y=play.getPosition().getY();
    int curr=play.getHitpoints();
    if(curr==0 || kills==50)
        return;
    play.update();
    for(int i=0;i<numNem;i++){
                    if(nemesii[i].getHitPoints()>0){
                    nemesii[i].update();
                    curr-=nemesii[i].checkForHits(x,y);
                    play.setHitpoints(curr);
                    play.checkForShots(nemesii[i]);
                    //OVDJE DECREASE HITPOINTS
                    }
                }

    //STUPID RJESENJE UVIJEK BRROJI BROJ UBISTAVA
    kills=0;
    for(int i=0;i<numNem;i++){
        if(nemesii[i].getHitPoints()==0)
            kills++;

    }
    //LEVEL UP NA BROJ UBISTAVA
    if(kills==10 && l1){
        spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship2White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship2Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        GetObject(spaceshipWhite,sizeof(BITMAP),&player);
        play.levelUp();
        l1=false;
       }

    if(kills==20 && l2){
        spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship3White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship3Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        GetObject(spaceshipWhite,sizeof(BITMAP),&player);
        play.levelUp();
        l2=false;

    }

    if(kills==30 && l3){
        spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship4White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship4Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        GetObject(spaceshipWhite,sizeof(BITMAP),&player);
        play.levelUp();
        l3=false;
    }

    nem--;
    if(nem==0)
    {

        generateNewNemesii();

        nem=100;
    }


}

void generateNewNemesii(){
    //PRAVI NOVOG NEMESISA I SVAKI PUT MU DODIJELI DA PUCA
    if(numNem>199)
        return;
    int r=rand()%700;
    nemesii[numNem].setPosition(r,0);
    nemesii[numNem].setVelocity(0,0.6);

    nemesii[numNem].shoot();

    numNem++;
}




#endif // PARAGON_H_INCLUDED
