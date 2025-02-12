/**
 * @file Box.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef BOX_H
#define BOX_H
#include "Component.h"
#include "Polygon.h"
#include "IKeyDropListener.h"

/**
 * Creates and builds the box and lid
 */
class Box : public Component, public IKeyDropListener { //, public IKeyDrop {
private:
 /// The box background image
 cse335::Polygon mBox;

 /// the Foreground
 cse335::Polygon mForeground;

 /// The Lid
 cse335::Polygon mLid;

 /// Directory containing the images
 std::wstring mImagesDir;

 /// Size of the box in pixels
 int mBoxSize;

 /// Size of the lid in pixels
 int mLidSize;

 /// Help with scaling the lid
 double mLidScale;

 /// Angle to determine lid position (in radians)
 double mLidAngle;

 /// Scale when the lid is fully closed
 const double mLidZeroAngleScale = 0.02;

 /// Increment for updating the angle (rate of change)
 double mAngleIncrement;

 /// flag to see if lid is open
 bool mIsOpen;

 /// lid opening speed
 const double mLidSpeed = 0.25;

public:
 Box(const std::wstring& imagesDir, int boxSize, int lidSize);
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) override;
 void UpdatePosition();
 void Advance(double delta) override;
 void Reset() override;
 void SetFrame() override;
 void SetTime(double time) override;
 void Open(bool open);
 void KeyDroppedTriggered(double keyY) override;

 /// Update the box if needed
 /// @param time
 void Update(double time) {};

 /// Set the lid angle
 /// @param angle
 void SetLidAngle(double angle) {mLidAngle = angle;}



};



#endif //BOX_H
