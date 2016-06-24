/*************************************************************
* Program:
*   objects.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will contain the class Objects. Also it will include
*     all the other classes that inherit from Objects.
*************************************************************/

#ifndef OBJECTS_H
#define OBJECTS_H

#include "vector.h"
#include "uiInteract.h"
#include "defines.h"
#include <vector>

// ENUM for the type of objects
enum {NOTHING, SHIP, PLANET, ASTEROID};

/**********************************
 * Objects
 *  This will contain all the base
 *    variables for all the objects
 *********************************/
class Object
{
public:
    //
    // Constructors
    //
    Object() : v(), mass(0.0), alive(true) { /* v.getPoint().setWrap(true); */ }
    Object(float x, float y, float dx, float dy, double m, int r) :
        v(x, y, dx, dy), mass(m), alive(true), radius(r) { /* v.getPoint().setWrap(true); */ }
    virtual ~Object() {}

    //
    // Methods
    //
    virtual void move(const Interface * pUI);        // Virtual function.
    virtual void move(std::vector<double> & inputs); // Virtual function.
    virtual void draw() = 0;                         // Pure virtual function.
    virtual int getValue() const { return 0; }       // Virtual function.
    void addVectors(Vector & v);                     // Add two vectors together.
    void kill()            { alive = false;        } // Kill the object!
    void rotate(int speed) { v.rotate(speed); } // Rotate the object.

    //
    // Getters
    //
    Vector getVector() const { return v;                 }
    float getMass()    const { return mass;              }
    Point getPoint()   const { return v.getPoint();      }
    Vector & getVector()     { return v;                 }
    int getAngle()     const { return v.getAngle();      }
    bool getIsAlive()  const { return alive;             }
    int getType()      const { return type;              }
    int getSize()      const { return radius;            }
    int getRadius()    const { return radius;            }

    //
    // Setters
    //
    void setVector(Vector & ve) { v = ve;                 }
    void setMass(float m)       { mass = m;               }
    void setWrap(bool wrap)     { v.setWrap(wrap);        }
    void setAngle(int angle)    { v.setAngle(angle);      }
    void setIsAlive(bool a)     { alive = a;              }
    void setType(int t)         { type = t;               }
    void setRadius(int r)       { radius = r;             }
private:
    Vector v;      // This will allow the object to move!
    double mass;   // This will hold the mass of the object!
    bool alive;    // This will keep track of whether it is alive
                   // or not.
    int type;      // What type of object is it?
    int radius;    // Radius for the objects.
};

/*********************************
 * Rock
 *  This will hold the values for
 *      for a given rock.
 ********************************/
class Rock : public Object
{
public:
    //
    // Constructors
    //
    Rock(float x, float y, float dx, float dy, double m, int r, int s, int type) : Object(x, y, dx, dy, m, r), rotationSpeed(s)
    {
        setType(type);
        createRock();
    }
    ~Rock()
    {
        int size = (getType() == ASTEROID) ? POINTS_FOR_ASTEROID : POINTS_FOR_PLANET;

        for (int r = 0; r < size; ++r)
        {
            delete [] points[r];
        }

        delete [] points;
    }

    //
    // Methods
    //
    void draw();
    int getValue() const { return value; }

    //
    // Setters
    //
    void setRotationSpeed(int s) { rotationSpeed = s; }

    //
    // Getters
    //
    int ** getPoints()           { return points;     }
private:
    void createRock(); // This will create the points for the rock.
    int rotationSpeed; // This will rotate the Rock.
    int **points;      // This will hold the length of each of the sides.
                       // this allows the asteroids to look jagged.
    int value;         // The value of the rock for the interaction for the ship.
};

/*********************************
 * Ship
 *  This will hold the values for
 *      for a given ship.
 ********************************/
class Ship : public Object
{
public:
    //
    // Constructors
    //
    Ship(float x, float y, double m, int r) : Object(x, y, 0, 0, m, r)
    {
        setAngle(0);
        setType(SHIP);
        fuel = 200;
    }
    ~Ship() {}

    //
    // Methods
    //
    void draw();
    void move(const Interface * pUI);
    void move(std::vector<double> & inputs);

    //
    // Getters
    //
    int getFuel()    const { return fuel;  }

    //
    // Setters
    //
    void setFuel(int f)       { fuel = f;        }
private:
    int fuel;  // How much fuel the ship has.
};

#endif // OBJECTS_H