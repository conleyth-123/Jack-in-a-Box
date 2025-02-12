/**
 * @file MachineSystemFactory.cpp
 *
 * @author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "MachineSystemFactory.h"
#include "MachineSystem.h"

/**
 * Constructor
 * @param resourcesDir Directory to load resources from
 */
MachineSystemFactory::MachineSystemFactory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
}


/**
 * Create a machine system object
 *
 * Do not change the return type of this function!
 *
 * @return Object of type IMachineSystem
 */
std::shared_ptr<IMachineSystem> MachineSystemFactory::CreateMachineSystem()
{
    return std::make_shared<MachineSystem>(mResourcesDir);
}
