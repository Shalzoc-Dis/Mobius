#pragma once

#include "Robot.h"



namespace Mobius { namespace Robot {

// This takes 

// This is a struct to represent a point on a path which specifies a position and a rotation the robot should have at that point

// This is to contain a path. Each note on the path has a position and a rotation
struct CubicBezier;
struct Path {
    std::vector<Position> m_points;

    Path() {};
    ~Path() {};

    // @brief Checks to see if the path is valid
    bool isValid();

    // @brief Draws the path on the Brain's Screen
    void visualise();

    // @brief returns the length of the path in cm
    float length();
    // @return the number of curves in the path
    uint8_t numCurves();

    // @brief Returns a reference to the nth curve in the path
    // @param n The index of the curve, starting at 0
    Mobius::CubicBezier getNthCurve(uint8_t n);

};

// @brief This is something the robot can do
struct Action {

    enum class Type {
        FOLLOW_CURVE, TURN, INTAKE_OUT, INTAKE_IN, WAIT
    };

    Type m_type;


    void followCurve(const CubicBezier& curve);
    void turn(float angle);
    void followPath(const Path& path);


    // @brief This function operates the intake
    void operateIntake();

    // @brief This is a function to wait for a certain amount of time
    // @param time The time to wait in milliseconds
    void wait(double time);

    // @brief This function performs the action
    void run();



    // @brief An action to follow a curve
    // @param type The type of action to perform
    // @param value The value to use for the action
    Action(CubicBezier& curve, float speed);

    // @brief An action to turn the robot
    // @param angle The angle to turn ccw
    // @param speed The speed to turn at
    // @param units The units the angle is in
    Action(float angle, float speed, Mobius::rotationUnits units);

    // @brief An actinon to follow a path
    // @param path The path to follow
    // @param speed The speed to follow the path at
    // @param lookInMoveDirection Whether the robot should look in the direction it is moving. If true, it will point turn to the final position's rotation
    Action(Path& path, float speed, bool lookInMoveDirection);

    // @brief An action to operate the intake
    // @param in Whether the intake should be in or out
    // @param speed The speed to operate the intake at
    // @param time The time to operate the intake for
    Action(bool in, float speed, float time);

    // @brief An action to wait for a certain amount of time
    // @param time The time to wait in milliseconds
    Action(double waitTime);




};

// @brief This is a struct to represent a plan for the autonomous period
struct AutonomousPlan {

    enum class state {
        RUNNING, PAUSED, SUSPENDED
    };

    uint16_t m_currentAction;
    state m_state;
    std::vector<Action> m_actions;

    // @brief This function runs the plan. It performs one action at a time
    void execute();
    // @brief This function pauses the plan until resumed
    void pause();
    // @brief This function resumes the plan
    void resume();
    // @brief This function suspends the plan for a certain amount of time
    // @param time The time to suspend the plan for in milliseconds
    void suspend(double time);


};

} // namespace Robot
} // namespace Mobius