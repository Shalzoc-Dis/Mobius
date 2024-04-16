#include "Auto.h"
#include "Robot.h"


namespace Mobius { namespace Robot {


bool Path::isValid() {
    // Check to see if there are any fractional bezier curves
    if (m_points.size() % 4 == 0) {
        // Check each point to see if each value is defined
        for (Position point : m_points) {
            if (!(point.x && point.y && point.angle)) {
                // One value was not defined, so the path is invalid
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}


float Path::length() {

    return 0;
}

// Implementations for the Auto.h file
void Path::visualise() {
    // Draw the path on the screen
}

uint8_t Path::numCurves() {
    return 0;
}

Mobius::CubicBezier Path::getNthCurve(uint8_t n) {
    Mobius::CubicBezier curve;
    curve.p0 = vector2(m_points[n].x, m_points[n].y);
    curve.p1 = vector2(m_points[n + 1].x, m_points[n + 1].y);
    curve.p2 = vector2(m_points[n + 2].x, m_points[n + 2].y);
    curve.p3 = vector2(m_points[n + 3].x, m_points[n + 3].y);
    return curve;
}

void Action::followCurve(CubicBezier& curve, float speed) {
    // Follow the curve
}

void Action::turn(float angle, float speed, Mobius::rotationUnits units) {
    // Turn the robot
}




} // namespace Robot
} // namespace Mobius