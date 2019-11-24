#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GDMLParser.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction(const G4GDMLParser& parser)
: G4VUserDetectorConstruction(),
  fScoringVolume(0),
   fParser(parser)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  const G4GDMLAuxMapType* auxmap = fParser.GetAuxMap();
  G4GDMLAuxMapType::const_iterator sv;
  G4cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << G4endl << G4endl;
  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++) 
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end(); vit++)
    {
      G4cout << "--> Type: " << (*vit).type
                << " Value: " << (*vit).value << G4endl;
    }
    if (((*iter).first)->GetName() == "Tracker") {
      sv = iter;
      G4cout << "Scoring Volume set to " << ((*sv).first)->GetName() << G4endl;
    }
  }
  G4cout << G4endl;

  // Set Shape2 as scoring volume
  //
  fScoringVolume = (*sv).first;

  //
  //always return the physical World
  //
  return fParser.GetWorldVolume();                
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
