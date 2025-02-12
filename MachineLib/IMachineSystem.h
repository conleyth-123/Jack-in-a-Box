/**
 * @file IMachineSystem.h
 *
 * @author Anik Momtaz
 * @author Charles Owen
 *
 * Interface that represents a machine.
 *
 * You are not allowed to change this class in any way!
 */

#ifndef CANADIANEXPERIENCE_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINESYSTEM_H

/**
 * Interface that represents a machine.
 *
 * This uses a standin class to provide a way to develop
 * the adapter class first if you so choose.
 *
 * You are not allowed to change this class in any way!
 */
class IMachineSystem {
public:
    /// Destructor
    virtual ~IMachineSystem() = default;

    /**
    * Set the position for the root of the machine
    * @param location The x,y location to place the machine
    */
    virtual void SetLocation(wxPoint location) = 0;

    /**
     * Get the location of hte machine
     * @return Location x,y in pixels as a point
     */
    virtual wxPoint GetLocation() = 0;

    /**
    * Draw the machine at the currently specified location
    * @param graphics Graphics object to render to
    */
    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
    * Set the current machine animation frame
    * @param frame Frame number
    */
    virtual void SetMachineFrame(int frame) = 0;

    /**
     * Set the expected frame rate in frames per second
     * @param rate Frame rate in frames per second
     */
    virtual void SetFrameRate(double rate) = 0;

    /**
    * Set the machine number
    * @param machine An integer number. Each number makes a different machine
    */
    virtual void ChooseMachine(int machine) = 0;

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    virtual int GetMachineNumber() = 0;

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    virtual double GetMachineTime() = 0;

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    virtual void SetFlag(int flag) = 0;
};


#endif //CANADIANEXPERIENCE_MACHINESYSTEM_H
