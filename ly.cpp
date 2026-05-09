#include <string>
#include <vector>
#include "note.h"

using namespace std;

class LyConverter {
public:
    string toLy(vector<Note> notes, string title = "Untitled") {
        string body;
        for (const auto& n : notes) {
            body += n.toLy() + " ";
        }

        return "\\version \"2.26.0\"\n"
               "\\header { title = \"" + title + "\" }\n"
               "\\score {\n"
               "    { " + body + "}\n"
               "    \\layout { }\n"
               "    \\midi { }\n"
               "}\n";
    }
};
