#include <vector>
#include "note.h"
#include "ly.cpp"

using namespace std;

int main() {
    Note c("C", 4, Duration(1, DURATIONS::QUARTER));
    Note e("E", 4, Duration(1, DURATIONS::QUARTER));
    Note g("G", 4, Duration(1, DURATIONS::QUARTER));
    Note d("D", 4, Duration(1, DURATIONS::QUARTER));
    Note f("F", 4, Duration(1, DURATIONS::QUARTER));
    Note b("B", 4, Duration(1, DURATIONS::QUARTER));

    vector<Note> melody = {c, e, g};

    LyConverter lc;

    Bar B({c, e, g, c});
    Bar B1({g, e, c, e});
    Bar B2({d, e, f, c});
    Bar B3({g, e, g, b});
 
    string BARS;
    BARS += B.toLy();
    BARS += B1.toLy();
    BARS += B2.toLy();
    BARS += B3.toLy();

    lc.toFile(BARS, "test");
    return 0;
}
