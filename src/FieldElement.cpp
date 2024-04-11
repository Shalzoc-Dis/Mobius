#include "FieldElement.h"

extern vex::brain Brain;

namespace Mobius {

void FieldElement::draw(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    // Set elementColour to the appropriate colour based on the alliance it belongs to 
    vex::color elementColour;
    if (m_alliance == FieldElement::alliance::RED) {
        elementColour = vex::color::red;
    } else if (m_alliance == FieldElement::alliance::BLUE) {
        elementColour = vex::color::blue;
    } else {
        elementColour = vex::color::green;
    }

    // Draw the element
    switch (m_elementType) {
        case FieldElement::type::NET:
            // Draw the circles
            Brain.Screen.setFillColor(elementColour);
            Brain.Screen.setPenColor(elementColour);
            Brain.Screen.setPenWidth(1);
            // The red side will be shown on the right
            if (m_alliance == FieldElement::alliance::RED) {
                Brain.Screen.drawCircle(x - width/2, y - height/2, width/5);
                Brain.Screen.drawCircle(x - width/2, y + height/2, width/5);
            } else {
                Brain.Screen.drawCircle(x + width/2, y - height/2, width/5);
                Brain.Screen.drawCircle(x + width/2, y + height/2, width/5);
            }
            // Draw the outside of the net
            Brain.Screen.setPenWidth(2);
            Brain.Screen.setFillColor(vex::color::black);
            Brain.Screen.drawRectangle(x - width/2, y - width/2, width, height);
            break;
        case FieldElement::type::TRIBALL:
            // Draw a triball
            Brain.Screen.setFillColor(elementColour);
            Brain.Screen.setPenColor(elementColour);
            Brain.Screen.setPenWidth(1);
            Brain.Screen.drawCircle(x, y, width/2);
            break;
        case FieldElement::type::LOW_BARRIER:
            // Draw a low barrier
            //Brain.Screen.setFillColor("#666666");  // Set the color to gray
            Brain.Screen.setFillColor(vex::color::purple);
            Brain.Screen.setPenColor(vex::color::black);
            Brain.Screen.setPenWidth(1);
            Brain.Screen.drawRectangle(x - width/2, y - height/2, width, height);
            break;
        case FieldElement::type::HIGH_BARRIER:
            // Draw a high barrier
            Brain.Screen.setFillColor(elementColour);
            Brain.Screen.setPenColor(elementColour);
            Brain.Screen.setPenWidth(1);
            Brain.Screen.drawRectangle(x - width/2, y - height/2, width, height);
            break;
        case FieldElement::type::LOAD_ZONE_BAR:
            // Draw a load zone bar
            Brain.Screen.setPenColor(elementColour);
            Brain.Screen.setPenWidth(3);
            if (m_alliance == FieldElement::alliance::RED) {
                // Draw the diagonal line
            } else if (m_alliance == FieldElement::alliance::BLUE) {
                // Draw the diagonal line
            }
            break;
    }
}

} // namespace Mobius