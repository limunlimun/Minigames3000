
#include <iostream>
#include <math.h>
#include<vector>
class Vector2D
{
	public:
    	Vector2D();
    	virtual ~Vector2D();
    	Vector2D(double x, double y);
    	Vector2D(const Vector2D&);
    	void SetAngle(double angle);  // postavlja _x i _y projekcije zavisno od ugla (angle)
    	double GetAngle(); // vraća trenutnu vrijednost ugla u radijanima, koristeći projekcije _x i _y
    	void SetLength(double length); // postavlja _x i _y projekcije zavisno od dužine (length)
    	double GetLength(); // vraća trenutnu dužinu vektora, koristeći projekcije _x i _y
    	Vector2D Add(const Vector2D& other); // dodaje vektor other na trenutni i vraća novi vektor
    	Vector2D Substract(const Vector2D& other); // oduzima trenutni vektor od vektora other i vraća novi vektor
    	Vector2D Multiply(int value); // množi trenutni vektor sa konstantom value i vraća novi vektor
    	Vector2D Divide(int value); // dijeli trenutni vektor sa konstantom i vraća novi vektor
    	void AddTo(const Vector2D& other); // dodaje vektor other na trenutni
    	void SubstractFrom(const Vector2D& other); // oduzima vektor other od trenutnog
	    void MultiplyBy(int value);   // množi trenutni vektor sa skalarom value
    	void DivideBy(int value); // dijeli trenutni vektor sa skalarom value
    	//MOJI METODI
    	void operator=(const Vector2D&);
        void print();

        Vector2D operator+(const Vector2D&);
        //NAMJERNO ODRADJENO SUPROTNO OD SUBSTRACT JER JE LOGICNIJE DA IDE (PRVI - DRUGI)
        Vector2D operator-(const Vector2D&);
        Vector2D operator*(double);
        Vector2D operator/(double);
        //getters and setters
        inline double getX();
        inline double getY();
        inline void setX(double);
        inline void setY(double);
        void operator+=(const Vector2D&);
        void operator-=(const Vector2D&);
        void operator*=(double);
        void operator/=(double);
        inline void randomize(int);
        friend std::ostream& operator<<(std::ostream&,const Vector2D);

//	private:
    	double _x;
    	double _y;
};

