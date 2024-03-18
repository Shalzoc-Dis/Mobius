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


// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here


int main() {

    Brain.Screen.printAt( 10, 50, "Hello V5" );

    Mobius::CubicBezier curve;
    curve.p0 = Mobius::vector2(50, 50);
    curve.p1 = Mobius::vector2(220, 170);
    curve.p2 = Mobius::vector2(300, 50);
    curve.p3 = Mobius::vector2(400, 150);
    curve.visualise();
    //curve.visualise(1);
    //curve.visualise(2);
   
    while(1) {
        
        // Allow other tasks to run
        vex::this_thread::sleep_for(10);
    }
}
