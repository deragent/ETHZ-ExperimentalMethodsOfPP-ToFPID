#include "TimingDetector.hh"

#include "G4EventManager.hh"
#include "DataManager.hh"

TimingDetector::TimingDetector(G4String name, G4int timingIDx) : G4VSensitiveDetector(name)
{
  this->idx = timingIDx;
}

G4bool TimingDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  // Check if we just entered the sensor volume
  if(aStep->IsFirstStepInVolume())
  {
    // Global Time: Time since start of event
    G4double time = aStep->GetPostStepPoint()->GetGlobalTime();

    // TODO Apply Gaussian Time uncertainty
    time += G4RandGauss::shoot(0., 100e-3);

    // Record the time of hitting our timing detector

    auto eventAction = (DataManager::EventAction*) G4EventManager::GetEventManager()->GetUserEventAction();
    eventAction->SetTime(idx, time);
  }

	return 0;
}
