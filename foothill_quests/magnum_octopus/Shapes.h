#pragma once

#include <bits/stdc++.h>

class Screen {
 public:
  static const char FG = '*', BG = '.';

  Screen(size_t w, size_t h)
      : _w(w), _h(h), _pix(h, std::vector<char>(w, '.')) {}

  size_t get_w() const { return _w; }

  size_t get_h() const { return _h; }

  std::vector<std::vector<char>> &get_pix() { return _pix; }

  void set_w(size_t w) { _w = w; }

  void set_h(size_t h) { _h = h; }

  void clear() { fill(BG); }

  void fill(char c) {
    for (auto &row : _pix) {
      std::fill(row.begin(), row.end(), c);
    }
  }

  std::string to_string() const {
    std::string result;
    std::for_each(_pix.rbegin(), _pix.rend(),
                  [&](const std::vector<char> &row) {
                    result += std::string(row.begin(), row.end()) + "\n";
                  });
    return result;
  }

  friend std::ostream &operator<<(std::ostream &os, const Screen &scr) {
    return os << scr.to_string();
  };

 private:
  friend class Shape;
  friend class Tests;

  size_t _w, _h;
  std::vector<std::vector<char>> _pix;
};

class Shape {
 public:
  virtual ~Shape() {}

  virtual bool draw(Screen &scr, char ch = Screen::FG) = 0;

 private:
  friend class Tests;
};

// --------- Point ---------------------------------
class Point : public Shape {
 public:
  Point(size_t x, size_t y) : _x(x), _y(y) {}

  virtual ~Point() {}

  bool draw(Screen &scr, char ch = Screen::FG) {
    if (_y >= scr.get_h() || _x >= scr.get_w()) return false;

    scr.get_pix()[_y][_x] = ch;
    return true;
  }

 private:
  friend class Tests;

  size_t _x, _y;
};

// ----------- Line in two point notation ---------------------
class Line : public Shape {
 public:
  Line(size_t a, size_t b, size_t c, size_t d)
      : _x1(a), _y1(b), _x2(c), _y2(d) {}

  virtual ~Line() {}

  bool draw(Screen &scr, char ch = Screen::FG) {
    return _x1 != _x2 &&
                   (static_cast<long long>(_y2) - static_cast<long long>(_y1)) /
                           (static_cast<long long>(_x2) -
                            static_cast<long long>(_x1)) ==
                       0
               ? draw_by_x(scr, ch, _x1, _y1, _x2, _y2)
               : draw_by_y(scr, ch, _x1, _y1, _x2, _y2);
  }

 private:
  friend class Tests;

  size_t _x1, _y1, _x2, _y2;

  static bool draw_by_x(Screen &scr, char ch, size_t x1, size_t y1, size_t x2,
                        size_t y2) {
    if (x1 > x2) return draw_by_x(scr, ch, x2, y2, x1, y1);

    bool contained(true);

    for (double dy((static_cast<double>(y2) - y1) /
                   (static_cast<double>(x2) - x1)),
         x(x1), y(y1);
         x <= x2; ++x, y += dy)
      contained &= Point(x, y).draw(scr, ch);

    return contained;
  }

  static bool draw_by_y(Screen &scr, char ch, size_t x1, size_t y1, size_t x2,
                        size_t y2) {
    if (y1 > y2) return draw_by_y(scr, ch, x2, y2, x1, y1);

    bool contained(true);

    for (double dx((static_cast<double>(x2) - x1) /
                   ((static_cast<double>(y2) - y1))),
         x(x1), y(y1);
         y <= y2; x += dx, ++y)
      contained &= Point(x, y).draw(scr, ch);

    return contained;
  }
};

// ----------- Quadrilateral -------------------------------------------------
// A general quadrilateral with points (x1,y1) ... (x4,y4), clockwise
// from bottom left. For the special case when x1==x2, y2==y3, x3==x4
// and y4==y1, we'd use an Upright_Rectangle.
class Quadrilateral : public Shape {
 public:
  Quadrilateral(size_t a, size_t b, size_t c, size_t d, size_t e, size_t f,
                size_t g, size_t h)
      : _x1(a), _y1(b), _x2(c), _y2(d), _x3(e), _y3(f), _x4(g), _y4(h) {}

  virtual ~Quadrilateral() {}

  bool draw(Screen &scr, char ch = Screen::FG) {
    return Line(_x1, _y1, _x2, _y2).draw(scr, ch) &
           Line(_x2, _y2, _x3, _y3).draw(scr, ch) &
           Line(_x3, _y3, _x4, _y4).draw(scr, ch) &
           Line(_x4, _y4, _x1, _y1).draw(scr, ch);
  }

 private:
  friend class Tests;

  size_t _x1, _y1, _x2, _y2, _x3, _y3, _x4, _y4;
};

// ----------- UprightRectangle, a special Quadrilateral -----------------
// A Rectangle is a special upright Quadrilateral so we don't have to
// parameterize the constructor with a ton of numbers
class Upright_Rectangle : public Quadrilateral {
 public:
  Upright_Rectangle(size_t x1, size_t y1, size_t x2, size_t y2)
      : Quadrilateral(x1, y1, x1, y2, x2, y2, x2, y1) {}

  virtual ~Upright_Rectangle() {}
};

// ----------- StickMan, a composite Shape ------------------------------
class Stick_Man : public Shape {
 public:
  Stick_Man(size_t x = 0, size_t y = 0, size_t w = DEFAULT_W,
            size_t h = DEFAULT_H)
      : _x(x),
        _y(y),
        _w(w < 2 ? DEFAULT_W : w),
        _h(h < 2 ? DEFAULT_H : h),
        _parts{new Upright_Rectangle(x, y + _h / 2, x + _w - 1, y + _h - 1),
               new Line(x + _w / 2, y + _h / 2, x + _w / 2, y + _h / 4),
               new Line(x + _w / 2, y + _h / 2, x + _w / 4, y + _h / 4),
               new Line(x + _w / 2, y + _h / 2, x + 3 * _w / 4, y + _h / 4),
               new Line(x + _w / 2, y + _h / 4, x, y),
               new Line(x + _w / 2, y + _h / 4, x + _w - 1, y)} {}

  virtual ~Stick_Man() {
    for (const auto &part : get_parts()) {
      delete part;
    }
  }

  const std::vector<Shape *> &get_parts() const { return _parts; }

  bool draw(Screen &scr, char ch = Screen::FG) {
    bool contained(true);
    for (const auto &part : get_parts()) {
      contained &= part->draw(scr, ch);
    }
    return contained;
  }

 private:
  friend class Tests;

  static const size_t DEFAULT_W = 20, DEFAULT_H = 40;

  size_t _x, _y, _w, _h;
  std::vector<Shape *> _parts;
};
