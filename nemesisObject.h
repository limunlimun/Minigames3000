#ifndef NEMESISOBJECT_H_INCLUDED
#define NEMESISOBJECT_H_INCLUDED
#include "vector2D.h"
#include <iostream>
#include<vector>
#include"ammo.h"
#include"constants.h"


class Nemesis{
   private:
        Vector2D _position;
        Vector2D _velocity;
        Vector2D _acceleration;
        int _hitpoints;
        std::vector<Vector2D> _shots;
        //HBITMAP nemesisWhite;
        //HBITMAP nemesisBlack;
        //BITMAP bmp;
    public:
        //konstruktori
        Nemesis();
        Nemesis(double,double);
        Nemesis(const Nemesis&);
        ~Nemesis();
        //seteri i geteri
        void setVelocity(double,double);
        void setPosition(double,double);
        void setAcceleration(double,double);
        void setHitpoints(int);

        Vector2D getVelocity();
        Vector2D getPosition();
        Vector2D getAcceleration();
        double getHeight();
        double getWidth();
        int getHitPoints();
        //gameObject metodi

        void update();
        void takeHit();
        void render(HDC);
        void levelUp(int);
        void shoot();
        int checkForHits(int,int);
        void print();
};

Nemesis::Nemesis(){
    //nemesisWhite=(HBITMAP)LoadImage(NULL,"nemesis1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //nemesisBlack=(HBITMAP)LoadImage(NULL,"nemesis1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
  GetObject(nemesisBlack,sizeof(BITMAP),&bmp);
    _position=Vector2D(0,0);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    _hitpoints=4;

}

Nemesis::Nemesis(double x,double y){
    //nemesisWhite=(HBITMAP)LoadImage(NULL,"nemesis1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //nemesisBlack=(HBITMAP)LoadImage(NULL,"nemesis1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
  GetObject(nemesisBlack,sizeof(BITMAP),&bmp);
    _position=Vector2D(x,y);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    _hitpoints=4;
}

Nemesis::Nemesis(const Nemesis& other){
    _position=other._position;
    _velocity=other._velocity;
    _acceleration=other._acceleration;
}
Nemesis::~Nemesis(){
    DeleteObject(nemesisWhite);
    DeleteObject(nemesisBlack);
}
void Nemesis::setVelocity(double x,double y){
    _velocity.setX(x);
    _velocity.setY(y);
}

void Nemesis::setPosition(double x,double y){
    _position.setX(x);
    _position.setY(y);
}

void Nemesis::setAcceleration(double x,double y){
    _acceleration.setX(x);
    _acceleration.setY(y);
}

Vector2D Nemesis::getVelocity(){
    return _velocity;
}

Vector2D Nemesis::getAcceleration(){
    return _acceleration;
}

Vector2D Nemesis::getPosition(){
    return _position;
}

double Nemesis::getHeight(){

    return bmp.bmHeight;
}

double Nemesis::getWidth(){

    return bmp.bmWidth;
}

void Nemesis::update(){
    _position.AddTo(_velocity);
    for(int i=0;i<_shots.size();i++)
        _shots[i].AddTo(Vector2D(0,2));
}

void Nemesis::render(HDC hdc){
 HDC hdcMem;

 /*nemesisWhite=(HBITMAP)LoadImage(NULL,"nemesis1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 nemesisBlack=(HBITMAP)LoadImage(NULL,"nemesis1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
*/

 hdcMem=CreateCompatibleDC(hdc);
 SelectObject(hdcMem,nemesisBlack);
 BitBlt(hdc,_position.getX(),_position.getY(),bmp.bmWidth,bmp.bmHeight,hdcMem,0,0,SRCPAINT);
 SelectObject(hdcMem,nemesisWhite);
 BitBlt(hdc,_position.getX(),_position.getY(),bmp.bmWidth,bmp.bmHeight,hdcMem,0,0,SRCAND);


 //ZADNJE DODANO
 HBRUSH r=CreateSolidBrush(RGB(255,0,0));
 SelectObject(hdc,r);
 for(int i=0;i<_hitpoints;i++)
    Rectangle(hdc,_position.getX()+i*bmp.bmWidth/_hitpoints,_position.getY(),_position.getX()+(i+1)*bmp.bmWidth/_hitpoints,_position.getY()-10);

 for(int i=0;i<_shots.size();i++){
    SelectObject(hdcMem,_nemAmmoBlack);
    BitBlt(hdc,_shots[i].getX(),_shots[i].getY(),nemesisAmmo.bmWidth,nemesisAmmo.bmHeight,hdcMem,0,0,SRCPAINT);
    SelectObject(hdcMem,_nemAmmoWhite);
    BitBlt(hdc,_shots[i].getX(),_shots[i].getY(),nemesisAmmo.bmWidth,nemesisAmmo.bmHeight,hdcMem,0,0,SRCAND);
 }

 DeleteObject(r);
 DeleteObject(hdcMem);


}

void Nemesis::print(){
    std::cout<<"Acceleration"<<std::endl;
        _acceleration.print();
    std::cout<<"velocity"<<std::endl;
        _velocity.print();
    std::cout<<"Position"<<std::endl;
        _position.print();
}

void Nemesis::takeHit(){
    --_hitpoints;
}

void Nemesis::setHitpoints(int h){
    _hitpoints=h;
}

int Nemesis::getHitPoints(){
    return _hitpoints;
}

void Nemesis::shoot(){
    _shots.push_back(Vector2D(_position.getX()+nemesisAmmo.bmWidth/2,_position.getY()+nemesisAmmo.bmHeight));
   // std::cout<<"Shots fired: "<<_shots.size()<<std::endl;
}


int Nemesis::checkForHits(int x,int y){
    int xs,ys,ret;
    xs=x+player.bmWidth;
    ys=y+player.bmHeight;
    ret=0;

    //std::cout<<"State: "<<" "<<x<<" "<<y<<" "<<xs<<" "<<ys<<std::endl;
for(int i=0;i<_shots.size();i++){
        if(_shots[i].getX()>=x && _shots[i].getX()<=xs){
        if(_shots[i].getY()>=y && _shots[i].getY()<=ys){
            _shots.erase(_shots.begin()+i);
            ret++;
            }
        }
    }
    return ret;
}



#endif // NEMESISOBJECT_H_INCLUDED
