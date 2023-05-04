// Implementatie van klasse Puzzel

#include <iostream>
#include <fstream>
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
  // TODO: implementeer deze memberfunctie

  return true;

}  // leesInPuzzel

//*************************************************************************

void Puzzel::drukAfPuzzel ()
{
  // TODO: implementeer deze memberfunctie

}  // drukAfPuzzel

//*************************************************************************

void Puzzel::drukAfInhoud ()
{
  // TODO: implementeer deze memberfunctie

}  // drukAfInhoud

//*************************************************************************

void Puzzel::drukAfOplossing (int oplossing[MaxDimensie][MaxDimensie])
{
  // TODO: implementeer deze memberfunctie

}  // drukAfOplossing

//*************************************************************************

int Puzzel::getWaarde (int rij, int kolom)
{
  // TODO: implementeer deze memberfunctie

  return GeenWaarde;

}  // getWaarde

//*************************************************************************

bool Puzzel::vulWaardeIn (int rij, int kolom, int nwWaarde)
{
  // TODO: implementeer deze memberfunctie

  return false;

}  // vulWaardeIn

//*************************************************************************

bool Puzzel::haalWaardeWeg (int rij, int kolom)
{
  // TODO: implementeer deze memberfunctie

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

