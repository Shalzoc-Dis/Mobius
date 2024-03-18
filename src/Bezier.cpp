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
    Brain.Screen.clearScreen(vex::color::black);
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
    if (derivative == 0) {
        for (float t = 0; t <= 1 - 0.01; t +=0.01) {
            vector2 p = position(t);
            vector2 p1 = position(t + 0.01);
            Brain.Screen.drawLine(p.x, p.y, p1.x, p1.y);
            vex::wait(10, vex::msec);
        }
    } else if (derivative == 1) {
        for (float t = 0; t <= 1 - 0.01; t +=0.01) {
            vector2 p = positionDerivative1(t);
            vector2 p1 = positionDerivative1(t + 0.01);
            Brain.Screen.drawLine(p.x, p.y, p1.x, p1.y);
            vex::wait(10, vex::msec);
        }
    } else if (derivative == 2) {
        for (float t = 0; t <= 1 - 0.01; t +=0.01) {
            vector2 p = positionDerivative2(t);
            vector2 p1 = positionDerivative2(t + 0.01);
            Brain.Screen.drawLine(p.x, p.y, p1.x, p1.y);
            vex::wait(10, vex::msec);
        }
    }

}

} // namespace Mobius