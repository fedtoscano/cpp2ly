#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum CONTINUITY_TYPE {
  rhythmic, melodic, harmonic
};

class Continuity {
  public:
    CONTINUITY_TYPE type;
    vector<int> generators;

};
