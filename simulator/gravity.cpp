/***************************************************
* Program:
*   gravity.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will define all the methods for the gravity
*       class.
***************************************************/

#include "gravity.h"
#include <math.h>
using namespace std;

// Set the gravitational constant
double Gravity::gravitationalConstant = .0000000000667;

#define deg2rad(value) ((M_PI / 180) * (value))
#define PI 3.14159265
#define rad2deg(value) (value * 180 / PI)
#define MILLMETERS 1000000
#define METERS5    100000
#define METERS4    10000
#define KILOMETERS 1000

/******************************
 * Non-defualt Constructor
 *****************************/
Gravity::Gravity(list<Object *> & objs)
{
    // Set the objects
    objects = objs;
}

/******************************
 * setWrap
 *  This will make the objects
 *      wrap.
 *****************************/
void Gravity::setWrap(bool wrap)
{
    // See if we will enable wrapping.
    if (wrap)
    {
        // Loop through all the objects and set to true
        for (list<Object *> :: iterator i = objects.begin(); i != objects.end(); ++i)
        {
            (*i)->setWrap(wrap);
        }
    }
    
    return;
}

/****************************************
 * cacluateAcceleration
 *  This will first calulate the force for 
 *      all the objects and then calculate
 *      the acceleration those objects
 *      have on each other.
 ***************************************/
void Gravity::calculateAccerlation()
{
    // First calculate the force between each of the objects
    for (list<Object *> :: iterator obj1 = objects.begin(); obj1 != objects.end(); ++obj1)
    {
        // Make the secound for loop start one before the other object
        list<Object *> :: iterator obj2 = obj1;
        ++obj2;
        for (; obj2 != objects.end(); ++obj2)
        {
            // Find the displacement between the objects
            double xDistance = (*obj2)->getPoint().getX() - (*obj1)->getPoint().getX();
            double yDistance = (*obj2)->getPoint().getY() - (*obj1)->getPoint().getY();
            double d =  sqrt((xDistance * xDistance) + (yDistance * yDistance)) * METERS4;
            
            // Hurry and find their angle
            // This is in radians
            double angle = atan2(yDistance, xDistance);
            
//            cout << "angle = " << angle << endl;
//            cout << "mass = " << (*obj1)->getMass() << endl;
//            cout << "Calculating\n";
//            cout << xDistance << endl;
//            cout << yDistance << endl;
//            cout << rad2deg(angle) << endl;
//            cout << "ending\n";
//            cout << "Displacement = " << d << endl;

            
            // Now calculate the Force between the objects
            //       G * m1 * m2    G = Gravitational Constant N * m^2 / kg^2
            // F  = -------------   d = Distance in meters
            //           d^2        m1, m2 = kg
            double f = (gravitationalConstant * (*obj1)->getMass() * (*obj2)->getMass()) / (d * d);
            
//            cout << "force = " << f << endl;
            
            // Now find the acceleration they have towards each other
            //      F
            // a = ---
            //      m
            double a1 = (f / (*obj1)->getMass()) / METERS4;
            double a2 = (f / (*obj2)->getMass()) / METERS4;
            
//            cout << "a1 = " << a1 << endl;
//            cout << "a2 = " << a2 << endl;

            // Now convert it back to dx and dy
            // Do the first object
            (*obj1)->getVector().addVectors(a1 * cos(angle), a1 * sin(angle));
            
//            float dx = a1 * cos(angle);
//            float dy = a1 * sin(angle);

//            cout << "dx = " << dx << endl
//            << "dy = " << dy << endl;

            // Check if we need to minus or plus 180 for the secound object
            if (angle < 0)
            {
                angle = PI + angle;
            }
            else
            {
                angle = angle - PI;
            }
            
            // Finally add the vectors
            (*obj2)->getVector().addVectors(a2 * cos(angle), a2 * sin(angle));
            
//            dx = a2 * cos(angle);
//            dy = a2 * sin(angle);
//            cout << "dx1 = " << dx << endl
//            << "dy1 = " << dy << endl;
        }
    }

    return;
}

/****************************
 * move
 *  This will first run all
 *      the calculations of
 *      the objects and will
 *      then move them.
 ***************************/
void Gravity::move()
{
    // Calculate gravity!
    calculateAccerlation();
    
    // Loop through all the objects and move them!
    for (list<Object *> :: iterator i = objects.begin(); i != objects.end(); ++i)
    {
        (*i)->move();
    }
    
    return;
}

/****************************
 * draw
 *  This will then draw the
 *      objects.
 ***************************/
void Gravity::draw()
{
    // Loop through all the objects
    for (list<Object *> :: iterator i = objects.begin(); i != objects.end(); ++i)
    {
        (*i)->draw();
    }
    
    return;
}