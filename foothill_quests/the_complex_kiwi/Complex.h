

#pragma once

#include <bits/stdc++.h>

class Complex {
 public:
  class Div_By_Zero_Exception {
   public:
    std::string what() { return "Divide by zero exception"; }

    std::string to_string() { return what(); }
  };

  Complex(double re = 0, double im = 0) : _real(re), _imag(im) {}

  bool operator==(const Complex &that) {
    return _real == that._real && _imag == that._imag;
  }

  bool operator!=(const Complex &that) { return !(*this == that); }

  double norm() const { return sqrt(_real * _real + _imag * _imag); }

  bool operator<(const Complex &that) { return norm() < that.norm(); }

  Complex operator+(const Complex &that) {
    return Complex(_real + that._real, _imag + that._imag);
  }

  Complex operator-(const Complex &that) {
    return Complex(_real - that._real, _imag - that._imag);
  }

  Complex operator*(const Complex &that) {
    return Complex(_real * that._real - _imag * that._imag,
                   _real * that._imag + _imag * that._real);
  }

  Complex reciprocal() const {
    double denom = _real * _real + _imag * _imag;
    if (denom == 0) throw Div_By_Zero_Exception();

    return Complex(_real / denom, -_imag / denom);
  }

  Complex operator/(const Complex &that) { return *this * that.reciprocal(); }

  std::string to_string() const {
    char buf[64];
    snprintf(buf, 64, "(%.11g,%.11g)", _real, _imag);
    return buf;
  }

  friend std::ostream &operator<<(std::ostream &os, const Complex &x) {
    return os << x.to_string();
  }

  double _real, _imag;
};
