/**
 * @file MachineSystem.h
 * @author Thomas Conley
 *
 *
 */
 
#ifndef MACHINESYSTEM_H
#define MACHINESYSTEM_H
#include "IMachineSystem.h"

class Machine;

/// Implements the `IMachineSystem` interface to manage a machine's state
class MachineSystem : public IMachineSystem {
private:
 /// Location
 wxPoint mLocation;

 /// Pointer to the Machine
 std::shared_ptr<Machine> mMachine;

 /// machine number
 int mMachineNumber = 0;

 /// Resources Directory
 std::wstring mResourcesDir;

 /// frame rate
 double mFrameRate = 30;

 ///Time
 double mTime = 0.0;

 /// frame
 double mFrame;




public:
 MachineSystem(const std::wstring& resourcesDir);
 void SetLocation(wxPoint location) override;
 wxPoint GetLocation() override;
 void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
 void SetMachineFrame(int frame) override;
 void SetFrameRate(double rate) override;
 void ChooseMachine(int machine)override;
 int GetMachineNumber() override;
 double GetMachineTime() override;
 void SetFlag(int flag) override;
 void Reset();
};



#endif //MACHINESYSTEM_H
