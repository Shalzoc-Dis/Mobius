/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       hypatia                                                   */
/*    Created:      09/03/2024, 10:19:11                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Robot.h"
#include <random>   // For testing purposes
#define PLANNING


// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here


int main() {

    Brain.Screen.printAt( 10, 50, "Hello V5" );
    int generatorSeed = 11;
    int iterations = 5;
    bool regenerate = true;
    bool actionTaken = false;
    int xOffset = 0;
    int yOffset = 0;
    float moveSpeed = 0.01f;
    std::random_device rd;
    printf("Variables Initialised\n");

    while(true) {
        printf("Testing...");
        if (Controller1.ButtonX.pressing() || regenerate) {
            printf("Regenerating...");
            Brain.Screen.clearScreen();
            regenerate = false;

            // Info
            Brain.Screen.printAt(0, 15, "GenSeed: %d", generatorSeed);
            Brain.Screen.printAt(0, 30, "Iterations: %d", iterations);

            // Generate pseudo-random numbers
            std::mt19937 gen(generatorSeed);
            std::uniform_int_distribution<> height(0 + 5, 240 - 5);
            std::uniform_int_distribution<> width(0 + 5, 480 - 5);

            // The screen is 480 by 240 pixels. (1, 1) is in the top left corner
            // Draw random test curve
            Mobius::CubicBezier curve;
            
            curve.p0 = Mobius::vector2(width(gen), height(gen));
            curve.p1 = Mobius::vector2(width(gen), height(gen));
            curve.p2 = Mobius::vector2(width(gen), height(gen));
            curve.p3 = Mobius::vector2(width(gen), height(gen));
            curve.visualise();
            printf("Curve Created and drawn.");

            // Draw test point and find closest point on curve
            Mobius::vector2 testPoint(width(gen) + xOffset, height(gen) + yOffset);
            Brain.Screen.setPenColor(vex::color::purple);
            Brain.Screen.setPenWidth(1);
            Brain.Screen.drawCircle(testPoint.x, testPoint.y, 3);
            printf("About to calculate closest T\n");
            float closestT = curve.calculateClosestT(testPoint, 5, iterations);
            Mobius::vector2 posAtClosestT = curve.position(closestT);
            float radius = sqrt(pow(testPoint.x - posAtClosestT.x, 2) + pow(testPoint.y - posAtClosestT.y, 2));
            Brain.Screen.setPenColor(vex::color::cyan);
            Brain.Screen.setFillColor(vex::color::transparent);
            Brain.Screen.drawCircle(testPoint.x, testPoint.y, radius);
            Brain.Screen.drawLine(testPoint.x, testPoint.y, posAtClosestT.x, posAtClosestT.y);
            Brain.Screen.drawCircle(posAtClosestT.x, posAtClosestT.y, 3);

            printf("Display regenerated.");            
        }
        /*
        if (Controller1.ButtonB.pressing() && !actionTaken) {
            generatorSeed++;
            actionTaken = true;
            regenerate = true;
        } else if (!Controller1.ButtonB.pressing() && actionTaken) {
            actionTaken = false;
        }

        if (Controller1.ButtonY.pressing() && !actionTaken) {
            iterations++;
            actionTaken = true;
            regenerate = true;
        } else if (!Controller1.ButtonY.pressing() && actionTaken) {
            actionTaken = false;
        }

        if (Controller1.ButtonA.pressing() && !actionTaken) {
            iterations--;
            actionTaken = true;
            regenerate = true;
        } else if (!Controller1.ButtonA.pressing() && actionTaken) {
            actionTaken = false;
        }

        if (fabs(Controller1.Axis3.value()) > 3) {
            yOffset += -Controller1.Axis3.value() * moveSpeed;
            regenerate = true;
        }
        if (fabs(Controller1.Axis4.value()) > 3) {
            xOffset += Controller1.Axis4.value() * moveSpeed;
            regenerate = true;
        }
        */


        // Allow other tasks to run
        vex::this_thread::sleep_for(50);
    }
}
