#include "../note.h"
#include "continuity.cpp"
#include <numeric>

using namespace std;

class RhythmicContinuity : public Continuity {
public:
  TimeSignature TS = TimeSignature(4, 4);

  vector<int> sync() {
    int cp = getCommonProduct(this->generators);

    vector<int> resultant = getRhythmitcResultantFromGenerators(cp, generators);
    return replaceRests(resultant);
  };

  int getCommonProduct(const vector<int> &numbers) {
    if (numbers.empty())
      return 0;

    long long result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
      result = std::lcm(result, (long long)numbers[i]);
    }

    return result;
  };

  vector<int> getRhythmitcResultantFromGenerators(int cp,
                                                  vector<int> generators) {
    vector<vector<int>> individuals;
    for (int g : generators) {
      individuals.push_back(generateRhythmSequence(g, cp));
    }

    return this->mergeRhythmicalContinuities(individuals);
  };

  vector<int> generateRhythmSequence(int g, int cp) {
    vector<int> result;
    for (int i = 0; i < cp; i++)
      result.push_back(i % g == 0 ? 1 : 0);
    return result;
  };

 vector<int> mergeRhythmicalContinuities( const vector<vector<int>> &continuities) {
    if (continuities.empty()) return {};

    size_t length = continuities[0].size();
    std::vector<int> result(length, 0);

    for (size_t i = 0; i < length; ++i) {
      for (const auto &continuity : continuities) {
        if (continuity[i] == 1) {
          result[i] = 1;
          break;
        }
      }
    }

    return result;
  };

  vector<int> replaceRests(vector<int> resultant){
      vector<int> result;
      int n = resultant.size();
      int i = 0;

      while (i < n){
          int count = 0;
          if(resultant[i] == 1){
              count = 1;

              while (i + count < n && resultant [i+count] == 0)
                  count ++;
              result.push_back(count);
              i += count;
          } else i++;
      }

      return result;
  };

  // TODO when printing toLy() a continuity, we must 
  // use a RhythmicStaff and get only rhythmic values;

  RhythmicContinuity(vector<int> generators) {
    this->generators = generators;
    this->type = CONTINUITY_TYPE::rhythmic;
  }
};
