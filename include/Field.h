#pragma once

#include "MobiusUtilities.h"

// This file contains all field data

namespace Mobius {

class FieldElement {

public:
    enum class type { NET, TRIBALL, LOW_BARRIER, HIGH_BARRIER };
    enum class alliance { RED, BLUE };

    FieldElement() {};
    FieldElement(FieldElement::type type, vector2 position, vector2 size, FieldElement::alliance alliance);
    ~FieldElement() {};

    void draw();

    

private:
    FieldElement::type elementType;
    vector2 position;
    vector2 size;
    FieldElement::alliance alliance;

};

struct Field {
    std::vector<FieldElement> elements;
    float width = 365.76; // in cm; 12ft x 12ft
    float height = 365.76; 

    void draw();
    void init();
};



} // namespace Mobius