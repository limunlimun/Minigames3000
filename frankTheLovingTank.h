#ifndef FRANKTHELOVINGTANK_H_INCLUDED
#define FRANKTHELOVINGTANK_H_INCLUDED

#include"tankObject.h"
#include"soldierObject.h"
#include"constantsTank.h"


Tank playt;
Soldier sols[3];
struct Obstacle balboa[3];
int numObst=3;
int numSols=3;


void drawFrankie(HWND hwnd){
    HDC hdc,hdcMem;
    //BITMAP bmp;
    //HBITMAP tankWhite=(HBITMAP)LoadImage(NULL,"tankWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    //HBITMAP tankBlack=(HBITMAP)LoadImage(NULL,"tankBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    HBITMAP hbmold,hbmMem;
            hdc=GetDC(hwnd);
            hdcMem=CreateCompatibleDC(hdc);
            //FillRect(hdc,&clientRect,(HBRUSH)GetStockObject(WHITE_BRUSH));
                //crtanje pozadine
                if(playt.getHitpoints()<=0){
                    TextOut(hdc,(clientRect.right-strlen("-----YOU LOSE-----"))/2,clientRect.bottom/2,"-----YOU LOSE-----",strlen("-----YOU LOSE-----"));
                }
                else if(shooter>=numSols || init>=numObst){
                     TextOut(hdc,(clientRect.right-strlen("-----YOU WIN-----"))/2,clientRect.bottom/2,"-----YOU WIN-----",strlen("-----YOU WIN-----"));
                     //TextOut(hdc,(clientRect.right-strlen("Let me tell you a little secret. "))/2,clientRect.bottom/2+20,"Let me tell you a little secret. ",strlen("Let me tell you a little secret. "));
                     TextOut(hdc,(clientRect.right-strlen("Frankie didn't quite fire hearts. Frankie is actually a psychopath.")*6)/2,clientRect.bottom/2+20,"Frankie didn't really fire hearts. Frankie is actually a psychopath.",strlen("Frankie didn't really fire hearts. Frankie is actually a psychopath."));
                     TextOut(hdc,(clientRect.right-strlen("Frankie thinks that he is spreading the love by dispersing the wrath of God in form of his 120 mm gun.")*6)/2,clientRect.bottom/2+40,"Frankie thinks that he is spreading the love by dispersing the wrath of God in form of his 120 mm gun.",strlen("Frankie thinks that he is spreading the love by dispersing the wrath of God in form of his 120 mm gun."));
                     TextOut(hdc,(clientRect.right-strlen("But he's a really nice guys otherwise ... of course that applies to when he is not on homocidal rampage.")*6)/2,clientRect.bottom/2+60,"But he's a really nice guys otherwise ... of course that applies to when he is not on homocidal rampage.",strlen("But he's a really nice guys otherwise ... of course that applies to when he is not on homocidal rampage."));
                     TextOut(hdc,(clientRect.right-strlen("Oh like you're so perfect!")*6)/2,clientRect.bottom/2+80,"Oh like you're so perfect!.",strlen("Oh like you're so perfect!"));
                }
                else{

                hbmMem=CreateCompatibleBitmap(hdc,clientRect.right,clientRect.bottom);
                hbmold=(HBITMAP)SelectObject(hdcMem,hbmMem);
                drawBackground(hdcMem);

                //crtanje tenka
                /*SelectObject(hdcMem,tankBlack);
                BitBlt(hdc,clientRect.left,clientRect.bottom-bmp.bmHeight/6,bmp.bmWidth,bmp.bmHeight/6,hdcMem,0,i*bmp.bmHeight/6,SRCPAINT);
                SelectObject(hdcMem,tankWhite);
                BitBlt(hdc,clientRect.left,clientRect.bottom-bmp.bmHeight/6,bmp.bmWidth,bmp.bmHeight/6,hdcMem,0,i*bmp.bmHeight/6,SRCAND);
                */
                 renderObstacle(hdcMem);
                 if(rigLocation<clientRect.right)
                drawOilField(hdcMem);
                playt.render(hdcMem);
                //crtanje stijene
                /*SelectObject(hdcMem,rockBlack);
                BitBlt(hdc,clientRect.right-rock.bmWidth,clientRect.bottom-rock.bmHeight,rock.bmWidth,rock.bmHeight,hdcMem,0,0,SRCPAINT);
                SelectObject(hdcMem,rockWhite);
                BitBlt(hdc,clientRect.right-rock.bmWidth,clientRect.bottom-rock.bmHeight,rock.bmWidth,rock.bmHeight,hdcMem,0,0,SRCAND);
                */


                //crtanje vojnika
                /*SelectObject(hdcMem,soldierBlack);
                BitBlt(hdc,clientRect.right-soldier.bmWidth,clientRect.bottom-soldier.bmHeight/7,soldier.bmWidth,soldier.bmHeight/7,hdcMem,0,j*soldier.bmHeight/7,SRCPAINT);
                SelectObject(hdcMem,soldierWhite);
                BitBlt(hdc,clientRect.right-soldier.bmWidth,clientRect.bottom-soldier.bmHeight/7,soldier.bmWidth,soldier.bmHeight/7,hdcMem,0,j*soldier.bmHeight/7,SRCAND);
               */

                //crtanje refinerije
                /*SelectObject(hdcMem,oilBlack);
                BitBlt(hdc,rigLocation,clientRect.bottom-oil.bmHeight+20,oil.bmWidth,oil.bmHeight,hdcMem,0,0,SRCPAINT);
                SelectObject(hdcMem,oilWhite);
                BitBlt(hdc,rigLocation,clientRect.bottom-oil.bmHeight+20,oil.bmWidth,oil.bmHeight,hdcMem,0,0,SRCAND);*/


               for(int i=0;i<=shooter;i++){
                    if(sols[i].getHitPoints()>0)
                sols[i].render(hdcMem);
                }
                BitBlt(hdc,0,0,clientRect.right,clientRect.bottom,hdcMem,0,0,SRCCOPY);
                }

             SelectObject(hdcMem,hbmold);
             DeleteObject(hbmMem);
             DeleteObject(hdcMem);
             //DeleteObject(hdcTransient);
             //DeleteObject(background);

            ReleaseDC(hwnd,hdc);
             DeleteObject(hdc);


}


