/**
 * @file Machine.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef MACHINE_H
#define MACHINE_H
#include "Component.h"

/// Represents a machine consisting of multiple components
class Machine {
private:
 /// Location of the machine on the screen
 wxPoint mLocation;

 /// Collection of components in the machine
 std::vector<std::shared_ptr<Component>> mComponents;

public:
 Machine();

 /**
  * Draw the machine
  * @param graphics
  */
 void Draw(std::shared_ptr<wxGraphicsContext> graphics);

 /**
  * Add the component to the machine
  * @param component
  */

 void AddComponent(std::shared_ptr<Component> component);

 /**
  * Set the Time
  * @param time
  */
 void SetTime(double time);

 /**
  * Advance the machine animation
  * @param delta
  */
 void Advance(double delta);

 /**
  * Reset the machine
  */
 void Reset();

};



#endif //MACHINE_H
