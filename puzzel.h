// Definitie van klasse Puzzel

#ifndef PuzzelHVar  // voorkom dat dit bestand meerdere keren
#define PuzzelHVar  // ge-include wordt

#include <unordered_set>
#include <map>
#include <vector>
#include "constantes.h"
#include "groep.h"


typedef map<pair<int,int>, vector<Groep*>> groupmap;
typedef unordered_set<int> my_set;

class Puzzel
{ public:

    // Default constructor
    Puzzel ();

    // Destructor
    ~Puzzel ();

    // Lees een puzzel, bestaande uit een rijtje waardes, de inhoud en
    // de groepen, in uit bestand invoernaam. De invoer bevat integers
    // volgens het format in de specificatie van de opdracht.
    // Controleer of
    // * het bestand invoernaam te openen is
    // * het aantal toegestane waardes positief is
    // * alle toegestane waardes positief en verschillend zijn
    // * de dimensies van de puzzel binnen de grenzen van de opdracht vallen
    // * elk getal in (de inhoud van) de puzzel ofwel Leeg (=0) is, ofwel
    //   een van de toegestane waardes is
    // * er minstens 1 groep is
    // * elke groep minstens 1 vakje bevat, en ook positieve waardes voor
    //   maxSom en maxVoorkomens heeft
    // * alle vakjes in een groep geldige vakjes voor deze puzzel zijn,
    //   en bovendien verschillend
    // * de reeds ingevulde vakjes van de puzzel voldoen aan de eisen
    //   van de groepen met vakjes, wat betreft som en aantal voorkomens van
    //   een waarde.
    // Retourneer:
    // * true, als alle controles goed uitpakken.
    //   In dat geval is alle ingelezen informatie in het object opgeslagen,
    //   en is er een geldige puzzel.
    // * false, anders
    bool leesInPuzzel (const char* invoerNaam);

    // Druk alle gegevens van de puzzel (toegestane waardes, inhoud,
    // groepen) af op het scherm.
    // Controleer eerst of er een geldige puzzel is.
    void drukAfPuzzel ();

    // Druk de inhoud van de puzzel af op het scherm.
    // Controleer eerst of er een geldige puzzel is.
    void drukAfInhoud ();

    // Druk de oplossing in array `oplossing' af op het scherm.
    // Controleer eerst of er een geldige puzzel is.
    // Pre:
    // * Als er een geldige puzzel is, bevat oplossing
    //   een hoogte x breedte oplossing
    void drukAfOplossing (int oplossing[MaxDimensie][MaxDimensie]);

    // Eenvoudige getters:
    int getHoogte ()
    { return hoogte;
    }
    int getBreedte ()
    { return breedte;
    }

    // Geef de waarde in vakje (rij,kolom) van de puzzel.
    // Controleer eerst of er een geldige puzzel is, en of (rij,kolom)
    // daar een geldig vakje is.
    // Retourneer:
    // * de waarde in vakje (rij,kolom), als beide controles goed uitpakken
    // * een passende default-waarde, anders
    int getWaarde (int rij, int kolom);

    // Vul waarde nwWaarde in in vakje (rij,kolom).
    // Controleer eerst of
    // * er een geldige puzzel is
    // * vakje (rij,kolom) een geldig, leeg vakje is
    // * waarde nwWaarde daar wel ingevuld mag worden
    // Retourneer:
    // * true, als alle controles goed uitpakken
    // * false, anders
    // Post:
    // * Als returnwaarde true is, is de waarde ingevuld.
    // * Anders is er niets aan de puzzel veranderd.
    bool vulWaardeIn (int rij, int kolom, int nwWaarde);

    // Haal de huidige waarde weg uit vakje (rij,kolom).
    // Controleer eerst of
    // * er een geldige puzzel is
    // * vakje (rij,kolom) een geldig, gevuld vakje is
    // Retourneer:
    // * true, als beide controles goed uitpakken
    // * false, anders
    // Post:
    // * Als returnwaarde true is, is de waarde weggehaald.
    // * Anders is er niets aan de puzzel veranderd.
    bool haalWaardeWeg (int rij, int kolom);

