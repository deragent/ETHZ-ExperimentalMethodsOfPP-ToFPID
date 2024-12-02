#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;
class G4ParticleGun;

//
// Primary particle generation class
//
class FakeBeam : public G4VUserPrimaryGeneratorAction
{
  public:
    FakeBeam();
    ~FakeBeam() override = default;

    void GeneratePrimaries(G4Event* event) override;

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4ParticleGun* fParticleGun = nullptr;
};
