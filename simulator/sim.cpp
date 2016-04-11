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
#include <cassert>
#include "uiDraw.h"
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
Simulator::Simulator() : objects(), graphics(), time(100), timer(30)
{
    // Set the distance for each pixel
    distance = CUSTOM;
    // distance = MILLMETERS;
    // distance = METERS4;

    // Standard earth and moon
    // objects.push_back(new Rock(0, 0, 0, 0, EARTH, 30, 5));
    // objects.push_back(new Rock(0, 280, 1.2, 0, MOON, 15, -10));

    // Two earths
    // objects.push_back(new Rock(-250, 0, 0, 0.5, EARTH, 30, 5));
    // objects.push_back(new Rock(250, 0, 0, -0.5, EARTH, 30, 5));

    // Create the ship. The ship will always be the first object
    // The collision function will use that assumption.
    // ************ WARNING ************
    // If changed then the logic will break.
    objects.push_back(new Ship(650, -350, SHIPW, 4));

    // Sun and Jupiter
    objects.push_back(new Rock(0, 0, 0, 0, SUN, 70, 0, PLANET));
    objects.push_back(new Rock(200, 0, 0, 3.5, JUPITER, 40, 0, PLANET));
    objects.push_back(new Rock(300, 0, 0, 2.5, SATURN, 30, 0, PLANET));
    objects.push_back(new Rock(-375, 0, 0, 2.5, EARTH, 20, 0, PLANET));
    objects.push_back(new Rock(-390, 0, 0, 2.0, MOON, 15, 0, PLANET));

    // Create some asteroids!
    objects.push_back(new Rock(0, -350, 1.7, 0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(-350, -350, 1.8, 0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(-350, 350, 1.8, 0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(350, 350, 0.0, -1.7, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(350, -350, 0.0, 1.8, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(100, 50, -4.0, 4.0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(-100, 50, 4.0, 4.0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(100, -50, -4.0, -4.0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(-100, -50, -4.0, 4.0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(200, 200, -3.0, 0.0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(200, -200, 0.0, 3.0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(-200, 200, 3.0, 0.0, ASTEROIDW, 10, 5, ASTEROID));
    objects.push_back(new Rock(-200, -200, 3.0, 0.0, ASTEROIDW, 10, 5, ASTEROID));

    for (int i = 0; i < 40; ++i)
    {
        objects.push_back(new Rock(random(-700, 700),
                                    random(-400, 400),
                                    random(-3.0, 3.0),
                                    random(-3.0, 3.0), ASTEROIDW, 10, 5, ASTEROID));
    }
}

/*******************************************
 * Destructor
 ******************************************/
Simulator::~Simulator()
{
    // Delete all the pointers in the object list
    list<Object *> :: iterator i = objects.begin();
    while (i != objects.end())
    {
        delete *i;
        i = objects.erase(i);
    }
}

/**************************************************
 * cacluateAcceleration
 *  This will first calculate the force for all the
 *      objects and then calculate the acceleration
 *      those objects have on each other.
 *************************************************/
void Simulator::calculateAccerlation()
{
    // First calculate the force between each of the objects
    for (list<Object *> :: iterator obj1 = objects.begin(); obj1 != objects.end(); ++obj1)
    {
        // Make the second for loop start one before the other object
        list<Object *> :: iterator obj2 = obj1;
        ++obj2;
        for (; obj2 != objects.end(); ++obj2)
        {
            // Find the displacement between the objects
            double xDistance = (*obj2)->getPoint().getX() - (*obj1)->getPoint().getX();
            double yDistance = (*obj2)->getPoint().getY() - (*obj1)->getPoint().getY();
            double d =  sqrt((xDistance * xDistance) + (yDistance * yDistance)) * distance;

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
            double a1 = (f / (*obj1)->getMass()) / distance;
            double a2 = (f / (*obj2)->getMass()) / distance;

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

            // Check if we need to minus or plus 180 for the second object
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

/*******************************************
 * checkCollision
 *  This will loop through all the objects
 *      and check to see if any of the objects
 *      have hit the ship. If so then we need
 *      to kill the ship. This will use the
 *      difference operator in the vector
 *      class to see if the object has hit
 *      the ship.
 ******************************************/
void Simulator::checkCollision()
{
    // Grab the ship object and check if it is alive
    list<Object*> :: iterator ship = objects.begin();

    if ((*ship)->getIsAlive())
    {
        // Make sure it is a SHIP
        assert((*ship)->getType() == SHIP);

        // Loop through all the objects to see if any have hit
        // the ship. If so then kill the ship.
        list<Object*> :: iterator o = objects.begin();

        // Increment once to skip the ship.
        ++o;
        for (; o != objects.end(); ++o)
        {
            if (((*ship)->getVector() - (*o)->getVector()) < ((*ship)->getSize() + (*o)->getSize()))
            {
                (*ship)->kill();
            }
        }
    }

    return;
}

/**************************************************
 * move
 *  This will first run all the calculations of the
 *      objects and will then move them.
 *************************************************/
void Simulator::move(const Interface * pUI)
{
    // Calculate gravity!
    calculateAccerlation();

    // Loop through all the objects and move them!
    for (list<Object *> :: iterator i = objects.begin(); i != objects.end(); ++i)
    {
        (*i)->move(pUI);
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

    // Now draw the graphics
    Ship * ship = (Ship *) objects.front();

    // Make sure it is a SHIP
    assert(ship->getType() == SHIP);

    // Now grab the fuel and the distance of the ship
    graphics.draw(ship->getFuel(), ship->getDistance(), time);

    if (--timer == 0)
    {
        --time;
        timer = 30;
    }

    return;
}

/********************************
 * run
 *  This will run the Simulator
 *******************************/
void Simulator::run(const Interface * pUI)
{
    // First move the objects.
    move(pUI);

    // Check if a collision has happened
    checkCollision();

    // Now draw them.
    draw();

    return;
}