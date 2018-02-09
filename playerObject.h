#ifndef PLAYEROBJECT_H_INCLUDED
#define PLAYEROBJECT_H_INCLUDED
#include "vector2D.h"
#include <iostream>
#include "ammo.h"
#include<vector>
class Player{
   private:
        Vector2D _position;
        Vector2D _velocity;
        Vector2D _acceleration;
        int _hitpoints;
        int level;
        //HBITMAP spaceshipWhite;
        //HBITMAP spaceshipBlack;
        //BITMAP player;
        std::vector<Ammo> _shots;
     public:
        //konstruktori
        Player();
        Player(double,double);
        Player(const Player&);
        ~Player();

        //seteri i geteri
        void setVelocity(double,double);
        void setPosition(double,double);
        void setAcceleration(double,double);
        void setHitpoints(double);
        double getHitpoints();
        Vector2D getVelocity();
        Vector2D getPosition();
        Vector2D getAcceleration();

        //gameObject metodi
        void checkInput(int);
        void update();
        void render(HDC);
        void levelUp();
        void checkForShots(Nemesis&);
        void print();
};

Player::Player(){
    //spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    _position=Vector2D(0,0);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    GetObject(spaceshipBlack,sizeof(BITMAP),&player);
     _hitpoints=5;
     level=1;

}

Player::Player(double x,double y){
   // spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    _position=Vector2D(x,y);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    _hitpoints=5;
     //GetObject(spaceshipBlack,sizeof(BITMAP),&player);
     level=1;
}

Player::Player(const Player& other){
    _position=other._position;
    _velocity=other._velocity;
    _acceleration=other._acceleration;
    _hitpoints=5;
    level=1;
}
Player::~Player(){
    DeleteObject(spaceshipWhite);
    DeleteObject(spaceshipBlack);
}
void Player::setVelocity(double x,double y){
    _velocity.setX(x);
    _velocity.setY(y);
}

void Player::setPosition(double x,double y){
    _position.setX(x);
    _position.setY(y);
}

void Player::setAcceleration(double x,double y){
    _acceleration.setX(x);
    _acceleration.setY(y);
}

void Player::setHitpoints(double x){
    _hitpoints=x;
}

double Player::getHitpoints(){
    return _hitpoints;
}

Vector2D Player::getVelocity(){
    return _velocity;
}

Vector2D Player::getAcceleration(){
    return _acceleration;
}

Vector2D Player::getPosition(){
    return _position;
}

void Player::checkInput(int choice){
    int b=player.bmWidth/(2*level+1);
    switch(choice){
        case VK_ESCAPE:
                exit(0);
                break;
        case VK_DELETE:
                break;
        case VK_RIGHT:
                _position.AddTo(Vector2D(10,0));
                break;
        case VK_LEFT:
            _position.AddTo(Vector2D(-10,0));
                break;
        case VK_UP:
            _position.AddTo(Vector2D(0,-10));
            break;
        case VK_DOWN:
            _position.AddTo(Vector2D(0,10));
            break;
        case VK_SPACE:
             _acceleration.setX(0);
            _acceleration.setY(0);
            //EMPIRIJSKI UTVRDJENA VRIJEDNOST OVO 20

            for(int i=1;i<(2*level+1);i+=2)
           //BOG DRAGI SAMO ZNA KAKO SAM DOSO DO OVE RELACIJE AL U BITI SVAKI PUT DODAJE level METAKA KAD SE SPACE PRITISNE
           _shots.push_back(Ammo(_position.getX()+i*b+20-4*level,_position.getY()));
                break;
        default:
            _acceleration.setX(0);
            _acceleration.setY(0);
            break;
    }
    //_velocity=_acceleration;

}

void Player::update(){
    for(int i=0;i<_shots.size();i++){
        if(_shots[i].getPosition().getY()<0)
            _shots.erase(_shots.begin()+i);
        _shots[i].update();
    }
    _position.AddTo(_velocity);
}

void Player::render(HDC hdc){
 HDC hdcMem;
 /*spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);*/


 hdcMem=CreateCompatibleDC(hdc);
 SelectObject(hdcMem,spaceshipBlack);
 BitBlt(hdc,_position.getX(),_position.getY(),player.bmWidth,player.bmHeight,hdcMem,0,0,SRCPAINT);
 SelectObject(hdcMem,spaceshipWhite);
 BitBlt(hdc,_position.getX(),_position.getY(),player.bmWidth,player.bmHeight,hdcMem,0,0,SRCAND);
 for(int i=0;i<_shots.size();i++){
    _shots[i].render(hdc);
  }
  DeleteObject(hdcMem);
}

void Player::print(){
    std::cout<<"Acceleration"<<std::endl;
        _acceleration.print();
    std::cout<<"velocity"<<std::endl;
        _velocity.print();
    std::cout<<"Position"<<std::endl;
        _position.print();
}

void Player::checkForShots(Nemesis& other){
    int x,y,xs,ys;
    x=other.getPosition().getX();
    y=other.getPosition().getY();
    xs=x+160;
    ys=y+100;

    //std::cout<<"State: "<<" "<<x<<" "<<y<<" "<<xs<<" "<<ys<<std::endl;
for(int i=0;i<_shots.size();i++){
        if(_shots[i].getPosition().getX()>=x && _shots[i].getPosition().getX()<=xs){
        if(_shots[i].getPosition().getY()>=y && _shots[i].getPosition().getY()<=ys){
            _shots.erase(_shots.begin()+i);
            other.takeHit();
            }
        }
    }
}

void Player::levelUp(){
    level++;
    _hitpoints+=2;
    _shots.erase(_shots.begin(),_shots.end());
}
#endif // PLAYEROBJECT_H_INCLUDED
