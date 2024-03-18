#include "Bezier.h"

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

} // namespace Mobius