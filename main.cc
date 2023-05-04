// Hoofdprogramma voor oplossing voor tweede programmeeropdracht Algoritmiek,
// voorjaar 2023: Puzzel.
//
// Biedt de gebruiker een menustructuur om een door hem/haar in te lezen
// puzzel of waardereeks in te lezen. Bij de waardereeks wordt dan gretig
// een puzzel gemaakt.
// Biedt vervolgens een menustructuur om bij de gelezen of gemaakte puzzel:
// * een vakje in te vullen of leeg te maken
// * met backtracking een oplossing te bepalen (waarbij de vakjes in
//   een standaard volgorde of in een slimme volgorde worden ingevuld)
// * met backtracking alle oplossingen te bepalen (waarbij de vakjes in
//   een standaard volgorde of in een slimme volgorde worden ingevuld)
// * een experiment te doen
//
// Namen studenten, datum

#include <iostream>
#include <ctime>  // voor clock() en clock_t
#include "standaard.h"
#include "constantes.h"
#include "puzzel.h"
using namespace std;

//*************************************************************************

// Schrijf het menu voor een puzzel op het scherm,
// en vraag een keuze van de gebruiker.
// Retourneer: de keuze van de gebruiker
int keuzeUitMenu ()
{ int keuze;

  cout << endl;
  cout << "1. Een leeg vakje invullen" << endl;
  cout << "2. Een gevuld vakje leegmaken" << endl;
  cout << "3. Een oplossing bepalen (backtracking, standaard)" << endl;
  cout << "4. Een oplossing bepalen (backtracking, slim)" << endl;
  cout << "5. Alle oplossingen bepalen (backtracking, standaard)" << endl;
  cout << "6. Alle oplossingen bepalen (backtracking, slim)" << endl;
  cout << "7. Een experiment doen" << endl;
  cout << "8. Stoppen met deze puzzel" << endl;
  cout << endl;
  cout << "Maak een keuze: ";
  cin >> keuze;

  return keuze;

}  // keuzeUitMenu

//*************************************************************************

// Vraag van de gebruiker om een vakje (rij,kolom) op te geven, binnen
// de grenzen van de puzzel.
void vraagVakje (int hoogte, int breedte, int &rij, int &kolom)
{
  cout << endl;
  cout << "Geef de rij op (0.." << hoogte-1 << ") : ";
  cin >> rij;
  cout << "Geef de kolom op (0.." << breedte-1 << ") : ";
  cin >> kolom;

}  // vraagVakje

//*************************************************************************

// Voer de actie uit die hoort bij een keuze 3, 4, 5 of 6 in het menu voor
// instantie p1.
// Pre:
// * keuze is 3, 4, 5 of 6
void verwerkKeuze3456 (Puzzel *p1, int keuze)
{ int oplossing[MaxDimensie][MaxDimensie];
  long long aantalDeeloplossingen;  // aantal deeloplossingen dat we hebben
                                    // opgebouwd
  clock_t t1, t2;
  bool bo = false;  // lukt het om een oplossing te bepalen
  int ao = 0;       // aantal oplossingen

  t1 = clock ();
  cout << endl;
  switch (keuze)
  { case 3:
        cout << "bepaalOplossingBT standaard" << endl;
        bo = p1->bepaalOplossingBT (false, oplossing, aantalDeeloplossingen);
        break;
    case 4:
        cout << "bepaalOplossingBT slim" << endl;
        bo = p1->bepaalOplossingBT (true, oplossing, aantalDeeloplossingen);
        break;
    case 5:
        cout << "bepaalAlleOplossingenBT standaard" << endl;
        ao = p1->bepaalAlleOplossingenBT (false, oplossing,
                                          aantalDeeloplossingen);
        bo = (ao>=1);
        break;
    case 6:
        cout << "bepaalAlleOplossingenBT slim" << endl;
        ao = p1->bepaalAlleOplossingenBT (true, oplossing,
                                          aantalDeeloplossingen);
        bo = (ao>=1);
        break;
    default: ;   // komt niet voor
  }
  t2 = clock ();

  if (bo)
  { cout << endl;
    cout << "We hebben de volgende oplossing gevonden:" << endl;
    p1 -> drukAfOplossing (oplossing);
  }

  if (keuze==3 || keuze==4)
  { if (!bo)
    { cout << endl;
      cout << "Helaas, we vonden geen oplossing";
    }
  }
  else  // keuze==5 of 6
  { cout << endl;
    cout << "We hebben " << ao << " oplossing(en) gevonden." << endl;
  }

  cout << endl;
  cout << "We hebben hiervoor " << aantalDeeloplossingen
       << " deeloplossingen opgebouwd." << endl;
  cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
   << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;

}  // verwerkKeuze3456

//*************************************************************************

// Bied de gebruiker een menu om vakjes in te vullen of leeg te maken,
// een oplossing te bepalen, alle oplossingen te bepalen, of een experiment
// te doen.
// Roep vervolgens p1 aan voor de gekozen taak.
// Herhaal dit totdat de gebruiker aangeeft te willen stoppen.
void menuVoorInstantie (Puzzel *p1)
{ int hoogte, breedte,
      keuze,
      rij, kolom,
      nwWaarde;

  hoogte = p1->getHoogte();
  breedte = p1->getBreedte();

  keuze = 0;
  while (keuze!=8)
  {
    p1 -> drukAfInhoud ();

    keuze = keuzeUitMenu ();

    switch (keuze)
    { case 1: vraagVakje (hoogte, breedte, rij, kolom);
              cout << "Geef de in te vullen waarde: ";
              cin >> nwWaarde;
              if (!p1->vulWaardeIn (rij, kolom, nwWaarde))
                cout << "We kunnen deze waarde hier niet invullen." << endl;
              break;
      case 2: vraagVakje (hoogte, breedte, rij, kolom);
              if (!p1->haalWaardeWeg (rij, kolom))
                cout << "We kunnen hier geen waarde weghalen." << endl;
              break;
      case 3:
      case 4:
      case 5:
      case 6: verwerkKeuze3456 (p1, keuze);
              break;
      case 7: cout << endl;
              cout << "doeExperiment" << endl;
              p1 -> doeExperiment ();
              break;
      case 8: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }  // switch

  }  // while

}  // menuVoorInstantie

//*************************************************************************

void hoofdmenu ()
{ Puzzel *p1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
               // en weer weg te gooien
  int keuze;
  char invoernaam[MaxBestandsNaamLengte+1];
  bool OK;

  p1 = nullptr;  // om compiler warning te voorkomen
  OK = true;     // om compiler warning te voorkomen

  do
  {
    cout << endl;
    cout << "1. Een puzzel inlezen" << endl;
    cout << "2. Een waardereeks voor een puzzel inlezen (gretig)" << endl;
    cout << "3. Stoppen" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;
    if (integerInBereik (keuze, 1, 2))
    { p1 = new Puzzel ();
      cout << "Geef de naam van het tekstbestand met de invoer: ";
      cin >> invoernaam;
    }

    switch (keuze)
    { case 1: OK = p1 -> leesInPuzzel (invoernaam);
              break;
      case 2: OK = p1 -> maakPuzzelMetWaardeReeksGretig (invoernaam);
              break;
      case 3: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }

    if (integerInBereik (keuze, 1, 2))
    { if (OK)
      { p1 -> drukAfPuzzel ();
        menuVoorInstantie (p1);
      }
      delete p1;  // netjes opruimen
    }

  } while (keuze!=3);

}  // hoofdmenu

//*************************************************************************
  
int main ()
{
  hoofdmenu ();

  return 0;

}
