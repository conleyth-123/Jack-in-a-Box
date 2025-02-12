/**
 * @file IRotationSink.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef IROTATIONSINK_H
#define IROTATIONSINK_H


///Interface for objects that need to respond to an rotation event.
class IRotationSink {
private:

public:
 virtual ~IRotationSink() {}

 /// Set the Rotation
 /// @param rotation
 virtual void SetRotation(double rotation){}


};



#endif //IROTATIONSINK_H
