#include "Bezier.h"
#include "robot-config.h"

namespace Mobius {

vector2 CubicBezier::position(float t) {
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
    // This is for testing only. It draws the curve on the Brain's Screen
    // The screen's usable area is 480 by 240 pixels. (1, 1) is in the top left corner
    Brain.Screen.setPenColor(vex::color::blue);
    Brain.Screen.setPenWidth(1);
    Brain.Screen.drawCircle(p0.x, p0.y, 3);
    Brain.Screen.drawCircle(p3.x, p3.y, 3);
    
    vector2 lastPos = position(0);
    if (derivative == 0) {
        Brain.Screen.setPenColor(vex::color::green);
        for (float t = 0.05; t <= 1.05; t+=0.05) {
            vector2 pos = position(t);
            Brain.Screen.drawLine(lastPos.x, lastPos.y, pos.x, pos.y);
            lastPos = pos;
            //vex::wait(10, vex::msec);
        }
    } else if (derivative == 1) {
        Brain.Screen.setPenColor(vex::color::yellow);
        for (float t = 0.05; t <= 1.05; t+=0.05) {
            vector2 pos = positionDerivative1(t);
            Brain.Screen.drawLine(lastPos.x, lastPos.y, pos.x, pos.y);
            lastPos = pos;
            //vex::wait(10, vex::msec);
        }
    } else if (derivative == 2) {
        Brain.Screen.setPenColor(vex::color::red);
        for (float t = 0.05; t <= 1.05; t+=0.05) {
            vector2 pos = positionDerivative2(t);
            Brain.Screen.drawLine(lastPos.x, lastPos.y, pos.x, pos.y);
            lastPos = pos;
            //vex::wait(10, vex::msec);
        }
    }
}

float CubicBezier::calculateClosestT(vector2 point, uint8_t divisions, uint8_t iterations) {
    // This function uses two points on the curve and calculates the distance from each to the test point
    // The t that produces the farther point is then changed to be the average of the points. The other point stays the same
    // The search is performed anew on these two points. Overall, it runs [iteration] times
    // This is also a divide-and-conquer algorithm to address some gradient ascent pitfalls.
    // The curve is divided up into [divisions] sectors, the start and end points of which are the inputs to the search
    // The smallest distance from the smallest distances of each sector is then returned.

    float delta = 1.0f / divisions; // The difference in t between two points. The 1.0f is important because the result is
                                    // cast to an int if we simply write 1, rounding it and messing up the calculations
    float bestTs[divisions];
    for (int i = 0; i < divisions; i++) {

        float t_0 = delta * i; // Let divisions=1/3. If i=0, t_0=0. If i=1, t_0=1/3. If i=2, t_0=2/3
        float t_1 = delta * (i + 1); // Let divisions=1/3. If i=0, t_0=1/3. If i=1, t_0=2/3. If i=2, t_0=3/3=1

        for (int j = 0; j < iterations; j++) {
            // Calculate the distance from the point to the curve at t_0
            float distance_0 = hypot(position(t_0).x - point.x, position(t_0).y - point.y);
            // Calculate the distance from the point to the curve at t_1
            float distance_1 = hypot(position(t_1).x - point.x, position(t_1).y - point.y);
            // Check to see which is lower
            // If the distance to t_0 is lower, make t_1 = (t_0 + t_1) / 2
            // If the distance to t_1 is lower, make t_0 = (t_0 + t_1) / 2
            if (distance_0 < distance_1) {
                t_1 = (t_0 + t_1) / 2;
            } else {
                t_0 = (t_0 + t_1) / 2;
            }
        }

        bestTs[i] = (t_0 + t_1) / 2;
    }

    // Find best T of the array bestTs
    float smallestDist = MAXFLOAT;
    uint8_t smallestDistLocation;
    for (int i = 0; i < divisions; i++) {
        float distance = hypot(position(bestTs[i]).x - point.x, position(bestTs[i]).y - point.y);
        if (distance < smallestDist) {
            smallestDist = distance;
            smallestDistLocation = i;
        }
    }
    return bestTs[smallestDistLocation];
    
}


void CubicBezier::test() {
    Brain.Screen.printAt( 10, 50, "Hello V5" );
    int generatorSeed = 11;
    int iterations = 5;
    bool regenerate = true;
    bool actionTaken = false;
    int xOffset = 0;
    int yOffset = 0;
    float moveSpeed = 0.05f;
    std::random_device rd;

    while(true) {
        if (Controller1.ButtonX.pressing() || regenerate) {
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
            
            curve.p0 = vector2(width(gen), height(gen));
            curve.p1 = vector2(width(gen), height(gen));
            curve.p2 = vector2(width(gen), height(gen));
            curve.p3 = vector2(width(gen), height(gen));
            curve.visualise();

            // Draw test point and find closest point on curve
            vector2 testPoint(width(gen) + xOffset, height(gen) + yOffset);
            Brain.Screen.setPenColor(vex::color::purple);
            Brain.Screen.setPenWidth(1);
            Brain.Screen.drawCircle(testPoint.x, testPoint.y, 3);
            float closestT = curve.calculateClosestT(testPoint, 5, iterations);
            vector2 posAtClosestT = curve.position(closestT);
            float radius = sqrt(pow(testPoint.x - posAtClosestT.x, 2) + pow(testPoint.y - posAtClosestT.y, 2));
            Brain.Screen.setPenColor(vex::color::cyan);
            Brain.Screen.setFillColor(vex::color::transparent);
            Brain.Screen.drawCircle(testPoint.x, testPoint.y, radius);
            Brain.Screen.drawLine(testPoint.x, testPoint.y, posAtClosestT.x, posAtClosestT.y);
            Brain.Screen.drawCircle(posAtClosestT.x, posAtClosestT.y, 3);

        }
        
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

        if (std::abs(Controller1.Axis3.value()) > 3) {
            yOffset += -Controller1.Axis3.value() * moveSpeed;
            regenerate = true;
        }
        if (std::abs(Controller1.Axis4.value()) > 3) {
            xOffset += Controller1.Axis4.value() * moveSpeed;
            regenerate = true;
        }
        


        // Allow other tasks to run
        vex::this_thread::sleep_for(50);
    }
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