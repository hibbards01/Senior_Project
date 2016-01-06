/*************************************************************
* Program:
*   objects.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will contain the class Objects. Also it will include
*     all the other classes that inherit from Objects.
*************************************************************/

#include "vector.h"

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
    Object() : vector(), mass(0.0) {}
    Object(float x, float y, float dx, float dy, double m) : vector(x, y, dx, dy), mass(m) {}
    
    //
    // Methods
    //
    virtual void move();         // Virtual function
    virtual void draw() = 0;     // Pure virtual function
    void addVectors(Vector & v); // Add two vectors together
    
    //
    // Getters
    //
    Vector getVector() const { return vector;            }
    float getMass()    const { return mass;              }
    Point getPoint()   const { return vector.getPoint(); }
    Vector & getVector()     { return vector;            }
    
    //
    // Setters
    //
    void setVector(Vector & v) { vector = v;           }
    void setMass(float m)      { mass = m;             }
    void setWrap(bool wrap)    { vector.setWrap(wrap); }
private:
    Vector vector; // This will allow the object to move!
    double mass;    // This will hold the mass of the object!
};

/*********************************
 * Planet
 *  This will hold the values for
 *      for a given planet.
 ********************************/
class Planet : public Object
{
public:
    //
    // Constructors
    //
    Planet(float x, float y, float dx, float dy, double m, int r, int s) : radius(r), Object(x, y, dx, dy, m), rotationSpeed(s) {}
    
    //
    // Methods
    //
    void draw();
    void rotate();
    
    //
    // Setters
    //
    void setRotationSpeed(int s) { rotationSpeed = s; }
private:
    int radius;        // This is the radius of the planet.
    int rotationSpeed; // This will rotate the planet.
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
    Ship(float x, float y, float dx, float dy, double m, int r) : Object(x, y, dx, dy, m) {}
    
    //
    // Methods
    //
    void draw();
private:
};
