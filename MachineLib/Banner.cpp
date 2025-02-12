/**
 * @file Banner.cpp
 * @author Thomas Conley
 */

#include "pch.h"
#include "Banner.h"
#include <wx/graphics.h>
#include <wx/region.h>
#include <memory>
#include <algorithm>


/// Scale to draw relative to the image sizes
const double BannerScale = 0.42;

/// Height of the banner in pixels
double const BannerHeight = 150 * BannerScale;

/// Width fo the banner in pixels
const double BannerWidth = 1024 * BannerScale;

/// Height of the banner roll image in pixels
const double BannerRollHeight = 300 * BannerScale;

/// Width of the banner roll image in pixels
double const BannerRollWidth = 16 * BannerScale;

/// How fast ot unfurl the banner in pixels per second
double const BannerSpeed = 41.65;

/// Minimum number of pixels to start with as unfurled
const double BannerMinimum = 15;



/**
 * Constructor to initialize the banner object
 * @param imagesDir
 */
Banner::Banner(const std::wstring& imagesDir)
    : mImagesDir(imagesDir),
      mCurrentHeight(BannerMinimum),
      mUnfurlSpeed(BannerSpeed),
      mUnfurlProgress(0)
{
    // Initialize the banner polygon as a rectangle (this defines the banner's shape)
    mBanner.Rectangle(-BannerWidth / 2, 0, BannerWidth, BannerHeight);  // Centered banner
    mBanner.SetImage(imagesDir + L"/banner.png");

    mBannerRoll.Rectangle(-BannerRollWidth / 2, 0, BannerRollWidth, BannerHeight);
    mBannerRoll.SetImage(imagesDir + L"/banner-roll.png");
}


/**
 * Method to trigger the unfurling when the key is dropped
 * @param keyY
 */
void Banner::KeyDroppedTriggered(double keyY) {
    mIsUnfurling = true;
    mUnfurlProgress = 0;
}

/**
 * Update method to handle the banner's unfurling progress
 * @param delta
 */
void Banner::Advance(double delta)
{
    if (mIsUnfurling) {
        // Gradually increase the progress of the unfurling
        mUnfurlProgress += mUnfurlSpeed * delta;

        // Ensure that unfurl progress does not exceed the banner width
        if (mUnfurlProgress >= BannerWidth) {
            mUnfurlProgress = BannerWidth;  // Cap progress to the banner width
            mIsUnfurling = false;  // Stop unfurling once fully revealed
        }

        mCurrentHeight = mUnfurlProgress;  // Set the current height to the unfurl progress
    }
}


/**
 * Method to draw the banner
 * @param graphics
 */
void Banner::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    graphics->PushState();

    // Draw the banner roll image (this is the starting image, visible until the banner unfurls)
    DrawBannerRoll(graphics, GetPosition().x + BannerWidth/2, GetPosition().y);

    // If the banner is still unfurling or partially unfurled, draw the banner image
    if (mIsUnfurling || (mUnfurlProgress > 0)) {
        // Draw the banner image that is being unfurled, coming out from the left
        DrawBannerImage(graphics, GetPosition().x - BannerWidth / 2, GetPosition().y - BannerHeight);
    }

    graphics->PopState();
}

/**
 * Helper method to draw the banner roll image
 * @param graphics
 * @param x
 * @param y
 */
void Banner::DrawBannerRoll(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) {
    mBannerRoll.DrawPolygon(graphics, x, y);
}

/**
 * Helper method to draw the banner image with the current height (cropped)
 * @param graphics
 * @param x
 * @param y
 */
void Banner::DrawBannerImage(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) {
    //mBanner.DrawPolygon(graphics, x + BannerWidth, y);

    // Define the clipping rectangle: Only show the banner portion to the left of the roll
    //int clipWidth = mUnfurlProgress - BannerWidth;
    wxRect clipRect(x + BannerWidth, y, -mUnfurlProgress, BannerHeight);  // Clip to the left portion of the banner

    // Create a region from the clipping rectangle
    wxRegion region(clipRect);

    // Save the current state of the graphics context (including clipping state)
    graphics->PushState();

    // Set the clipping region to the created region
    graphics->Clip(region);

    // Draw the banner image, only the clipped portion will be visible
    mBanner.DrawPolygon(graphics, x + BannerWidth * 2 - BannerWidth/2 + clipRect.GetWidth(), y + BannerHeight);

    // Restore the previous state, which removes the clipping region
    graphics->PopState();
}

/**
 * Reset the banner
 */
void Banner::Reset()
{
    mUnfurlProgress = 0;
    mIsUnfurling = false;
}












