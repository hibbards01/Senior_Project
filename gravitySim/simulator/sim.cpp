/**************************************************************
* Program
*  sim.cpp
* Author:
*  Samuel Hibbard
* Summary:
*  This will define all the methods for the class Simulator
*************************************************************/

#include "sim.h"
#include "uiDraw.h"
using namespace std;

#define EARTH (5.98 * pow(10, 24))
#define MOON  (7.34 * pow(10, 22))

/********************************
 * Constructor
 *******************************/
Simulator::Simulator()
{
    // Lets create two objects!
    list<Object *> objects;
    
//    objects.push_back(new Planet(200, 0, random(-5, 5), random(-5, 5), 5000, 20, 5));
//    objects.push_back(new Planet(-200, 0, random(-10, 10), random(-10, 10), 500, 10, -10));
    objects.push_back(new Planet(0, 0, 0, 0, EARTH, 20, 5));
    objects.push_back(new Planet(300, 0, 0, 0, MOON, 10, -10));
    objects.push_back(new Planet(-300, 0, 0, 0, MOON, 10, -10));
//    objects.push_back(new Planet(-200, 0, 0, 0, 50, 10, -10));
//    objects.push_back(new Planet(-200, 0, 0, 0, 50, 10, -10));
//    objects.push_back(new Planet(-200, 0, 0, 0, 50, 10, -10));
    
    // Now create the gravity with the objects
    gravity.setObjects(objects);
    gravity.setWrap(true);
}

/********************************
 * run
 *  This will run the Simulator
 *******************************/
void Simulator::run()
{
    // First move the objects.
    gravity.move();
    
    // Now draw them.
    gravity.draw();
    return;
}
