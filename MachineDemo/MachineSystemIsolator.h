/**
 * @file MachineSystemIsolator.h
 * @author Charles Owen
 *
 * This class makes it possible for MachineDemoLib to be isolated from
 * MachineLib completely, abstracting all machine functionality
 * to this single class, allowing for dependency injection into
 * MachineDemoLib
 *
 * Do not modify this file!
 *
 * Do not try to include this file. It is for MachineDemo use only.
 */

#ifndef MACHINEDEMO_MACHINEISOLATOR_H
#define MACHINEDEMO_MACHINEISOLATOR_H

#include <memory>
#include <IMachineSystemIsolator.h>
#include <machine-api.h>


/**
 * This class makes it possible for MachineDemo to be isolated from
 * MachineLib completely, abstracting all machine functionality
 * to this single class.
 *
 * Do not modify this class!
 */
class MachineSystemIsolator final : public IMachineSystemIsolator {
private:
    /// The machine we are isolating
    std::shared_ptr<IMachineSystem> mMachine;

public:
    /**
     * Constructor
     * @param resourcesDir Directory containing the resources
     */
    explicit MachineSystemIsolator(std::wstring resourcesDir)
    {
        //
        // Use the MachineSystemFactory factory to create the machine object
        //
        MachineSystemFactory factory(resourcesDir);
        mMachine = factory.CreateMachineSystem();
    }

    /**
     * Choose the machine you want to use
     * @param machine New machine number
     */
    void ChooseMachine(int machine) override
    {
        mMachine->ChooseMachine(machine);
    }

    /**
     * Get the current machine number
     * @return Machine number
     */
    int GetMachineNumber() override
    {
        return mMachine->GetMachineNumber();
    }

    /**
     * Set the machine location
     * @param location Location of the machine
     */
    void SetLocation(wxPoint location) override
    {
        mMachine->SetLocation(location);
    }

    /**
    * Set the current machine animation frame
    * @param frame Frame number
    */
    void SetMachineFrame(int frame) override
    {
        mMachine->SetMachineFrame(frame);
    }

    /**
     * Set the frame rate
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) override
    {
        mMachine->SetFrameRate(rate);
    }


    /**
     * Display the machine selection dialog box
     * @param parent Parent window for the dialog box
     * @return True if OK pressed
     */
    bool DoDialog(wxWindow* parent) override
    {
        MachineDialog dialog(parent, mMachine);
        return (dialog.ShowModal() == wxID_OK);
    }

    /**
    * Draw the machine at the currently specified location
    * @param graphics Graphics object to render to
    */
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override
    {
        mMachine->DrawMachine(graphics);
    }

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    double GetMachineTime() override
    {
        return mMachine->GetMachineTime();
    }

    /**
     * General-purpose flag system for development use.
     * @param flag Flag value to use (8-bits with bits set from control panel)
     */
    void SetFlag(int flag) override
    {
        mMachine->SetFlag(flag);
    }
};

#endif //MACHINEDEMO_MACHINEISOLATOR_H
