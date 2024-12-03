//
// Geant4 Include Files
//
#include "FTFP_BERT.hh"
#include "G4RunManagerFactory.hh"
#include "G4Types.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4VUserActionInitialization.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

//
// Project Include Files
//
#include "SimpleToFDetectorConstruction.hh"
#include "FakeBeam.hh"
#include "DataManager.hh"


//
// Event / Run handler initialization
//
class ActionInitialization : public G4VUserActionInitialization
{
public:
  ~ActionInitialization() override = default;

  void BuildForMaster() const override
  {
    // Handles runs
    // Needed here for the Analysis Manager to work properly
    SetUserAction(new DataManager::RunAction());
  }

  void Build() const override
  {
    // Handles primary particle generation
    SetUserAction(new FakeBeam());

    // Handles Runs
    SetUserAction(new DataManager::RunAction());

    // Handles events
    SetUserAction(new DataManager::EventAction());
  }
};




//
// Main Simulation Function
// Support both interactive (UI) and simulation via macro files
//
int main(int argc, char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = nullptr;
  if(argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }
  auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);


  // Configure the Physics of the Simulation
  //
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  runManager->SetUserInitialization(physicsList);

  // Create the Detector
  auto det = new SimpleToFDetectorConstruction();
  runManager->SetUserInitialization(det);

  // Initialize user defined actions
  runManager->SetUserInitialization(new ActionInitialization());


  // Setup the run manager / visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if(ui)
  {
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }
  else
  {
    // Batch mode
    G4String command  = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }

  return 0;
}