class Ammo{
    //private:
    public:
        //HBITMAP _ammoWhite;
        //HBITMAP _ammoBlack;
        //BITMAP _ammoInfo;
        Vector2D _position;
        Vector2D _velocity;
        Vector2D _acceleration;
    //public:
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



class Nemesis{
   //private:
   public:
        Vector2D _position;
        Vector2D _velocity;
        Vector2D _acceleration;
        int _hitpoints;
        std::vector<Vector2D> _shots;
        //HBITMAP nemesisWhite;
        //HBITMAP nemesisBlack;
        //BITMAP bmp;
    //public:
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



class Player{
   //private:
   public:
        Vector2D _position;
        Vector2D _velocity;
        Vector2D _acceleration;
        int _hitpoints;
        int level;
        //HBITMAP spaceshipWhite;
        //HBITMAP spaceshipBlack;
        //BITMAP player;
        std::vector<Ammo> _shots;
     //public:
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









Vector2D::Vector2D(){
    _x=0;
    _y=0;
}

Vector2D::~Vector2D(){

}

Vector2D::Vector2D(double x,double y){
    _x=x;
    _y=y;
}

Vector2D::Vector2D(const Vector2D& o){
    _x=o._x;
    _y=o._y;
}

void Vector2D::operator=(const Vector2D& o){
    _x=o._x;
    _y=o._y;
}

void Vector2D::SetAngle(double angle){
    _x=cos(angle);
    _y=sin(angle);
}

double Vector2D::GetAngle(){
    return atan(_x/_y);
}

void Vector2D::SetLength(double length){
    _x=length*cos(length);
    _y=length*sin(length);
}

double Vector2D::GetLength(){
    return sqrt(pow(_x,2)+pow(_y,2));
}

Vector2D Vector2D::Add(const Vector2D& other){
    Vector2D r(other._x+_x,other._y+_y);
    return r;
}

Vector2D Vector2D::Substract(const Vector2D& other){
    Vector2D r(other._x-_x,other._y-_y);
    return r;
}

Vector2D Vector2D::Multiply(int value){
    Vector2D r(_x*value,_y*value);
    return r;
}

Vector2D Vector2D::Divide(int value){
    Vector2D r(_x/value,_y/value);
    return r;
}

void Vector2D::AddTo(const Vector2D& other){
    _x=_x+other._x;
    _y=_y+other._y;

}

void Vector2D::SubstractFrom(const Vector2D& other){
    _x-=other._x;
    _y-=other._y;
}

void Vector2D::MultiplyBy(int value){
    _x*=value;
    _y*=value;
}

void Vector2D::DivideBy(int value){
    _x/=value;
    _y/=value;
}
void Vector2D::print(){
    std::cout<<"x: "<<_x<<"\ty: "<<_y<<std::endl;
}

Vector2D Vector2D::operator+(const Vector2D& o){
    Vector2D ret(_x+o._x,_y+o._y);
    return ret;
}

Vector2D Vector2D::operator-(const Vector2D& o){
    Vector2D ret(_x-o._x,_y-o._y);
    return ret;
}

Vector2D Vector2D::operator*(double val){
    Vector2D ret(_x*val,_y*val);
    return ret;
}

Vector2D Vector2D::operator/(double val){
    Vector2D ret(_x/val,_y/val);
    return ret;
}

void Vector2D::operator+=(const Vector2D& other){
    AddTo(other);
}

void Vector2D::operator-=(const Vector2D& other){
    SubstractFrom(other);
}

void Vector2D::operator*=(double val){
    MultiplyBy(val);
}

void Vector2D::operator/=(double val){
    DivideBy(val);
}

std::ostream& operator<<(std::ostream& out,const Vector2D other){
    out<<"x: "<<other._x<<"\ty: "<<other._y;
    return out;
}

void Vector2D::setX(double x){
    _x=x;
}

void Vector2D::setY(double y){
    _y=y;
}

double Vector2D::getX(){
    return _x;
}

double Vector2D::getY(){
    return _y;
}

void Vector2D::randomize(int koef){
    int a=rand();
    _x=((int)(pow(-1,a)*a)%koef)*0.05;
    a=rand();
    _y=((int)(pow(-1,a)*a)%koef)*0.05;
    if(_x==0 && _y==0){
        //std::cout<<"Zeroed in"<<std::endl;
        while(_x==0 && _y==0){
                 a=rand();
            _x=((int)(pow(-1,a)*a)%koef)*0.05;
             a=rand();
            _y=((int)(pow(-1,a)*a)%koef)*0.05;
        }
    }

}

/////////////////////
static HBITMAP nemesisWhite;
static HBITMAP nemesisBlack;
static HBITMAP spaceshipWhite;
static HBITMAP spaceshipBlack;
static HBITMAP _ammoWhite;
static HBITMAP _ammoBlack;
static HBITMAP _nemAmmoBlack;
static HBITMAP _nemAmmoWhite;
static HBITMAP nemAmmo;
static HBITMAP nemAmmoBlack;
static HBITMAP background;
static int correction=5;
static BITMAP _ammoInfo;
static BITMAP player;
static BITMAP bmp;
static BITMAP nemesisAmmo;
static BITMAP back;
static BITMAP bitmapbackground;
static RECT clientRect;
static int numNem=0;
static int kills=0;
//BITNO ZA LEVEL UP
static bool l1=true;
static bool l2=true;
static bool l3=true;
static bool l4=true;

void draw(HWND);
void runSetup();
void drawBackground(HDC hdc);
void drawHealthBar(HDC hdc);
void update();
void generateNewNemesii();
static Nemesis nemesii[200];
static Player play;
static HBRUSH gr=CreateSolidBrush(RGB(0,255,0));


//////////////////////////////////////////////////////

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
    //GetObject(_ammoBlack,sizeof(BITMAP),&_ammoInfo);
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



Player::Player(){
    //spaceshipWhite=(HBITMAP)LoadImage(NULL,"spaceship1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //spaceshipBlack=(HBITMAP)LoadImage(NULL,"spaceship1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    _position=Vector2D(0,0);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    //GetObject(spaceshipBlack,sizeof(BITMAP),&player);
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
//metod uklopljen u draw funkciju
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
//////////////////////////////////////////////////////














Nemesis::Nemesis(){
    //nemesisWhite=(HBITMAP)LoadImage(NULL,"nemesis1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //nemesisBlack=(HBITMAP)LoadImage(NULL,"nemesis1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
  //GetObject(nemesisBlack,sizeof(BITMAP),&bmp);
    _position=Vector2D(0,0);
    _velocity=Vector2D(0,0);
    _acceleration=Vector2D(0,0);
    _hitpoints=4;

}

Nemesis::Nemesis(double x,double y){
    //nemesisWhite=(HBITMAP)LoadImage(NULL,"nemesis1White.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 //nemesisBlack=(HBITMAP)LoadImage(NULL,"nemesis1Black.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
  //GetObject(nemesisBlack,sizeof(BITMAP),&bmp);
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


//////////////////////////////////////////////////////////////






void drawHealthBar(HDC hdc){
    //metod prebacen u draw
    /*int i=play.getHitpoints();
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
    TextOut(hdc,clientRect.right-slen*9,clientRect.bottom-70,disp.c_str(),slen);*/
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





