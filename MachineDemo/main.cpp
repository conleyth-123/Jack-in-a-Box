/**
 * @file main.cpp
 * @author Charles B. Owen
 *
 * Main entry point for machine demonstrator program
 *
 * Do not modify this file!
 */
#include "pch.h"
#include <MachineDemoBaseApp.h>
#include "MachineSystemIsolator.h"

//<editor-fold desc="MachineDemoApp">
/**
 * MachineDemo main application class.
 * Most of the work is actually done in the base class.
 */
class MachineDemoApp : public MachineDemoBaseApp {
public:
    /**
     * Create the machine isolator, which contains the machine we are displaying.
     * @param resourcesDir Directory containing the resources for the program
     * @return MachineSystemIsolator object
     */
    std::shared_ptr<IMachineSystemIsolator> CreateMachineIsolator(std::wstring resourcesDir) override
    {
        return std::make_shared<MachineSystemIsolator>(resourcesDir);
    }

    /**
     * Initialize the application
     * @return True if successful
     */
    bool OnInit() override
    {
        auto ret = MachineDemoBaseApp::OnInit();

        SetBackgroundColor(wxColour(0, 220, 255)); // *wxWHITE);

        return ret;
    }
};
//</editor-fold>

wxIMPLEMENT_APP(MachineDemoApp);

