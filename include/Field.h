#pragma once

#include "MobiusUtilities.h"

// This file contains all field data

namespace Mobius {

class FieldElement {

public:
    FieldElement();
    FieldElement(uint8_t type, vector2 position, vector2 size, uint8_t alliance);
    ~FieldElement();

    void draw();

    enum class Type { NET, TRIBALL, LOW_BARRIER, HIGH_BARRIER };
    enum class Alliance { RED, BLUE };

private:
    vector2 position;
    vector2 size;
    uint8_t type;
    uint8_t alliance;

};

struct Field {
    std::vector<FieldElement> elements;
    float width = 365.76; // in cm; 12ft x 12ft
    float height = 365.76; 

    void draw();
    void init();
};



} // namespace Mobius