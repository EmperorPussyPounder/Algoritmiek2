// Implementatie van klasse Groep

#include <iostream>
#include "standaard.h"
#include "constantes.h"
#include "groep.h"

//*************************************************************************
unordered_set<int> Groep::keuzes{};
bool Groep::commit = true;
Groep::Groep ()
{
  // TODO: implementeer zo nodig deze constructor

}  // default constructor

//*************************************************************************

// TODO: implementeer de benodigde memberfuncties voor groep
Groep::Groep(const int maxSom, const int maxVoorkomens)
{
  for(const auto& keys: keuzes)
  {
    invulbareWaardes.insert({keys, maxVoorkomens});
  }
  somResterend = maxSom;
}

void Groep::insert(pair<int,int> coordinaten, int waarde)
{
  commit =  commit
      && (!ingevuldeVakjes.count(coordinaten)
      &&   keuzes.count(waarde)
      &&   invulbareWaardes[waarde]
      &&   somResterend - waarde >= 0);
}

void Groep::erase(pair<int,int> coordinaten)
{
// TODO: voer benodigde controles uit, en bij success een vakje "invullen", dus verwijderen uit keuzes.
  commit &= ingevuldeVakjes.count(coordinaten);
}

void Groep::setDomain(unordered_set<int> domein)
{
  keuzes = domein;
}

void Groep::commitInsert(pair<int,int> coordinaten, int waarde)
{
    ingevuldeVakjes.insert({coordinaten, waarde});
    --invulbareWaardes[waarde];
    somResterend -= waarde;
    if(!invulbareWaardes[waarde]) keuzes.erase(waarde);
}

void Groep::commitErase(pair<int,int> coordinaten)
{
  auto ondoeWaarde = ingevuldeVakjes[coordinaten];
  if(!invulbareWaardes[ondoeWaarde]) keuzes.insert(ondoeWaarde);
  somResterend += ondoeWaarde;
  ++invulbareWaardes[ondoeWaarde];
  ingevuldeVakjes.erase(coordinaten);
}
