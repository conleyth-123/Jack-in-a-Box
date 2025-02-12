/**
 * @file Machine2Factory.h
 * @author Thomas Conley
 *
 * Factory for creating Machine #2
 */
 
#ifndef CANADIANEXPERIENCE_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINE2FACTORY_H


#include <memory>
#include <string>

class Machine;
class Shape;

/**
 * Factory for creating Machine #1
 */
class Machine2Factory {
private:
 /// Path to the resources directory
 std::wstring mResourcesDir;

 /// Path to the images directory
 std::wstring mImagesDir;

public:
 Machine2Factory(std::wstring resourcesDir);

 std::shared_ptr<Machine> Create();
};



#endif //CANADIANEXPERIENCE_MACHINE2FACTORY_H
