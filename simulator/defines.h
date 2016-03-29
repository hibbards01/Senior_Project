/********************************************************
 * Program:
 *  defines.h
 * Author:
 *  Samuel Hibard
 * Summary:
 *  This is where al the #define 's are defined. This was
 *      more to keep all the definitions in one place.
 *******************************************************/

#ifndef DEFINES_H
#define DEFINES_H

#include <math.h>

// All the weights for the objects. Particularly with
//  the planets of the solar system.
#define SUN       (1.989 * pow(10, 30))
#define EARTH     (5.98  * pow(10, 24))
#define MOON      (7.34  * pow(10, 22))
#define JUPITER   (1.898 * pow(10, 27))
#define SATURN    (5.683 * pow(10, 26))
#define SHIPW     25000
#define ASTEROIDW 63503

// The gravitational constant. This is used for part of
//  of the physics calculation for F = ma
#define gravitationalConstant .0000000000667

// These are the distances for between the points on the
//  the gUI screen.
#define MILLMETERS 1000000
#define CUSTOM     375000
#define METERS5    100000
#define METERS4    10000
#define KILOMETERS 1000

// Other calculations needed for doing the math correctly.
#define PI 3.14159265
#define deg2rad(value) ((M_PI / 180) * (value))
#define rad2deg(value) (value * 180 / PI)

#endif // DEFINES_H