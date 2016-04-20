/****************************************************
* Program:
*   graphics.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will be the class that will hold all the text
*       and backgrounds looks for the simulator. This
*       will display the distance you have traveled,
*       the fuel that has been consumed.
****************************************************/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "point.h"

/****************************************************
* Graphics
*   This class will hold the functions to draw the text
*       and the stars that will appear in the background.
****************************************************/
class Graphics
{
public:
    //
    // Constructors
    //
    Graphics();

    //
    // Methods
    //
    void draw(int fuel, int dist, int time) const; // Draw all the graphics
    int getFinishSize()                     const { return finishSize;   }
    Point & getFinishCircle()                     { return finishCircle; }
private:
    Point fuelText;     // The fuel display of the text.
    Point fuelNum;      // This will show how much fuel you have.
    Point distText;     // Where to display the distance text.
    Point distNum;      // How much distance is covered will be
                        // displayed at the point specified.
    Point timeText;     // Display the word "time."
    Point timeNum;      // Display the number.
    Point finishCircle; // Where the finish line will be.
    Point finishText;   // The text will be saved inside the circle.
    int finishSize;     // Size of the finish line.
};

#endif // GRAPHICS_H