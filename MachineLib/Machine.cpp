/**
 * @file Machine.cpp
 * @author Thomas Conley
 */

#include "pch.h"
#include "Machine.h"
#include "MachineSystem.h"

Machine::Machine() {
 // Initialize the Machine if needed
}

void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
 for (const auto& component : mComponents) {
  component->Draw(graphics); // Assuming no rotation for simplicity
 }

 for (auto& component : mComponents)
 {
  component->DrawForeground(graphics);
 }
}

void Machine::AddComponent(std::shared_ptr<Component> component)
{
 mComponents.push_back(component);
}


void Machine::Advance(double delta) {
 for (const auto& component : mComponents) {
  component->Advance(delta); // Advance each component
 }
}

void Machine::Reset() {
 for (const auto& component : mComponents) {
  component->Reset(); // Reset each component
 }
}



