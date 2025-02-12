/**
 * @file Shaft.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef SHAFT_H
#define SHAFT_H
#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "RotationSource.h"

/// The Shaft component
class Shaft : public Component, public IRotationSink{
private:
 /// Cyliner of the shaft
 cse335::Cylinder mCylinder;

 /// Diameter of the shaft
 double mDiameter;

 /// length of the shaft
 double mLength;

 /// Rotation offset
 double mOffset;

 /// Rotation of the shaft
 double mRotation;

 /// Rotation source
 RotationSource mRotationSource;

public:
 Shaft();
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 void Reset() override;
 void SetRotation(double rotation) override;
 void Update(double time) override;
 void SetSize(double diameter, double length);
 void SetOffset(double offset);

 /**
  * Get the rotation source
  * @return RotationSource
  */
 RotationSource* GetSource() {return &mRotationSource;}
};



#endif //SHAFT_H
