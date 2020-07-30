
#include "TMath.h" 
#include "EventAction.hh"
#include "DataManager.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ios.hh"
#include "MoreUnits.hh"
//-------------------------------------------------------------------------------
 
EventAction::EventAction() :fEventMessenger(0)
{
  G4cout << "Construction of Event Action"  << G4endl;
  fEventMessenger= new EventActionMessenger(this);
  data       = DataManager::GetInstance();
}

//-------------------------------------------------------------------------------
 
EventAction::~EventAction()
{
  delete fEventMessenger;
}

//------------------------------------------------------------------------------
 
void EventAction::BeginOfEventAction(const G4Event* evnt)
{
  if(evnt->GetEventID()%10000==0)
    G4cout<<Form("Processing Event #: %d",evnt->GetEventID())<<G4endl; 

  //Initializing all values to null
  data->InitializeEvent();
  
  //Here we are going to assume some things about how the PrimaryGenerator Action is Written
  //We assume that GeneratePrimaries only has one call to ParticleGun->GeneratePrimaryVertex
  //And that there is only one particle associated with that vertex
  if(evnt->GetNumberOfPrimaryVertex()==1 && evnt->GetPrimaryVertex(0)->GetNumberOfParticle()==1)
    {
      //Useful Pointers and Values
      G4PrimaryVertex* thePrimaryVertex = evnt->GetPrimaryVertex(0);
      G4PrimaryParticle* thePrimaryParticle = thePrimaryVertex->GetPrimary(0);
      G4int PrimaryTrackID=thePrimaryParticle->GetTrackID();
      G4String PrimaryParticleName=thePrimaryParticle->GetG4code()->GetParticleName();
      G4ThreeVector PrimaryParticlePosition=thePrimaryVertex->GetPosition();
      G4ThreeVector PrimaryParticleMomentum=thePrimaryParticle->GetMomentum();
      G4double PrimaryParticleMass=thePrimaryParticle->GetMass();
      G4double PrimaryParticleKineticEnergy=sqrt(PrimaryParticleMomentum.mag2()+PrimaryParticleMass*PrimaryParticleMass)-PrimaryParticleMass;
      G4double PrimaryParticleTheta=PrimaryParticleMomentum.getTheta();
      G4double PrimaryParticlePhi=PrimaryParticleMomentum.getPhi();
      G4double PrimaryParticleX=PrimaryParticlePosition.x();
      G4double PrimaryParticleY=PrimaryParticlePosition.y();
      G4double PrimaryParticleZ=PrimaryParticlePosition.z();
      
      //Setting Branch Variables for Event Information
      data->SetEventName(TString::Format("Event_%d", evnt->GetEventID()));
      data->SetEventNumber(evnt->GetEventID());
      data->SetPrimaryTrackID(PrimaryTrackID);
      data->SetPrimaryParticleName(PrimaryParticleName);
      data->SetPrimaryParticleKineticEnergy(PrimaryParticleKineticEnergy);
      data->SetPrimaryParticleTheta(PrimaryParticleTheta);
      data->SetPrimaryParticlePhi(PrimaryParticlePhi);
      data->SetPrimaryParticleX(PrimaryParticleX);
      data->SetPrimaryParticleY(PrimaryParticleY);
      data->SetPrimaryParticleZ(PrimaryParticleZ);

      
    }
  else
    {
      G4cerr<<"**ERROR:  EVENT ACTION::BeginOfEventAction  INCORRECT GENERATION OF PRIMARIES IN PRIMARY GENERATOR ACTION!!**"<<G4endl;
      G4Exception();
    }
 
}

//------------------------------------------------------------------------------
 
void EventAction::EndOfEventAction(const G4Event* evnt)
{
  //G4cout<<"EndOfEvent"<<G4endl;
  data->FillEventTree();
  /*
  data->FillEvent();
  G4int event_id = evnt->GetEventID();
  
  // get number of stored trajectories
  //
  G4TrajectoryContainer* trajectoryContainer = evnt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
  
  // periodic printing
  //
  G4cout << "Hello"  <<G4endl;

  if (event_id < 100 || event_id%100 == 0) {
    G4cout << ">>> Event " << evnt->GetEventID() << G4endl;
    G4cout << "    " << n_trajectories 
	   << " trajectories stored seth in this event." << G4endl;
    G4cout << "\tDetEventName:  " << data->GetEventName() << G4endl;
  }
  */
}


G4int EventAction::PrepareOutput(){

  //if no output file name given, don't save output
  if(fOutFileName==TString("")){
    G4cout<<"EventAction::PrepareOutput() no output file to be written"<<G4endl;
    G4cout<<"Provide output file name by"<<G4endl;
    G4cout<<"/Hinda/event/SetOutputFile XXX.root"<<G4endl;
    return 0;
  }

  //if file name given, try to open the file
  fOutFile=new TFile(fOutFileName,"CREATE");
  //if the file already exists, ask if it should be overwritten
  while (!fOutFile->IsOpen()){
    G4cout<<"EventAction::PrepareOutput() output file already exists, do you want to overwrite it? enter y/n"<<G4endl;
    G4String ans;
    G4cin>>ans;
    if(ans==G4String("y")) fOutFile=new TFile(fOutFileName,"RECREATE");
    else {
      G4cout<<"Provide a new name, or type n to exit simulation"<<G4endl;
      G4cin>>ans;
      if(ans==G4String("n")) exit(1);
      else {
	fOutFileName=ans;
	fOutFile=new TFile(fOutFileName,"CREATE");
      }
    }
  }
  
  G4cout<<"EventAction::PrepareOutput() output will be written to "<<fOutFileName<<G4endl;

  //sets output file, creates trees, sets branches
  data->SetOutputFile(fOutFile);

}


void EventAction::CloseOutput(){

  if(!data) return;
  data->WriteTrees();
  //delete data;
  fOutFile->Close();
  if(fOutFile) delete fOutFile;

}



//-----------------------------------------------------------------------------
