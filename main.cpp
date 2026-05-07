#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Note {
public:
  string pitch;
  int octave;

  void print() { cout << pitch << octave << "\n"; };

  int getOctave() { return this->octave; };

  Note(string pitch, int octave) {
    this->pitch = pitch;
    this->octave = octave;
  }
};

class Interval {
private:
  inline static const std::array<std::string, 12> CHROMATIC_SCALE = {
      "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

  inline static const map<int, string> INTERVAL_NAMES = {
      {0, "u"},  {1, "m2"}, {2, "M2"}, {3, "m3"}, {4, "M3"},  {5, "4g"},
      {6, "4e"}, {7, "5g"}, {8, "5e"}, {9, "6M"}, {10, "7m"}, {11, "7M"},
  };

public:
  Note bottom;
  Note top;
  int name;
  string quality;

  int computeDistance() {
    string b = this->bottom.pitch;
    string t = this->top.pitch;

    auto b_ptr = find(CHROMATIC_SCALE.begin(), CHROMATIC_SCALE.end(), b);
    int b_idx = distance(CHROMATIC_SCALE.begin(), b_ptr);

    auto t_ptr = find(CHROMATIC_SCALE.begin(), CHROMATIC_SCALE.end(), t);
    int t_idx = distance(CHROMATIC_SCALE.begin(), t_ptr);

    cout << "Index B: " << b_idx << endl;
    cout << "Index T: " << t_idx << endl;

    cout << "INTERVALLO: " << INTERVAL_NAMES.at(t_idx - b_idx);

    return t_idx - b_idx;
  }

  Interval(Note b, Note t) : bottom(b), top(t) {
    this->name = this->computeDistance();

    cout << "THIS->NAME: " << this->name;
  }
};

class Chord {
public:
  string name;
  vector<Note> notes;

  void print() {
    cout << "Name: " << name;
    for (auto i : this->notes) {
      i.print();
    };
    cout << "\n";
  }

  Chord(string _name, vector<Note> _notes) {
    name = _name;
    notes = _notes;
  };
};

int main() {

  Note c("C", 4);
  Note e("E", 4);
  Note g("G", 4);

  Chord C("C_MAJOR", {c, e, g});

  Interval I(c, g);
  return 0;
}
