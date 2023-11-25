#include "graphic_window.h"
#include <Graph_Lib/Graph.h>
#include <Graph_lib/GUI.h>
#include <Graph_lib/Simple_window.h>

using namespace Graph_lib;

int main ()
{
    Graphic_window grw(Point(100, 100), 1000, 700, "DESMOS", 50);
    grw.wait_for_button();
}