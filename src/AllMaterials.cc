#include "AllMaterials.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

AllMaterials::AllMaterials()
  :  a(0), n(0), z(0), density(0), fractionMass(0), nComponents(0), nIsotopes(0), nAtoms(0)
{
  G4cout << "Instance of AllMaterials Constructed!" << G4endl;

  DefineElements();
  DefineMaterials();

}//END of constructor

AllMaterials::~AllMaterials()
{
  G4cout << "Instance of AllMaterials Destructed!" << G4endl;

}//END of destructor

G4Material* AllMaterials::GetMaterial(G4String materialName)
{
  G4Material *theMaterial = G4Material::GetMaterial(materialName);

  if( !theMaterial )
  {
    G4cerr << "   AllMaterials::GetMaterial - Error! The material \"" << materialName << "\" does not exist." << G4endl;
    G4Exception("AllMaterials::GetMaterial", "007", FatalException, "material does not exist");
  }

  return theMaterial;

}//END of GetMaterial()

void AllMaterials::PrintElementTable(void)
{
  G4cout << *( G4Element::GetElementTable() ) << G4endl;

}//END of PrintElementTable()

void AllMaterials::PrintMaterialTable(void)
{
  G4cout << *( G4Material::GetMaterialTable() ) << G4endl;

}//END of PrintMaterialTable()

