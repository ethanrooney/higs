/*********************************************************************
Created by S. Henshaw 4/6/10

This is a Singleton class which is uesd to parse hit,track,and step data
from the Run.  It is accessed by RunAction, EventAction, HINDASD's process hits.


*********************************************************************/
#include "DataManager.hh"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"


//This Creates a Singleton Intance (which means its the only instance)
DataManager* DataManager::GetInstance()
{ static DataManager *pointerToTheSingletonInstance = new DataManager();
  return pointerToTheSingletonInstance;
}

//------------------------------------------------------------------------
DataManager::~DataManager()
{
  if(fRunTree)   delete fRunTree;
  if(fEventTree) delete fEventTree;
  if(fOutFile)   delete fOutFile;
}


//-----------------------------------------------------------------------

void DataManager::SetOutputFile(TFile* f)
{

  fOutFile=f;

  //Creating an New RunTree (To Store Info about Run)
  TString tree_comment=TString::Format("HINDA simmulation RunInfo, Run #: %d ",fRunNumber);
  fRunTree = new TTree("RunTree", tree_comment);
  fRunTree->SetDirectory(fOutFile);
  fRunTree->SetAutoSave();
  //fRunTree->SetAutoSave(500000000); // autosave when every 500Mb
  //fRunTree->SetCacheSize(10000000);  //set a 10 MBytes cache (useless when writing local files)
  
  //save each core to a single tree
  //Creating a New EventTree (To Store Data from Events)
  tree_comment=TString::Format("HINDA simmulation EventTree (Data from Events), Run #: %d ",fRunNumber);
  fEventTree = new TTree("EventTree", tree_comment);
  fEventTree->SetDirectory(fOutFile);
  fEventTree->SetAutoSave();
  //fEventTree->SetAutoSave(500000000); // autosave when every 500Mb
  //fEventTree->SetCacheSize(10000000);  //set a 10 MBytes cache (useless when writing local files)
  

 //save each core to a separate tree
  // fEventTree = new TTree*[fNumCores];
//   tree_comment=TString::Format("HINDA simmulation EventTree (Data from Events), Run #: %d ",fRunNumber);
//   for (Int_t i = 0; i < fNumCores; ++i) {
//     fEventTree[i] = new TTree(fCoreNamesArray[i],tree_comment);
//     fEventTree[i]->SetDirectory(fOutFile);
//     fEventTree[i]->SetAutoSave();
//   }


  //Set the branches
  SetBranches();
  
}


void DataManager::SetBranches()
{

  if(!fRunTree){
    G4cout<<"DataManager::SetBranches() Run tree does not exist, cannot set branches!"<<G4endl;
    return;
  }

  //Creating Branches of the Tree for Run Info
  fRunTree->Branch("RunNumber",&fRunNumber, "RunNumber/I"); 
  fRunTree->Branch("RunComment",&fRunComment, "RunComment/C"); 
  fRunTree->Branch("WorldX",&fWorldLengthX, "WorldX/F"); 
  fRunTree->Branch("WorldY",&fWorldLengthY, "WorldY/F"); 
  fRunTree->Branch("WorldZ",&fWorldLengthZ, "WorldZ/F"); 
  fRunTree->Branch("TargetShape",&fTargetShape, "TargetShape/C");
  fRunTree->Branch("TargetMaterial",&fTargetMaterialName, "TargetMaterial/C");


  if(!fEventTree){
    G4cout<<"DataManager::SetBranches() Event tree does not exist, cannot set branches!"<<G4endl;
    return;
  }

  // //Creating Branches of the Tree for Event Info
  fEventTree->Branch("EventName",&fEventName, "EventName/C"); 
  fEventTree->Branch("EventNumber",&fEventNumber, "EventNumber/D"); 
  fEventTree->Branch("PrimaryID",&fPrimaryTrackID, "PrimaryID/I"); 
  fEventTree->Branch("PrimaryName",&fPrimaryParticleName, "PrimaryName/C"); 
  fEventTree->Branch("PrimaryEnergy",&fPrimaryParticleKineticEnergy, "PrimaryEnergy/F"); 
  fEventTree->Branch("PrimaryTheta",&fPrimaryParticleTheta, "PrimaryTheta/F"); 
  fEventTree->Branch("PrimaryPhi",&fPrimaryParticlePhi, "PrimaryPhi/F"); 
  fEventTree->Branch("PrimaryX",&fPrimaryParticleX, "PrimaryX/F"); 
  fEventTree->Branch("PrimaryY",&fPrimaryParticleY, "PrimaryY/F"); 
  fEventTree->Branch("PrimaryZ",&fPrimaryParticleZ, "PrimaryZ/F"); 
 
  
  //Creating Branches for Sensitive Detector Volumes in Event Tree
  for(Int_t i=0;i<fNumSensitiveVols;i++)
    {
      TString Name=TString(fSensitiveLogVolName[i].data());
      G4cout<<"Name:  "<<Name.Data()<<G4endl;
      fEventTree->Branch(Form("%s",Name.Data()),&fEnergyDep[Name],Form("%s/D",Name.Data()));
    }



  //save each core to a separate tree
  // TString name;
//   for (Int_t i = 0; i < fNumCores; ++i) {
//     name = Form("%s/D",static_cast<TString>(fCoreNamesArray[i]).Data());
//     fEventTree[i]->Branch(fCoreNamesArray[i],
// 			  &fEnergyDep[fCoreNamesArray[i]],name);
//   }


}


void DataManager::InitializeEvent()
{
  fEventNumber=0;
  sprintf(fEventName," ");
  for(G4int i=0;i<fNumSensitiveVols;i++)
    //SetEnergyDeposited(fSensitiveLogVolName[i],0.0);
    SetEnergyDeposited(fSensitiveLogVolName[i],NULL);
}

// //only fill event tree if energy deposited is > 0
// void DataManager::FillEventTree() {
//   for (Int_t i = 0; i < fNumCores; ++i) {
//     if (fEnergyDep[fCoreNamesArray[i]] > 0) fEventTree[i]->Fill();
//   }

// }


// void DataManager::WriteTrees() {
//   fRunTree->Write();
//   for (Int_t i = 0; i < fNumCores; ++i) fEventTree[i]->Write();

// }
