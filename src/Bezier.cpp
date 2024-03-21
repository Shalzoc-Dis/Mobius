#include "Bezier.h"
#include "robot-config.h"

namespace Mobius {

vector2 CubicBezier::position(float t) {
    if (t < 0 || t > 1) {
    t /= t;
    t = abs(t);
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
        t = abs(t);
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
        t = abs(t);
        printf("Error: Bezier t must be between 0 and 1\n");
    }

    vector2 res;
    res.x = 6 * (1 - t) * (p2.x - 2 * p1.x + p0.x) + 6 * t * (p3.x - 2 * p2.x + p1.x);
    res.y = 6 * (1 - t) * (p2.y - 2 * p1.y + p0.y) + 6 * t * (p3.y - 2 * p2.y + p1.y);
    return res;
}

void CubicBezier::visualise(int derivative) {
    // This is for testing only. It draws the curve on the Brain's Screen
    // The screen is 480 by 272 pixels. (1, 1) is in the top left corner
    Brain.Screen.setPenColor(vex::color::blue);
    Brain.Screen.setPenWidth(1);
    Brain.Screen.drawCircle(p0.x, p0.y, 3);
    Brain.Screen.drawCircle(p3.x, p3.y, 3);
    Brain.Screen.setPenColor(vex::color::green);
    Brain.Screen.drawCircle(p1.x, p1.y, 3);
    Brain.Screen.drawCircle(p2.x, p2.y, 3);
    Brain.Screen.drawLine(p0.x, p0.y, p1.x, p1.y);
    Brain.Screen.drawLine(p2.x, p2.y, p3.x, p3.y);
    Brain.Screen.setPenColor(vex::color::red);

    vector2 lastPos = position(0);
    if (derivative == 0) {
        for (float t = 0.05; t <= 1 - 0.05; t +=0.05) {
            vector2 p1 = position(t);
            Brain.Screen.drawLine(lastPos.x, lastPos.y, p1.x, p1.y);
            lastPos = p1;
            //vex::wait(10, vex::msec);
        }
    } else if (derivative == 1) {
        for (float t = 0.05; t <= 1 - 0.05; t +=0.05) {
            vector2 p1 = positionDerivative1(t);
            Brain.Screen.drawLine(lastPos.x, lastPos.y, p1.x, p1.y);
            lastPos = p1;
            //vex::wait(10, vex::msec);
        }
    } else if (derivative == 2) {
        for (float t = 0.05; t <= 1 - 0.05; t +=0.05) {
            vector2 p1 = positionDerivative2(t);
            Brain.Screen.drawLine(lastPos.x, lastPos.y, p1.x, p1.y);
            lastPos = p1;
            //vex::wait(10, vex::msec);
        }
    }

}

float CubicBezier::calculateClosestT(vector2 point, int iterations) {
    
    // FIXME: Bezier distance function
    // Works sometimes, but gets stuck on some gradient ascent problems. It is probably good enough
    // This function takes a point and tries to find the closest t value on the curve to that point
    // To do this, it first measures the distances to the point and both end points (t=0 and t=1)
    // It then performs the bisection method, going between the closest point and a t between the two end points
    float t_0 = 0;
    float t_1 = 1;
    for(int i = 0; i < iterations; i++) {
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
    return (t_0 + t_1) / 2;
    
   /*
   // Test a bunch of points and use the closest one
   float distances[iterations];
   for (int i = 0; i < iterations; i++) {
       float t = i / iterations;
       vector2 p = position(t);
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