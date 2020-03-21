#include "Plotter.h"
#include "strlib.h"
#include <vector>

using namespace std;

void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    PenStyle style = { 1, "black" };
    bool flag= 1;
    double x0 = 0, x1 = 0;
    double y0 = 0, y1 = 0;

    for (string line; getline(input, line); ) {
        /* ... do something with line ... */
        Vector<string> res = stringSplit(line, " ");
        string cmd = res[0];
        if (cmd == "PenDown") flag = 0;
        if (cmd == "PenUp") flag = 1;
        if (cmd == "MoveAbs") {
            x0 = x1;
            y0 = y1;
            x1 = stringToReal(res[1]);
            y1 = stringToReal(res[2]);
            if (flag == 0) drawLine(x0, y0, x1, y1, style);
        }
        if (cmd == "MoveRel") {
            x0 = x1;
            y0 = y1;
            x1 += stringToReal(res[1]);
            y1 += stringToReal(res[2]);
            if (flag == 0) drawLine(x0, y0, x1, y1, style);
        }
        if (cmd == "color") style.color = cmd;
        if (cmd == "width") style.width = stringToReal(cmd);
    }
}
