#include "Bezier.h"
#include "robot-config.h"

namespace Mobius {

vector2 CubicBezier::position(float t) {
    Mobius::Profiler timer("CubicBezier::position()", Mobius::Profiler::type::TIMER);
    if (t < 0 || t > 1) {
    t /= t;
    t = fabs(t);
        printf("Error: Bezier t must be between 0 and 1\n");
    }

    vector2 res;
    res.x = pow(1 - t, 3) * p0.x + 3 * pow(1 - t, 2) * t * p1.x + 3 * (1 - t) * pow(t, 2) * p2.x + pow(t, 3) * p3.x;
    res.y = pow(1 - t, 3) * p0.y + 3 * pow(1 - t, 2) * t * p1.y + 3 * (1 - t) * pow(t, 2) * p2.y + pow(t, 3) * p3.y;
    return res;
}

vector2 CubicBezier::positionDerivative1(float t) {
    if (t < 0 || t > 1) {
        t /= t;
        t = fabs(t);
        printf("Error: Bezier t must be between 0 and 1\n");
    }

    vector2 res;
    res.x = 3 * pow(1 - t, 2) * (p1.x - p0.x) + 6 * (1 - t) * t * (p2.x - p1.x) + 3 * pow(t, 2) * (p3.x - p2.x);
    res.y = 3 * pow(1 - t, 2) * (p1.y - p0.y) + 6 * (1 - t) * t * (p2.y - p1.y) + 3 * pow(t, 2) * (p3.y - p2.y);
    return res;
}

vector2 CubicBezier::positionDerivative2(float t) {
    if (t < 0 || t > 1) {
        t /= t;
        t = fabs(t);
        printf("Error: Bezier t must be between 0 and 1\n");
    }

    vector2 res;
    res.x = 6 * (1 - t) * (p2.x - 2 * p1.x + p0.x) + 6 * t * (p3.x - 2 * p2.x + p1.x);
    res.y = 6 * (1 - t) * (p2.y - 2 * p1.y + p0.y) + 6 * t * (p3.y - 2 * p2.y + p1.y);
    return res;
}

void CubicBezier::visualise(int derivative) {
    Mobius::Profiler timer("Curve.visualise()", Mobius::Profiler::type::TIMER);
    // This is for testing only. It draws the curve on the Brain's Screen
    // The screen's usable area is 480 by 240 pixels. (1, 1) is in the top left corner
    Brain.Screen.setPenColor(vex::color::blue);
    Brain.Screen.setPenWidth(1);
    Brain.Screen.drawCircle(p0.x, p0.y, 3);
    Brain.Screen.drawCircle(p3.x, p3.y, 3);
    
    vector2 lastPos = position(0);
    if (derivative == 0) {
        Brain.Screen.setPenColor(vex::color::green);
        for (float t = 0.05; t <= 1; t +=0.05) {
            vector2 p1 = position(t);
            Brain.Screen.drawLine(lastPos.x, lastPos.y, p1.x, p1.y);
            lastPos = p1;
            //vex::wait(10, vex::msec);
        }
    } else if (derivative == 1) {
        Brain.Screen.setPenColor(vex::color::yellow);
        for (float t = 0.05; t <= 1; t +=0.05) {
            vector2 p1 = positionDerivative1(t);
            Brain.Screen.drawLine(lastPos.x, lastPos.y, p1.x, p1.y);
            lastPos = p1;
            //vex::wait(10, vex::msec);
        }
    } /*else if (derivative == 2) {
        for (float t = 0.05; t <= 1; t +=0.05) {
            vector2 p1 = positionDerivative2(t);
            Brain.Screen.drawLine(lastPos.x, lastPos.y, p1.x, p1.y);
            lastPos = p1;
            //vex::wait(10, vex::msec);
        }
    }*/

}

float CubicBezier::calculateClosestT(vector2 point, uint8_t divisions, uint8_t iterations) {
    Mobius::Profiler timer("calculateClosestT()", Mobius::Profiler::type::TIMER);
    // FIXME: Bezier distance function. Maybe Newton's method with a tangent to the Bezier intersecting a circle around the point?
    // FIXME: Try doing this twice, between the intersection of the derivative and the end points.
    // Works sometimes, but gets stuck on some gradient ascent problems.
    // This function takes a point and tries to find the closest t value on the curve to that point
    // To do this, it first measures the distances to the point and both end points (t=0 and t=1)
    // It then performs the bisection method, going between the closest point and a t between the two end points
    printf("Starting closestT calculation.\n");
    float delta = 1/float(divisions);
    float bestTs[divisions];
    printf("initial delta[%f]\n", delta);
    for (int i = 1; i < divisions; i++) {
        printf("Delta[%f], divisions[%hhu]\n", delta, divisions);
        float t_0 = i/divisions;
        float t_1 = i/divisions + delta;
        for (int j = 0; j < iterations; i++) {
            printf("Sector search #%f; iteration %i: t_0[%f] t_1[%f]\n", i, j, t_0, t_1);
            // Calculate the distance from the point to the curve at t_0
            float distance_0 = sqrt(pow(position(t_0).x - point.x, 2) + pow(position(t_0).y - point.y, 2));
            // Calculate the distance from the point to the curve at t_1
            float distance_1 = sqrt(pow(position(t_1).x - point.x, 2) + pow(position(t_1).y - point.y, 2));
            // Check to see which is lower
            // If the distance to t_0 is lower, make t_1 = (t_0 + t_1) / 2
            // If the distance to t_1 is lower, make t_0 = (t_0 + t_1) / 2
            if (distance_0 < distance_1) {
                t_1 = (t_0 + t_1) / 2;
            } else {
                t_0 = (t_0 + t_1) / 2;
            }
        }
        // Store the best t value in the section
        bestTs[(int)i * divisions] = (t_0 + t_1) / 2;
        printf("Best t in sector: %f\n", bestTs[(int)i * divisions]);
    } 
    // Return the best value found
    float smallestDist = MAXFLOAT;
    uint8_t tOfBestDist = 0;
    for (int i = 0; i < divisions; i++) {
        vector2 p = position(bestTs[i]);
        float distance = sqrt(pow(p.x - point.x, 2) + pow(p.y - point.y, 2));
        if (distance < smallestDist) {
            smallestDist = distance;
            tOfBestDist = i;
        }
    }

    printf("Best t overall: %f\n", bestTs[tOfBestDist]);
    return bestTs[tOfBestDist];
    
   /*
   // Test a bunch of points and use the closest one
   float distances[iterations];
   for (int i = 0; i < iterations; i++) {
       float t = i / iterations;
       vector2 p = position(t);
       Brain.Screen.drawRectangle(p.x - 1, p.y - 1, 3, 3, vex::color::orange);
       distances[i] = sqrt(pow(p.x - point.x, 2) + pow(p.y - point.y, 2));
   }
    // Find the minimum distance
    float minDistance = distances[0];
    int location = 0;
    for (int i = 1; i < iterations; i++) {
        if (distances[i] < minDistance) {
            minDistance = distances[i];
            location = i;
        }
    }
    // Find the t value that corresponds to the minimum distance
    for (int i = 0; i < iterations; i++) {
        printf("%f, ", distances[i]);
    }
    return location / iterations;
    */
    
}

void Spline::visualise() {
    // This is for testing only. It draws the curve on the Brain's Screen
    // The screen is 480 by 272 pixels. (1, 1) is in the top left corner
    if (points.size() < 4) {
        printf("Error: Spline must have at least 4 points\n");
    } else if (points.size() % 4 != 0) {
        printf("Error: Spline must have a multiple of 4 points\n");
    }
    
    for (int i = 0; i < points.size() - 3; i += 3) {
        CubicBezier curve(points[i], points[i + 1], points[i + 2], points[i + 3]);
        curve.visualise();
    }
}

} // namespace Mobius