/**
 * @file Box.cpp
 * @author Thomas Conley
 */


#include "pch.h"
#include "Box.h"

///To get the lid into the right place
const int lidOffset = 250;

/**
 * Constructor
 * @param imagesDir Directory containing the images
 * @param boxSize Size of the box in pixels (just the box, not the lid)
 * @param lidSize Size of the lid in pixels
 */
Box::Box(const std::wstring& imagesDir, int boxSize, int lidSize)
    : Component(),
      mImagesDir(imagesDir),
      mBoxSize(boxSize),
      mLidSize(lidSize),
      mLidAngle(0),
      mAngleIncrement(1.0),
      mIsOpen(false)  // Set mIsOpen to false initially
{
    mBox.Rectangle(-mBoxSize / 2, 0, mBoxSize, mBoxSize);
    mBox.SetImage(mImagesDir + L"/box-background.png");

    mLid.Rectangle(-mBoxSize / 2, -mLidSize, mBoxSize, mLidSize);
    mLid.SetImage(mImagesDir + L"/box-lid.png");

    mForeground.Rectangle(-mBoxSize / 2, 0, mBoxSize, mBoxSize);
    mForeground.SetImage(mImagesDir + L"/box-foreground.png");
}

/**
 * Draw the Box
 * @param graphics
 */
void Box::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    UpdatePosition();

    // Draw the box
    mBox.DrawPolygon(graphics, 0, 0);

    graphics->PushState();

    // Translate to lid position
    double lidX = GetPosition().x;
    double lidY = GetPosition().y - (mLid.GetImageHeight() / 2.0);
    graphics->Translate(0, 0);

    // Calculate the scale factor based on the lid angle
    double sinValue = std::sin(mLidAngle);
    mLidScale = mLidZeroAngleScale + (1.0 - mLidZeroAngleScale) * sinValue;

    // Adjust lid's position based on scale
    double adjustedY = mLid.GetImageHeight() * (1.0 - mLidScale) / 2.0;

    graphics->Translate(0, -adjustedY);
    graphics->Scale(1.0, mLidScale);

    // Draw the lid
    mLid.DrawPolygon(graphics, 0, 0);

    graphics->PopState();
}

/**
 * Draw the box foreground (overlay).
 * @param graphics
 */
void Box::DrawForeground(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(0, 0);

    // Draw the foreground image
    mForeground.DrawPolygon(graphics, 0, 0);
    graphics->PopState();
}

/// Update the lid position
void Box::UpdatePosition()
{
    mLidScale = std::max(mLidZeroAngleScale, mLidScale);
}

/**
 * Advance the animation of lid opening
 * @param delta time
 */
void Box::Advance(double delta)
{
    if (mIsOpen && mLidAngle <= M_PI / 2)
    {
        mLidAngle = mLidAngle + (M_PI / 2) * delta / mLidSpeed;
        if (mLidAngle > M_PI / 2)
        {
            mLidAngle = M_PI / 2;
        }
        UpdatePosition();
    }
}

/// Reset the box to its original state
void Box::Reset()
{
    mLidAngle = 0.0;
    mIsOpen = false;
    UpdatePosition();
}

/// Set the frame
void Box::SetFrame()
{
    // Placeholder for setting the current frame of the box animation
}

/// Set Time for lid animation
/// @param time
void Box::SetTime(double time)
{
    mLidScale = mLidZeroAngleScale + (time / mLidSpeed) * (1 - mLidZeroAngleScale);
    mLidScale = std::min(mLidScale, 1.0);

    UpdatePosition();
}

/// Flag for if the box is open
/// @param open
void Box::Open(bool open)
{
    mIsOpen = open;
}

/**
 * Connection to interface to see if the key has dropped
 * @param keyY
 */
void Box::KeyDroppedTriggered(double keyY)
{
    // Only trigger the lid opening if it's not already open
    if (!mIsOpen)
    {
        mIsOpen = true;  // This triggers the opening of the box lid
    }
}


