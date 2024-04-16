#pragma once

#include "MobiusUtilities.h"

extern vex::brain Brain;
namespace Mobius {

// Reference: https://en.wikipedia.org/wiki/Bézier_curve
// A struct to represent a cubic bezier curve
struct CubicBezier {
    vector2 p0, p1, p2, p3;

    CubicBezier() {};
    /*
        @param p0 The starting point of the curve
        @param p1 The first control point
        @param p2 The second control point
        @param p3 The ending point of the curve
    */
    CubicBezier(vector2 p0, vector2 p1, vector2 p2, vector2 p3)
     : p0(p0), p1(p1), p2(p2), p3(p3) {};
    
    ~CubicBezier() {};

    /*
        @brief Returns the position of the curve at time t
        @param t The time parameter. 0 <= t <= 1
        @return The position of the curve at time t
    */
    vector2 position(float t);
    /*
        @brief Returns the first derivative (velocity) of the curve at time t
        @param t The time parameter. 0 <= t <= 1
        @return The first derivative of the curve at time t
    */
    vector2 positionDerivative1(float t);
    /*
        @brief Returns the second derivative (acceleration) of the curve at time t
        @param t The time parameter. 0 <= t <= 1
        @return The second derivative of the curve at time t
    */
    vector2 positionDerivative2(float t);

    /*
        @brief Visualises the curve on the Brain's Screen. The start/end points are blue circles
        @param derivative=0 The curve in green
        @param derivative=1 The first derivative in yellow
        @param derivative=2 The second derivative in red
    */
    void visualise(int derivative = 0);   // This is for testing only. It draws the curve on the Brain's Screen

    /*
        @brief Calculates the point on the curve closest to the point specified. It is an approximation
        @param point The point from which to calculate the closest point on the curve
        @param divisions=5 The number of sectors the curve should be broken into for the search. More sectors means more accuracy
        @param iterations=5 The number of iterations of the search in a sector. Each iteration halves the search space
        @return The t value of the curve that corresponds to the closest point
    */
    float calculateClosestT(vector2 point, uint8_t divisions = 5, uint8_t iterations = 5);
    // Tests the visualise and calculateClosestT functions
    static void test();

}; // struct CubicBezier


struct Spline {
    // The points that define the spline. Each group of four points makes up a curve
    std::vector<vector2> points;

    Spline() {};
    ~Spline() {};

    // This draws the spline on the Brain's Screen
    void visualise();
}; // struct Spline

} // namespace Mobius