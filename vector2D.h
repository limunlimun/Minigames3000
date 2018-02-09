#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED
#include <iostream>
#include <math.h>

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

	private:
    	double _x;
    	double _y;
};

#include"vector2D.h"

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




#endif // VECTOR2D_H_INCLUDED
