/**
 * @file MachineSystem.cpp
 * @author Thomas Conley
 */

#include "pch.h"
#include "MachineSystem.h"
#include "MachineStandin.h"
#include "Machine.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"

/**
 * Constructor
 * @param resourcesDir
 */
MachineSystem::MachineSystem(const std::wstring& resourcesDir) : mResourcesDir(resourcesDir)
{
 ChooseMachine(1);
}


/**
 * Get the location of hte machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystem::GetLocation()
{
 return wxPoint(mLocation.x, mLocation.y);
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
 // This will put the machine where it is supposed to be drawn
 graphics->PushState();
 graphics->Translate(mLocation.x, mLocation.y);

 mMachine->Draw(graphics);

 graphics->PopState();

}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystem::SetMachineFrame(int frame)
{
 if (frame < mFrame)
 {
  Reset();
 }

 while (mFrame < frame) {
  mFrame++;
  mTime = mFrame / mFrameRate;
  mMachine->Advance(1.0/ mFrameRate);  // Advance components
 }
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate(double rate)
{
 mFrameRate = rate;
}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void MachineSystem::ChooseMachine(int machine)
{
 mMachineNumber = machine;
 if(machine == 1)
 {
  Machine1Factory factory(mResourcesDir);
  mMachine = factory.Create();
 }
 else
 {
  Machine2Factory factory(mResourcesDir);
  mMachine = factory.Create();
 }

}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystem::GetMachineNumber()
{
 return mMachineNumber;
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystem::GetMachineTime()
{
 return mTime;
}

/**
 * Set the flag from the control panel
 * @param flag Flag to set
 */
void MachineSystem::SetFlag(int flag)
{

}

/**
 * Reset the machine system
 */
void MachineSystem::Reset()
{
 mTime = 0.0;
 mFrame = 0;
 mMachine->Reset(); // Reset all components within the machine
}

/**
 * Set the location
 * @param location
 */
void MachineSystem::SetLocation(wxPoint location)
{
 mLocation = location;
}

