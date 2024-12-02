#include "FakeBeam.hh"

#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "Randomize.hh"


#include "DataManager.hh"


FakeBeam::FakeBeam()
{
  G4int n_particle;
  fParticleGun = new G4ParticleGun(n_particle = 1);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticlePosition(G4ThreeVector(0. ,0., -1.5 * CLHEP::m));
}

void FakeBeam::GeneratePrimaries(G4Event* event)
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  // TODO Randomize particle and Energy / Momentum
  G4ParticleDefinition* particle = nullptr;
  G4double pProb = G4RandFlat::shoot(0., 1.);
  if(pProb < 0.33)
  {
    particle = particleTable->FindParticle("e-");
  } else if(pProb >= 0.33 && pProb < 0.66)
  {
    particle = particleTable->FindParticle("mu-");
  } else
  {
    // Proton
    particle = particleTable->FindParticle(2212);
  }

  fParticleGun->SetParticleDefinition(particle);

  // Random momentum between 1 and 1000 GeV
  // G4double momentum = std::pow(10., G4RandFlat::shoot(-3, 0));
  G4double momentum = G4RandFlat::shoot(0.01, 2);
  fParticleGun->SetParticleMomentum(momentum * GeV);

  // Store the true particle indentification
  auto eventAction = (DataManager::EventAction*) G4EventManager::GetEventManager()->GetUserEventAction();
  eventAction->SetPrimaryParticle(particle->GetPDGEncoding(), momentum);

  // G4cout << "Particle [" << particle->GetPDGEncoding() << "]: " << momentum << " GeV" << G4endl;
  fParticleGun->GeneratePrimaryVertex(event);
}
