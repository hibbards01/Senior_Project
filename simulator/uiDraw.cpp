/***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock

// #define LINUX
#define MAC_XCODE
// #define WIN_VISUAL_STUDIO

#ifdef MAC_XCODE
#include <OpenGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // MAC_XCODE

#ifdef LINUX
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // LINUX

#ifdef WIN_VISUAL_STUDIO
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>         // OpenGL library we copied
#define _USE_MATH_DEFINES
#include <math.h>
#endif // WIN_VISUAL_STUDIO


#include "point.h"
#include "uiDraw.h"

using namespace std;

#define deg2rad(value) ((M_PI / 180) * (value))

/*********************************************
 * NUMBER OUTLINES
 * We are drawing the text for score and things
 * like that by hand to make it look "old school."
 * These are how we render each individual charactger.
 * Note how -1 indicates "done".  These are paired
 * coordinates where the even are the x and the odd
 * are the y and every 2 pairs represents a point
 ********************************************/
const char NUMBER_OUTLINES[10][20] =
{
  { 0, 0,  12, 0,  12, 0,  12,18,  12,18,   0,18,   0,18,   0, 0,  -1,-1,  -1,-1},//0
  {12, 0,  12,18,  -1,-1,  -1,-1,  -1,-1,  -1,-1,  -1,-1,  -1,-1,  -1,-1,  -1,-1},//1
  { 0, 0,  12, 0,  12, 0,  12, 9,  12, 9,   0, 9,   0, 9,   0,18,   0,18,  12,18},//2
  { 0, 0,  12, 0,  12, 0,  12,18,  12,18,   0,18,   6, 9,  12, 9,  -1,-1,  -1,-1},//3
  { 0, 0,   0, 9,   0, 9,  12, 9,  12, 0,  12,18,  -1,-1,  -1,-1,  -1,-1,  -1,-1},//4
  {12, 0,   0, 0,   0, 0,   0, 9,   0, 9,  12, 9,  12, 9,  12,18,  12,18,   0,18},//5
  {12, 0,   0, 0,   0, 0,   0,18,   0,18,  12,18,  12,18,  12, 9,  12, 9,   0, 9},//6
  { 0, 0,  12, 0,  12, 0,  12,18,  -1,-1,  -1,-1,  -1,-1,  -1,-1,  -1,-1,  -1,-1},//7
  { 0, 0,  12, 0,   0, 9,  12, 9,   0,18,  12,18,   0, 0,   0,18,  12, 0,  12,18},//8
  { 0, 0,  12, 0,  12, 0,  12,18,   0, 0,   0, 9,   0, 9,  12, 9,  -1,-1,  -1,-1} //9
};

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawDigit(const Point & topLeft, char digit)
{
   // we better be only drawing digits
   assert(isdigit(digit));
   if (!isdigit(digit))
      return;

   // compute the row as specified by the digit
   int r = digit - '0';
   assert(r >= 0 && r <= 9);

   // go through each segment.
   for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4)
   {
      assert(NUMBER_OUTLINES[r][c    ] != -1 &&
             NUMBER_OUTLINES[r][c + 1] != -1 &&
             NUMBER_OUTLINES[r][c + 2] != -1 &&
             NUMBER_OUTLINES[r][c + 3] != -1);

      //Draw a line based off of the num structure for each number
      Point start;
      start.setX(topLeft.getX() + NUMBER_OUTLINES[r][c]);
      start.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 1]);
      Point end;
      end.setX(topLeft.getX() + NUMBER_OUTLINES[r][c + 2]);
      end.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 3]);

      drawLine(start, end);
   }
}

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawNumber(const Point & topLeft, unsigned int number)
{
   // render the number as text
   ostringstream sout;
   sout << number;
   string text = sout.str();

   // walk through the text one digit at a time
   Point point = topLeft;
   for (const char *p = text.c_str(); *p; p++)
   {
      assert(isdigit(*p));
      drawDigit(point, *p);
      point.addX(11);
   }
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void drawText(const Point & topLeft, const char * text)
{
   // void *pFont = GLUT_BITMAP_HELVETICA_18;  // also try _18

   // // prepare to draw the text from the top-left corner
   // glRasterPos2f(topLeft.getX(), topLeft.getY());

   // // loop through the text
   // for (const char *p = text; *p; p++)
   //    glutBitmapCharacter(pFont, *p);
}

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  point    The point to be moved
 *           center   The center point we will rotate around
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
void rotate(Point & point, const Point & origin, int rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(deg2rad(rotation));
   double sinA = sin(deg2rad(rotation));

   // remember our original point
   Point tmp(false /*check*/);
   tmp.setX(point.getX() - origin.getX());
   tmp.setY(point.getY() - origin.getY());

   // find the new values
   point.setX(static_cast<int> (tmp.getX() * cosA -
                                tmp.getY() * sinA) +
              origin.getX());
   point.setY(static_cast<int> (tmp.getX() * sinA +
                                tmp.getY() * cosA) +
              origin.getY());
}

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 *  INPUT  center    Center of the rectangle
 *         width     Horizontal size
 *         height    Vertical size
 *         rotation  Orientation
 *************************************************************************/
void drawRect(const Point & center, char width, char height, int rotation)
{
   Point tl(false /*check*/); // top left
   Point tr(false /*check*/); // top right
   Point bl(false /*check*/); // bottom left
   Point br(false /*check*/); // bottom right

   //Top Left point
   tl.setX(center.getX() - (width  / 2));
   tl.setY(center.getY() + (height / 2));

   //Top right point
   tr.setX(center.getX() + (width  / 2));
   tr.setY(center.getY() + (height / 2));

   //Bottom left point
   bl.setX(center.getX() - (width  / 2));
   bl.setY(center.getY() - (height / 2));

   //Bottom right point
   br.setX(center.getX() + (width  / 2));
   br.setY(center.getY() - (height / 2));

   //Rotate all points the given degrees
   rotate(tl, center, rotation);
   rotate(tr, center, rotation);
   rotate(bl, center, rotation);
   rotate(br, center, rotation);

   //Finally draw the rectangle
   glBegin(GL_LINE_STRIP);
   glVertex2f(tl.getX(), tl.getY());
   glVertex2f(tr.getX(), tr.getY());
   glVertex2f(br.getX(), br.getY());
   glVertex2f(bl.getX(), bl.getY());
   glVertex2f(tl.getX(), tl.getY());
   glEnd();
}

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *  INPUT   center   Center of the circle
 *          radius   Size of the circle
 *          points   How many points will we draw it.  Larger the number,
 *                   the more line segments we will use
 *          rotation True circles are rotation independent.  However, if you
 *                   are drawing a 3-sided circle (triangle), this matters!
 *************************************************************************/
void drawCircle(const Point & center, char radius, int points, int rotation)
{
   // begin drawing
   glBegin(GL_LINE_LOOP);

   //loop around a circle the given number of times drawing a line from
   //one point to the next
   for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / points)
   {
      Point temp(false /*check*/);
      temp.setX(center.getX() + static_cast<int>(radius * cos(i)));
      temp.setY(center.getY() + static_cast<int>(radius * sin(i)));
      rotate(temp, center, rotation);
      glVertex2f(temp.getX(), temp.getY());
   }

   // complete drawing
   glEnd();

}

