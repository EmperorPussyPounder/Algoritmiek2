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
    vector<int> invulVolgorde;
    if (!gretigBord)
    {
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
    }
    else
    {
      auto inleesbareWaardes = 0;
      auto inleesWaarde = 0;
      fin >> inleesbareWaardes;
      for (auto i = 0; i < inleesbareWaardes; ++i)
      {
        fin >> inleesWaarde;
        invulVolgorde.push_back(inleesWaarde);
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
  aantalLeeg = hoogte*breedte;
  if(!gretigBord)
  {
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
  }
  else
  {
    while (!invulVolgorde.empty())
    {
      if(bouwGretigBord(invulVolgorde)) return true;
      invulVolgorde.pop_back();
    }

  return false;
  }
} // leesInPuzzel

void Puzzel::resetBord()
{
  for (auto y = 0; y < hoogte; ++y)
  {
    for (auto x = 0; x < breedte; ++x)
    {
      haalWaardeWeg(y,x);
    }
  }
}

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

  for (int j = 0; j < hoogte; ++j)
  {
    for (int i = 0; i < breedte; ++i)
    {
       cout << " " << ((bord[i][j]) ? to_string(bord[i][j]) : "_") << " ";
    }
    cout << endl;
  }


}  // drukAfInhoud

//*************************************************************************

void Puzzel::drukAfOplossing (int oplossing[MaxDimensie][MaxDimensie])
{
  for (int j = 0; j < hoogte; ++j)
  {
    for (int i = 0; i < breedte; ++i)
    {
      cout << " " << oplossing[i][j] << " ";
    }
    cout << endl;
  }
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
    --aantalLeeg;
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
    ++aantalLeeg;
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


void Puzzel::sorteer(vector<pair<int,int>> lijst)
{
  map<int,vector<pair<int,int>>> emmers;
  for(auto vakje : lijst)
  {
    auto mogelijkheden = mogelijkeInputs(vakje.first, vakje.second);
    auto aantalMogelijkheden = mogelijkheden.size();
    if(!emmers.count(aantalMogelijkheden))
    {
      vector<pair<int,int>> vakjes;
      vakjes.push_back(vakje);
      emmers.insert({aantalMogelijkheden, vakjes});
    }
    else emmers[aantalMogelijkheden].push_back(vakje);
  }
  lijst.clear();
  for(auto & emmer : emmers)
  {
    for(auto & vakje : emmer.second) lijst.push_back(vakje);
  }
}

bool Puzzel::bepaalOplossingBT (bool slim,
                         int oplossing[MaxDimensie][MaxDimensie],
                         long long &aantalDeeloplossingen)
{
  // TODO: maak deze invoerlijst elders aan en maak het een field van de class
  aantalDeeloplossingen = 0;
  auto aantalOplossingen = 0;
  if(!erIsEenPuzzel) return false;
  vector<pair<int, int>> invoerLijst;
  for (int j = 0; j < hoogte; ++j)
  {
    for (int i = 0; i < breedte; ++i)
    {
      auto coordinaten = make_pair(i, j);
      invoerLijst.push_back(coordinaten);
    }
  }
  bepaalOplossingBT(slim, oplossing,
                    aantalDeeloplossingen,
                    invoerLijst, aantalOplossingen);


  return aantalOplossingen;
}  // bepaalOplossingBT

//TODO: construeer het eerste bord dat invulVolgorde volledig bevat, waarvoor 1 oplossing bestaat!
// elementen die eerder in de lijst komen, moeten zo links en boven mogelijk komen
// return true als er 1 unieke oplossing is
// return anders false;
bool Puzzel::bouwGretigBord(vector<int> waardeVolgorde)
{
  long long aantalDeelOplossingen = 0;
  int aantalOplossingen = 0;
  int oplossing[MaxDimensie][MaxDimensie];
  vector<pair<int, int>> invoerLijst;
  for (int j = 0; j < hoogte; ++j)
  {
    for (int i = 0; i < breedte; ++i)
    {
      auto coordinaten = make_pair(i, j);
      invoerLijst.push_back(coordinaten);
    }
  }
  cout << "We proberen het met: " << waardeVolgorde.size() << " waardes\n";
  return bepaalOplossingBT(false, oplossing, aantalDeelOplossingen,
                           invoerLijst, aantalOplossingen,
                           false, waardeVolgorde);
}


bool Puzzel::bepaalOplossingBT (bool slim, int oplossing[MaxDimensie][MaxDimensie],
                                long long &aantalDeeloplossingen, vector<pair<int,int>> invulVolgorde,
                                int & aantalOplossingen, bool doorstroom,
                                vector<int> waardeVolgorde, int start)
{
  ++aantalDeeloplossingen;
  if(slim) sorteer(invulVolgorde);
  auto gretig = false;
  my_set volgende;
  if(!waardeVolgorde.empty())
  {
    volgende.insert(waardeVolgorde[0]);
    waardeVolgorde.erase(waardeVolgorde.begin());
    gretig = true;
  }
  for (auto i = start; i < invulVolgorde.size(); ++i)
  {
    auto vakje = invulVolgorde[i];
    auto rij = vakje.second;
    auto kolom = vakje.first;
    auto keuzes = (gretig) ? volgende : mogelijkeInputs(kolom, rij);
    if (bord[kolom][rij] == Leeg)
    {
        for (auto waarde : keuzes)
        {
          if (vulWaardeIn(rij, kolom, waarde))
          {

            auto succesvol = bepaalOplossingBT(slim, oplossing,
                                               aantalDeeloplossingen,
                                               invulVolgorde,
                                               aantalOplossingen, doorstroom,
                                               waardeVolgorde, start);
            haalWaardeWeg(rij, kolom);
            if (succesvol)
            {
              if(gretig) vulWaardeIn(rij, kolom, waarde);
              if(!doorstroom) return true;
            }
          }
        }
        return false;
      }
  }
  if(gretig && (!aantalLeeg || !waardeVolgorde.empty()) ) return false;
  for (int rij = 0; rij < hoogte; ++rij)
  {
    for (int kolom = 0; kolom < breedte; ++kolom)
    {
        oplossing[kolom][rij] = bord[kolom][rij];
    }
  }
    ++aantalOplossingen;
    return true;
}




//*************************************************************************

int Puzzel::bepaalAlleOplossingenBT
      (bool slim, int oplossing[MaxDimensie][MaxDimensie],
       long long &aantalDeeloplossingen)
{
  // TODO: implementeer deze memberfunctie
  aantalDeeloplossingen = 0;
  int aantalOplossingen = 0;
  if(!erIsEenPuzzel) return false;
  vector<pair<int, int>> invoerLijst;
  for (int j = 0; j < hoogte; ++j)
  {
    for (int i = 0; i < breedte; ++i)
    {
      auto coordinaten = make_pair(i, j);
      invoerLijst.push_back(coordinaten);
    }
  }
  bepaalOplossingBT(slim, oplossing,
                           aantalDeeloplossingen,
                           invoerLijst, aantalOplossingen, true);

  return aantalOplossingen;
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

  gretigBord = true;
  auto succes = leesInPuzzel(invoerNaam);
  gretigBord = false;
  return succes;

}  // maakPuzzelMetWaardeReeksGretig

