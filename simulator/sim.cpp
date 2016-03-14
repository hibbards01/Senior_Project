/**************************************************************
* Program
*  sim.cpp
* Author:
*  Samuel Hibbard
* Summary:
*  This will define all the methods for the class Simulator
*************************************************************/

#include "sim.h"
#include "defines.h"
#include <math.h>
using namespace std;

// For debugging purposes.
// To run debug code run in command line: g++ -DDEBUG <file>
#ifdef DEBUG
#define Debug(x) x
#else
#define Debug(x)
#endif

/********************************
 * Constructor
 *******************************/
Simulator::Simulator()
{
//    objects.push_back(new Planet(200, 0, random(-5, 5), random(-5, 5), 5000, 20, 5));
//    objects.push_back(new Planet(-200, 0, random(-10, 10), random(-10, 10), 500, 10, -10));
    objects.push_back(new Planet(0, 0, 0, 0, EARTH, 20, 5));
    objects.push_back(new Planet(0, 280, 1.2, 0, MOON, 10, -10));
    objects.push_back(new Ship(0, 100, SHIP, 10));
    // objects.push_back(new Planet(-300, 0, 0, 0, MOON, 10, -10));
//    objects.push_back(new Planet(-200, 0, 0, 0, 50, 10, -10));
//    objects.push_back(new Planet(-200, 0, 0, 0, 50, 10, -10));
//    objects.push_back(new Planet(-200, 0, 0, 0, 50, 10, -10));
}

/**************************************************
 * cacluateAcceleration
 *  This will first calulate the force for all the
 *      objects and then calculate the acceleration
 *      those objects have on each other.
 *************************************************/
void Simulator::calculateAccerlation()
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

#ifdef DEBUG
            cout << "--------DEBUG CODE FOR sim.cpp #1--------\n";
            cout << "angle = " << angle << endl;
            cout << "mass = " << (*obj1)->getMass() << endl;
            cout << "Calculating\n";
            cout << xDistance << endl;
            cout << yDistance << endl;
            cout << rad2deg(angle) << endl;
            cout << "ending\n";
            cout << "Displacement = " << d << endl;
            cout << "--------END OF DEBUG--------\n";
#endif

            // Now calculate the Force between the objects
            //       G * m1 * m2    G = Gravitational Constant N * m^2 / kg^2
            // F  = -------------   d = Distance in meters
            //           d^2        m1, m2 = kg
            double f = (gravitationalConstant * (*obj1)->getMass() * (*obj2)->getMass()) / (d * d);

#ifdef DEBUG
            cout << "--------DEBUG CODE FOR sim.cpp #2--------\n";
            cout << "force = " << f << endl;
            cout << "--------END OF DEBUG--------\n";
#endif

            // Now find the acceleration they have towards each other
            //      F
            // a = ---
            //      m
            double a1 = (f / (*obj1)->getMass()) / METERS4;
            double a2 = (f / (*obj2)->getMass()) / METERS4;

#ifdef DEBUG
            cout << "--------DEBUG CODE FOR sim.cpp #3--------\n";
            cout << "a1 = " << a1 << endl;
            cout << "a2 = " << a2 << endl;
            cout << "--------END OF DEBUG--------\n";
#endif

            // Now convert it back to dx and dy
            // Do the first object
            (*obj1)->getVector().addVectors(a1 * cos(angle), a1 * sin(angle));

#ifdef DEBUG
            cout << "--------DEBUG CODE FOR sim.cpp #4--------\n";
            float dx = a1 * cos(angle);
            float dy = a1 * sin(angle);

            cout << "dx = " << dx << endl
                 << "dy = " << dy << endl;
            cout << "--------END OF DEBUG--------\n";
#endif

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
        }
    }

    return;
}

/**************************************************
 * move
 *  This will first run all the calculations of the
 *      objects and will then move them.
 *************************************************/
void Simulator::move()
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

/**************************************************
 * draw
 *  This will then draw the objects.
 *************************************************/
void Simulator::draw()
{
    // Loop through all the objects
    for (list<Object *> :: iterator i = objects.begin(); i != objects.end(); ++i)
    {
        (*i)->draw();
    }

    return;
}

/*******************************************
 * interact
 *  This will take the interactions of the
 *      keyboard and tell the objects what
 *      to do.
 ******************************************/
void Simulator::interact(const Interface * pUI)
{
    return;
}

/********************************
 * run
 *  This will run the Simulator
 *******************************/
void Simulator::run(const Interface * pUI)
{
    // First move the objects.
    move();

    // Handle the user's input
    interact(pUI);

    // Now draw them.
    draw();

    return;
}