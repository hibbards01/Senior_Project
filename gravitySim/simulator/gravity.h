/***************************************************************
* Program:
*   gravity.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold the class Gravity.
***************************************************************/

#include <list>
#include "object.h"

/************************************
 * Gravity
 *  This will hold all the objects.
 *      It will be the one calculating
 *      what will happen to the given
 *      objects
 ***********************************/
class Gravity
{
public:
    //
    // Constructors
    //
    Gravity() {}
    Gravity(std::list<Object *> & objs);
    
    //
    // Methods
    //
    void move();
    void draw();
    
    //
    // Getters
    //
    std::list<Object *> & getObjects() { return objects; }
    
    //
    // Setters
    //
    void setObjects(std::list<Object *> & objs) { objects = objs; }
    void setWrap(bool wrap);
private:
    void calculateAccerlation();         // This will calculate the force for all the objects
    std::list<Object *> objects;         // This will hold all the objects.
    static double gravitationalConstant; // This will hold the gravitational constant
};
