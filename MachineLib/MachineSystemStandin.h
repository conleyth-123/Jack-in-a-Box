/**
 * @file MachineSystemStandin.h
 * @author Charles Owen
 *
 * A Machine System class that displays a standin machine only.
 *
 * DO NOT CHANGE THIS FILE!
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMSTANDIN_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMSTANDIN_H

#include "IMachineSystem.h"

class MachineStandin;

/**
 * A Machine System class that displays a standin machine only.
 */
class MachineSystemStandin : public IMachineSystem
{
private:
    /**
     * A stand-in machine class.
     *
     * This draws simple stand-in graphics
     * so you can see where the machine will be and what its state
     * is. This makes it easy to develop code that uses the
     * machine before you have the machine working.
     *
     * And no, you may not change this to point to your
     * machine implementation!
     */
    std::shared_ptr<MachineStandin> mStandin;

public:
    /// Constructor
    MachineSystemStandin();

    /// Copy constructor (disabled)
    MachineSystemStandin(const MachineSystemStandin &) = delete;

    /// Assignment operator
    void operator=(const MachineSystemStandin &) = delete;


    virtual void SetLocation(wxPoint location);
    virtual wxPoint GetLocation();


    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics);
    virtual void SetMachineFrame(int frame);
    virtual void SetFrameRate(double rate);
    virtual void ChooseMachine(int machine);
    virtual int GetMachineNumber();
    virtual double GetMachineTime();

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    virtual void SetFlag(int flag) {}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMSTANDIN_H
