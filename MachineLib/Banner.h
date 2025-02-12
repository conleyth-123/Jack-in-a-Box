/**
 * @file Banner.h
 * @author Thomas Conley
 *
 * Creates and draws the banner
 */
 
#ifndef BANNER_H
#define BANNER_H

#include <wx/graphics.h>
#include <wx/bitmap.h>

#include "Component.h"
#include "IKeyDropListener.h"
#include "Polygon.h"

/// Creates and draws the banner
class Banner : public Component, public IKeyDropListener
{
private:
 /// Helper methods for drawing banner components
 void DrawBannerRoll(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);
 void DrawBannerImage(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);

 ///Image Directory
 std::wstring mImagesDir;
 /// The Banner roll
 cse335::Polygon mBannerRoll;
 /// the banner pulled out
 cse335::Polygon mBanner;

 /// height of the banner
 double mCurrentHeight;        // Current height of the banner
 /// Flag to check if the banner is unfurling
 bool mIsUnfurling = false;
 /// Speed at which the banner unfurls
 double mUnfurlSpeed;
 /// the progress
 double mUnfurlProgress;

public:
 /// Constructor
 Banner(const std::wstring& imagesDir);

 /// Method to trigger the unfurling process
 void KeyDroppedTriggered(double keyY) override;

 /// Update method to handle the unfurling logic
 /// @param delta
 void Update(double delta) override {}

 /// Method to draw the banner using wxGraphicsContext
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

 void Reset() override;

 /// Set the frame
 void SetFrame() override{}

 /// Set the Time
 /// @param time
 void SetTime(double time) override{}

 void Advance(double delta) override;
};



#endif //BANNER_H
