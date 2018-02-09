#ifndef AMMO_H_INCLUDED
#define AMMO_H_INCLUDED
#include"vector2D.h"
#include<string>
#include "constants.h"
class Ammo{
    private:
        //HBITMAP _ammoWhite;
        //HBITMAP _ammoBlack;
        //BITMAP _ammoInfo;
        Vector2D _position;
        Vector2D _velocity;
        Vector2D _acceleration;
    public:
        //int width;
        Ammo();
        Ammo(int x,int y);
        Ammo(int x,int y,std::string im);
       // ~Ammo();
        Vector2D getPosition();
        Vector2D getVelocity();
        Vector2D getAcceleration();
        void setPosition(double,double);
        void setVelocity(double,double);
        void setAcceleration(double,double);
        void render(HDC);
        void update();
};

Ammo::Ammo(){
    _position=Vector2D(0,0);
    _velocity=Vector2D(0,2);
    _acceleration=Vector2D(0,0);
    //_ammoWhite=(HBITMAP)LoadImage(NULL,"laserBeamWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    //_ammoBlack=(HBITMAP)LoadImage(NULL,"laserBeamBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   // GetObject(_ammoBlack,sizeof(BITMAP),&_ammoInfo);
   // width=_ammoInfo.bmWidth;

}

Ammo::Ammo(int x,int y){
    _position=Vector2D(x,y);
    _velocity=Vector2D(0,-5);
    _acceleration=Vector2D(0,0);
    //_ammoWhite=(HBITMAP)LoadImage(NULL,"laserBeamWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
   // _ammoBlack=(HBITMAP)LoadImage(NULL,"laserBeamBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObject(_ammoBlack,sizeof(BITMAP),&_ammoInfo);
}

/*Ammo::~Ammo(){
    DeleteObject(_ammoWhite);
    DeleteObject(_ammoBlack);
}*/

void Ammo::setVelocity(double x,double y){
    _velocity.setX(x);
    _velocity.setY(y);
}

void Ammo::setPosition(double x,double y){
    _position.setX(x);
    _position.setY(y);
}

void Ammo::setAcceleration(double x,double y){
    _acceleration.setX(x);
    _acceleration.setY(y);
}

Vector2D Ammo::getVelocity(){
    return _velocity;
}

Vector2D Ammo::getAcceleration(){
    return _acceleration;
}

Vector2D Ammo::getPosition(){
    return _position;
}

void Ammo::update(){

    _position.AddTo(_velocity);
}

void Ammo::render(HDC hdc){
    HDC hdcMem;
   // _ammoWhite=(HBITMAP)LoadImage(NULL,"laserBeamWhite.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    //_ammoBlack=(HBITMAP)LoadImage(NULL,"laserBeamBlack.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    hdcMem=CreateCompatibleDC(hdc);
 SelectObject(hdcMem,_ammoBlack);
 BitBlt(hdc,_position.getX(),_position.getY(),_ammoInfo.bmWidth,_ammoInfo.bmHeight,hdcMem,0,0,SRCPAINT);
 SelectObject(hdcMem,_ammoWhite);
 BitBlt(hdc,_position.getX(),_position.getY(),_ammoInfo.bmWidth,_ammoInfo.bmHeight,hdcMem,0,0,SRCAND);
 DeleteObject(hdcMem);

}


#endif // AMMO_H_INCLUDED
