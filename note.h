#pragma once
#include <iostream>
#include <string>

enum class DURATIONS {
    THIRTYTWO,
    SIXTEEN,
    EIGHT,
    QUARTER,
    HALF,
    FULL
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
            case DURATIONS::THIRTYTWO: ly_duration = "32"; break;
            case DURATIONS::SIXTEEN:   ly_duration = "16"; break;
            case DURATIONS::EIGHT:     ly_duration = "8";  break;
            case DURATIONS::QUARTER:   ly_duration = "4";  break;
            case DURATIONS::HALF:      ly_duration = "2";  break;
            case DURATIONS::FULL:      ly_duration = "1";  break;
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
            if (c == '#') ly_pitch += "is";
            else ly_pitch += tolower(c);
        }

        if (octave >= 4) ly_pitch += std::string(octave - 3, '\'');
        if (octave <= 3) ly_pitch += std::string(3 - octave, ',');

        std::string ly_note = ly_pitch + duration.toLy();
        if (duration.dotted) ly_note += ".";
        return ly_note;
    }

    void print() const { std::cout << pitch << octave << "\n"; }
    int getOctave() const { return this->octave; }
};
