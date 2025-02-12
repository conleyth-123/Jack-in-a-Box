/**
* @file Machine1Factory.h
 *
 * @author Thomas Conley
 *
 * Factory for creating Machine #1
 */

#ifndef CANADIANEXPERIENCE_MACHINE1FACTORY_H
#define CANADIANEXPERIENCE_MACHINE1FACTORY_H

#include <memory>
#include <string>

class Machine;
class Shape;

/**
 * Factory for creating Machine #1
 */
class Machine1Factory {
private:
 /// Path to the resources directory
 std::wstring mResourcesDir;

 /// Path to the images directory
 std::wstring mImagesDir;

public:
 Machine1Factory(std::wstring resourcesDir);

 std::shared_ptr<Machine> Create();
};

#endif //CANADIANEXPERIENCE_MACHINE1FACTORY_H
