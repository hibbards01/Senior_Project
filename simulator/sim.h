/***************************************************************
* Program:
*   sim.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold the class Simulator.
***************************************************************/

#include "gravity.h"
#include <list>

/**********************************
 * Simulator
 *  This class will be the one that
 *      that will tell the objects
 *      when to do what.
 *********************************/
class Simulator
{
public:
    //
    // Constructors
    //
    Simulator();
    Simulator(std::list<Object *> & objects) : gravity(objects) {}
    
    //
    // Methods
    //
    void run();
private:
    Gravity gravity; // We need gravity!
};
