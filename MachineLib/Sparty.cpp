/**
 * @file Sparty.cpp
 * @author Thomas Conley
 */


#include "pch.h"
#include "Sparty.h"

/// The spring pen size to use in pixels
const double SpringWireSize = 2;

/// Minimum spacing between spring wire
const double SpringWireMinSpacing = 1;

/// Spring Color
const wxColour SpringColor = wxColour(220, 220, 220);

/// Sparty popup time in seconds
const double SpartyPopupTime = 25;

/// the minimum spring size
const double MinSpringPosition = 40.0;

/// move the spring into the right spot
const int SpringOffset = 20;

/// Minimum amplitude for horizontal bounce
const double MinHorizontalBounceAmplitude = 30.0;

/// Frequency of horizontal bounce
const double HorizontalBounceFrequency = 5.0;

/// makes the sparty slowly stop bouncing around
const double HorizontalBounceDecay = 0.05;
/**
 * Constructor
 * @param imagesDir
 * @param size
 * @param springLength
 * @param springWidth
 * @param numLinks
 */
Sparty::Sparty(const std::wstring& imagesDir, int size, int springLength, int springWidth, int numLinks)
    : mImagesDir(imagesDir),
      mSize(size),
      mSpringLength(springLength),
      mSpringWidth(springWidth),
      mNumLinks(numLinks),
      mSpringPosition(MinSpringPosition),
      mIsPopup(false),
      mShouldDecompress(false),  // Initially set to false, meaning no decompression
      mIsBouncing(false),        // Initially, Sparty is not bouncing
      mBounceTime(0.0),
      mBounceAmplitude(15.0),     // Starting bounce height (can be adjusted)
      mBounceFrequency(2.0),     // Frequency of bounce (can be adjusted)
      mBounceDecay(0.05),         // Decay of the bounce amplitude (can be adjusted)
      mHorizontalAmplitude(MinHorizontalBounceAmplitude),
      mHorizontalFrequency(HorizontalBounceFrequency),
      mHorizontalBounceDecay(HorizontalBounceDecay)
{
    mSparty.Rectangle(-mSize / 2, 0, mSize, mSize);
    mSparty.SetImage(mImagesDir);
}

/**
 * Draw Sparty and call DrawSpring
 * @param graphics
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Apply horizontal and vertical translation to both Sparty and the spring
    double horizontalOffset = mHorizontalAmplitude * std::sin(mHorizontalFrequency * mBounceTime);
    graphics->Translate(horizontalOffset, 0);  // Move both horizontally

    // Draw the spring first (spring will move horizontally with Sparty)
    DrawSpring(graphics, 0, 0, mSpringPosition, mSpringWidth, mNumLinks);

    // Now draw Sparty image on top of the spring, applying bounce translation
    if (mIsBouncing) {
        // Apply vertical bouncing translation (sinusoidal bounce effect)
        double bounceOffset = mBounceAmplitude * std::sin(mBounceFrequency * mBounceTime);
        graphics->Translate(0, -mSpringPosition + SpringOffset + bounceOffset);  // Adjust vertical translation for bounce
    } else {
        // If not bouncing, just use normal vertical positioning
        graphics->Translate(0, -mSpringPosition + SpringOffset);
    }

    // Draw the Sparty image at the correct position
    mSparty.DrawPolygon(graphics, 0, 0);

    graphics->PopState();
}

/**
 * Update positions so Sparty springs upwards
 */
void Sparty::UpdatePosition()
{
    // Check if decompression is triggered
    if (mShouldDecompress && mSpringPosition < mSpringLength) {
        mSpringPosition += SpartyPopupTime;  // Gradually decompress the spring
    } else if (mSpringPosition >= mSpringLength) {
        mIsPopup = true;  // Sparty has finished popping up
        StartBounce();    // Start bouncing once Sparty has popped up
    }
}

/**
 * Reset Sparty and spring into original loctaions
 */
void Sparty::Reset()
{
    mSpringPosition = MinSpringPosition;
    mIsPopup = false;
    mShouldDecompress = false;
    mIsBouncing = false;
    mBounceTime = 0.0;
    mBounceAmplitude = 15.0;
    mHorizontalAmplitude = MinHorizontalBounceAmplitude;  // Reset horizontal bounce
}

/**
 * Sets flags for when key drop is triggered
 * @param keyY
 */
void Sparty::KeyDroppedTriggered(double keyY)
{
    // Set the flag to start decompression
    mShouldDecompress = true;
    mIsPopup = false;  // Ensure Sparty is not already in the popped-up state

}

/**
 * Draw the spring
 * @param graphics
 * @param x
 * @param y
 * @param length
 * @param width
 * @param numLinks
 */
void Sparty::DrawSpring(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, double length, double width, int numLinks)
{
    auto path = graphics->CreatePath();

    double y1 = y;
    double linkLength = length / numLinks;

    double xR = x + width / 2;
    double xL = x - width / 2;

    path.MoveToPoint(x + mHorizontalAmplitude * std::sin(mHorizontalFrequency * mBounceTime), y1); // Apply horizontal offset

    for (int i = 0; i < numLinks; i++) {
        auto y2 = y1 - linkLength;
        auto y3 = y2 - linkLength / 2;

        path.AddCurveToPoint(xR, y1, xR, y3, x, y3);
        path.AddCurveToPoint(xL, y3, xL, y2, x, y2);

        y1 = y2;
    }

    graphics->StrokePath(path);
}

/**
 * Update the animation of sparty bouncing and him springing up
 * @param delta
 */
void Sparty::Advance(double delta)
{
    if (mIsBouncing) {
        mBounceTime += delta; // Update bounce time

        // Vertical bounce decay
        mBounceAmplitude -= mBounceDecay;
        if (mBounceAmplitude < 0) mBounceAmplitude = 0;  // Stop vertical bouncing when amplitude is too small

        // Horizontal bounce decay
        mHorizontalAmplitude -= mHorizontalBounceDecay;
        if (mHorizontalAmplitude < 0) mHorizontalAmplitude = 0; // Stop horizontal bouncing when amplitude is too small
    }

    UpdatePosition();  // Update the spring position and other related states
}

/**
 * Start the bouncing animation of sparty
 */
void Sparty::StartBounce()
{
    if (mIsPopup && !mIsBouncing) {
        mIsBouncing = true;  // Start bouncing once Sparty pops up

        // Set initial horizontal bounce parameters
        mHorizontalAmplitude = MinHorizontalBounceAmplitude;  // Initial horizontal amplitude (adjustable)
        mHorizontalFrequency = 1.0;   // Initial horizontal bounce frequency (adjustable)
        mHorizontalBounceDecay = 0.05; // Decay for horizontal bounce
    }
}


