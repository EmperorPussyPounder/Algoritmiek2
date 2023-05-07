// Definitie van klasse Groep, om een groep van vakjes bij te houden
// en de eisen daarop te controleren.

#ifndef GroepHVar  // voorkom dat dit bestand meerdere keren
#define GroepHVar  // ge-include wordt

#include <unordered_set>
#include <set>
#include <map>
using namespace std;

class Groep
{ public:

    // Default constructor
    Groep ();
    Groep (const int maxSom, const int maxVoorkomens);
    void insert(pair<int,int> coordinaten, int waarde);
    void erase(pair<int,int> coordinaten);
    static void setDomain(unordered_set<int> domein);
    static bool commit;
    void commitInsert(pair<int,int> coordinaten, int waarde);
    void commitErase(pair<int,int> coordinaten);
    // TODO: uw eigen publieke memberfuncties

  private:
    map<int, int> invulbareWaardes;
    map<pair<int,int>,int> ingevuldeVakjes;
    int somResterend;
    static unordered_set<int> keuzes;
    // TODO: uw eigen private memberfuncties en -variabelen

};

#endif

