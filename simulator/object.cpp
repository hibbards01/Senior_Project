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

/***********************************************************
* move
*   Same as the function below.
***********************************************************/
void Object::move(vector<double> & inputs)
{
    if (getIsAlive())
    {
        v.move();
    }

    return;
}

/*********************************
 * move
 *  This will add the vector to the
 *      point.
 ********************************/
void Object::move(const Interface * pUI)
{
    if (getIsAlive())
    {
        // Move the object
        v.move();
    }

    return;
}

/***********************************************************
 ************************* Rock ****************************
 **********************************************************/

/*********************************
 * draw
 *  Draw the rock.
 ********************************/
void Rock::draw()
{
    if (getIsAlive())
    {

        // Draw the rock depending upon the type it is
        if (getType() == PLANET)
        {
            drawCircle(getPoint(), getRadius(), 20, getAngle());
        }
        else if (getType() == ASTEROID)
        {
            drawAsteroid(getPoint(), points, POINTS_FOR_ASTEROID, getAngle());
        }

        rotate(rotationSpeed);
    }

    return;
}

/*******************************************
 * createRock
 *  This will create random points for the
 *      asteroid.
 ******************************************/
void Rock::createRock()
{
    int p = 0;
    if (getType() == ASTEROID)
    {
        points = new int*[POINTS_FOR_ASTEROID];

        for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / POINTS_FOR_ASTEROID)
        {
            points[p] = new int[2];

            points[p][0] = (getRadius() * cos(i)) * random(0.5, 1.0);
            points[p][1] = (getRadius() * sin(i)) * random(0.5, 1.0);

            ++p;
        }

        value = -10;
    }
    else
    {
        points = new int*[POINTS_FOR_PLANET];

        for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / POINTS_FOR_PLANET)
        {
            points[p] = new int[2];

            points[p][0] = (getRadius() * cos(i)) * 0.9;
            points[p][1] = (getRadius() * sin(i)) * 0.9;

            ++p;
        }

        value = -20;
    }

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
    // Draw the ship, make sure it is alive
    if (getIsAlive())
    {
        int x = getPoint().getX();
        int y = getPoint().getY();

        drawBigShip(getPoint(), getAngle());
        // drawRect(Point(x + 0, y + 0), 20, 20, 0);
        // drawRect(Point(x + -20, y + 0), 20, 20, 0);
        // drawRect(Point(x + 0, y + 20), 20, 20, 0);
        // drawRect(Point(x + 0, y + -20), 20, 20, 0);
        // drawRect(Point(x + 20, y + 0), 20, 20, 0);

        // drawRect(Point(x + -20, y + 20), 20, 20, 0);
        // drawRect(Point(x + 20, y + 20), 20, 20, 0);
        // drawRect(Point(x + 20, y + -20), 20, 20, 0);
        // drawRect(Point(x + -20, y + -20), 20, 20, 0);

        // drawRect(Point(x + -40, y + 0), 20, 20, 0);
        // drawRect(Point(x + 0, y + 40), 20, 20, 0);
        // drawRect(Point(x + 0, y + -40), 20, 20, 0);
        // drawRect(Point(x + 40, y + 0), 20, 20, 0);

        // drawRect(Point(x + -40, y + 40), 20, 20, 0);
        // drawRect(Point(x + 40, y + 40), 20, 20, 0);
        // drawRect(Point(x + 40, y + -40), 20, 20, 0);
        // drawRect(Point(x + -40, y + -40), 20, 20, 0);

        // drawRect(Point(x + -40, y + 20), 20, 20, 0);
        // drawRect(Point(x + -20, y + 40), 20, 20, 0);
        // drawRect(Point(x + 20, y + 40), 20, 20, 0);
        // drawRect(Point(x + 40, y + 20), 20, 20, 0);

        // drawRect(Point(x + -40, y + -20), 20, 20, 0);
        // drawRect(Point(x + -20, y + -40), 20, 20, 0);
        // drawRect(Point(x + 20, y + -40), 20, 20, 0);
        // drawRect(Point(x + 40, y + -20), 20, 20, 0);
    }

    return;
}

/*******************************************
 * moveShip
 *    This will move the ship based on the
 *      interactions of the keyboard.
 ******************************************/
void Ship::move(const Interface * pUI)
{
    if (getIsAlive())
    {
        if (fuel > 0)
        {
            // Grab the angle of the ship and change it
            int angle = getAngle();
            setAngle(angle + (pUI->isLeft() * 3) + (pUI->isRight() * -3));

            // Thrust forward the ship if the user pressed the up key.
            if (pUI->isUp())
            {
                // Create the thrust
                Vector thrust;
                thrust.setDx(cos(deg2rad(180 - angle)) * .2);
                thrust.setDy(-sin(deg2rad(180 - angle)) * .2);

                // Add the thrusts together.
                getVector() += thrust;

                // Minus off some fuel
                --fuel;
            }
        }

        // Move the ship
        getVector().move();
    }

    return;
}

/***********************************************************************
* move
*   This will move the ship based off of what the computer gives it.
***********************************************************************/
void Ship::move(vector<double> & inputs)
{
    if (getIsAlive())
    {
        if (fuel > 0)
        {
            // For now only move the ship if the inputs are not zero.
            bool usedFuel = false;

            // Up key
            if (inputs[0] > 0)
            {
                getPoint().addX(-5);
                usedFuel = true;
            }

            // Right Key
            if (inputs[1] > 0)
            {
                getPoint().addY(5);
                usedFuel = true;
            }

            // Down Key
            if (inputs[2] > 0)
            {
                getPoint().addX(5);
                usedFuel = true;
            }

            // Left Key
            if (inputs[3] > 0)
            {
                getPoint().addY(-5);
                usedFuel = true;
            }

            // See if any fuel was used
            if (usedFuel)
            {
                // Add the thrusts together and take off fuel.
                --fuel;
            }
        }

        // Move the ship
        getVector().move();
    }
    return;
}