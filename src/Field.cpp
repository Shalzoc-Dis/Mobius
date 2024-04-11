#include "Field.h"

extern vex::brain Brain;
namespace Mobius {

void Field::init() {

    for (int i = 0; i < m_staticElements.size(); i++) {
        m_staticElements[i] = FieldElement();
    }

    // Add the static elements

    // Nets
    m_staticElements[0] = Mobius::FieldElement(Mobius::FieldElement::type::NET, vector2(-m_width/2.0f + 58.62f/2.0f, 0), vector2(58.62f, 199.71f), Mobius:: FieldElement::alliance::BLUE);

    // Low barriers
    m_staticElements[2] = Mobius::FieldElement(Mobius::FieldElement::type::LOW_BARRIER, vector2(0, 0), vector2(6.05f, 245.44f), Mobius:: FieldElement::alliance::NONE);


    // Add the initial triballs. Their placement varies depending on the match type
    m_dynamicElements.reserve(12);
    for (Mobius::FieldElement element : m_dynamicElements) {
        m_dynamicElements.push_back(element);
    }
}


vector2 Field::FieldSpaceToScreenSpace(vector2 point, uint16_t ScreenCornerX, uint16_t ScreenCornerY, uint16_t drawnWidth) {
    // The available screen area is 480x240 pixels
    // 0,0 is the top left corner and y is negative on the screen
    // The field is 365.76cm x 365.76cm
    // 0, 0 on the field is the middle of it
    
    // The distance one pixel represents in cm
    float cmPerPixel = m_width / drawnWidth;

    // Middle of the field on the screen
    vector2 middleOfFieldOnScreen(ScreenCornerX + drawnWidth / 2, ScreenCornerY + drawnWidth / 2);

    vector2 pointOnScreen;
    pointOnScreen.x = point.x / cmPerPixel - middleOfFieldOnScreen.x;
    pointOnScreen.y = middleOfFieldOnScreen.y - point.y / cmPerPixel;

    return pointOnScreen;
}

void Field::draw(uint8_t ScreenCornerX, uint8_t ScreenCornerY, uint8_t drawnWidth) {

    Brain.Screen.clearScreen();

    // Draw background
    Brain.Screen.setFillColor("#939393");
    Brain.Screen.setPenColor(vex::color::black);
    Brain.Screen.setPenWidth(2);
    Brain.Screen.drawRectangle(ScreenCornerX, ScreenCornerY, drawnWidth, drawnWidth);

    // Draw static elements
    for (int i = 0; i < m_staticElements.size(); i++) {
        // TEST Circle
        Brain.Screen.setFillColor(vex::color::red);
        Brain.Screen.drawCircle(240, 120, 10);

        printf("Drawing element %i of alliance %i\n", m_staticElements[i].m_elementType, m_staticElements[i].m_alliance);
        // Convert the element's position to screen space
        vector2 elementPosition = FieldSpaceToScreenSpace(m_staticElements[i].m_position, ScreenCornerX, ScreenCornerY, drawnWidth);
        printf("Element Screen position: %f, %f\n", elementPosition.x, elementPosition.y);
        // Convert the element's size to screen space
        vector2 elementSize = elementSize / (m_width / drawnWidth);
        printf("Element size: %f, %f\n", elementSize.x, elementSize.y);

        // Draw the element
        m_staticElements[i].draw(elementPosition.x, elementPosition.y, elementSize.x, elementSize.y);
    }

    // Draw dynamic elements
    for (FieldElement element : m_dynamicElements) {
        printf("Drawing element %i of alliance %i\n", element.m_elementType, element.m_alliance);
        // Convert the element's position to screen space
        vector2 elementPosition = FieldSpaceToScreenSpace(element.m_position, ScreenCornerX, ScreenCornerY, drawnWidth);
        printf("Element Screen position: %f, %f\n", elementPosition.x, elementPosition.y);
        // Convert the element's size to screen space
        vector2 elementSize = element.m_size / (m_width / drawnWidth);
        printf("Element size: %f, %f\n", elementSize.x, elementSize.y);

        // Draw the element
        element.draw(elementPosition.x, elementPosition.y, elementSize.x, elementSize.y);
    }

    } // draw

} // namespace Mobius