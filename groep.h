// Definitie van klasse Groep, om een groep van vakjes bij te houden
// en de eisen daarop te controleren.

#ifndef GroepHVar  // voorkom dat dit bestand meerdere keren
#define GroepHVar  // ge-include wordt

#include <unordered_set>
#include <set>
#include <map>
using namespace std;

typedef unordered_set<int> my_set;

class Groep
{ public:

    // Default constructor
    Groep ();
    /*
     * constructor voor het instantieren van grenswaarden van de groep.
     *
     */
    Groep (const int maxSom, const int maxVoorkomens);

    /*
     * functie voor een insert verzoek, indien de check van deze en de andere
     * groepen volstaan,
     * kan men waarde op coordinaten invullen
     */
    void insert(pair<int,int> coordinaten, int waarde);

    /*
     * functie voor een erase verzoek, indien de check van deze en de andere
     * groepen volstaan,
     * kan men de waarde op deze coordinaat verwijderen. Als de waarde niet
     * ingevuld is, zal er niets gebeuren.
     */
    void erase(pair<int,int> coordinaten);
    /*
     * static setter voor keuzes.
     */
    static void setDomain(unordered_set<int> domein);
    /*
     * static getter voor keuzes.
     */
    static my_set getDomain();

    /*
     * Voert inserts uit
     * post:
     * - als commit == true, dan zal in elke groep van deze coordinaat
     * de waarde ingevuld zijn.
     */
    void commitInsert(pair<int,int> coordinaten, int waarde);
    /*
     * voert Erase uit
     * post:
     * - als commit == true, dan zal in elke groep van deze coordinaat
     * de waarde ingevuld zijn
     */
    void commitErase(pair<int,int> coordinaten);
    /*
     * getter voor resterendeKeuzes.
     */
    my_set getResterendeKeuzes();
    static bool commit; // Geeft aan of gecheckte groepen door moeten gaan met insert/delete.

  private:
    map<int, int> invulbareWaardes;         // invulbareWaardes samen met de hoeveelheid die nog mogen ingevoerd worden.
    map<pair<int,int>,int> ingevuldeVakjes;  // vakjes die ingevuld zijn, samen met de ingevulde waarde.
    int somResterend;               // wat er nog resteert van maxSom.
    static my_set keuzes;          // domein van waardes die ingevuld mogen worden.
    my_set resterendeKeuzes;       // waardes die nog ingevoerd mogen worden, in set vorm.

};

#endif

