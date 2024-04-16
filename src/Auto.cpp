#include "Auto.h"
#include "Robot.h"


extern vex::brain Brain;

namespace Mobius { namespace Robot {


bool Path::isValid() {
    // Check to see if there are any fractional bezier curves
    if (m_points.size() % 4 == 0) {
        // Check each point to see if each value is defined
        for (Position point : m_points) {
            if (!(point.x && point.y && point.angle)) {
                // One value was not defined, so the path is invalid
                printf("Path Invalid!\n");
                return false;
            }
        }
        return true;
    } else {
        printf("Path Invalid!\n");
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
    if (isValid())
        return m_points.size() / 4;
    else 
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

void Action::followCurve(Mobius::CubicBezier& curve, float precision, float speed) {
    // Follow the curve
    vector2 location;
    do {
        location.x = Robot::FieldCentricPosition.x;
        location.y = Robot::FieldCentricPosition.y;

        // Find the closest point on the curve
        float closestT = curve.calculateClosestT(location);
        float nextT;
        if (closestT + precision > 1)
            nextT = 1;
        else
            nextT = closestT + precision;

        vector2 targetPosition = curve.position(nextT);
        vector2 toClosestPoint = location - targetPosition;

        Robot::desiredVelocity = toClosestPoint.normalised() * speed;

        curve.visualise();
        Brain.Screen.setPenColor(vex::yellow);
        Brain.Screen.drawCircle(location.x, location.y, 3);
        Brain.Screen.drawLine(location.x, location.y, targetPosition.x, targetPosition.y);
        vex::wait(500, vex::timeUnits::msec);

    } while (location.x - curve.p3.x > precision && location.y - curve.p3.y > precision);

    // For testing purposes; remove before use
    printf("Done");
    while (true) { vex::this_thread::sleep_for(100); }
}

void Action::turn(float angle, float speed, Mobius::rotationUnits units) {
    // Turn the robot
}

void Action::run() {
    printf("Running action type %d...\n", m_type);

    switch(m_type) {
        case Action::Type::FOLLOW_CURVE:
            followCurve(m_curve, m_precision, m_speed); break;
        case Action::Type::TURN:
            turn(m_angle, m_speed, m_rotationUnits); break;
        default: break;
    }

    printf("Action complete.\n");
}



void AutonomousPlan::execute() {

    m_currentAction = 0;

    for (int i = m_currentAction; i < m_actions.size(); i++) {
        if (m_state == AutonomousPlan::state::RUNNING)
            m_actions[i].run();
        else if (m_state == AutonomousPlan::state::PAUSED)
            vex::wait(100, vex::timeUnits::msec);
    }
}

} // namespace Robot
} // namespace Mobius