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
void Object::move(const Interface * pUI)
{
    if (getIsAlive())
    {
        // Move the object
        vector.move();
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
            drawAsteroid(getPoint(), points, POINTS_FOR_ROCK, getAngle());
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
    // Allocate the memory for the points
    points = new int*[POINTS_FOR_ROCK];

    int p = 0;
    if (getType() == ASTEROID)
    {
        for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / POINTS_FOR_ROCK)
        {
            points[p] = new int[2];

            points[p][0] = (getRadius() * cos(i)) * random(0.5, 1.0);
            points[p][1] = (getRadius() * sin(i)) * random(0.5, 1.0);

            ++p;
        }
    }
    else
    {
        for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / POINTS_FOR_ROCK)
        {
            points[p] = new int[2];

            points[p][0] = (getRadius() * cos(i));
            points[p][1] = (getRadius() * sin(i));

            ++p;
        }
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
        drawRect(Point(x + 0, y + 0), 20, 20, 0);
        drawRect(Point(x + -20, y + 0), 20, 20, 0);
        drawRect(Point(x + 0, y + 20), 20, 20, 0);
        drawRect(Point(x + 0, y + -20), 20, 20, 0);
        drawRect(Point(x + 20, y + 0), 20, 20, 0);

        drawRect(Point(x + -20, y + 20), 20, 20, 0);
        drawRect(Point(x + 20, y + 20), 20, 20, 0);
        drawRect(Point(x + 20, y + -20), 20, 20, 0);
        drawRect(Point(x + -20, y + -20), 20, 20, 0);

        drawRect(Point(x + -40, y + 0), 20, 20, 0);
        drawRect(Point(x + 0, y + 40), 20, 20, 0);
        drawRect(Point(x + 0, y + -40), 20, 20, 0);
        drawRect(Point(x + 40, y + 0), 20, 20, 0);

        drawRect(Point(x + -40, y + 40), 20, 20, 0);
        drawRect(Point(x + 40, y + 40), 20, 20, 0);
        drawRect(Point(x + 40, y + -40), 20, 20, 0);
        drawRect(Point(x + -40, y + -40), 20, 20, 0);

        drawRect(Point(x + -40, y + 20), 20, 20, 0);
        drawRect(Point(x + -20, y + 40), 20, 20, 0);
        drawRect(Point(x + 20, y + 40), 20, 20, 0);
        drawRect(Point(x + 40, y + 20), 20, 20, 0);

        drawRect(Point(x + -40, y + -20), 20, 20, 0);
        drawRect(Point(x + -20, y + -40), 20, 20, 0);
        drawRect(Point(x + 20, y + -40), 20, 20, 0);
        drawRect(Point(x + 40, y + -20), 20, 20, 0);
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