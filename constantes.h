// Enkele constantes die op verschillende plekken gebruikt kunnen worden.

#ifndef ConstantesHVar  // voorkom dat dit bestand meerdere keren
#define ConstantesHVar  // ge-include wordt

#include <unordered_set>
#include <vector>
using namespace std;

const int MaxBestandsNaamLengte = 30; // maximale lengte van een bestandsnaam
const int Leeg = 0;
const int MaxDimensie = 12;
const int MinDimensie = 1;
const int GeenWaarde = -1;   // een waarde die niet voor kan komen in
                             // een puzzel
const unordered_set<int> GeenMogelijkheden {};
const vector<int> GeenVolgorde {};
const pair<int,int> GeenVakje = make_pair (-1,-1);  // ongeldig vakje
const int nrRuns = 100;      // voor het experiment

#endif

