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

// ENUM for the type of objects
enum {NOTHING, SHIP, PLANET, ASTEROID};
#define POINTS_FOR_ROCK 20

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
    Object() : vector(), mass(0.0), alive(true) { /* vector.getPoint().setWrap(true); */ }
    Object(float x, float y, float dx, float dy, double m, int r) :
        vector(x, y, dx, dy), mass(m), alive(true), radius(r) { /* vector.getPoint().setWrap(true); */ }
    virtual ~Object() {}

    //
    // Methods
    //
    virtual void move(const Interface * pUI);        // Virtual function
    virtual void draw() = 0;                         // Pure virtual function
    void addVectors(Vector & v);                     // Add two vectors together
    void kill()            { alive = false;        } // Kill the object!
    void rotate(int speed) { vector.rotate(speed); } // Rotate the object

    //
    // Getters
    //
    Vector getVector() const { return vector;            }
    float getMass()    const { return mass;              }
    Point getPoint()   const { return vector.getPoint(); }
    Vector & getVector()     { return vector;            }
    int getAngle()     const { return vector.getAngle(); }
    bool getIsAlive()  const { return alive;             }
    int getType()      const { return type;              }
    int getSize()      const { return radius;            }
    int getRadius()    const { return radius;            }

    //
    // Setters
    //
    void setVector(Vector & v) { vector = v;             }
    void setMass(float m)      { mass = m;               }
    void setWrap(bool wrap)    { vector.setWrap(wrap);   }
    void setAngle(int angle)   { vector.setAngle(angle); }
    void setIsAlive(bool a)    { alive = a;              }
    void setType(int t)        { type = t;               }
    void setRadius(int r)      { radius = r;             }
private:
    Vector vector; // This will allow the object to move!
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

        if (type == ASTEROID)
        {
            createRock();
        }
    }
    ~Rock() {}

    //
    // Methods
    //
    void draw();

    //
    // Setters
    //
    void setRotationSpeed(int s) { rotationSpeed = s; }
private:
    void createRock();              // This will create the points for the rock
    int rotationSpeed;              // This will rotate the Rock.
    int points[POINTS_FOR_ROCK][2]; // This will hold the length of each of the sides
                                    // this allows the asteroids to look jagged.
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
        odometer = 0;
    }
    ~Ship() {}

    //
    // Methods
    //
    void draw();
    void move(const Interface * pUI);
    // void moveship(int angle, float dx, float dy);

    //
    // Getters
    //
    float getDistance() const { return odometer; }
    int getFuel()       const { return fuel;     }

    //
    // Setters
    //
    void setDistance(float d) { odometer = d;    }
    void setFuel(int f)       { fuel = f;        }
private:
    int fuel;       // How much fuel the ship has.
    float odometer; // The distance the ship as traveled.
};

#endif // OBJECTS_H