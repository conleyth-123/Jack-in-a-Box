/**
 * @file IKeyDropListener.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef IKEYDROPLISTENER_H
#define IKEYDROPLISTENER_H


/// Interface for objects that need to respond to a key drop event.
class IKeyDropListener {
private:

public:
 virtual ~IKeyDropListener() = default;

 /**
  * This method will be called when the key drops
  * @param keyY
  */
 virtual void KeyDroppedTriggered(double keyY) = 0;

};



#endif //IKEYDROPLISTENER_H
