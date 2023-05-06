// Implementatie van klasse Groep

#include <iostream>
#include "standaard.h"
#include "constantes.h"
#include "groep.h"

//*************************************************************************
unordered_set<int> Groep::keuzes{};
Groep::Groep ()
{
  // TODO: implementeer zo nodig deze constructor

}  // default constructor

//*************************************************************************

// TODO: implementeer de benodigde memberfuncties voor groep
Groep::Groep(const int maxSom, const int maxVoorkomens)
{

}

bool Groep::insert(pair<int,int> coordinaten)
{
// TODO: voer benodigde controles uit, en bij success een extra vakje aan mogelijkheden toevoegen.

  return true;
}

bool Groep::erase(pair<int,int> coordinaten)
{
// TODO: voer benodigde controles uit, en bij success een vakje "invullen", dus verwijderen uit keuzes.
  return true;
}

void Groep::setDomain(unordered_set<int> domein)
{
  keuzes = domein;
}
