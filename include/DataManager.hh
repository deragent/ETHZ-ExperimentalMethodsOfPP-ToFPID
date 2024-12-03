#pragma once

#include "G4UserRunAction.hh"
#include "G4UserEventAction.hh"

class G4Run;
class G4Event;

namespace DataManager
{
  class RunAction : public G4UserRunAction
  {
  public:
    RunAction();

    // Functions called at the start and end of each run
    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
  };

  class EventAction : public G4UserEventAction
  {
  public:
    // Functions called at the start and end of each event
    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

    // Set the detected time values
    void SetTime(G4int, G4double, G4double);

    // Set the primary particle info
    void SetPrimaryParticle(G4int, G4double);

  private:
    G4double time0, time1;
    G4int truePID;
    G4double trueMomentum;
    G4double trueTime0, trueTime1;
  };

};
