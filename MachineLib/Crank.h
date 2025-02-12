/**
 * @file Crank.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef CRANK_H
#define CRANK_H
#include "Component.h"
#include "Cylinder.h"
#include "RotationSource.h"

/// Crank Class that turns the crank and draws it
class Crank : public Component{
private:
 /// Handle Cylinder
 cse335::Cylinder mHandle;

 /// Rotation source
 RotationSource mRotationSource;

 /// Angle of start
 double mAngle;

 /// Rotation
 double mRotation = 0;

 /// rotation speed
 double mSpeed;

 /// time of animation
 double mTime = 0;



public:
 Crank();
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 void Reset() override;
 void Rotate(double rotation);
 void Advance(double delta) override;
 void SetSpeed(double speed);


 /// Get the rotation source
 /// @return RotationSource
 RotationSource* GetSource() {return &mRotationSource;}

};



#endif //CRANK_H
