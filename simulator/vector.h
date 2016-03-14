/***************************************************
* Program:
*   vector.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold the vector class.
***************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

/***************************
 * Vector
 *  This will help the
 *      objects to move where
 *      they need to.
 **************************/
class Vector
{
public:
    //
    // Constructor
    //
    Vector() : dx(0.0), dy(0.0), angle(0), position() {}
    Vector(float x, float y, float dx, float dy) : position(x, y), dx(dx), dy(dy), angle(0.0) {}
    Vector(float x, float y, float dx, float dy, float a) : position(x, y), dx(dx), dy(dy), angle(a) {}
    Vector(const Vector & v);

    //
    // Methods
    //
    void changePosition();                           // This will change the point
    void addVectors(const Vector & v);               // This will add two vectors
    void addVectors(const float dx, const float dy);
    Vector & operator = (const Vector & v);          // Assingment operator
    Vector & operator += (const Vector & rhs);       // += operator
    void rotate(int rotate) { angle += rotate; }

    //
    // Getters
    //
    float getDx()    const { return dx;       }
    float getDy()    const { return dy;       }
    int   getAngle() const { return angle;    }
    Point getPoint() const { return position; }

    //
    // Setters
    //
    void setDx(float dx)         { this->dx = dx;          }
    void setDy(float dy)         { this->dy = dy;          }
    void setAngle(float a)       { this->angle = a;        }
    void setPosition(Point & pt) { this->position = pt;    }
    void setWrap(bool wrap)      { position.setWrap(wrap); }
private:
    float dx;
    float dy;
    int angle;
    Point position;
};

#endif /* VECTOR_H */
