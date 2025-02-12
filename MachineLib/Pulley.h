/**
 * @file Pulley.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef PULLEY_H
#define PULLEY_H
#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "RotationSource.h"

/// The Pulley component
class Pulley : public Component, public IRotationSink{
private:
 /// Cylinder for the pulley body
 cse335::Cylinder mPulleyBody;
 /// Cylinder for the left hub
 cse335::Cylinder mHubLeft;
 /// Cylinder for the right hub
 cse335::Cylinder mHubRight;

 /// Diameter of the pulley
 double mDiameter;
 /// Total width of the pulley
 double mWidth;
 /// Current rotation (in turns)
 double mRotation;

 /// Pointer to the connected pulley
 std::shared_ptr<Pulley> mConnectedPulley;

 /// The previous Y location
 int mPreviousY;

 /// Member variable for the rotation source
 RotationSource mRotationSource;

public:
 Pulley(double diameter, double width);
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 void Reset() override;
 void SetRotation(double rotation) override;


 void BeltTo(std::shared_ptr<Pulley> otherPulley);
 void Update(double time) override;

 /**
  * Get position x
  * @return int
  */
 int GetX() { return GetPosition().x; }

 /**
  * Get the diameter of the pulley
  * @return double
  */
 double GetDiameter() { return mDiameter; }

 /// Get the rotation source
 /// @return RotationSource*
 RotationSource* GetSource() {return &mRotationSource;}


};



#endif //PULLEY_H
