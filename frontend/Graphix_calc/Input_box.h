#pragma once

// std libs
#include <string>
using std::string;

// Graphix_calc
#include "Numbed_button.h"
using Graphix_calc::Numbed_button;

// Graph_lib
#include <Graph_lib/GUI.h>
using Graph_lib::In_box;
using Graph_lib::Out_box;
using Graph_lib::Point;
#include <Graph_lib/Graph.h>
#include <Graph_lib/Window.h>

namespace Graphix_calc {

class Input_box : public Graph_lib::Widget
{
  public:
    // упрощенный конструктор
    Input_box(short graphics_amount, void cb_draw(void*, void*), void cb_hide(void*, void*),
              void cb_rem(void*, void*));

    // methods

    bool is_hidden () const;

    void graph_show ();

    void graph_hide ();

    void move (int dx, int dy) override;

    string get_string () const { return in_box->get_string(); }

    int get_number () const { return draw_button->get_number(); }

    void set_number (int);

    void set_message (const string&);

    // attach all buttons
    void attach (Graph_lib::Window&);

    // detach all buttons
    void detach (Graph_lib::Window&);

  private:
    // variables

    // поле, куда пользователь вводит функцию
    In_box* in_box;
    Numbed_button* draw_button;
    Numbed_button* hide_button;
    Numbed_button* rem_button;
    Out_box* out_box;
    bool is_graph_visible;
};

}  // namespace Graphix_calc