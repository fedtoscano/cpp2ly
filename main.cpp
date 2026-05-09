#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include "ly.cpp"

using namespace std;

// enum class DURATIONS { THIRTYTWO, SIXTEEN, EIGHT, QUARTER, HALF, FULL };
//
// class Duration {
// public:
//   int quantity;
//   DURATIONS value;
//   bool dotted = false;
//
//   Duration() : quantity(1), value(DURATIONS::QUARTER) {}
//   Duration(int q, DURATIONS v) : quantity(q), value(v) {}
// };
//
// class Note {
// public:
//   string pitch;
//   int octave;
//   Duration duration;
//
//   void print() { cout << pitch << octave << "\n"; };
//
//   int getOctave() { return this->octave; };
//
//   string toLy() {
//     string ly_p;
//
//     // parsing name notes
//     for (char c : pitch) {
//       if (c == '#')
//         ly_p += "is";
//       else if (c == 'b')
//         ly_p += "es";
//       else
//         ly_p += tolower(c);
//     }
//
//     // parsing octave
//     if (this->octave >= 4)
//       ly_p += string(this->octave - 3, '\'');
//     if (this->octave <= 3)
//       ly_p += string(3 - this->octave, ',');
//
//     // parsing duration
//     string ly_d;
//
//     switch (this->duration.value) {
//     case DURATIONS::THIRTYTWO:
//       ly_d = "32";
//       break;
//     case DURATIONS::SIXTEEN:
//       ly_d = "16";
//       break;
//     case DURATIONS::EIGHT:
//       ly_d = "8";
//       break;
//     case DURATIONS::QUARTER:
//       ly_d = "4";
//       break;
//     case DURATIONS::HALF:
//       ly_d = "2";
//       break;
//     case DURATIONS::FULL:
//       ly_d = "1";
//       break;
//     };
//
//     cout << ly_p + ly_d  << endl;
//
//     return ly_p + ly_d;
//   };
//
//   Note(string pitch, int octave, Duration duration) {
//     this->pitch = pitch;
//     this->octave = octave;
//     this->duration = duration;
//   }
// };

class Bar {
  public:
    vector<Note> notes;

    Bar(vector<Note> n) : notes(n) {};

    string toLy(){
      // TODO IMPLEMENT
      return "";
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

    // cout << "Index B: " << b_idx << endl;
    // cout << "Index T: " << t_idx << endl;
    //
    // cout << "INTERVALLO: " << INTERVAL_NAMES.at(t_idx - b_idx);

    return t_idx - b_idx;
  }

  Interval(Note b, Note t) : bottom(b), top(t) {
    this->name = this->computeDistance();
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

  string toLy(){
    string c_ly;
    for(auto& n : this->notes) c_ly += n.toLy() + " ";
    string duration;
    return "<" + c_ly + ">" + duration;
   
  };

  Chord(string _name, vector<Note> _notes) {
    name = _name;
    notes = _notes;
  };
};

// ============================================================

int main() {

  Note c("C", 4, Duration(1, DURATIONS::QUARTER));
  Note e("E", 4, Duration(1, DURATIONS::QUARTER));
  Note g("G", 4, Duration(1, DURATIONS::QUARTER));

  Chord C("C_MAJOR", {c, e, g});

  string c_str = c.toLy();
  string e_str = e.toLy();
  string g_str = g.toLy();

  vector<Note> melody = {c, e, g};

  LyConverter lc;

  string output = lc.toLy(melody, "My first export");
  ofstream file("export.ly");

  file << output;
  file.close();

  // Interval I(c, g);
  return 0;
}
