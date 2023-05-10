// Implementatie van klasse Groep

#include <iostream>
#include "standaard.h"
#include "constantes.h"
#include "groep.h"

//*************************************************************************
my_set Groep::keuzes{};
bool Groep::commit = true;
Groep::Groep ()
{

}  // default constructor

//*************************************************************************

// TODO: implementeer de benodigde memberfuncties voor groep
Groep::Groep(const int maxSom, const int maxVoorkomens)
{
  for(const auto& keys: keuzes)
  {
    invulbareWaardes.insert({keys, maxVoorkomens});
  }
  resterendeKeuzes = keuzes;
  somResterend = maxSom;
}

void Groep::insert(pair<int,int> coordinaten, int waarde)
{
  commit =  commit
      && (!ingevuldeVakjes.count(coordinaten)
      &&   resterendeKeuzes.count(waarde)
      &&   somResterend - waarde >= 0);
}

void Groep::erase(pair<int,int> coordinaten)
{
// TODO: voer benodigde controles uit, en bij success een vakje "invullen", dus verwijderen uit keuzes.
  commit &= ingevuldeVakjes.count(coordinaten);
}

void Groep::setDomain(my_set domein)
{
  keuzes = domein;
}

void Groep::commitInsert(pair<int,int> coordinaten, int waarde)
{
    ingevuldeVakjes.insert({coordinaten, waarde});
    --invulbareWaardes[waarde];
    somResterend -= waarde;
    if(!invulbareWaardes[waarde]) resterendeKeuzes.erase(waarde);
}

void Groep::commitErase(pair<int,int> coordinaten)
{
  auto ondoeWaarde = ingevuldeVakjes[coordinaten];
  if(!invulbareWaardes[ondoeWaarde]) resterendeKeuzes.insert(ondoeWaarde);
  somResterend += ondoeWaarde;
  ++invulbareWaardes[ondoeWaarde];
  ingevuldeVakjes.erase(coordinaten);
}

my_set Groep::getResterendeKeuzes()
{
  return resterendeKeuzes;
}
