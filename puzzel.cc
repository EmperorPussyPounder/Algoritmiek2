// Implementatie van klasse Puzzel

#include <iostream>
#include <fstream>
#include <set>
#include <ctime>  // voor clock() en clock_t
#include "standaard.h"
#include "puzzel.h"
using namespace std;

//*************************************************************************

Puzzel::Puzzel ()
{
  
  // TODO: implementeer zo nodig deze constructor

}  // default constructor

//*************************************************************************

Puzzel::~Puzzel ()
{
  // TODO: implementeer zo nodig deze destructor

}  // destructor

//*************************************************************************

bool Puzzel::leesInPuzzel (const char* invoerNaam)
{
    ifstream fin;
    fin.open (invoerNaam);
    if (!fin.is_open()) return false;
    fin >> aantalKeuzes;
    if(!integerPositief("aantalKeuzes", aantalKeuzes)) return false;
    int invoer;
    for (int i = 0; i < aantalKeuzes; ++i)
    {
      fin >> invoer;
      if (keuzes.count(invoer) || !integerPositief("sudokuVakje", invoer)) return false;
      keuzes.insert(invoer);
    }
    keuzes.insert(Leeg);

    fin >> hoogte >> breedte;
    vector<pair<int,int>> ingevuld;
    if (!integerInBereik(hoogte, MinDimensie, MaxDimensie) ||
        !integerInBereik(breedte, MinDimensie, MaxDimensie)) return false;
    for (int j = 0; j < hoogte; ++j)
    {
        for (int i = 0; i < breedte; ++i)
        {
          fin >> invoer;
          if (!keuzes.count(invoer)) return false;
          if (invoer) ingevuld.push_back(make_pair(i, j));
          bord[i][j] = invoer;
        }
      }
    keuzes.erase(Leeg);
    fin >> aantalGroepen;
    if(!integerPositief("aantalGroepen", aantalGroepen)) return false;
    int aantalGroepVakjes, maxSom, maxVoorkomens,
        x, y;
    Groep::setDomain(keuzes);
    for(int i = 0; i < aantalGroepen; ++i)
    {
      fin >> aantalGroepVakjes >> maxSom >> maxVoorkomens;
      if (!integerPositief("aantalGroepvakjes", aantalGroepVakjes)
          || !integerPositief("maxSom", maxSom)
          || !integerPositief("maxVoorkomens", maxVoorkomens)) return false;
      auto groep = new Groep(maxSom, maxVoorkomens);
      for(int j = 0; j < aantalGroepVakjes; ++j)
      {
        fin >> y >> x;
        auto coordinaten = make_pair(x,y);
        if ( !integerInBereik("x-coordinaat", x, 0, breedte - 1)
            || !integerInBereik("y-coordinaat", y, 0, hoogte - 1)) return false;
        if(!groepenWijzer.count(coordinaten))
        {
          vector<Groep*> groepenLijst({groep});
          groepenWijzer.insert({coordinaten, groepenLijst});
        }
        else groepenWijzer[coordinaten].push_back(groep);
    }
  }
  //TODO: vul gevonden waardes in en controlleer of deze geldig zijn.
  erIsEenPuzzel = true;
  return true;

}  // leesInPuzzel

//*************************************************************************

void Puzzel::drukAfPuzzel ()
{
}  // drukAfPuzzel

//*************************************************************************

void Puzzel::drukAfInhoud ()
{
  // TODO: implementeer deze memberfunctie
  if (!erIsEenPuzzel)
  {
    cout << "Er is geen geldige puzzel.\n";
    return;
  }

  for (int j = 0; j < breedte; ++j)
  {
    for (int i = 0; i < hoogte; ++i)
    {
       cout << " " << ((bord[i][j]) ? to_string(bord[i][j]) : "_") << " ";
    }
    cout << endl;
  }


}  // drukAfInhoud

//*************************************************************************

void Puzzel::drukAfOplossing (int oplossing[MaxDimensie][MaxDimensie])
{
  // TODO: implementeer deze memberfunctie

}  // drukAfOplossing

//*************************************************************************

int Puzzel::getWaarde (int rij, int kolom)
{
  if (bord[kolom][rij]) return bord[kolom][rij];
  return GeenWaarde;

}  // getWaarde

//*************************************************************************

bool Puzzel::vulWaardeIn (int rij, int kolom, int nwWaarde)
{
  // TODO: implementeer deze memberfunctie
  auto coordinaten = make_pair(kolom,rij);
  // TODO: deze lijn hier maakt elke keer een kopie van de originele groepen
  // maar we willen de originele groep. Fix dit
  auto & groepen = groepenWijzer[coordinaten];
  Groep::commit = true;
  for (auto groep : groepen) groep->insert(coordinaten, nwWaarde);

  if (Groep::commit)
  {
    for (auto groep : groepen) groep->commitInsert(coordinaten, nwWaarde);
    bord[kolom][rij] = nwWaarde;
    return true;
  }
  return false;

}  // vulWaardeIn

//*************************************************************************

bool Puzzel::haalWaardeWeg (int rij, int kolom)
{
  auto coordinaten = make_pair(kolom, rij);
  auto & groepen = groepenWijzer[coordinaten];
  Groep::commit = true;
  for (auto groep : groepen) groep->erase(coordinaten);

  if (Groep::commit)
  {
    for(auto groep : groepen) groep->commitErase(coordinaten);
    bord[kolom][rij] = Leeg;
    return true;
  }
  return false;

}  // haalWaardeWeg

//*************************************************************************

bool Puzzel::bepaalOplossingBT (bool slim,
                         int oplossing[MaxDimensie][MaxDimensie],
                         long long &aantalDeeloplossingen)
{
  // TODO: implementeer deze memberfunctie

  return false;

}  // bepaalOplossingBT

//*************************************************************************

int Puzzel::bepaalAlleOplossingenBT
      (bool slim, int oplossing[MaxDimensie][MaxDimensie],
       long long &aantalDeeloplossingen)
{
  // TODO: implementeer deze memberfunctie

  return 0;

}  // bepaalAlleOplossingenBT

//*************************************************************************

void Puzzel::doeExperiment ()
{
  // TODO: implementeer deze memberfunctie

}  // doeExperiment

//*************************************************************************

bool Puzzel::maakPuzzelMetWaardeReeksGretig (const char* invoerNaam)
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // maakPuzzelMetWaardeReeksGretig

