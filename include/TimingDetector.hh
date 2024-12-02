#pragma once

#include "G4VSensitiveDetector.hh"


class TimingDetector : public G4VSensitiveDetector
{
public:
	TimingDetector(G4String, G4int);
	~TimingDetector() = default;

private:
	// Function to be called for each particle entering the sensitive volume
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);

  G4int idx;
};
