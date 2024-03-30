#include "Field.h"

extern vex::brain Brain;
namespace Mobius {


void FieldElement::draw(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    // Set elementColour to the appropriate colour based on the alliance it belongs to 
    vex::color elementColour;
    if (alliance == FieldElement::alliance::RED) {
        elementColour = vex::color::red;
    } else if (alliance == FieldElement::alliance::BLUE) {
        elementColour = vex::color::blue;
    } else {
        elementColour = vex::color::green;
    }

    // Draw the element
    switch (elementType) {
        case FieldElement::type::NET:
            // Draw the circles
            Brain.Screen.setFillColor(elementColour);
            Brain.Screen.setPenColor(elementColour);
            Brain.Screen.setPenWidth(1);
            // The red side will be shown on the right
            if (alliance == FieldElement::alliance::RED) {
                Brain.Screen.drawCircle(x, y, width/5);
                Brain.Screen.drawCircle(x, y - height, width/5);
            } else {
                Brain.Screen.drawCircle(x + width, y, width/5);
                Brain.Screen.drawCircle(x + width, y - height, width/5);
            }
            // Draw the outside of the net
            Brain.Screen.setPenWidth(2);
            Brain.Screen.setFillColor(vex::color::black);
            Brain.Screen.drawRectangle(x, y, width, height);
            break;
        case FieldElement::type::TRIBALL:
            // Draw a triball
            Brain.Screen.setFillColor(elementColour);
            Brain.Screen.setPenColor(elementColour);
            Brain.Screen.setPenWidth(1);
            Brain.Screen.drawCircle(x + width / 2, y - width / 2, width/2);
            break;
        case FieldElement::type::LOW_BARRIER:
            // Draw a low barrier
            Brain.Screen.setFillColor(666666);  // Set the color to gray
            Brain.Screen.setPenColor(vex::color::black);
            Brain.Screen.setPenWidth(1);
            Brain.Screen.drawRectangle(x, y, width, height);
            break;
        case FieldElement::type::HIGH_BARRIER:
            // Draw a high barrier
            Brain.Screen.setFillColor(elementColour);
            Brain.Screen.setPenColor(elementColour);
            Brain.Screen.setPenWidth(1);
            Brain.Screen.drawRectangle(x, y, width, height);
            break;
    }
}

vector2 Field::FieldSpaceToScreenSpace(vector2& point, uint16_t ScreenCornerX, uint16_t ScreenCornerY, uint16_t drawnWidth) {
    // TODO: FieldSpaceToScreenSpace
    // The available screen area is 480x240 pixels
    // 0,0 is the top left corner and y is negative on the screen
    // The field is 365.76cm x 365.76cm
    // 0, 0 on the field is the middle of it
    
    // 
    return vector2(0.0f, 0.0f);
}

void Field::draw() { 
    // Draw background


    // Draw elements

}
} // namespace Mobius