/**************************************************
 * drawAsteroid
 *  Draw an asteroid based off the center of the
 *    point and radius that is given.
 *************************************************/
void drawAsteroid(const Point & center, int points[][2], int size, int rotation)
{
   // Begin drawing the Asteroid
   glBegin(GL_LINE_LOOP);

   // Run through all the points to draw the rocks
   for (int i = 0; i < size; ++i)
   {
      // Create a point for the one position
      Point temp(false /* check */);
      temp.setX(center.getX() + points[i][0]);
      temp.setY(center.getY() + points[i][1]);
      rotate(temp, center, rotation);
      glVertex2f(temp.getX(), temp.getY());
   }

   // Finally complete the drawing
   glEnd();

   return;
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the line
 *          end       The position of the end of the line
 *************************************************************************/
void drawLine(const Point & begin, const Point & end)
{
   // Get ready...
   glBegin(GL_LINES);

   // Note how we scale the lines by a factor of two
   glVertex2f(begin.getX(), begin.getY());
   glVertex2f(  end.getX(),   end.getY());

   // complete drawing.
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *  INPUT point   The position of the dow
 *************************************************************************/
void drawDot(const Point & point)
{
   // Get ready, get set...
   glBegin(GL_POINTS);

   // Go...
   glVertex2f(point.getX(),     point.getY()    );
   glVertex2f(point.getX() + 1, point.getY()    );
   glVertex2f(point.getX() + 1, point.getY() + 1);
   glVertex2f(point.getX(),     point.getY() + 1);

   // Done!  OK, that was a bit too dramatic
   glEnd();
}

/************************************************************************
 * DRAW cool ship
 *************************************************************************/
void drawCoolShip(const Point & center, int rotation)
{
   // Get ready, get set...
    Point pCenter(center);
    Point p(center);
    Point p1(center);
    Point p2(center);
    Point p3(center);
    Point p4(center);
    Point p5(center);
    Point p6(center);
    Point p7(center);
    Point p8(center);
    Point p9(center);
    Point p10(center);
    Point p11(center);
    Point p12(center);
    Point p13(center);
    Point p14(center);
    Point p15(center);
    Point p16(center);
    Point p17(center);
    Point p18(center);
    Point p19(center);
    Point p20(center);
    Point p21(center);
    Point p22(center);

    //1st lap!
    p.addXY(-8, 18);
    p1.addXY(-16, 24);
    p2.addXY(-24, 24);
    p3.addXY(-30, 20);
    p4.addXY(-30, 16);
    p5.addXY(-24, 12);
    p6.addXY(-16, 12);
    //
    p7.addXY(-18, 11);
    p8.addXY(-38, 8);
    p9.addXY(-38, 4);
    p10.addXY(-20, 4);
    //
    p11.addXY(-24, 4);
    p12.addXY(-24, -4);
    //
    p13.addXY(-20, -4);
    p14.addXY(-38, -4);
    p15.addXY(-38, -8);
    p16.addXY(-16, -13);
    //
    p17.addXY(12, -16);
    p18.addXY(16, -16);
    p19.addXY(22, -7);
    p20.addXY(22, 7);
    p21.addXY(16, 16);
    p22.addXY(12, 16);

    //2nd lap!
   //Rotate all points the given degrees
   rotate(p, center, rotation);
    rotate(p1, center, rotation);
    rotate(p2, center, rotation);
    rotate(p3, center, rotation);
    rotate(p4, center, rotation);
    rotate(p5, center, rotation);
    rotate(p6, center, rotation);
    rotate(p7, center, rotation);
    rotate(p8, center, rotation);
    rotate(p9, center, rotation);
    rotate(p10, center, rotation);
    rotate(p11, center, rotation);
    rotate(p12, center, rotation);
    rotate(p13, center, rotation);
    rotate(p14, center, rotation);
    rotate(p15, center, rotation);
    rotate(p16, center, rotation);
    rotate(p17, center, rotation);
    rotate(p18, center, rotation);
    rotate(p19, center, rotation);
    rotate(p20, center, rotation);
    rotate(p21, center, rotation);
    rotate(p22, center, rotation);

   //Finally draw the rectangle
    glBegin(GL_LINE_STRIP);
    glColor3f(0.658824  /*%red*/, 0.658824 /*%green*/, 0.658824 /*%blue*/);
    glVertex2f(p.getX(), p.getY());
    glVertex2f(p1.getX(), p1.getY());
    glVertex2f(p2.getX(), p2.getY());
    glVertex2f(p3.getX(), p3.getY());
    glVertex2f(p4.getX(), p4.getY());
    glVertex2f(p5.getX(), p5.getY());
    glVertex2f(p6.getX(), p6.getY());
    // Done!  OK, that was a bit too dramatic
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(p2.getX(), p2.getY());
    glVertex2f(p5.getX(), p5.getY());
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(p7.getX(), p7.getY());
    glVertex2f(p8.getX(), p8.getY());
    glVertex2f(p9.getX(), p9.getY());
    glVertex2f(p10.getX(), p10.getY());
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(p13.getX(), p13.getY());
    glVertex2f(p14.getX(), p14.getY());
    glVertex2f(p15.getX(), p15.getY());
    glVertex2f(p16.getX(), p16.getY());
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(p17.getX(), p17.getY());
    glVertex2f(p18.getX(), p18.getY());
    glVertex2f(p19.getX(), p19.getY());
    glVertex2f(p20.getX(), p20.getY());
    glVertex2f(p21.getX(), p21.getY());
    glVertex2f(p22.getX(), p22.getY());
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(p11.getX(), p11.getY());
    glVertex2f(p12.getX(), p12.getY());
    glEnd();

    drawCircle(pCenter, 20/*radius*/, 16/*sides*/, rotation);

    glBegin(GL_LINE_STRIP);
    glColor3f (1.0, 1.0, 1.0);  // reset to white
    glEnd();
}

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max)
{
   assert(min <= max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));

   assert(min <= num && num <= max);

   return num;
}