    // Bepaal met behulp van backtracking een oplossing voor de huidige
    // puzzel.
    // Controleer eerst of er een geldige puzzel is.
    // Als slim==true, wordt steeds een vakje ingevuld met zo weinig
    // mogelijk toegestane waardes. Anders worden de vakjes in een standaard
    // volgorde ingevuld.
    // Retourneer:
    // * true, als het lukt om een oplossing te bepalen
    // * false, als het niet lukt om een oplossing te bepalen
    // Post:
    // * als het lukt om een oplossing te bepalen, bevat parameter
    //   `oplossing' die oplossing
    // * aantalDeeloplossingen is gelijk aan het aantal deeloplossingen
    //   dat we hebben gezien bij het bepalen van een oplossing
    // * de puzzel is niet verder ingevuld dan hij al was bij aanroep van
    //   deze functie, dwz alle bij deze functie ingevulde waardes zijn
    //   weer weggehaald
    bool bepaalOplossingBT (bool slim,
                         int oplossing[MaxDimensie][MaxDimensie],
                         long long &aantalDeeloplossingen);

    // Bepaal met behulp van backtracking alle oplossingen voor de huidige
    // puzzel.
    // Controleer eerst of er een geldige puzzel is.
    // Als slim==true, wordt steeds een vakje ingevuld met zo weinig
    // mogelijk toegestane waardes. Anders worden de vakjes in een standaard
    // volgorde ingevuld.
    // Retourneer:
    // * het aantal gevonden oplossingen
    // Post:
    // * als het lukt om (minstens) een oplossing te bepalen, bevat parameter
    //   `oplossing' een van de gevonden oplossingen
    // * aantalDeeloplossingen is gelijk aan het aantal deeloplossingen
    //   dat we hebben gezien bij het bepalen van de oplossingen
    // * de puzzel is niet verder ingevuld dan hij al was bij aanroep van
    //   deze functie, dwz alle bij deze functie ingevulde waardes zijn
    //   weer weggehaald
    int bepaalAlleOplossingenBT (bool slim,
                         int oplossing[MaxDimensie][MaxDimensie],
                         long long &aantalDeeloplossingen);

    // Doe het experiment zoals beschreven in de opdracht:
    // * vul de puzzel in
    // * doe herhaaldelijk het volgende:
    //   - haal zo veel mogelijk getallen van random posities weg, zodat
    //     er nog wel steeds 1 oplossing mogelijk is
    //   - los de puzzel zowel standaard als slim op
    // * bereken de gemiddelde aantallen deeloplossingen en benodigde tijd
    //   voor beide varianten (standaard en slim)
    // Controleer eerst of er een geldige puzzel is.
    void doeExperiment ();

    // Lees een reeks waardes in uit bestand invoernaam, en probeer
    // de complete reeks van waardes met een gretig algoritme in
    // de ingelezen volgorde in een puzzel te plaatsen die nog minstens
    // 1 oplossing heeft. Als het niet lukt om de complete reeks in
    // een puzzel te plaatsen, plaats er dan zo veel mogelijk
    // (aaneengesloten vanaf het begin van de reeks).
    // Controleer of
    // * het bestand invoernaam te openen is
    // Pre:
    // * Als het bestand invoernaam te openen is, bevat het
    //   - een geldige reeks toegestane waardes
    //   - geldige dimensies
    //   - een geldige reeks waardes om in de puzzel te plaatsen
    //   - een geldige lijst met groepen
    // Retourneer:
    // * true, als het bestand te openen is
    // * false, anders
    // Post:
    // * Als de returnwaarde true is, zijn de toegestane waardes,
    //   de dimensies en de groepen in het object opgeslagen,
    //   en is er (gretig) een puzzel gevormd met zoveel mogelijk waardes
    //   uit de ingelezen waardereeks.
    bool maakPuzzelMetWaardeReeksGretig  (const char* invoerNaam);

  private:

    int hoogte, breedte,
        aantalKeuzes, aantalGroepen;    // dimensies van de puzzel
// bijvoorbeeld een 2-dimensionaal array voor de inhoud van de puzzel
    int bord[MaxDimensie][MaxDimensie];
    bool erIsEenPuzzel = false;
    my_set keuzes;
    set<pair<int,int>> ingevuld;

    groupmap groepenWijzer;
    my_set intersect(my_set A, my_set B);

    my_set mogelijkeInputs(int x, int y);
    bool eindeSpel();
    bool bepaalOplossingBT(bool slim, int oplossing[MaxDimensie][MaxDimensie],
                           long long &aantalDeeloplossingen, vector<pair<int,int>> invoerLijst);
    void sorteer(vector<pair<int,int>> lijst);
};

#endif

