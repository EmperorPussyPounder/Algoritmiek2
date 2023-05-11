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
    for(int x = 0; x < MaxDimensie; ++x)
    {
      for(int y = 0; y < MaxDimensie; ++y)
      {
        bord[x][y] = Leeg;
      }
    }
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
    vector<pair<pair<int,int>, int>> ingevuld;
    if (!integerInBereik(hoogte, MinDimensie, MaxDimensie) ||
        !integerInBereik(breedte, MinDimensie, MaxDimensie)) return false;
    for (int j = 0; j < hoogte; ++j)
    {
        for (int i = 0; i < breedte; ++i)
        {
          fin >> invoer;
          if (!keuzes.count(invoer)) return false;
          if (invoer) ingevuld.push_back(make_pair(make_pair(i, j),invoer));
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
  erIsEenPuzzel = true;

  for (auto & vakInvoer : ingevuld)
  {
    auto vakje = vakInvoer.first;
    auto invoerWaarde = vakInvoer.second;
    auto rij = vakje.second;
    auto kolom = vakje.first;
    erIsEenPuzzel = erIsEenPuzzel && vulWaardeIn(rij, kolom, invoerWaarde);
    if(!erIsEenPuzzel) return false;
  }
  return true;

}  // leesInPuzzel

//*************************************************************************

void Puzzel::drukAfPuzzel ()
{
   if (!erIsEenPuzzel) cout << "Het is niet gelukt een puzzel te laden; ";
   cout << "Er zijn " << aantalKeuzes << " invulbare waardes zijn: ";
   for (const auto & waarde : Groep::getDomain()) cout << waarde << ", ";
   cout << "met " << aantalGroepen << " groepen" << endl;
}  // drukAfPuzzel

//*************************************************************************

void Puzzel::drukAfInhoud ()
{
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
  auto coordinaten = make_pair(kolom,rij);
  if (!integerInBereik("Rij", rij, 0, hoogte - 1)
      || !integerInBereik("Kolom", kolom, 0, breedte - 1)
      || ingevuld.count(coordinaten)) return false;
  auto & groepen = groepenWijzer[coordinaten];
  Groep::commit = true;
  for (auto groep : groepen) groep->insert(coordinaten, nwWaarde);

  if (Groep::commit)
  {
    for (auto groep : groepen) groep->commitInsert(coordinaten, nwWaarde);
    ingevuld.insert(coordinaten);
    bord[kolom][rij] = nwWaarde;
    return true;
  }
  return false;

}  // vulWaardeIn

//*************************************************************************

bool Puzzel::haalWaardeWeg (int rij, int kolom)
{
  auto coordinaten = make_pair(kolom, rij);
  if (!integerInBereik("Rij", rij, 0, hoogte - 1)
      || !integerInBereik("Kolom", kolom, 0, breedte - 1)
      || !ingevuld.count(coordinaten)) return false;
  auto & groepen = groepenWijzer[coordinaten];
  Groep::commit = true;
  for (auto groep : groepen) groep->erase(coordinaten);

  if (Groep::commit)
  {
    for(auto groep : groepen) groep->commitErase(coordinaten);
    ingevuld.erase(coordinaten);
    bord[kolom][rij] = Leeg;
    return true;
  }
  return false;

}  // haalWaardeWeg

//*************************************************************************

my_set Puzzel::intersect(my_set A, my_set B)
{
  my_set intersection;
  for (auto & elem : A)
  {
    if (B.count(elem)) intersection.insert(elem);
  }
  return intersection;
}

my_set Puzzel::mogelijkeInputs(int x, int y)
{
  if (ingevuld.count(make_pair(x,y))) return GeenMogelijkheden;
  auto groepen = groepenWijzer[make_pair(x,y)];
  auto opties = groepen[0]->getResterendeKeuzes();
  for (auto & groep : groepen) opties = intersect(opties, groep->getResterendeKeuzes());
  return opties;

}

bool Puzzel::eindeSpel()
{
  for (int j = 0; j < hoogte; ++j)
  {
    for (int i = 0; i < breedte; ++i)
    {
      if (bord[i][j] == Leeg) return false;
    }
  }
  return true;
}

void Puzzel::sorteer(vector<pair<int,int>> &lijst)
{
  return;
}

bool Puzzel::bepaalOplossingBT (bool slim,
                         int oplossing[MaxDimensie][MaxDimensie],
                         long long &aantalDeeloplossingen)
{
  // TODO: maak deze invoerlijst elders aan en maak het een field van de class
  aantalDeeloplossingen = 0;
  if(!erIsEenPuzzel) return false;
  vector<pair<int, int>> invoerLijst;
  if(slim) sorteer(invoerLijst);
  for (int j = 0; j < hoogte; ++j)
  {
    for (int i = 0; i < breedte; ++i)
    {
      auto coordinaten = make_pair(i, j);
      if (!ingevuld.count(coordinaten)) invoerLijst.push_back(coordinaten);
    }
  }


  return bepaalOplossingBT(slim, oplossing, aantalDeeloplossingen, invoerLijst);

}  // bepaalOplossingBT

bool Puzzel::bepaalOplossingBT(bool slim, int oplossing[MaxDimensie][MaxDimensie],
                               long long &aantalDeeloplossingen, vector<pair<int, int>> invoerLijst)
{
  ++aantalDeeloplossingen;
  cout << "Poepie \n";
  for(auto & coordinaten : invoerLijst) cout << coordinaten.first << ", " << coordinaten.second << endl;
  if (invoerLijst.empty())
  {
    for(int x = 0; x < breedte; ++x)
    {
      for (int y = 0; y < hoogte; ++y)
      {
        oplossing[x][y] = bord[x][y];
      }
    }
    return true;
  }

  if(slim) sorteer(invoerLijst);
  for(auto it = invoerLijst.begin(); it != invoerLijst.end(); ++it)
  {
    auto kolom = (*it).first;
    auto rij = (*it).second;
    auto invulWaardes = mogelijkeInputs(kolom, rij);
    for (auto & invul : invulWaardes)
    {
      vulWaardeIn(rij, kolom, invul);
      it = invoerLijst.erase(it);
      auto succes = bepaalOplossingBT(slim, oplossing, aantalDeeloplossingen, invoerLijst);
      if (succes) return true;
      invoerLijst.insert(it, make_pair(kolom, rij));
      cout << (*it).first << ", " << (*it).second << " are back in their original place. \n";
    }
  }
  return false;
}

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

