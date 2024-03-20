#include "Robot.h"

int Mobius::positioningComputer() {
    while (true) {
        // Odometry


        // GPS
        if (gps.quality() < 40) {
            // GPS is not accurate enough
            //TODO: Broadcast that the gps is not accurate
        }
        Position gpsPosition(gps.xPosition(), gps.yPosition(), gps.heading() / 180 * M_PI);
        vector2 gpsAcceleration(gps.acceleration(vex::axisType::xaxis), gps.acceleration(vex::axisType::yaxis));


        // Inertial sensor


        // Check for accuracy
        Robot::FieldCentricPosition = gpsPosition;

        // Vision?
        vex::task::sleep(20);
    }
    return 0;
}