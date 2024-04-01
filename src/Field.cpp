#include "Field.h"

extern vex::brain Brain;
namespace Mobius {

void Field::init() {
    // Add the static elements
    m_staticElements[0] = FieldElement(FieldElement::type::NET, vector2(-m_width/2.0f + 58.62f/2.0f, 0), vector2(58.62f, 199.71f), FieldElement::alliance::BLUE);

    // Add the initial triballs. Their placement varies depending on the match type
    m_dynamicElements.reserve(12);
}


vector2 Field::FieldSpaceToScreenSpace(vector2 point, uint16_t ScreenCornerX, uint16_t ScreenCornerY, uint16_t drawnWidth) {
    // The available screen area is 480x240 pixels
    // 0,0 is the top left corner and y is negative on the screen
    // The field is 365.76cm x 365.76cm
    // 0, 0 on the field is the middle of it
    
    // The distance one pixel represents in cm
    float cmPerPixel = m_width / drawnWidth;

    // Middle of the field on the screen
    vector2 middleOfFieldOnScreen(ScreenCornerX + drawnWidth / 2, ScreenCornerY - drawnWidth / 2);

    vector2 pointOnScreen;
    pointOnScreen.x = point.x / cmPerPixel - middleOfFieldOnScreen.x;
    pointOnScreen.y = middleOfFieldOnScreen.y - point.y / cmPerPixel;

    return pointOnScreen;
}

    void Field::draw(uint8_t ScreenCornerX, uint8_t ScreenCornerY, uint8_t drawnWidth) {

    // Draw background
    Brain.Screen.setFillColor("#939393");
    Brain.Screen.setPenColor(vex::color::black);
    Brain.Screen.setPenWidth(2);
    Brain.Screen.drawRectangle(ScreenCornerX, ScreenCornerY, drawnWidth, drawnWidth);

    // Draw static elements
    for (FieldElement element : m_staticElements) {
        printf("Drawing element %i of alliance %i\n", element.m_elementType, element.m_alliance);
        // Convert the element's position to screen space
        vector2 elementPosition = FieldSpaceToScreenSpace(element.m_position, ScreenCornerX, ScreenCornerY, drawnWidth);
        // Convert the element's size to screen space
        vector2 elementSize = elementSize / (m_width / drawnWidth);

        // Draw the element
        element.draw(elementPosition.x, elementPosition.y, elementSize.x, elementSize.y);
    }

    // Draw dynamic elements
    for (FieldElement element : m_dynamicElements) {
        printf("Drawing element %i of alliance %i\n", element.m_elementType, element.m_alliance);
        // Convert the element's position to screen space
        vector2 elementPosition = FieldSpaceToScreenSpace(element.m_position, ScreenCornerX, ScreenCornerY, drawnWidth);
        // Convert the element's size to screen space
        vector2 elementSize = element.m_size / (m_width / drawnWidth);

        // Draw the element
        element.draw(elementPosition.x, elementPosition.y, elementSize.x, elementSize.y);
    }

    } // draw

} // namespace Mobius