void AllMaterials::DefineElements(void)
{
  z =  1;
  a =  1.008*g/mole;
  elH = new G4Element("Hydrogen", "H", z, a); // Cannot use G4Isotope for Hydrogen
  a =  2.014*g/mole;
  isoD = new G4Isotope("Deuteron", z, n=2, a);
  elD  = new G4Element("Deuterium", "D", nIsotopes=1);
  elD->AddIsotope(isoD, 1.0);

  z =  2;
  a =  3.016*g/mole;
  isoHe3 = new G4Isotope("Helium-3", z, n=3,a);
  elHe3  = new G4Element("Helium-3", "He3", nIsotopes=1);
  elHe3->AddIsotope(isoHe3, 1.0);
  a =  4.003*g/mole;
  isoHe4 = new G4Isotope("Helium-4", z, n=4,a);
  elHe4  = new G4Element("Helium-4", "He4", nIsotopes=1);
  elHe4->AddIsotope(isoHe4, 1.0);

  z = 5;
  isoB10 = new G4Isotope("Boron-10", z, n=10);
  isoB11 = new G4Isotope("Boron-11", z, n=11);
  elB    = new G4Element("Boron", "B", nIsotopes=2);
  elB->AddIsotope(isoB10, 0.1980);
  elB->AddIsotope(isoB11, 0.8020);

  z =  6;
  a = 12.01*g/mole;
  elC = new G4Element("Carbon", "C", z, a);

  z =  7;
  a = 14.01*g/mole;
  elN = new G4Element("Nitrogen", "N", z, a);

  z =  8;
  isoO16 = new G4Isotope("Oxygen-16", z, n=16);
  isoO17 = new G4Isotope("Oxygen-17", z, n=17);
  isoO18 = new G4Isotope("Oxygen-18", z, n=18);
  elO    = new G4Element("Oxygen", "O", nIsotopes=3);
  elO->AddIsotope(isoO16, 0.9976);
  elO->AddIsotope(isoO17, 0.0004);
  elO->AddIsotope(isoO18, 0.0020);

  z = 11;
  a = 22.98976928*g/mole;
  elNa = new G4Element("Sodium", "Na", z, a);

  z = 12;
  isoMg24 = new G4Isotope("Magnesium-24", z, n=24);
  isoMg25 = new G4Isotope("Magnesium-25", z, n=25);
  isoMg26 = new G4Isotope("Magnesium-26", z, n=26);
  elMg    = new G4Element("Magnesium", "Mg", nIsotopes=3);
  elMg->AddIsotope(isoMg24, 0.7899);
  elMg->AddIsotope(isoMg25, 0.1000);
  elMg->AddIsotope(isoMg26, 0.1101);

  z = 13;
  a = 26.98*g/mole;
  elAl = new G4Element("Aluminum", "Al", z, a);

  z = 14;
  isoSi28 = new G4Isotope("Silicon-28", z, n=28);
  isoSi29 = new G4Isotope("Silicon-29", z, n=29);
  isoSi30 = new G4Isotope("Silicon-30", z, n=30);
  elSi    = new G4Element("Silicon", "Si", nIsotopes=3);
  elSi->AddIsotope(isoSi28, 0.9223);
  elSi->AddIsotope(isoSi29, 0.0467);
  elSi->AddIsotope(isoSi30, 0.0310);

  z = 19;
  isoK39  = new G4Isotope("Potassium-39", z, n=39);
  isoK41  = new G4Isotope("Potassium-41", z, n=41);
  elK     = new G4Element("Potassium", "K", nIsotopes=2);
  elK->AddIsotope(isoK39, 0.9326);
  elK->AddIsotope(isoK41, 0.0674);

  z = 20;
  isoCa40 = new G4Isotope("Calcium-40", z, n=40);
  isoCa42 = new G4Isotope("Calcium-42", z, n=42);
  isoCa43 = new G4Isotope("Calcium-43", z, n=43);
  isoCa44 = new G4Isotope("Calcium-44", z, n=44);
  isoCa46 = new G4Isotope("Calcium-46", z, n=46);
  isoCa48 = new G4Isotope("Calcium-48", z, n=48);
  elCa    = new G4Element("Calcium", "Ca", nIsotopes=6);
  elCa->AddIsotope(isoCa40, 0.9694);
  elCa->AddIsotope(isoCa42, 0.00647);
  elCa->AddIsotope(isoCa43, 0.00135);
  elCa->AddIsotope(isoCa44, 0.0209);
  elCa->AddIsotope(isoCa46, 0.000035);
  elCa->AddIsotope(isoCa48, 0.00187);

  z = 22;
  isoTi46 = new G4Isotope("Titanium-46", z, n=46);
  isoTi47 = new G4Isotope("Titanium-47", z, n=47);
  isoTi48 = new G4Isotope("Titanium-48", z, n=48);
  isoTi49 = new G4Isotope("Titanium-49", z, n=49);
  isoTi50 = new G4Isotope("Titanium-50", z, n=50);
  elTi    = new G4Element("Titanium", "Ti", nIsotopes=5);
  elTi->AddIsotope(isoTi46, 0.0800);
  elTi->AddIsotope(isoTi47, 0.0730);
  elTi->AddIsotope(isoTi48, 0.7380);
  elTi->AddIsotope(isoTi49, 0.0550);
  elTi->AddIsotope(isoTi50, 0.0540);

  z = 24;
  isoCr50 = new G4Isotope("Chromium-50", z, n=50);
  isoCr52 = new G4Isotope("Chromium-52", z, n=52);
  isoCr53 = new G4Isotope("Chromium-53", z, n=53);
  isoCr54 = new G4Isotope("Chromium-54", z, n=54);
  elCr    = new G4Element("Chromium", "Cr", nIsotopes=4);
  elCr->AddIsotope(isoCr50, 0.04345);
  elCr->AddIsotope(isoCr52, 0.83789);
  elCr->AddIsotope(isoCr53, 0.09501);
  elCr->AddIsotope(isoCr54, 0.02365);

  z = 25;
  a = 54.938*g/mole;
  elMn = new G4Element("Manganese", "Mn", z, a);

  z = 26;
  isoFe54 = new G4Isotope("Iron-54", z, n=54);
  isoFe56 = new G4Isotope("Iron-56", z, n=56);
  isoFe57 = new G4Isotope("Iron-57", z, n=57);
  isoFe58 = new G4Isotope("Iron-58", z, n=58);
  elFe    = new G4Element("Iron", "Fe", nIsotopes=4);
  elFe->AddIsotope(isoFe54, 0.0580);
  elFe->AddIsotope(isoFe56, 0.9172);
  elFe->AddIsotope(isoFe57, 0.0220);
  elFe->AddIsotope(isoFe58, 0.0028);

  z = 29;
  isoCu63 = new G4Isotope("Copper-63", z, n=63);
  isoCu65 = new G4Isotope("Copper-65", z, n=65);
  elCu    = new G4Element("Copper", "Cu", nIsotopes=2);
  elCu->AddIsotope(isoCu63, 0.6920);
  elCu->AddIsotope(isoCu65, 0.3080);

  z = 30;
  isoZn64 = new G4Isotope("Zinc-64", z, n=64);
  isoZn66 = new G4Isotope("Zinc-66", z, n=66);
  isoZn67 = new G4Isotope("Zinc-67", z, n=67);
  isoZn68 = new G4Isotope("Zinc-68", z, n=68);
  isoZn70 = new G4Isotope("Zinc-70", z, n=70);
  elZn    = new G4Element("Zinc", "Zn", nIsotopes=5);
  elZn->AddIsotope(isoZn64, 0.4860);
  elZn->AddIsotope(isoZn66, 0.2790);
  elZn->AddIsotope(isoZn67, 0.0410);
  elZn->AddIsotope(isoZn68, 0.1880);
  elZn->AddIsotope(isoZn70, 0.0060);

  z = 38;
  isoSr84 = new G4Isotope("Strontium-84", z, n=84);
  isoSr86 = new G4Isotope("Strontium-86", z, n=86);
  isoSr87 = new G4Isotope("Strontium-87", z, n=87);
  isoSr88 = new G4Isotope("Strontium-88", z, n=88);
  elSr    = new G4Element("Stontium", "Sr", nIsotopes=4);
  elSr->AddIsotope(isoSr84, 0.0060);
  elSr->AddIsotope(isoSr86, 0.0980);
  elSr->AddIsotope(isoSr87, 0.0700);
  elSr->AddIsotope(isoSr88, 0.8260);

  z = 56;
  isoBa130 = new G4Isotope("Barium-130", z, n=130);
  isoBa132 = new G4Isotope("Barium-132", z, n=132);
  isoBa134 = new G4Isotope("Barium-134", z, n=134);
  isoBa135 = new G4Isotope("Barium-135", z, n=135);
  isoBa136 = new G4Isotope("Barium-136", z, n=136);
  isoBa137 = new G4Isotope("Barium-137", z, n=137);
  isoBa138 = new G4Isotope("Barium-138", z, n=138);
  elBa     = new G4Element("Barium", "Ba", nIsotopes=7);
  elBa->AddIsotope(isoBa130, 0.0012);
  elBa->AddIsotope(isoBa132, 0.0012);
  elBa->AddIsotope(isoBa134, 0.0242);
  elBa->AddIsotope(isoBa135, 0.0659);
  elBa->AddIsotope(isoBa136, 0.0785);
  elBa->AddIsotope(isoBa137, 0.1120);
  elBa->AddIsotope(isoBa138, 0.7170);

  z = 53;
  a = 126.90447*g/mole;
  elI = new G4Element( "Iodine", "I", z, a);

  /*
  z = 81;
  isoTl203=new G4Isotope("Thallium-203",z,n=122);
  isoTl205=new G4Isotope("Thallium-205",z,n=124);
  elTl=new G4Element("Thallium","Tl",nIsotopes=2);
  elTl->AddIsotope(isoTl203,0.29524);
  elTl->AddIsotope(isoTl205,0.70476);
  */

  z = 82;
  isoPb204 = new G4Isotope("Lead-204", z, n=204);
  isoPb206 = new G4Isotope("Lead-206", z, n=206);
  isoPb207 = new G4Isotope("Lead-207", z, n=207);
  isoPb208 = new G4Isotope("Lead-208", z, n=208);
  elPb    = new G4Element("Lead", "Pb", nIsotopes=4);
  elPb->AddIsotope(isoPb204, 0.0142);
  elPb->AddIsotope(isoPb206, 0.2410);
  elPb->AddIsotope(isoPb207, 0.2210);
  elPb->AddIsotope(isoPb208, 0.5238);

  z = 83;
  a = 208.98038*g/mole;
  elBi=new G4Element("Bismuth","Bi",z,a);


}//END of DefineElements()

