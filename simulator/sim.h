/***************************************************************
* Program:
*   sim.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold the class Simulator. This class will do the
*       main interaction with the gUI and the objects.
***************************************************************/

#ifndef SIM_H
#define SIM_H

#include <list>
#include "object.h"
#include "graphics.h"

/*********************************************************
 * Simulator
 *  This class will be the one that that will tell the
 *      objects when to do draw, interact, and move.
 ********************************************************/
class Simulator
{
public:
    //
    // Constructors
    //
    Simulator();
    ~Simulator();

    //
    // Methods
    //
    void move(const Interface * pUI);
    void draw();
    void run(const Interface * pUI);
    void checkCollision();
    void drawScore();

    //
    // Getters
    //
    std::list<Object *> & getObjects()          { return objects; }

    //
    // Setters
    //
    void setObjects(std::list<Object *> & objs) { objects = objs; }
private:
    void calculateAccerlation();         // This will calculate the force for all
                                         // the objects using physics to determine it.
    std::list<Object *> objects;         // This will hold all the objects in the simulator.
    double distance;                     // The distance for each pixel.
    Graphics graphics;                   // The graphics class
    int time;                            // How much time is left for the user.
    int timer;                           // This will count how many frames have passed.
    Vector finishLine;                   // Where the finish line is currently.
    int done;                            // Is the game done?
    Point startingPosition;              // This will save the starting position of the ship.
};

#endif // SIM_H