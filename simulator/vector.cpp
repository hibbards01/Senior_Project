/***************************************************
* Program:
*   vector.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will define the vector methods.
***************************************************/

#include "vector.h"
using namespace std;

/*********************************
 * Copy Constructor
 ********************************/
Vector::Vector(const Vector & v)
{
    // Use the assingment operator
    *this = v;
}

/*********************************
 * Operator =
 ********************************/
Vector & Vector::operator = (const Vector & v)
{
    // Assign all the values to this Vector
    this->dx = v.dx;
    this->dy = v.dy;
    this->position = v.position;
    this->angle = v.angle;

    // Finally return this
    return *this;
}

/*********************************
 * changePosition
 *  This will add the vector to
 *      the point.
 ********************************/
void Vector::changePosition()
{
    // Add the vector to the position
    position.addXY(dx, dy);
    return;
}

/*********************************
 * addVectors
 *  This will add the vector to itself
 ********************************/
void Vector::addVectors(const float dx, const float dy)
{
    // Add the vectors!
    this->dx += dx;
    this->dy += dy;
    return;
}

/*******************************************
 * += Operator
 *  Add the two vectors together.
 ******************************************/
Vector & Vector::operator += (const Vector & rhs)
{
    // The vectors together
    this->dx += rhs.dx;
    this->dy += rhs.dy;

    return *this;
}