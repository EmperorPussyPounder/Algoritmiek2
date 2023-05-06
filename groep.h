// Definitie van klasse Groep, om een groep van vakjes bij te houden
// en de eisen daarop te controleren.

#ifndef GroepHVar  // voorkom dat dit bestand meerdere keren
#define GroepHVar  // ge-include wordt

#include <unordered_set>
using namespace std;

class Groep
{ public:

    // Default constructor
    Groep ();
    Groep (const int maxSom, const int maxVoorkomens);
    bool insert(pair<int,int> coordinaten);
    bool erase(pair<int,int> coordinaten);
    static void setDomain(unordered_set<int> domein);

    // TODO: uw eigen publieke memberfuncties

  private:
    static unordered_set<int> keuzes;
    // TODO: uw eigen private memberfuncties en -variabelen

};

#endif

