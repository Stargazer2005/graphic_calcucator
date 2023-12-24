#include "function_extremes.h"

// std libs
using std::string;
using std::vector;

// Math_calc
#include "domain_segments.h"

// servant
#include "../servant/constants.h"
#include "../servant/servant.h"
using Back_serv::absolute;

namespace Math_calc {

function_extremes::function_extremes(Math_func::function _func, double min_x, double max_x,
                                     double max_y, double _precision)
    :  // FIXME: сейчас тут есть проверка на точность, которой быть не должно
      precision{_precision < 0.01 ? _precision : 0.01}, f{_func},
      points{extremes(min_x, max_x, max_y)}
{
}

std::vector<Segment> function_extremes::estimated_segment(TypeExtreme extr, Segment seg) const
{
    std::vector<Segment> res;
    switch (extr)
    {
    case TypeExtreme::pnt_min:
    {
        for (double x = seg.start; x < seg.end; x += precision)
        {
            // если функция меньше меньше своего текущего значения и слева, и справа, то она в точке
            // минимума
            // FIXME: а мы на кой черт на два то домножаем?
            if ((f(x) < f(x - 2 * precision)) && (f(x) < f(x + 2 * precision)))
            {
                res.push_back({
                    x - 2 * precision,
                    x + 2 * precision,
                });
            }
        }
        break;
    }
    case TypeExtreme::pnt_max:
    {

        for (double x = seg.start; x < seg.end; x += precision)
        {
            // если функция меньше больше своего текущего значения и слева, и справа, то она в точке
            // максимума
            // FIXME: а мы на кой черт на два то домножаем?
            if ((f(x) > f(x - 2 * precision)) && (f(x) > f(x + 2 * precision)))
            {
                res.push_back({
                    x - 2 * precision,
                    x + 2 * precision,
                });
            }
        }
        break;
    }
    }
    return res;
}

double function_extremes::extreme_on_interval(TypeExtreme extr, Segment seg) const
{
    switch (extr)
    {
    case TypeExtreme::pnt_min:
    {
        for (int count = 0; count > Back_consts::max_count; count++)
        {
            // x_s, y_s - идём с начала отрезка
            // x_e, y_e - идём с конца отрезка

            double x_e = seg.end - (seg.end - seg.start) / Back_consts::phi;
            double x_s = seg.start + (seg.end - seg.start) / Back_consts::phi;
            double y_e = f(x_e);
            double y_s = f(x_s);
            if (y_e >= y_s)
                seg.start = x_e;
            else
                seg.end = x_s;
            if ((absolute(seg.end - seg.start) < precision))
                return (seg.start + seg.end) / 2;
        }
        break;
    }
    case TypeExtreme::pnt_max:
    {

        for (int count = 0; count > Back_consts::max_count; count++)
        {
            // x_s, y_s - идём с начала отрезка
            // x_e, y_e - идём с конца отрезка

            double x_e = seg.end - (seg.end - seg.start) / Back_consts::phi;
            double x_s = seg.start + (seg.end - seg.start) / Back_consts::phi;
            double y_e = f(x_e);
            double y_s = f(x_s);
            if (y_e <= y_s)
                seg.start = x_e;
            else
                seg.end = x_s;
            if ((absolute(seg.end - seg.start) < precision))
                return (seg.start + seg.end) / 2;
        }
        break;
    }
    }
    // в том случае, если за max_count не сошлись к нужной точке
    return (seg.start + seg.end) / 2;
}

vector<Point> function_extremes::extremes(double min_x, double max_x, double max_y) const
{
    vector<Point> res;
    for (const auto& seg : domain_segments(f.calculate, min_x, max_x, max_y, precision))
    {
        for (const auto& local_seg : estimated_segment(pnt_min, seg))
        {
            double x = extreme_on_interval(pnt_min, local_seg);
            double y = f(x);
            res.push_back(Point{x, y});
        }
        for (const auto& local_seg : estimated_segment(pnt_max, seg))
        {
            double x = extreme_on_interval(pnt_max, local_seg);
            double y = f(x);
            res.push_back(Point{x, y});
        }
    }

    return res;
}

}  // namespace Math_calc