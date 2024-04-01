#pragma once

#include "MobiusUtilities.h"
#include "FieldElement.h"

// This file contains all field data

namespace Mobius {
// A struct to represent the field
struct Field {
    // This are the elements on the field
    std::vector<FieldElement> m_dynamicElements;
    std::array<FieldElement, 11> m_staticElements;

    const float m_width = 365.76; // In cm; 12ft x 12ft

    // Draw the field on the Brain's Screen
    void draw(uint8_t ScreenCornerX, uint8_t ScreenCornerY, uint8_t drawnWidth);
    // Set up a field object and all its elements
    void init();

    private:

    /*
     * @brief Converts a point in field space to screen space
     * @param point The point in field space
     * @param ScreenCornerX The x coordinate of the top left corner of the screen
     * @param ScreenCornerY The y coordinate of the top left corner of the screen
     * @param drawnWidth The width of the field drawn on the screen
    */
    vector2 FieldSpaceToScreenSpace(vector2 point, uint16_t ScreenCornerX, uint16_t ScreenCornerY, uint16_t drawnWidth);
};



} // namespace Mobius