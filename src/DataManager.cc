#include "DataManager.hh"

#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"


DataManager::RunAction::RunAction()
{
  // Default configuration of the data saving
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");

  // Configure the data table in the output file
  // One row per event.
  analysisManager->CreateNtuple("Events", "Timing and True Information for each Event");
  analysisManager->CreateNtupleDColumn("Time0");
  analysisManager->CreateNtupleDColumn("Time1");

  analysisManager->CreateNtupleIColumn("TruePID");
  analysisManager->CreateNtupleDColumn("TrueMomentum");

  analysisManager->CreateNtupleDColumn("TrueTime0");
  analysisManager->CreateNtupleDColumn("TrueTime1");

  analysisManager->FinishNtuple();
}

void DataManager::RunAction::BeginOfRunAction(const G4Run* run)
{
  auto analysisManager = G4AnalysisManager::Instance();
  auto filename = analysisManager->GetFileName();
  if(filename.empty())
  {
    // Set default file name if necessary
    analysisManager->SetFileName("DefaultOutput");
  }

  analysisManager->SetNtupleMerging(true);
  analysisManager->OpenFile();
  analysisManager->SetNtupleRowWise(true);
}
void DataManager::RunAction::EndOfRunAction(const G4Run* run)
{
  // Close and Write the output file
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();
}



void DataManager::EventAction::BeginOfEventAction(const G4Event* event)
{
  time0 = -1.;
  time1 = -1;

  trueTime0 = -1;
  trueTime1 = -1;

  // Do not reset truePID and trueMomentum here!
  // SetPrimaryParticle (by the gun) is called before BeginOfEventAction is called!
}
void DataManager::EventAction::EndOfEventAction(const G4Event* event)
{
  // Fill the event into the analysis manager file
  // Analysis Manager handles multi-threading
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->FillNtupleDColumn(0, time0);
  analysisManager->FillNtupleDColumn(1, time1);
  analysisManager->FillNtupleIColumn(2, truePID);
  analysisManager->FillNtupleDColumn(3, trueMomentum);
  analysisManager->FillNtupleDColumn(4, trueTime0);
  analysisManager->FillNtupleDColumn(5, trueTime1);

  analysisManager->AddNtupleRow();
}

void DataManager::EventAction::SetTime(G4int idx, G4double time, G4double trueTime)
{
  // Only record the first time for each detector
  if(idx == 0 && time0 == -1.)
  {
    time0 = time;
    trueTime0 = trueTime;
  } else if(idx == 1 && time1 == -1.)
  {
    time1 = time;
    trueTime1 = trueTime;
  }
}

void DataManager::EventAction::SetPrimaryParticle(G4int pid, G4double momentum)
{
  truePID = pid;
  trueMomentum = momentum;
}
