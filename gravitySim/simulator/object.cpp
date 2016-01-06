/***************************************************
* Program:
*   object.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will define the object methods.
***************************************************/

#include "object.h"
#include "uiDraw.h"
using namespace std;

/***********************************************************
 ************************* Object **************************
 **********************************************************/

/*********************************
 * move
 *  This will add the vector to the
 *      point.
 ********************************/
void Object::move()
{
    // Move the object
    vector.changePosition();
    return;
}

/***********************************************************
 ************************* Planet **************************
 **********************************************************/

/*********************************
 * draw
 *  Draw the planet.
 ********************************/
void Planet::draw()
{
    // Rotate the planet
//    getVector().rotate(rotationSpeed);
    
    // Draw the planet!
    drawCircle(getPoint(), radius, 8, getVector().getAngle());
    
    return;
}

/***********************************************************
 ************************** Ship ***************************
 **********************************************************/

/*********************************
 * draw
 *  Draw the ship.
 ********************************/
void Ship::draw()
{
    // Draw the ship!
    drawShip(getPoint(), getVector().getAngle());
    return;
}

