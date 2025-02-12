/**
 * @file Pulley.cpp
 * @author Thomas Conley
 */

#include "pch.h"
#include "Pulley.h"

/// How wide the hub is on each side of the pulley
const double PulleyHubWidth = 3;

/// How deep the belt is into the pulley
const double PulleyBeltDepth = 3;

/// The color to use for pulleys
const wxColour PulleyColor = wxColour(205, 250, 5);

/// The line color to use for the hub
/// First parameter to Cylinder::SetLines
const wxColour PulleyHubLineColor = wxColour(139, 168, 7);

/// The width to draw the lines on the hub
/// Second parameter to Cylinder::SetLines
const int PulleyHubLineWidth = 4;

/// The number of lines to draw on a pulley is the int(diameter / 6.0)
/// Third parameter to Cylinder::SetLines
const double PulleyHubLineCountDiviser = 6.0;

/// hub offset
const int PulleyHubOffset = 7;

/// Get pulley into the correct x spot
const double PulleyBodyOffsetX = 6.8;

/// Get teh pulley into the correct y spot
const int PulleyBodyOffsetY = 6;

/// Get the belt in the correct X spot
const int BeltOffsetX = 3;

/// Get the belt in the correct Y spot
const double BeltOffsetY = 4.6;

/// Depth offset
const int DepthOffset = 10;

/**
 * Constuctor
 * @param diameter
 * @param width
 */
Pulley::Pulley(double diameter, double width) : mDiameter(diameter), mWidth(width), mRotation(0.0)
{
 // Configure the pulley body
 mPulleyBody.SetColour(wxColour(0,0,0));
 mPulleyBody.SetLines(wxColour(0, 0, 0), 0, 0);  // No lines for the pulley body
 mPulleyBody.SetSize(mDiameter, PulleyHubWidth * 5 + 2);

 // Calculate the number of lines for the hubs
 int hubLineCount = diameter / PulleyHubLineCountDiviser;  // Implicit conversion to int

 // Configure the left hub
 mHubLeft.SetColour(PulleyColor);
 mHubLeft.SetLines(PulleyHubLineColor, PulleyHubLineWidth, hubLineCount);
 mHubLeft.SetSize(diameter, PulleyHubWidth);

 // Configure the right hub
 mHubRight.SetColour(PulleyColor);
 mHubRight.SetLines(PulleyHubLineColor, PulleyHubLineWidth, hubLineCount);
 mHubRight.SetSize(diameter, PulleyHubWidth);


}

/**
 * Draw the pulley
 * @param graphics
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
 // Draw the pulley body
 mPulleyBody.Draw(graphics, GetPosition().x - PulleyBodyOffsetX, GetPosition().y - PulleyBodyOffsetY, mRotation);

 // Draw the left hub
 mHubLeft.Draw(graphics, GetPosition().x - mWidth / 2 - PulleyHubWidth, GetPosition().y - PulleyHubOffset, mRotation);

 // Draw the right hub
 mHubRight.Draw(graphics, GetPosition().x + mWidth / 2 + PulleyHubWidth, GetPosition().y - PulleyHubOffset, mRotation);

 // If the pulley is connected to another pulley, draw the connecting belt
 if (mConnectedPulley) {
  wxPoint pos1 = GetPosition();  // Position of this pulley
  wxPoint pos2 = mConnectedPulley->GetPosition();  // Position of the connected pulley

  double radius1 = mDiameter / 2.0;  // Radius of this pulley
  double radius2 = mConnectedPulley->GetDiameter() / 2.0;  // Radius of the connected pulley

  // Calculate the starting and ending points for the vertical belt
  wxPoint start = wxPoint(pos1.x, pos1.y + radius1);  // Bottom edge of this pulley body
  wxPoint end = wxPoint(pos2.x, pos2.y - radius2);    // Top edge of the connected pulley body

  // Set the belt color
  graphics->SetBrush(wxBrush(wxColour(0, 0, 0)));  // Belt color (black)

  // Set the pen to draw the belt line (rectangle)
  graphics->SetPen(wxPen(wxColour(0, 0, 0), 2));  // Black pen for the belt with line thickness 2

  // Draw the vertical belt (rectangle) using SetSize
  // The width of the belt is PulleyBeltDepth (thickness), and the height is the distance between the pulleys
  graphics->DrawRectangle((start.x - PulleyBeltDepth / 2) - BeltOffsetX, start.y - BeltOffsetY,
   PulleyBeltDepth + DepthOffset, end.y - start.y);
 }
}

/**
 * Reset the pulley into its original location
 */
void Pulley::Reset()
{
 mRotation = 0.0;

}

/**
 * Set Rotation of pulley
 * @param rotation
 */
void Pulley::SetRotation(double rotation)
{
 mRotation = rotation;
 mRotationSource.Rotate(mRotation);
}

/**
 * Update the animation
 * @param time
 */
void Pulley::Update(double time)
{
 Component::Update(time);
}

/**
 * Connect the 2 hubs/pulleys together
 * @param otherPulley
 */
void Pulley::BeltTo(std::shared_ptr<Pulley> otherPulley)
{
 mConnectedPulley = otherPulley;

 mPreviousY = GetPosition().y;

 mRotationSource.AddSink(otherPulley);

}


