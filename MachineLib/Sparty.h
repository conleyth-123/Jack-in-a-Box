/**
 * @file Sparty.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef SPARTY_H
#define SPARTY_H
#include "Component.h"
#include "Polygon.h"
#include "IKeyDropListener.h"

/// The Sparty Component
class Sparty : public Component, public IKeyDropListener {
private:
 /// Sparty polygon
 cse335::Polygon mSparty;

 /// store the image Directory
 std::wstring mImagesDir;

 /// size
 int mSize;

 /// Spring length
 int mSpringLength;

 /// Spring width
 int mSpringWidth;

 /// number of links/loops in spring
 int mNumLinks = 0;

 /// Controls the spring's decompression and Sparty's position
 double mSpringPosition;

 /// Flag to determine if Sparty is currently popping up
 bool mIsPopup;

 ///should Key trigger
 bool mShouldDecompress;

 /// Flag to indicate if Sparty is currently bouncing
 bool mIsBouncing;

 /// Time tracking for the bounce
 double mBounceTime;

 /// Amplitude (height) of the bounce
 double mBounceAmplitude;

 /// Frequency of the bounce (speed)
 double mBounceFrequency;

 /// The decay rate for vertical bounce motion.
 double mBounceDecay;

 /// Amplitude of horizontal bounce
 double mHorizontalAmplitude;

 /// Frequency of horizontal bounce
 double mHorizontalFrequency;

 /// The decay rate for horizontal bounce motion.
 double mHorizontalBounceDecay;

public:
 Sparty(const std::wstring &imagesDir, int size, int springLength, int springWidth, int numLinks);
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 void DrawSpring(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, double length, double width, int numLinks);
 void UpdatePosition();
 void Reset() override;
 void Advance(double delta) override;
 void StartBounce();
 void KeyDroppedTriggered(double keyY) override;
};



#endif //SPARTY_H
