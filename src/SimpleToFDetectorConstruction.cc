#include "SimpleToFDetectorConstruction.hh"

#include "TimingDetector.hh"

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

SimpleToFDetectorConstruction::SimpleToFDetectorConstruction()
{
  G4Element* elN  = new G4Element("Nitrogen", "N", 7., 14.00674*g/mole);
  G4Element* elO  = new G4Element("Oxygen", "O", 8., 15.9994*g/mole);

  // Define / retrieve the necessary materials
  G4double density = CLHEP::universe_mean_density;
  fVacuum = new G4Material("Vacuum", density, 2);
  fVacuum->AddElement(elN, .7);
  fVacuum->AddElement(elO, .3);

  fSi = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
}


G4VPhysicalVolume* SimpleToFDetectorConstruction::Construct()
{
  // Geometrical sizes
  G4double flight_x = 0.2 * CLHEP::m;
  G4double flight_y = 0.2 * CLHEP::m;
  G4double flight_z = 1 * CLHEP::m;

  G4double timing_thickness = 0.2 * CLHEP::mm;

  // The experimental hall walls are all 1m away from the ToF volume
  G4double expHall_x = flight_x + 1. * m;
  G4double expHall_y = flight_y + 1. * m;
  G4double expHall_z = flight_z + 1. * m;

  // Create experimental hall
  auto fExperimentalHall_box = new G4Box("expHall_box", expHall_x, expHall_y, expHall_z);
  fExperimentalHall_log = new G4LogicalVolume(fExperimentalHall_box, fVacuum, "expHall_log");
  auto fExperimentalHall_phys = new G4PVPlacement(nullptr, G4ThreeVector(), fExperimentalHall_log, "expHall", nullptr, false, 0);

  // Do not show the experimental hall in the visualization
  fExperimentalHall_log->SetVisAttributes(G4VisAttributes::GetInvisible());


  // Create the first Timing Detector (at start of flight volume)
  auto fTiming0_box = new G4Box("timing0_box", flight_x, flight_y, timing_thickness);
  fTiming0_log = new G4LogicalVolume(fTiming0_box, fSi, "timing0_log");
  auto fTiming0_phys = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -1*(flight_z + timing_thickness)), fTiming0_log, "timing0", fExperimentalHall_log, false, 0);

  // Create the second Timing Detector (at end of flight volume)
  auto fTiming1_box = new G4Box("timing1_box", flight_x, flight_y, timing_thickness);
  fTiming1_log = new G4LogicalVolume(fTiming1_box, fSi, "timing1_log");
  auto fTiming1_phys = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, (flight_z + timing_thickness)), fTiming1_log, "timing1", fExperimentalHall_log, false, 0);


  return fExperimentalHall_phys;
}

void SimpleToFDetectorConstruction::ConstructSDandField()
{
  // Assign a detector handler to our timing detectors
  TimingDetector *sensDet0 = new TimingDetector("TimingDetector0", 0);
  fTiming0_log->SetSensitiveDetector(sensDet0);

  TimingDetector *sensDet1 = new TimingDetector("TimingDetector1", 1);
  fTiming1_log->SetSensitiveDetector(sensDet1);
}
