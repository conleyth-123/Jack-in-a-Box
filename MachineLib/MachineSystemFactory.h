/**
 * @file MachineSystemFactory.h
 *
 * @author Charles Owen
 *
 * IMachineSystem factory class. Creates IMachineSystem objects
 *
 * You should not have any reason to change this header file!
 */

#ifndef CANADIANEXPERIENCE_MACHINESYSTEMFACTORY_H
#define CANADIANEXPERIENCE_MACHINESYSTEMFACTORY_H

#include <memory>

class IMachineSystem;

/**
 * IMachineSystem factory class. Creates IMachineSystem objects
 */
class MachineSystemFactory
{
private:
    /// The resources directory
    std::wstring mResourcesDir;

public:
    MachineSystemFactory(std::wstring resourcesDir);

    // Do not change the return type for CreateMachineSystem!
    std::shared_ptr<IMachineSystem> CreateMachineSystem();
};

#endif //CANADIANEXPERIENCE_MACHINESYSTEMFACTORY_H