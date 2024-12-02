#pragma once

#include "G4VUserDetectorConstruction.hh"
#include <CLHEP/Units/SystemOfUnits.h>


class G4Box;
class G4Material;
class G4LogicalVolume;

class SimpleToFDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  SimpleToFDetectorConstruction();
  ~SimpleToFDetectorConstruction() override = default;

  // Function which will construct / define the physical layout of the simulation
  G4VPhysicalVolume* Construct() override;
  // Function which will define which parts of the simulation are sensitive / detectors
  void ConstructSDandField() override;

private:
  // References to the different volumes in the simulation
  G4LogicalVolume* fExperimentalHall_log = nullptr;
  G4LogicalVolume* fTiming0_log = nullptr;
  G4LogicalVolume* fTiming1_log = nullptr;

  // Materials
  G4Material* fVacuum = nullptr;
  G4Material* fSi = nullptr;
};
