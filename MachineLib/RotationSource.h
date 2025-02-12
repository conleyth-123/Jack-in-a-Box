/**
 * @file RotationSource.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef ROTATIONSOURCE_H
#define ROTATIONSOURCE_H

#include <memory>
#include <memory>
#include "Component.h"
#include "IRotationSink.h"

/// this handles the rotation for multiple movements
class RotationSource {
private:
 /// vector of all components that spin
 std::vector<std::shared_ptr<IRotationSink>> mSinks;


public:
 /// Constructor to initialize the rotation source
 RotationSource();
 void AddSink(std::shared_ptr<IRotationSink> sink);
 void Rotate(double rotation);
};



#endif //ROTATIONSOURCE_H