void AllMaterials::DefineMaterials(void)
{
  theState = kStateGas;
  theTemp = STP_Temperature + 20;
  thePressure = STP_Pressure;
  density = 1.29*mg/cm3;
//  matAir = new G4Material("Air", density, nComponents=2, theState, theTemp, thePressure);
  matAir = new G4Material("Air", density, nComponents=2);
  matAir->AddElement(elN, fractionMass=0.7);
  matAir->AddElement(elO, fractionMass=0.3);

  density = 2.70*g/cm3;
  matAluminum = new G4Material("Aluminium", density, nComponents=1);
  matAluminum->AddElement(elAl, fractionMass=1.0);

  density = 2.267*g/cm3;
  matCarbon = new G4Material("Carbon", density, nComponents=1);
  matCarbon->AddElement(elC, fractionMass=1.0);

  matAlAlloy6082 = new G4Material("AlAlloy6082", density, nComponents=9);
  matAlAlloy6082->AddElement(elAl, fractionMass=0.9535);
  matAlAlloy6082->AddElement(elSi, fractionMass=0.0130);
  matAlAlloy6082->AddElement(elMg, fractionMass=0.0120);
  matAlAlloy6082->AddElement(elMn, fractionMass=0.0100);
  matAlAlloy6082->AddElement(elFe, fractionMass=0.0050);
  matAlAlloy6082->AddElement(elCr, fractionMass=0.0025);
  matAlAlloy6082->AddElement(elZn, fractionMass=0.0020);
  matAlAlloy6082->AddElement(elCu, fractionMass=0.0010);
  matAlAlloy6082->AddElement(elTi, fractionMass=0.0010);

  density = 0.901*g/cm3;
  matBC501 = new G4Material("BC501", density, nComponents=2);
  matBC501->AddElement(elC, nAtoms=1000);
  matBC501->AddElement(elH, nAtoms=1287);

  density = 0.874*g/cm3;
  matBC501A = new G4Material("BC501A", density, nComponents=2);
  matBC501A->AddElement(elC, nAtoms=1000);
  matBC501A->AddElement(elH, nAtoms=1212);

  density = 0.877*g/cm3;
  matBC505 = new G4Material("BC505", density, nComponents=2);
  matBC505->AddElement(elC, nAtoms=1000);
  matBC505->AddElement(elH, nAtoms=1331);

  theState = kStateGas;
  theTemp = 294.0*kelvin;
  thePressure = 170*bar;
  density = 0.021*g/cm3;
  matHelium3Gas = new G4Material("Helium3Gas", density, nComponents=2, theState, theTemp, thePressure);
  matHelium3Gas->AddElement(elHe3, fractionMass=0.9987);
  matHelium3Gas->AddElement(elHe4, fractionMass=0.0013);

  density = 1.18*g/cm3;
  matLucite = new G4Material("Lucite", density, nComponents=3);
  matLucite->AddElement(elC, nAtoms=5);
  matLucite->AddElement(elH, nAtoms=8);
  matLucite->AddElement(elO, nAtoms=2);

  density = 3.67*g/cm3;
  matNaI = new G4Material("NaI", density, nComponents=2);
  matNaI->AddElement(elNa,  nAtoms=1);
  matNaI->AddElement(elI,   nAtoms=1);

  //Doesn't seem to work
  //  matNaITl=new G4Material("NaITl", density, nComponents=2);
  //  matNaITl->AddMaterial(matNaI, fractionMass=0.996);
  //  matNaITl->AddElement(elTl,fractionMass=0.004); 

  density = 0.95*g/cm3;
  matPolyethelene = new G4Material("Polyethelene", density, nComponents=2);
  matPolyethelene->AddElement(elC, nAtoms=1);
  matPolyethelene->AddElement(elH, nAtoms=2);

  density = 0.90*g/cm3;
  matParaffinWax = new G4Material("ParaffinWax", density, nComponents=2);
  matParaffinWax->AddElement(elC, nAtoms=25);
  matParaffinWax->AddElement(elH, nAtoms=52);

  density = 7.7*g/cm3;
  matSteel = new G4Material("Steel", density, nComponents=2);
  matSteel->AddElement(elC,  fractionMass=0.04);
  matSteel->AddElement(elFe, fractionMass=0.96);

//  theState = kStateGas;
//  theTemp = STP_Temperature;
//  thePressure = 2.0e-2*bar;
//  density = 1.0e-5*g/cm3;
//  matVacuum = new G4Material("Vacuum", density, nComponents=1, theState, theTemp, thePressure);
  density = 1.7e-09*mg/cm3; // for a pressure of 1e-6 torr
  matVacuum = new G4Material("Vacuum", density, nComponents=1);
  matVacuum->AddMaterial(matAir, fractionMass=1.0);

  density = 1.0*g/cm3;
  matHydrogen1 = new G4Material("smallHydrogen1", density, nComponents=1);
  matHydrogen1->AddElement(elH, nAtoms=1);

  // liquid deuterium
  density = 0.164*g/cm3;
  matlDeuterium = new G4Material("liquidDeuterium", density, nComponents=1);
  matlDeuterium->AddElement(elD, fractionMass=1.0);

  // liquid helium-4
  density = 0.125*g/cm3;
  matlHelium4 = new G4Material("liquidHelium4", density, nComponents=1);
  matlHelium4->AddElement(elHe4, fractionMass=1.0);

  density = 1.1056*g/cm3;
  matD2O = new G4Material("D2O", density, nComponents=2);
  matD2O->AddElement(elD, nAtoms=2);
  matD2O->AddElement(elO, nAtoms=1);

  density = 11.35*g/cm3;
  matLead = new G4Material("Lead", density, nComponents=1);
  matLead->AddElement(elPb, fractionMass=1.0000);

  //target materials
  density=9.78*g/cm3;
  matBismuth= new G4Material("Bismuth",density,nComponents=1);
  matBismuth->AddElement(elBi,fractionMass=1.0000);
  
  matYttrium = G4NistManager::Instance()->FindOrBuildMaterial("G4_Y"); 
  matG4Bismuth = G4NistManager::Instance()->FindOrBuildMaterial("G4_Bi");
  matUranium238 = G4NistManager::Instance()->FindOrBuildMaterial("G4_U");
  matTin = G4NistManager::Instance()->FindOrBuildMaterial("G4_Sn");

  density = 2.23*g/cm3;
  matPyrex = new G4Material("Pyrex", density, nComponents=6);
  matPyrex->AddElement(elB,  fractionMass=0.0401);
  matPyrex->AddElement(elO,  fractionMass=0.5396);
  matPyrex->AddElement(elNa, fractionMass=0.0282);
  matPyrex->AddElement(elAl, fractionMass=0.0116);
  matPyrex->AddElement(elSi, fractionMass=0.3772);
  matPyrex->AddElement(elK,  fractionMass=0.0033);


  density = 2.76*g/cm3;
  matGE180 = new G4Material("GE180", density, nComponents=6);
  matGE180->AddElement(elO,  fractionMass=0.4271);
  matGE180->AddElement(elAl, fractionMass=0.0757);
  matGE180->AddElement(elSi, fractionMass=0.2819);
  matGE180->AddElement(elCa, fractionMass=0.0465);
  matGE180->AddElement(elSr, fractionMass=0.0059);
  matGE180->AddElement(elBa, fractionMass=0.1630);

  density = 3.510*g/cm3;
  matBarium = new G4Material("Barium", density, nComponents=1);
  matBarium->AddElement(elBa,  fractionMass=1.0000);

  density = 1.29*g/cm3;
  matSilicone=new G4Material("Silicone", density, nComponents=4);
  matSilicone->AddElement(elSi,nAtoms=1);
  matSilicone->AddElement(elC,nAtoms=2);
  matSilicone->AddElement(elH,nAtoms=6);
  matSilicone->AddElement(elO,nAtoms=1);


  matConcrete = G4NistManager::Instance()->FindOrBuildMaterial("G4_CONCRETE");
  matPlastic  = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC");
  matPVC  = G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
  matKAPTON  = G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON");
  matQuartzGlass = G4NistManager::Instance()->FindOrBuildMaterial("G4_GLASS_PLATE");
  matQuartzGlass->SetName("QuartzGlass");
  matTEFLON = G4NistManager::Instance()->FindOrBuildMaterial("G4_TEFLON");
  matTEFLON->SetName("Teflon");


  density = 2.70*g/cm3 * 1e3;
  matDenseAl = new G4Material("DenseAluminum", density, nComponents=1);
  matDenseAl->AddElement(elAl, fractionMass=1.0000);

  density = 1.0*g/cm3;
  matDeuterium = new G4Material("Deuterium", density, nComponents=1);
  matDeuterium->AddElement(elD, fractionMass=1.0000);

  theState = kStateGas;
  theTemp = 296.15*kelvin; // = 23 C
  thePressure = 3808*0.001315789474*atmosphere; // converting from torr to atm
  G4double rho0 = 1.683e-04*g/cm3; // density at T = 293.15 K and P = 1 atm
  G4double temp0 = 293.15*kelvin;
  G4double pres0 = 1*atmosphere;
  density = rho0 * (thePressure/pres0) * (temp0/theTemp);
  matD2Gas = new G4Material("D2Gas", density, nComponents=1, theState, theTemp, thePressure);
  matD2Gas->AddElement(elD, nAtoms=2);

}//END of DefineMaterials()
