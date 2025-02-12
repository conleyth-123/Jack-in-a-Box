/**
 * @file Component.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef COMPONENT_H
#define COMPONENT_H
#include <wx/dc.h>
#include <wx/gdicmn.h>

class RotationSource;

///Component class that holds all component functions
class Component {
private:
 /// Component position
 wxPoint mPosition;

public:
 Component() = default;
 virtual ~Component() = default;

 /**
  * Draw the component
  * @param graphics
  */
 virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

 /**
  * Set the Position
  * @param x
  * @param y
  */
 virtual void SetPosition(int x, int y) {mPosition = wxPoint(x, y);}

 /// Return the position
 /// @return wxPoint
 virtual wxPoint GetPosition() {return mPosition;}

 /**
  * Reset the component
  */
 virtual void Reset() = 0;

 /// Set the Frame
 virtual void SetFrame(){};

 /**
  * Set the time
  * @param time
  */
 virtual void SetTime(double time) {};

 /**
  * Advance the time
  * @param delta
  */
 virtual void Advance(double delta) {}

 /**
  * Draw the purple outline on the box
  * @param graphics
  */
 virtual void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) {};

 /**
  * update the time
  * @param time
  */
 virtual void Update(double time) {};

 /// Set the Rotation
 ///@param rotation
 virtual void SetRotation(double rotation) {};


};



#endif //COMPONENT_H
