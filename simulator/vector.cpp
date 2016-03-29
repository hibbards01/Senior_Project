
/***************************************************
* Program:
*   vector.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will define the vector methods.
***************************************************/

#include "vector.h"
#include <iostream>
#include <math.h>       // sqrtf
#include <limits>       // numeric_limits
#include <algorithm>    // max
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
 * move
 *  This will add the vector to
 *      the point.
 ********************************/
void Vector::move()
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

/*******************************************
 * findMax
 *  This is only needed for the function
 *      below this one. Find the number
 *      that is the max.
 ******************************************/
float findMax(float a, float b, float c, float d)
{
    // Loop through each of the values
    float maxDist = abs((long)max(a, b));
    maxDist = abs((long)max(maxDist, c));
    maxDist = abs((long)max(maxDist, d));

    return maxDist;
}

/*******************************************
 * - operator
 *  This will take two vectors and find the
 *      shortest distance between them and return
 *      a number.
 ******************************************/
float Vector::operator - (const Vector & rhs)
{
    float max = findMax(this->dx, this->dy, rhs.dx, rhs.dy);

    float slice = 1.0 / max;

    float minDist = numeric_limits<float>::max();

    for (float percent = 0.0; percent <= 1.0; percent += slice)
    {
        float x = (this->position.getX() + this->dx * percent) - (rhs.position.getX() + rhs.dx * percent);
        float y = (this->position.getY()  + this->dy * percent) - (rhs.position.getY() + rhs.dy * percent);

        //              c^2   =   a^2   +   b^2
        float distanceSquared = (x * x) + (y * y);

        minDist = min(distanceSquared, minDist);
    }

    return sqrtf(minDist);
}

/*******************************************
 * Insertion Operator
 *  Output the member variables of the Vector.
 ******************************************/
ostream & operator << (ostream & out, const Vector & rhs)
{
    out << "*************Vector variables*****************\n"
        << "Point " << rhs.getPoint() << endl
        << "Vector (" << rhs.getDx() << ", " << rhs.getDy() << ")\n"
        << "Angle = " << rhs.getAngle() << endl
        << "******************END*************************\n";
    return out;
}