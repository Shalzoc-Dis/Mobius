#pragma once

#include "MobiusUtilities.h"

// This file contains all field data

namespace Mobius {

// A struct to represent a field element
class FieldElement {

public:
    // The type of the field element
    enum class type { NET, TRIBALL, LOW_BARRIER, HIGH_BARRIER, LOAD_ZONE_BAR };
    // The alliance of the field element
    enum class alliance { RED, BLUE, NONE };

    FieldElement() {};

    /*
        @param type The type of the field element
        @param position The position of the field element in field space (0, 0) is the field centre
        @param size The size of the field element in cm
        @param alliance The alliance of the field element belongs to
    */
    FieldElement(FieldElement::type type, vector2 position, vector2 size, FieldElement::alliance alliance);

    ~FieldElement() {};

    /*
        @brief Draws the field element on the Brain's Screen
        @param x The x coordinate of the top left corner of the field element on the screen
        @param y The y coordinate of the top left corner of the field element on the screen
        @param width The width of the field element on the screen
        @param height The height of the field element on the screen
    */
    void draw(uint16_t x, uint16_t y, uint16_t width, uint16_t height);



    // The type of the field element (https://www.vexrobotics.com/over-under-manual#AppA-Specs)
    FieldElement::type m_elementType;
    // The position of the field element in field space (0, 0) is the field centre. It is the centre point of the element
    vector2 m_position;
    // The size of the field element in cm. size/2 is the distance from the centre to the edge of the element
    vector2 m_size;
    // The alliance of the field element belongs to
    FieldElement::alliance m_alliance;
};

} // namespace Mobius