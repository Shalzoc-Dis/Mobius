#pragma once

#include "MobiusUtilities.h"

namespace Mobius {

// Reference: https://en.wikipedia.org/wiki/Bézier_curve
struct CubicBezier {
    vector2 p0, p1, p2, p3;

    CubicBezier();
    CubicBezier(vector2 p0, vector2 p1, vector2 p2, vector2 p3);
    ~CubicBezier();

    vector2 position(float t);
    vector2 positionDerivative1(float t);
    void visualise();   // This is for testing only. It draws the curve on the Brain's Screen

}; // struct CubicBezier

} // namespace Mobius