/*********************************
 * DRAWTEXTCOLOR
 ********************************/
void drawTextColor(const Point & topLeft, const char * text)
{
    // void *pFont = GLUT_BITMAP_HELVETICA_12;  // also try _18

    // // prepare to draw the text from the top-left corner
    // glRasterPos2f(topLeft.getX(), topLeft.getY());

    // // loop through the text
    // for (const char *p = text; *p; p++)
    // {
    //     glutBitmapCharacter(pFont, *p);
    // }
}

/************************************************************************
 * DRAW Ship
 * Draw a spaceship on the screen
 *  INPUT point   The position of the ship
 *        angle   Which direction it is ponted
 *************************************************************************/
void drawShip(const Point & center, int rotation)
{
    // Get ready, get set...
    Point bow(      center); // front
    Point stern(    center); // back
    Point starboard(center); // right
    Point port(     center); // left

    bow.addX(-6);

    stern.addX(2);

    starboard.addY(3);
    starboard.addX(3);

    port.addY(-3);
    port.addX( 3);

    //Rotate all points the given degrees
    rotate(bow,       center, rotation);
    rotate(stern,     center, rotation);
    rotate(starboard, center, rotation);
    rotate(port,      center, rotation);

    //Finally draw the rectangle
    glBegin(GL_LINE_STRIP);
    glColor3f(0.8515625 /*%red*/, 0.64453125 /*%green*/, 0.125 /*%blue*/);
    glVertex2f(      bow.getX(),       bow.getY());
    glVertex2f(starboard.getX(), starboard.getY());
    glVertex2f(    stern.getX(),     stern.getY());
    glVertex2f(     port.getX(),      port.getY());
    glVertex2f(      bow.getX(),       bow.getY());
    glColor3f (1.0, 1.0, 1.0);  // reset to white

    // Done!  OK, that was a bit too dramatic
    glEnd();
}

