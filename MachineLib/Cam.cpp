/**
 * @file Cam.cpp
 * @author Thomas Conley
 */

#include "pch.h"
#include "Cam.h"

/// Width of the cam on the screen in pixels
const double CamWidth = 17;

/// Cam diameter
const double CamDiameter = 60;

/// How big is the hole in the cam?
const double HoleSize = 8;

/// The key image
const std::wstring KeyImage = L"/key.png";

/// The key image size
const int KeyImageSize = 20;

/// The amount the key drops into the hole
const int KeyDrop = 10;

/// Key start Offset
int KeyStartOffset = 35;

/// hole x position offset
const double HoleOffset = 3;
/// get the key into the right spot
const double KeyOffset = 89;
/// Put the key into the correct y point
double KeyY = 185;
/// the key's starting point for reset
double KeyYStart = 185;



/// Constructor
/// @param imagesDir
Cam::Cam(const std::wstring& imagesDir) : mImagesDir(imagesDir)
{
 mKey.SetImage(imagesDir + KeyImage);
 mKey.Rectangle(-KeyImageSize/2, 0, KeyImageSize, KeyImageSize);

 mHoleAngle = mRotation;

}

/**
 * Draw the cam
 * @param graphics
 */
void Cam::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
 graphics->PushState();

 // Translate to the cam's position
 graphics->Translate(GetPosition().x - 5, GetPosition().y - 5);

 // Key bottom position
 double keyBottomY = -(KeyStartOffset - KeyDrop);


 mKey.DrawPolygon(graphics, GetPosition().x + KeyOffset, GetPosition().y - KeyStartOffset + KeyY);

 // Draw the cam
 mCam.SetSize(CamDiameter, CamWidth);
 mCam.Draw(graphics, 0, 0, mRotation / 5);

 // Calculate the position and size of the hole (dot)
 double dotX = 0;  // Centered horizontally
 double maxDisplacement = CamDiameter / 2; // Max vertical displacement
 double dotY = maxDisplacement * std::cos(mRotation); // Oscillates based on rotation




 // Check if the ellipse is below the key's bottom
 if (dotY < keyBottomY)
 {
  mMaxNotReached = false;
  if (KeyY == KeyYStart)
  {
   KeyY += 10;

   // Notify all listeners
   for (auto listener : mKeyDropListeners)
   {
    listener->KeyDroppedTriggered(KeyY);
   }
  }
  graphics->PopState();
  return; // Stop drawing the ellipse
 }


 // Calculate normalizedY to control the dynamic height of the ellipse
 double normalizedY = dotY / maxDisplacement; // Range: -1 (top) to 1 (bottom)
 mHoleAngle = 1.0 - std::abs(normalizedY);


 // Adjust the hole size based on the mHoleAngle
 double ellipseHeight = HoleSize * mHoleAngle; // Dynamic height
 double ellipseWidth = HoleSize;


 // Draw the hole (ellipse)
 if (mMaxNotReached)
 {
  graphics->SetBrush(wxBrush(wxColour(0, 0, 0))); // Black color for the hole
  graphics->DrawEllipse(dotX - ellipseWidth / 2 + HoleOffset + 5,
                        dotY - ellipseHeight / 2 - HoleSize + 5,
                        ellipseWidth, ellipseHeight);
 }


 graphics->PopState();


}

/**
 * Reset the cam back to its original position
 */
void Cam::Reset()
{
 mRotation = mStartingAngle;
 mHoleAngle = mStartingAngle;
 KeyY = KeyYStart;
 mMaxNotReached = true;
}

/**
 * Set the rotation
 * @param rotation
 */
void Cam::SetRotation(double rotation)
{
 mRotation = rotation;
 mRotationSource.Rotate(mRotation);
}


/**
 * Update
 * @param time
 */
void Cam::Update(double time)
{
 Component::Update(time);
}

/**
 * Set the hole angle of the cam
 * @param angle
 */
void Cam::SetHoleAngle(double angle)
{
 mStartingAngle = angle;
 mHoleAngle = angle;
 mRotation = angle;

}



