/**
 * @file Crank.cpp
 * @author Thomas Conley
 */
#include "pch.h"
#include "Crank.h"
#include "RotationSource.h"

/// The width of the crank on the screen in pixels
const int CrankWidth = 10;

/// The depth of the crank away from the screen in pixels
const int CrankDepth = 20;

/// The length of the crank in pixels
const int CrankLength = 50;

/// The diameter to draw the crank handle
const int HandleDiameter = 7;

/// How long the handle is in pixels
const int HandleLength = 40;

/// How much to the left of the crank X the handle starts in pixels
const int HandleStartX = -10;

/// Crank color
const wxColour CrankColor = wxColour(220, 220, 220);

/// Line color for the rod
const wxColour CrankHandleLineColor = wxColour(100, 100, 100);


/// Constructor
Crank::Crank()
{
 mHandle.SetSize(HandleDiameter, HandleLength);
 mHandle.SetColour(CrankColor);
 mHandle.SetLines(CrankHandleLineColor, 1, 4);
}

/**
 * Draw the crank
 * @param graphics
 */
void Crank::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

 // Calculate the rotation angle in radians
 mAngle = mRotation * 2 * M_PI;

 double handleY = GetPosition().y + cos(mAngle) * CrankLength; // Handle's Y position

 // Draw the handle (cylinder) first
 graphics->PushState();

 mHandle.SetSize(HandleDiameter, HandleLength);
 mHandle.SetColour(CrankColor);
 mHandle.SetLines(CrankHandleLineColor, 1, 4);

 // Draw at the calculated position
 //mHandle.Draw(graphics, handleX - HandleDiameter / 2 - 5, handleY + 35, mAngle);
 mHandle.Draw(graphics, GetPosition().x - 15, handleY - 17, mAngle);

 graphics->PopState(); // Restore state after drawing the handle

 // Draw the crank arm (rectangle) next
 graphics->PushState();

 // Calculate the height of the crank arm
 double crankHeight = (CrankLength * cos(mAngle)) * 1.2;

 crankHeight = std::max(crankHeight, 20.0);


 // Draw the crank arm
 graphics->SetBrush(wxBrush(CrankColor));
 graphics->DrawRectangle(GetPosition().x + HandleStartX,  GetPosition().y - 16, CrankWidth,(CrankLength * cos(mAngle)) * 1.2);
 graphics->DrawRectangle(GetPosition().x + HandleStartX,  GetPosition().y - 17, CrankWidth,crankHeight); //(CrankLength * cos(mAngle)) * 1.2);


 graphics->PopState();

}

/**
 * Reset the crank into its original position
 */
void Crank::Reset()
{
 mRotation = 0.0;
 mTime = 0.0;
}

/**
 * Rotate the handle with the rotation source
 * @param rotation
 */
void Crank::Rotate(double rotation)
{
 mRotationSource.Rotate(rotation);
}

/**
 * Update the animation
 * @param delta
 */
void Crank::Advance(double delta)
{
 double time = delta - mTime;
 mTime = delta;

 // Update the rotation in turns
 mRotation += delta * mSpeed;

 // Keep mRotation in [0, 1) to simplify calculations
 mRotationSource.Rotate(mRotation);
}

/**
 * Set the speed
 * @param speed
 */
void Crank::SetSpeed(double speed)
{
 mSpeed = speed/2;
}








