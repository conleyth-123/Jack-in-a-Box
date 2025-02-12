/**
 * @file Cam.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef CAM_H
#define CAM_H
#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "RotationSource.h"
#include "Polygon.h"
#include "IKeyDropListener.h"

/// Creates and Draws the Cam that is derived form Component and IRotation sink
class Cam : public Component, public IRotationSink{
private:
 /// the cylinder for cam
 cse335::Cylinder mCam;
 /// Image Directory
 std::wstring mImagesDir;

 ///starting hole angle
 double mHoleAngle;

 /// Rotation of the cam
 double mRotation;
 /// polygon of the key image
 cse335::Polygon mKey;
 /// sink up the rotation
 RotationSource mRotationSource;
 ///teh starting angle for the ellipse
 double mStartingAngle;
 /// flag to see if the top of the cam was reached for the ellipse
 bool mMaxNotReached = true;
 /// Pointer to the interface for the key drop
 std::vector<IKeyDropListener*> mKeyDropListeners;

public:
 Cam(const std::wstring &imagesDir);
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 void Reset() override;
 void SetRotation(double rotation) override;
 void Update(double time) override;
 void SetHoleAngle(double angle);

 /**
  * Get the rotation source
  * @return RotationSource*
  */
 RotationSource* GetSource() {return &mRotationSource;}

 /// Add the components to the key lister list
 /// @param listener add the component that has to listen
 void AddKeyDrop(IKeyDropListener* listener)
 {
  mKeyDropListeners.push_back(listener);
 }

};



#endif //CAM_H
