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

#define deg2rad(value) ((M_PI / 180) * (value))

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
    drawCircle(getPoint(), radius, 20, getVector().getAngle());

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

/*******************************************
 * moveShip
 *    This will move the ship based on the
 *      interactions of the keyboard.
 ******************************************/
void Ship::moveShip(const Interface * pUI)
{
    // Grab the angle of the ship and change it
    int angle = getAngle();
    setAngle(angle - (pUI->isLeft() * -3) + (pUI->isRight() * 3));

    // Thrust forward the ship if the user pressed the up key.
    if (pUI->isUp())
    {
        // Create the thrust
        Vector thrust;
        thrust.setDx(cos(deg2rad(180 - angle)) * .2);
        thrust.setDy(-sin(deg2rad(180 - angle)) * .2);

        // Add the thrusts together.
        getVector() += thrust;
    }

    return;
}