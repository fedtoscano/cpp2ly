#include "note.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class LyConverter {
public:
  string toLy(vector<Note> notes, string title = "Untitled") {
    string body;
    for (const auto &n : notes) {
      body += n.toLy() + " ";
    }

    return "\\version \"2.26.0\"\n"
           "\\header { title = \"" +
           title +
           "\" }\n"
           "\\score {\n"
           "    { " +
           body +
           "}\n"
           "    \\layout { }\n"
           "    \\midi { }\n"
           "}\n";
  };

  string toLyStr(string notes, string title = "Untitled") {
    return "\\version \"2.26.0\"\n"
           "\\header { title = \"" +
           title +
           "\" }\n"
           "\\score {\n"
           "    { " +
           notes +
           "}\n"
           "    \\layout { }\n"
           "    \\midi { }\n"
           "}\n";
  }

  void toFile(string content, string filename = "export",
              string title = "test") {
    ofstream file(filename + ".ly");
    file << this->toLyStr(content, title);
    file.close();
  };
};
