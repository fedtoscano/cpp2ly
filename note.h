#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class DURATIONS { THIRTYTWO, SIXTEEN, EIGHT, QUARTER, HALF, FULL };

class TimeSignature {
public:
  int num;
  int den;

  string toStr(){
      return to_string(this->num) + "/" + to_string(this->den);
  }

  TimeSignature(int n, int d) : num(n), den(d) {};
};

class Duration {
public:
  int quantity;
  DURATIONS value;
  bool dotted = false;

  Duration() : quantity(1), value(DURATIONS::QUARTER) {}
  Duration(int q, DURATIONS v) : quantity(q), value(v) {}
  Duration(int q, DURATIONS v, bool d) : quantity(q), value(v), dotted(d) {}

  std::string toLy() const {
    std::string ly_duration;
    switch (value) {
    case DURATIONS::THIRTYTWO:
      ly_duration = "32";
      break;
    case DURATIONS::SIXTEEN:
      ly_duration = "16";
      break;
    case DURATIONS::EIGHT:
      ly_duration = "8";
      break;
    case DURATIONS::QUARTER:
      ly_duration = "4";
      break;
    case DURATIONS::HALF:
      ly_duration = "2";
      break;
    case DURATIONS::FULL:
      ly_duration = "1";
      break;
    }
    return ly_duration;
  }
};

class Note {
public:
  std::string pitch;
  int octave;
  Duration duration;

  Note(std::string p, int o, Duration d) : pitch(p), octave(o), duration(d) {}
  Note(std::string p, int o) : pitch(p), octave(o), duration(Duration()) {}

  std::string toLy() const {
    std::string ly_pitch;
    for (char c : pitch) {
      if (c == '#')
        ly_pitch += "is";
      else
        ly_pitch += tolower(c);
    }

    if (octave >= 4)
      ly_pitch += std::string(octave - 3, '\'');
    if (octave <= 3)
      ly_pitch += std::string(3 - octave, ',');

    std::string ly_note = ly_pitch + duration.toLy();
    if (duration.dotted)
      ly_note += ".";
    return ly_note;
  }

  void print() const { std::cout << pitch << octave << "\n"; }
  int getOctave() const { return this->octave; }
};

class Bar {
public:
  vector<Note> notes;
  TimeSignature TS = TimeSignature(4, 4);

  Bar(vector<Note> n) : notes(n) {};

  string toLy() {
    string notes_ly;
    for (const auto &n : notes) {
      notes_ly += n.toLy() + " ";
    }

    return notes_ly + "|" + "\n";
  }
};

class Interval {
private:
  inline static const array<string, 12> CHROMATIC_SCALE = {
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
    for (auto i : this->notes) {
      i.print();
    };
    cout << "\n";
  }

  string toLy() {
    string c_ly;
    for (auto &n : this->notes)
      c_ly += n.toLy() + " ";
    string duration;
    return "<" + c_ly + ">" + duration;
  };

  Chord(string _name, vector<Note> _notes) {
    name = _name;
    notes = _notes;
  };
};
