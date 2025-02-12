/**
 * @file Machine2Factory.cpp
 * @author Thomas Conley
 */

#include "pch.h"
#include "Machine2Factory.h"


#include "Banner.h"
#include "Machine.h"
#include "Box.h"
#include "Crank.h"
#include "Sparty.h"
#include "Shaft.h"
#include "Pulley.h"
#include "Cam.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
Machine2Factory::Machine2Factory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
 mImagesDir = mResourcesDir + ImagesDirectory;
}



/**
 * Factory method to create machine #2
 * @return
 */
std::shared_ptr<Machine> Machine2Factory::Create()
{
    // The machine itself
    auto machine2 = std::make_shared<Machine>();

    // Locations of some things in the machine
    const int Shaft1Y = -180;
    const int Shaft2Y = -70;
    const int Shaft3Y = -180;

    /*
     * The Box class constructor parameters are:
     * @param imagesDir Directory containing the images
     * @param boxSize Size of the box in pixels (just the box, not the lid)
     * @param lidSize Size of the lid in pixels
     */
    auto box = std::make_shared<Box>(mImagesDir, 250, 240);
    machine2->AddComponent(box);

    /*
     * The Sparty class constructor parameters are:
     * @param image Image file to load
     * @param size Size to draw Sparty (width and height)
     * @param springLength How long the spring is when fully extended in pixels
     * @param springWidth How wide the spring is in pixels
     * @param numLinks How many links (loops) there are in the spring
     */
    auto sparty =
        std::make_shared<Sparty>(mImagesDir + L"/sparty2.png", 212, 260, 80, 15);
    machine2->AddComponent(sparty);

    // The hand crank
    auto crank = std::make_shared<Crank>();
    crank->SetPosition(150, Shaft1Y);
    crank->SetSpeed(0.5);       // In turns per second
    machine2->AddComponent(crank);


    // The first shaft
    auto shaft1 = std::make_shared<Shaft>();
    shaft1->SetPosition(90, Shaft1Y);       // Left-center end of the shaft
    shaft1->SetSize(10, 70);                // Diameter, length
    shaft1->SetOffset(0.3);                 // Rotation offset so the
                                            // lines don't all line up
    machine2->AddComponent(shaft1);

    // Connect crank to shaft
    crank->GetSource()->AddSink(shaft1);

    // Note: If you made sinks through composition rather than
    // inheriting an interface, your code would likely be more
    // like this:
    // crank->GetSource()->AddSink(shaft1->GetSink());

    // Add the crank after the shaft is added so it is on top of the shaft
    machine2->AddComponent(crank);

    // The first pulley

    /*
     * The first pulley
     * @param diameter The pully diameter to draw
     * @param width The total width of the pulley
     */
    auto pulley1 = std::make_shared<Pulley>(30, 15);
    pulley1->SetPosition(103, Shaft1Y);

    shaft1->GetSource()->AddSink(pulley1);

    // The second pulley
    auto pulley2 = std::make_shared<Pulley>(80, 15);
    pulley2->SetPosition(pulley1->GetX(), Shaft2Y);
    pulley1->BeltTo(pulley2);

    auto shaft2 = std::make_shared<Shaft>();
    shaft2->SetPosition(-115, Shaft2Y);       // Left end of the shaft
    shaft2->SetSize(10, 230);                // Diameter and length
    shaft2->SetOffset(0.1);
    machine2->AddComponent(shaft2);

    pulley2->GetSource()->AddSink(shaft2);

    // We add the driven pulley first, then the driving pulley
    // so the belt draws on top of both
    machine2->AddComponent(pulley2);
    machine2->AddComponent(pulley1);

    auto pulley3 = std::make_shared<Pulley>(15, 15);
    pulley3->SetPosition(-103, Shaft2Y);
    shaft2->GetSource()->AddSink(pulley3);

    auto pulley4 = std::make_shared<Pulley>(90, 15);
    pulley4->SetPosition(pulley3->GetX(), Shaft3Y);
    pulley3->BeltTo(pulley4);

    auto shaft3 = std::make_shared<Shaft>();
    shaft3->SetPosition(-115, Shaft3Y);       // Left end of the shaft
    shaft3->SetSize(10, 50);                // Diameter and length
    shaft3->SetOffset(0.1);
    machine2->AddComponent(shaft3);

    pulley4->GetSource()->AddSink(shaft3);

    machine2->AddComponent(pulley4);
    machine2->AddComponent(pulley3);

    auto cam = std::make_shared<Cam>(mImagesDir);
    cam->SetPosition(-80, Shaft3Y);     // Center of the cam
    cam->SetHoleAngle(0.00);            // How far the hole is from top-dead-center
                                        // in turns. This means the cam would need
                                        // to rotate 0.44 turns before the key drops.
    machine2->AddComponent(cam);

    cam->AddKeyDrop(box.get());               // Key drop triggers the box
    cam->AddKeyDrop(sparty.get());            // Key drop triggers Sparty

    shaft3->GetSource()->AddSink(cam);

    auto banner = std::make_shared<Banner>(mImagesDir);
    banner->SetPosition(0, -500);
    machine2->AddComponent(banner);
    cam->AddKeyDrop(banner.get());
/*
    auto musicBox =
        std::make_shared<MusicBox>(mResourcesDir, L"/songs/fight.xml");
    musicBox->SetPosition(0, Shaft2Y);      // Center of the music box
    machine->AddComponent(musicBox);
    shaft2->GetSource()->AddSink(musicBox);

    // This optional feature avoids noise when dragging the slider
    // backwards. It mutes the sound when moving time backwards
    machine->AddMutable(musicBox);
*/
    return machine2;

}
