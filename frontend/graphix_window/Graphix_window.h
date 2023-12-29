#pragma once

// std libs
#include <string>
#include <vector>

// Graphix_calc
#include "../../backend/Math_func/function.h"
#include "../Graphix_calc/Axis.h"
#include "../Graphix_calc/Bothput_box.h"
#include "../Graphix_calc/Function_box.h"
#include "../Graphix_calc/Graphix.h"
#include "../Graphix_calc/Point_box.h"
#include "../Graphix_calc/Segmented_Graphix.h"

// Backend
#include "../../backend.h"

// Graph_lib
#include "../Graph_lib/GUI.h"
#include "../Graph_lib/Graph.h"
#include "../Graph_lib/Window.h"

namespace Graphix_win {

// класс окна с осями и возможностью добавлять графики
class Graphix_window : public Graph_lib::Window
{
  public:
    Graphix_window();

    Graphix_window(Graph_lib::Point left_corner, pix_amount width, pix_amount height,
                   const std::string& title, pix_amount unit_intr);

    // methods

    // ждём, когда нажмётся какая-нибудь кнопка
    void wait_for_button ()
    {
        while (!button_pushed && Fl::wait())
            ;

        cout << "some button pushed" << endl;
        cout << "unit_intr: " << unit_intr << endl;
        cout << "inputed_strings: ";
        print(inputed_strings);
        cout << "inputed_func_strs: ";
        print(inputed_funcs);
        cout << endl << endl;

        button_pushed = false;
        Fl::redraw();
    }

    bool window_is_open () const { return !quit_button_pushed; }

  private:
    // vars

    // общее значение масштаба: количество пикселей в единичном отрезке!?
    double unit_intr;
    // начало координат в пикселях (используется только в Graph_lib::Graphix и методах на
    // отображение точки)
    Graph_lib::Point origin;
    // линия - ограничитель системы координат от меню ввода
    Graph_lib::Line border;
    // вертикальная и горизонтальная оси
    Graphix_calc::Axis *x_axis, *y_axis;
    // кнопка выхода из программы
    Graph_lib::Button quit_button;
    // кнопка масштаб "+"
    Graph_lib::Button incr_button;
    // кнопка масштаб "-"
    Graph_lib::Button decr_button;
    // кнопка "создать новый график"
    Graph_lib::Button new_button;

    // вектор полей ввода (группы поля ввода и трёх кнопок: draw, hide, remove)
    std::vector<Graphix_calc::Function_box*> enter_menu;

    // общий вектор введенных пользователем строк
    std::vector<std::string> inputed_strings;
    std::vector<Math_func::function> inputed_funcs;
    // общий вектор со всеми сегментированными функциями (графиками)
    std::vector<Graphix_calc::Segmented_Graphix*> graphics;
    // общий вектор со всеми сегментированными производными функций (графиками)
    std::vector<Graphix_calc::Segmented_Graphix*> derivs;

    // меню с общим полем для точек
    Graphix_calc::Point_box point_box;
    // общий массив всех точек на экране
    std::vector<Graph_lib::Marks*> all_points;

    Graph_lib::Button unit_intr_button;

    Graphix_calc::Bothput_box scale_box;

    bool is_points_visible{false};
    bool button_pushed{false};
    bool quit_button_pushed{false};

    // methods

    void init () override;

    void initial_attach ();

    // callbacks

    static void cb_quit (void*, void* widget);
    static void cb_incr_unit_intr (void*, void* widget);
    static void cb_decr_unit_intr (void*, void* widget);
    static void cb_draw_graph (void*, void* widget);
    static void cb_hide_graph (void*, void* widget);
    static void cb_draw_der (void*, void* widget);
    static void cb_hide_der (void*, void* widget);
    static void cb_rem_func (void*, void* widget);
    static void cb_new_func (void*, void* widget);
    static void cb_show_points (void*, void* widget);
    static void cb_hide_points (void*, void* widget);
    static void cb_change_unit_intr (void*, void* widget);

    // функции, которые вызывают callbacks

    void quit ()
    {
        hide();

        quit_button_pushed = true;
    }

    // вспомогательная функция, меняющая текущий масштаб
    void update_unit_intr (double new_unit_intr);

    void change_unit_intr ();

    void incr_unit_intr ();

    void decr_unit_intr ();

    // вспомогательная функция, полностью перерисовывающая график (без нажатия кнопки)
    void update_graphix (size_t func_index);

    // вспомогательная фунция, отчищающая память и удаляющая строку из вектора введенных
    // пользователем строк
    void clear_graphix (size_t func_index, bool need_delete = true);

    void draw_graphix (size_t func_index);

    void hide_graphix (size_t func_index);

    // вспомогательная функция, полностью перерисовывающая производную (без нажатия кнопки))
    void update_deriv (size_t der_index);

    void clear_deriv (size_t der_index, bool need_delete = true);

    void draw_deriv (size_t der_index);

    void hide_deriv (size_t der_index);

    void rem_func_box (size_t func_index);

    // вспомогательная фунция, добавляющая в вектор введенных пользователем строк тек
    void update_inputed_func (size_t func_index, bool need_update_strings = true);

    // вспомогательная фунция, добавляющая в вектор введенных пользователем строк всё из enter_menu
    void fill_inputed_funcs ();

    void new_func_box ();

    void update_points ();

    // вспомогательная фунция, удаляющая все точки с экрана и чистящая память
    void clear_points ();

    void show_points ();

    void hide_points ();
};

}  // namespace Graphix_win