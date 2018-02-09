#ifndef SOLDIEROBJECT_H_INCLUDED
#define SOLDIEROBJECT_H_INCLUDED
#include"ft/vector2D.h"
#include"constantsTank.h"
class Soldier{
   private:
        Vector2D _position;
        Vector2D _velocity;
        Vector2D _acceleration;
        int _hitpoints;
        std::vector<POINT> _shots;
        //HBITMAP SoldierWhite;
        //HBITMAP SoldierBlack;
        //BITMAP bmp;
    public:
        //konstruktori
        Soldier();
        Soldier(double,double);
        Soldier(const Soldier&);
        ~Soldier();
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
        void checkInput(int);
        void print();
};

Soldier::Soldier(){
    //SoldierWhite=(HBITMAP)LoadImage(NULL,"Soldier1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //SoldierBlack=(HBITMAP)LoadImage(NULL,"Soldier1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
//  GetObject(SoldierBlack,sizeof(BITMAP),&bmp);
    _position=Vector2D(0,0);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    _hitpoints=4;

}

Soldier::Soldier(double x,double y){
    //SoldierWhite=(HBITMAP)LoadImage(NULL,"Soldier1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //SoldierBlack=(HBITMAP)LoadImage(NULL,"Soldier1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
//  GetObject(SoldierBlack,sizeof(BITMAP),&bmp);
    _position=Vector2D(x,y);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    _hitpoints=4;
}

Soldier::Soldier(const Soldier& other){
    _position=other._position;
    _velocity=other._velocity;
    _acceleration=other._acceleration;
}
Soldier::~Soldier(){
//    DeleteObject(SoldierWhite);
  //  DeleteObject(SoldierBlack);
}
void Soldier::setVelocity(double x,double y){
    _velocity.setX(x);
    _velocity.setY(y);
}

void Soldier::setPosition(double x,double y){
    _position.setX(x);
    _position.setY(y);
}

void Soldier::setAcceleration(double x,double y){
    _acceleration.setX(x);
    _acceleration.setY(y);
}

Vector2D Soldier::getVelocity(){
    return _velocity;
}

Vector2D Soldier::getAcceleration(){
    return _acceleration;
}

Vector2D Soldier::getPosition(){
    return _position;
}

double Soldier::getHeight(){

    return bmp.bmHeight;
}

double Soldier::getWidth(){

    return bmp.bmWidth;
}

void Soldier::update(){
    _position.AddTo(_velocity);
//    for(int i=0;i<_shots.size();i++)
  //      _shots[i].AddTo(Vector2D(0,2));
   j=(j+1)%8;
   for(int i=0;i<_shots.size();i++){
        if(_shots[i].x>0)
            _shots[i].x=_shots[i].x-4+amInc;
        else
            _shots.erase(_shots.begin()+i);
   }
   amInc=0;
}

void Soldier::render(HDC hdc){
 HDC hdcMem;

 /*SoldierWhite=(HBITMAP)LoadImage(NULL,"Soldier1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 SoldierBlack=(HBITMAP)LoadImage(NULL,"Soldier1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
*/

 hdcMem=CreateCompatibleDC(hdc);
 SelectObject(hdcMem,soldierBlack);
 BitBlt(hdc,_position.getX(),_position.getY(),soldier.bmWidth,soldier.bmHeight/7,hdcMem,0,j*soldier.bmHeight/7,SRCPAINT);
 SelectObject(hdcMem,soldierWhite);
 BitBlt(hdc,_position.getX(),_position.getY(),soldier.bmWidth,soldier.bmHeight/7,hdcMem,0,j*soldier.bmHeight/7,SRCAND);

 for(int i=0;i<_shots.size();i++){
    SelectObject(hdcMem,flowerBlack);
    BitBlt(hdc,_shots[i].x,_shots[i].y,flower.bmWidth,flower.bmHeight,hdcMem,0,0,SRCPAINT);
    SelectObject(hdcMem,flowerWhite);
    BitBlt(hdc,_shots[i].x,_shots[i].y,flower.bmWidth,flower.bmHeight,hdcMem,0,0,SRCAND);
 }


 DeleteObject(hdcMem);


}

void Soldier::print(){
    std::cout<<"Acceleration"<<std::endl;
        _acceleration.print();
    std::cout<<"velocity"<<std::endl;
        _velocity.print();
    std::cout<<"Position"<<std::endl;
        _position.print();
}

void Soldier::takeHit(){
    --_hitpoints;
}

void Soldier::setHitpoints(int h){
    _hitpoints=h;
}

int Soldier::getHitPoints(){
    return _hitpoints;
}

void Soldier::shoot(){
//    _shots.push_back(Vector2D(_position.getX()+SoldierAmmo.bmWidth/2,_position.getY()+SoldierAmmo.bmHeight));
   // std::cout<<"Shots fired: "<<_shots.size()<<std::endl;
   POINT newShot;
   newShot.x=_position.getX();
   newShot.y=_position.getY()+20;

   _shots.push_back(newShot);
}


int Soldier::checkForHits(int x,int y){
    int ret=0;
    for(int i=0;i<_shots.size();i++){
        if(_shots[i].x>x && _shots[i].x<x+bmp2.bmWidth-80 &&_shots[i].y>y && _shots[i].y<y+bmp2.bmHeight/6-100){
            ret++;
            _shots.erase(_shots.begin()+i);
        }
    }
    return ret;

}

void Soldier::checkInput(int choice){
    //int b=Tank.bmWidth/(2*level+1);
    switch(choice){
        case VK_ESCAPE:
                exit(0);
                break;
        case VK_DELETE:
                break;
        case VK_RIGHT:
             i++;
             i=i%6;
            if(moveForward)
                _position.AddTo(Vector2D(-6,0));
                amInc=-10;
                break;
        case VK_LEFT:
             i++;
             i=i%6;
            _position.AddTo(Vector2D(6,0));
            //amInc=10;
                break;
        default:
            _acceleration.setX(0);
            _acceleration.setY(0);
            break;
    }
    //_velocity=_acceleration;

}
#endif // SOLDIEROBJECT_H_INCLUDED