void runSetupFrankie(HWND hwnd){
   GetClientRect(hwnd,&clientRect);
   tankWhite=(HBITMAP)LoadImage(NULL,"tankWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   tankBlack=(HBITMAP)LoadImage(NULL,"tankBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   background=(HBITMAP)LoadImage(NULL,"land.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   oilWhite=(HBITMAP)LoadImage(NULL,"oilRigWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   oilBlack=(HBITMAP)LoadImage(NULL,"oilRigBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   rockWhite=(HBITMAP)LoadImage(NULL,"rockWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   rockBlack=(HBITMAP)LoadImage(NULL,"rockBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   soldierWhite=(HBITMAP)LoadImage(NULL,"soldierWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   soldierBlack=(HBITMAP)LoadImage(NULL,"soldierBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   heartWhite=(HBITMAP)LoadImage(NULL,"heartWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   heartBlack=(HBITMAP)LoadImage(NULL,"heartBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   flowerWhite=(HBITMAP)LoadImage(NULL,"flowerWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   flowerBlack=(HBITMAP)LoadImage(NULL,"flowerBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   rockSmileWhite=(HBITMAP)LoadImage(NULL,"smileWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   rockSmileBlack=(HBITMAP)LoadImage(NULL,"smileBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   GetObject(tankWhite,sizeof(BITMAP),&bmp2);
   GetObject(background,sizeof(BITMAP),&scene);
   GetObject(oilWhite,sizeof(BITMAP),&oil);
   GetObject(rockWhite,sizeof(BITMAP),&rock);
   GetObject(soldierWhite,sizeof(BITMAP),&soldier);
   GetObject(heartWhite,sizeof(BITMAP),&heart);
   GetObject(flowerWhite,sizeof(BITMAP),&flower);
   GetObject(rockSmileWhite,sizeof(BITMAP),&smile);

   playt.setPosition(clientRect.left,clientRect.bottom-bmp2.bmHeight/6);
   //test.setPosition(clientRect.right-soldier.bmWidth,clientRect.bottom-soldier.bmHeight/7);
   rigLocation=clientRect.right-oil.bmWidth+1000;
   for(int i=0;i<numObst;i++){
    balboa[i].positionX=clientRect.right-rock.bmWidth+i*1000;//400;
    balboa[i].positionY=clientRect.bottom-rock.bmHeight;//800;
    balboa[i].passed=false;
    init=0;
   }
   for(int i=0;i<numSols;i++){
    sols[i].setPosition(clientRect.right-soldier.bmWidth+i*500,clientRect.bottom-soldier.bmHeight/7);
   }
}

void updateFrankie(){
    checkForObstacles();
    bool shouldIUpdate=true;
    //shooter=0;
    //opet stupid rjesenje
    int counter=0;
    for(int i=0;i<numSols;i++){
        if(sols[i].getHitPoints()==0)
            counter++;
    }
    shooter=counter;
    counter=0;
    int currHealth=playt.getHitpoints();
    for(int i=0;i<=shooter;i++){
        //if(sols[i].getPosition().getX()<clientRect.right ){

            shouldIUpdate=playt.checkForHits(sols[i].getPosition().getX(),sols[i].getPosition().getY()+50);
            if(!shouldIUpdate){
            if(sols[i].getHitPoints()>0){
            sols[i].update();
            counter+=sols[i].checkForHits(playt.getPosition().getX(),playt.getPosition().getY());
            }

            if(shootingTime==0){
                    if(sols[shooter].getPosition().getX()+200<clientRect.right)
            sols[shooter].shoot();
            shootingTime=100;
                }
            }
            else{
            sols[i].setHitpoints(0);

            }
        }
        playt.setHitpoints(currHealth-counter);
        //else
          //  break;



    //shooter=counter;
    playt.update();

    if(playt.getPosition().getX()>rigLocation && (playt.getPosition().getX())<(rigLocation+oil.bmWidth) ){
        playt.setFuel(200);
        rigLocation+=9000;
    }
    /*if(shootingTime==0){
    sols[shooter].shoot();
    shootingTime=400;
    }*/
    shootingTime--;
}

void checkInput(int wParam){
    //test.checkInput(wParam);
    for(int i=0;i<numSols;i++){
        sols[i].checkInput(wParam);
    }
    playt.checkInput(wParam);
    if(wParam==VK_RIGHT){
        //if(moveForward){
        rigLocation-=10;
        for(int i=0;i<numObst;i++)
        balboa[i].positionX-=10;
   // }
    }
    if(wParam==VK_LEFT){
        rigLocation+=10;
        for(int i=0;i<numObst;i++)
        balboa[i].positionX+=10;
    }
}

void renderObstacle(HDC hdc){
     //crtanje stijene
     HDC hdcMem=CreateCompatibleDC(hdc);
     HDC hdcMem2=CreateCompatibleDC(hdc);
     SelectObject(hdcMem,rockSmileBlack);
     SelectObject(hdcMem2,rockSmileWhite);
     for(int i=0;i<init;i++){
          //if(balboa[i].positionX>clientRect.right)
            //continue;
            BitBlt(hdc,balboa[i].positionX,balboa[i].positionY,smile.bmWidth,smile.bmHeight,hdcMem,0,0,SRCPAINT);
            BitBlt(hdc,balboa[i].positionX,balboa[i].positionY,smile.bmWidth,smile.bmHeight,hdcMem2,0,0,SRCAND);
        }
        SelectObject(hdcMem,rockBlack);
        SelectObject(hdcMem2,rockWhite);
        if(init>numObst)
            return;
        for(int i=init;i<numObst;i++){
                if(balboa[i].positionX>clientRect.right)
                continue;
            BitBlt(hdc,balboa[i].positionX,balboa[i].positionY,rock.bmWidth,rock.bmHeight,hdcMem,0,0,SRCPAINT);
            BitBlt(hdc,balboa[i].positionX,balboa[i].positionY,rock.bmWidth,rock.bmHeight,hdcMem2,0,0,SRCAND);
        }
     DeleteObject(hdcMem);
     DeleteObject(hdcMem2);
}

void checkForObstacles(){
    int playFront=playt.getPosition().getX()+bmp2.bmWidth-100;
    int playLow=playt.getPosition().getY()+bmp2.bmHeight/6;
    moveForward=true;
          if(playFront>balboa[init].positionX)
                moveForward=false;
          if(playLow<balboa[init].positionY)
                moveForward=true;
          if(balboa[init].positionX+500<playFront)
                init++;


}

void drawOilField(HDC hdc){
    HDC hdcMem;
    hdcMem=CreateCompatibleDC(hdc);
    SelectObject(hdcMem,oilBlack);
    BitBlt(hdc,rigLocation,clientRect.bottom-oil.bmHeight+20,oil.bmWidth,oil.bmHeight,hdcMem,0,0,SRCPAINT);
    SelectObject(hdcMem,oilWhite);
    BitBlt(hdc,rigLocation,clientRect.bottom-oil.bmHeight+20,oil.bmWidth,oil.bmHeight,hdcMem,0,0,SRCAND);
    DeleteObject(hdcMem);
}

void drawBackground(HDC hdc){
    HDC hdcMem;
    hdcMem=CreateCompatibleDC(hdc);
    SelectObject(hdcMem,background);
    BitBlt(hdc,0,0,scene.bmWidth,scene.bmHeight,hdcMem,0,0,SRCCOPY);
    DeleteObject(hdcMem);
}

#endif // FRANKTHELOVINGTANK_H_INCLUDED
