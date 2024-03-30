#pragma once

#include "Robot.h"


namespace Mobius {

// This is for a cursor object so the user can interact with the autonomous planner
struct cursor {
    vector2 position;
    vector2 velocity;
    vector2 acceleration;

    enum class State { IDLE, HOVERING };

    void updatePosition();
    void render();
};

void PlanRoute();





} // namespace Mobius