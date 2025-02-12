/**
 * @file MachineSystemStandin.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "MachineSystemStandin.h"
#include "MachineStandin.h"

/**
 * Constructor
 */
MachineSystemStandin::MachineSystemStandin()
{
    mStandin = std::make_shared<MachineStandin>();
}

/**
* Set the position for the root of the machine
* @param location The x,y location to place the machine
*/
void MachineSystemStandin::SetLocation(wxPoint location)
{
    mStandin->SetLocation(location);
}

/**
 * Get the location of hte machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystemStandin::GetLocation()
{
    return mStandin->GetLocation();
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineSystemStandin::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);
    mStandin->DrawMachine(graphics);
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystemStandin::SetMachineFrame(int frame)
{
    mStandin->SetMachineFrame(frame);
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystemStandin::SetFrameRate([[maybe_unused]] double rate)
{

}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void MachineSystemStandin::ChooseMachine(int machine)
{
    mStandin->SetMachine(machine);
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystemStandin::GetMachineNumber()
{
    return mStandin->GetMachine();
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystemStandin::GetMachineTime()
{
    return 0;
}

