#pragma once
#include<iostream>
#include<cmath>

class Shape{
protected: 
    struct point{
        point(): x(0), y(0){}
        point(int x, int y): x(x), y(y){}
        int x;
        int y;
        double getDist(const point& other) const{
            int dx = x - other.x;
            int dy = y - other.y;
            return std::sqrt(dx*dx + dy*dx);
        }
    };
    const point& getPointAtIndex(int index) const;
private:
    point* points;
    int pointsCount;

    void copyFrom(const Shape& other);
    void free();
public:
    Shape(int pointsCount);

    Shape(const Shape& other);
    Shape& operator=(const Shape& other);
    virtual ~Shape(); //!!!!!!

    void setPoint(int pointIndx, int x, int y);

    virtual double getArea() const = 0;
    virtual double getPer() const = 0;
    virtual bool isPointIn(int x, int y) const = 0;
    virtual Shape* clone() const = 0; 
};