#pragma once

#include "MobiusUtilities.h"

// This file contains all field data

namespace Mobius {

// A struct to represent a field element
class FieldElement {

public:
    // The type of the field element
    enum class type { NET, TRIBALL, LOW_BARRIER, HIGH_BARRIER };
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



private:
    // The type of the field element
    FieldElement::type elementType;
    // The position of the field element in field space (0, 0) is the field centre
    vector2 position;
    // The size of the field element in cm
    vector2 size;
    // The alliance of the field element belongs to
    FieldElement::alliance alliance;
};

// A struct to represent the field
struct Field {
    // This are the elements on the field
    std::vector<FieldElement> elements;
    float width = 365.76; // In cm; 12ft x 12ft

    // Draw the field on the Brain's Screen
    void draw();
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
    vector2 FieldSpaceToScreenSpace(vector2& point, uint16_t ScreenCornerX, uint16_t ScreenCornerY, uint16_t drawnWidth);
};



} // namespace Mobius