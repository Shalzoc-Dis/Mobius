#include "Robot.h"

int Mobius::positioningComputer() {

    vex::timer PositioningComputerUpdateTimer;

    vector2 gpsAcceleration(0, 0);
    vector2 gpsLastAcceleration(0, 0);
    vector2 gpsVelocityByAcceleration(0, 0);
    vector2 gpsLastVelocityByAcceleration(0, 0);

    Position gpsPosition(0, 0, 0);
    Position gpsLastPosition(0, 0, 0);

    float gpsLastAngularAcceleration = 0;
    float gpsAngularAcceleration = 0;
    float gpsLastAngularVelocity = 0;
    float gpsAngularVelocity = 0;


    while (true) {        
        float timeSinceLastUpdate = PositioningComputerUpdateTimer.time(vex::msec);
        PositioningComputerUpdateTimer.clear();

        // Odometry


        // GPS
        if (gps.quality() < 40) {
            // GPS is not accurate enough
            //TODO: Broadcast that the gps is not accurate
        }

        // Calculate the velocity based on integration of acceleration
        gpsLastAcceleration = gpsAcceleration;
        gpsAcceleration = vector2(gps.acceleration(vex::axisType::xaxis), gps.acceleration(vex::axisType::yaxis));
        // Trapezoidal sum of last acceleration, current acceleration, and time since last update
        gpsLastVelocityByAcceleration = gpsVelocityByAcceleration;
        gpsVelocityByAcceleration.x = (gpsLastAcceleration.x + gpsAcceleration.x) / 2 * timeSinceLastUpdate;
        gpsVelocityByAcceleration.y = (gpsLastAcceleration.y + gpsAcceleration.y) / 2 * timeSinceLastUpdate;


        // Calculate the velocity based on change in position
        vector2 gpsVelocityByPosition;
        gpsLastPosition = gpsPosition;
        gpsPosition = Position(gps.xPosition(), gps.yPosition(), gps.heading() / 180 * M_PI);
        gpsVelocityByPosition.x = (gpsPosition.x - gpsLastPosition.x) / timeSinceLastUpdate;
        gpsVelocityByPosition.y = (gpsPosition.y - gpsLastPosition.y) / timeSinceLastUpdate;

        // TODO: GPS Velocity Comparison
        // Compare the two velocities
        // If their derivative is less than some value, then the velocity is accurate
        // If both are are accurate, they are averaged to get the final velocity
        // If only one is accurate, only that one is used
        // If neither are accurate, the velocity is not updated
        vector2 gpsDeltaVelocityByAcceleration = gpsVelocityByAcceleration - gpsLastVelocityByAcceleration;
        if (gpsDeltaVelocityByAcceleration.magnitude() > Robot::maxVelocityInDirection(10)) {
            
        }


        // Inertial sensor


        // Check for accuracy
        //TODO: Update with inertial sensor
        Robot::FieldCentricPosition = gpsPosition;
        Robot::acceleration = gpsAcceleration;
        Robot::angularAcceleration = gps.acceleration(vex::axisType::zaxis);

        // Vision?
        vex::task::sleep(20);
    }
    return 0;
}