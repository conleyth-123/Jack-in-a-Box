/**
 * @file Shaft.cpp
 * @author Thomas Conley
 */
#include "pch.h"
#include "Shaft.h"

/// The color to draw the shaft
const wxColour ShaftColor = wxColour(220, 220, 220);

/// The color to draw the lines on the shaft
/// First parameter to Cylinder::SetLines
const wxColour ShaftLineColor = wxColour(100, 100, 100);

/// The width to draw the lines on the shaft
/// Second parameter to Cylinder::SetLines
const int ShaftLinesWidth = 1;

/// The number of lines to draw on the shaft
/// Third parameter to Cylinder::SetLines
const int ShaftNumLines = 4;

/// Constructor
Shaft::Shaft()
{

}

/**
 * Draw the shaft
 * @param graphics
 */
void Shaft::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
 // Set the color for the shaft body
 graphics->SetBrush(wxBrush(ShaftColor));  // Set the color for the shaft
 graphics->SetPen(wxPen(wxColour(0, 0, 0), 1));  // Set pen for border (if necessary)

 // Use the mCylinder to set line properties and draw the shaft
 mCylinder.SetLines(ShaftLineColor, ShaftLinesWidth, ShaftNumLines);  // Set lines for the cylinder

 // Now draw the cylinder (shaft) at the given position with rotation
 mCylinder.Draw(graphics, GetPosition().x, GetPosition().y - 8, mRotation);

}

/**
 * Reset the shaft to its original spot
 */
void Shaft::Reset()
{
 mRotation = 0.0;

}

/**
 * Set the rotation
 * @param rotation
 */
void Shaft::SetRotation(double rotation)
{
 mRotation = rotation;
 mRotationSource.Rotate(mRotation);
}

/**
 * Update the Shaft animation
 * @param time
 */
void Shaft::Update(double time)
{
 Component::Update(time);
}

/**
 * Set the size of the shaft
 * @param diameter
 * @param length
 */
void Shaft::SetSize(double diameter, double length) {
 mCylinder.SetSize(diameter, length);
}

/**
 * Set the offset of the cyliner
 * @param offset
 */
void Shaft::SetOffset(double offset) {
 mCylinder.SetOffset(offset);
}