void drawBigShip(const Point & center, int rotation)
{
    // Get ready, get set...
    Point bow(      center); // front
    Point stern(    center); // back
    Point starboard(center); // right
    Point port(     center); // left

    bow.addX(-12);

    stern.addX(4);

    starboard.addY(6);
    starboard.addX(6);

    port.addY(-6);
    port.addX( 6);

    //Rotate all points the given degrees
    rotate(bow,       center, rotation);
    rotate(stern,     center, rotation);
    rotate(starboard, center, rotation);
    rotate(port,      center, rotation);

    //Finally draw the rectangle
    glBegin(GL_LINE_STRIP);
    glColor3f(0.8515625 /*%red*/, 0.64453125 /*%green*/, 0.125 /*%blue*/);
    glVertex2f(      bow.getX(),       bow.getY());
    glVertex2f(starboard.getX(), starboard.getY());
    glVertex2f(    stern.getX(),     stern.getY());
    glVertex2f(     port.getX(),      port.getY());
    glVertex2f(      bow.getX(),       bow.getY());
    glColor3f (1.0, 1.0, 1.0);  // reset to white

    // Done!  OK, that was a bit too dramatic
    glEnd();
}

void drawLesserShip(const Point & center, int rotation)
{
    Point pt(center);
    Point pt1(center);
    Point pt2(center);
    Point pt3(center);
    Point pt4(center);
    Point pt5(center);
    Point pt6(center);
    Point pt7(center);
    //
    Point pt8(center);
    Point pt9(center);
    Point pt10(center);
    Point pt11(center);
    Point pt12(center);
    Point pt13(center);
    Point pt14(center);
    Point pt15(center);
    //
    pt.addXY(10, 2);
    pt1.addXY(17, 2);
    pt2.addXY(17, 14);
    pt3.addXY(21, 14);
    pt4.addXY(21, -14);
    pt5.addXY(17, -14);
    pt6.addXY(17, -2);
    pt7.addXY(10, -2);
    //
    pt8.addXY(-10, 2);
    pt9.addXY(-17, 2);
    pt10.addXY(-17, 14);
    pt11.addXY(-21, 14);
    pt12.addXY(-21, -14);
    pt13.addXY(-17, -14);
    pt14.addXY(-17, -2);
    pt15.addXY(-10, -2);
    //
    rotate(pt, center, rotation);
    rotate(pt1, center, rotation);
    rotate(pt2, center, rotation);
    rotate(pt3, center, rotation);
    rotate(pt4, center, rotation);
    rotate(pt5, center, rotation);
    rotate(pt6, center, rotation);
    rotate(pt7, center, rotation);
    rotate(pt8, center, rotation);
    rotate(pt9, center, rotation);
    rotate(pt10, center, rotation);
    rotate(pt11, center, rotation);
    rotate(pt12, center, rotation);
    rotate(pt13, center, rotation);
    rotate(pt14, center, rotation);
    rotate(pt15, center, rotation);
    //
    glBegin(GL_LINE_LOOP);
    glColor3f(0.466667, 0.533333, 0.6);
    drawCircle(center, 10, 20, rotation);
    glColor3f(1.0, 1.0, 1.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.466667, 0.533333, 0.6);  //color?
    glVertex2f(pt.getX(), pt.getY());
    glVertex2f(pt1.getX(), pt1.getY());
    glVertex2f(pt2.getX(), pt2.getY());
    glVertex2f(pt3.getX(), pt3.getY());
    glVertex2f(pt4.getX(), pt4.getY());
    glVertex2f(pt5.getX(), pt5.getY());
    glVertex2f(pt6.getX(), pt6.getY());
    glVertex2f(pt7.getX(), pt7.getY());
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(pt8.getX(), pt8.getY());
    glVertex2f(pt9.getX(), pt9.getY());
    glVertex2f(pt10.getX(), pt10.getY());
    glVertex2f(pt11.getX(), pt11.getY());
    glVertex2f(pt12.getX(), pt12.getY());
    glVertex2f(pt13.getX(), pt13.getY());
    glVertex2f(pt14.getX(), pt14.getY());
    glVertex2f(pt15.getX(), pt15.getY());

    glColor3f(1.0, 1.0, 1.0);  //reset to white
    glEnd();

    return;
}
