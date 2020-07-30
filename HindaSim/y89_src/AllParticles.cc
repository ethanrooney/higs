#include "AllParticles.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4ParticleTable.hh"

AllParticles::AllParticles()
{
}//END of constructor

AllParticles::~AllParticles()
{
}//END of destructor

void AllParticles::ConstructAllParticles(void)
{
  G4BosonConstructor      :: ConstructParticle();
  G4LeptonConstructor     :: ConstructParticle();
  G4MesonConstructor      :: ConstructParticle();
  G4BaryonConstructor     :: ConstructParticle();
  G4IonConstructor        :: ConstructParticle();
  G4ShortLivedConstructor :: ConstructParticle();

}//END of ConstructAllParticles()

void AllParticles::PrintParticleTable(void)
{
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

  G4cout << "-*-*-*- Printing Particle Table -*-*-*-" << G4endl;
  G4cout << " -> Table contains " << particleTable->entries()
         << " entries." << G4endl;

  particleTable->DumpTable();

  G4cout << G4endl;
  G4cout << "-*-*-*- End of Particle Table -*-*-*-" << G4endl;
  G4cout << G4endl;

}//END of PrintParticleTable()

