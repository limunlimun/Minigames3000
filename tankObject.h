#ifndef TANKOBJECT_H_INCLUDED
#define TANKOBJECT_H_INCLUDED
#include "constantsTank.h"
#include"ft/vector2D.h"
class Tank{
   private:
        Vector2D _position;
        Vector2D _velocity;
        Vector2D _acceleration;
        int _hitpoints;
        int level;
        double fuel;
        //HBITMAP spaceshipWhite;
        //HBITMAP spaceshipBlack;
        //BITMAP Tank;
        std::vector<POINT> _shots;
     public:
        //konstruktori
        Tank();
        Tank(double,double);
        Tank(const Tank&);
        ~Tank();

        //seteri i geteri
        void setVelocity(double,double);
        void setPosition(double,double);
        void setAcceleration(double,double);
        void setHitpoints(double);
        void setFuel(double);
        double getHitpoints();
        Vector2D getVelocity();
        Vector2D getPosition();
        Vector2D getAcceleration();
        double getFuel();

        //gameObject metodi
        void checkInput(int);
        void update();
        void render(HDC);
        bool checkForHits(double,double);
        void print();
};

Tank::Tank(){
    //spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    _position=Vector2D(0,0);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    _hitpoints=5;
     level=1;
     fuel=100;

}

Tank::Tank(double x,double y){
   // spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    _position=Vector2D(x,y);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    _hitpoints=5;
     //GetObject(spaceshipBlack,sizeof(BITMAP),&Tank);
     level=1;
     fuel=100;

}

Tank::Tank(const Tank& other){
    _position=other._position;
    _velocity=other._velocity;
    _acceleration=other._acceleration;
    _hitpoints=5;
    level=1;
}
Tank::~Tank(){
    DeleteObject(tankWhite);
    DeleteObject(tankBlack);
}
void Tank::setVelocity(double x,double y){
    _velocity.setX(x);
    _velocity.setY(y);
}

void Tank::setPosition(double x,double y){
    _position.setX(x);
    _position.setY(y);
}

void Tank::setAcceleration(double x,double y){
    _acceleration.setX(x);
    _acceleration.setY(y);
}

void Tank::setHitpoints(double x){
    _hitpoints=x;
}

double Tank::getHitpoints(){
    return _hitpoints;
}

Vector2D Tank::getVelocity(){
    return _velocity;
}

Vector2D Tank::getAcceleration(){
    return _acceleration;
}

Vector2D Tank::getPosition(){
    return _position;
}

void Tank::checkInput(int choice){
    //int b=Tank.bmWidth/(2*level+1);
    switch(choice){
        case VK_UP:
            _velocity=Vector2D(1,-8);
            break;

        case VK_SPACE:
             _acceleration.setX(0);
            _acceleration.setY(0);
            //EMPIRIJSKI UTVRDJENA VRIJEDNOST OVO 20
            POINT newShot;
            newShot.x=_position.getX()+bmp2.bmWidth-50;
            newShot.y=_position.getY()+bmp2.bmHeight/12-20;
            _shots.push_back(newShot);

            //std::cout<<"Shot no:"<<_shots.size()<<" x: "<<newShot.x<<" y: "<<newShot.y<<std::endl;
             break;
        default:
            _acceleration.setX(0);
            _acceleration.setY(0);
            break;
    }
    //_velocity=_acceleration;

}
bool fall=false;
void Tank::update(){
    /*for(int i=0;i<_shots.size();i++){
        if(_shots[i].getPosition().getY()<0)
            _shots.erase(_shots.begin()+i);
        _shots[i].update();
    }
    _position.AddTo(_velocity);*/

    if(fuel>0)
    fuel-=0.05;
    for(int i=0;i<_shots.size();i++){
            //std::cout<<"Shot no:"<<_shots.size()<<" x: "<<_shots[i].x<<" y: "<<_shots[i].y<<std::endl;
        if(_shots[i].x<clientRect.right)
        _shots[i].x+=4+amInc;
        else{
            _shots.erase(_shots.begin()+i);
            //std::cout<<"Shot: "<<i<<" erased!"<<std::endl;
        }
    }
    amInc=0;
    if(_position.getY()<100){
    _velocity=Vector2D(1,4);
    fall=true;
    }
    //std::cout<<"Fall: "<<clientRect.bottom-bmp.bmHeight/6<<std::endl;
   //uradi tako da u 4 frejma padne nazad
    if(_position.getY()==clientRect.bottom-bmp2.bmHeight/6+30 && fall){
        _velocity=Vector2D(-0.5,0);
        _position.AddTo(Vector2D(-40,0));
        fall=false;
        //_position.setY(clientRect.bottom-bmp.bmHeight/6);
    }
        //if(_position.getY()==clientRect.bottom-bmp.bmHeight/6)
          //  fall=false;
    _position.AddTo(_velocity);
}

void Tank::render(HDC hdc){
 HDC hdcMem;
 hdcMem=CreateCompatibleDC(hdc);
 SelectObject(hdcMem,tankBlack);
 BitBlt(hdc,_position.getX(),_position.getY(),bmp2.bmWidth,bmp2.bmHeight/6,hdcMem,0,i*bmp2.bmHeight/6,SRCPAINT);
 SelectObject(hdcMem,tankWhite);
 BitBlt(hdc,_position.getX(),_position.getY(),bmp2.bmWidth,bmp2.bmHeight/6,hdcMem,0,i*bmp2.bmHeight/6,SRCAND);

 for(int i=0;i<_shots.size();i++){
    SelectObject(hdcMem,heartBlack);
    BitBlt(hdc,_shots[i].x,_shots[i].y,heart.bmWidth,heart.bmHeight,hdcMem,0,0,SRCPAINT);
    SelectObject(hdcMem,heartWhite);
    BitBlt(hdc,_shots[i].x,_shots[i].y,heart.bmWidth,heart.bmHeight,hdcMem,0,0,SRCAND);
 }
 SelectObject(hdc,br);
 Rectangle(hdc,0,0,fuel*5,20);
  SelectObject(hdc,red);
  for(int i=0;i<_hitpoints;i++){
    Rectangle(hdc,i*30,30,(i+1)*30,60);
 }
 DeleteObject(hdcMem);

}

void Tank::print(){
    std::cout<<"Acceleration"<<std::endl;
        _acceleration.print();
    std::cout<<"velocity"<<std::endl;
        _velocity.print();
    std::cout<<"Position"<<std::endl;
        _position.print();
}


void Tank::setFuel(double f){
    fuel=f;
}

double Tank::getFuel(){
    return fuel;
}

bool Tank::checkForHits(double ox,double oy){
    for(int i=0;i<_shots.size();i++){
        if(_shots[i].x>ox && _shots[i].x<ox+soldier.bmWidth){
            //if(_shots[i].y>oy && _shots[i].y<oy+soldier.bmHeight/7){
               // std::cout<<"TRUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"<<std::endl;
                _shots.erase(_shots.begin()+i);
                return true;
            //}
        }
    }
    return false;
}

#endif // TANKOBJECT_H_INCLUDED
