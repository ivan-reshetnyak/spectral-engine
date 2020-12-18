/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <cmath>

#include <algorithm>
#include <array>

#include "math.h"
#include "vec.h"

namespace spectral {


template<class type>
class matrix_t {
public:
  static const int Size = 4;
  using row = std::array<type, Size>;


  ~matrix_t() {
  }


  explicit matrix_t( const type &A0 = 1, const type &A1 = 0, const type &A2 = 0, const type &A3 = 0,
                     const type &B0 = 0, const type &B1 = 1, const type &B2 = 0, const type &B3 = 0,
                     const type &C0 = 0, const type &C1 = 0, const type &C2 = 1, const type &C3 = 0,
                     const type &D0 = 0, const type &D1 = 0, const type &D2 = 0, const type &D3 = 1 ) {
    Data[0][0] = A0;
    Data[0][1] = A1;
    Data[0][2] = A2;
    Data[0][3] = A3;

    Data[1][0] = B0;
    Data[1][1] = B1;
    Data[1][2] = B2;
    Data[1][3] = B3;

    Data[2][0] = C0;
    Data[2][1] = C1;
    Data[2][2] = C2;
    Data[2][3] = C3;

    Data[3][0] = D0;
    Data[3][1] = D1;
    Data[3][2] = D2;
    Data[3][3] = D3;
  }


  matrix_t( const matrix_t &Other ) {
    Data = Other.Data;
  }


  matrix_t( matrix_t &&Other ) : Data(std::move(Other.Data)) {
  }


  /*************
   * Operators
   *************/
  bool operator==( const matrix_t &Other ) const {
    return Data == Other.Data;
  }

  matrix_t & operator=( const matrix_t &Other ) {
    Data = Other.Data;
    return *this;
  }


  row & operator[]( int Index ) {
    return Data[Index];
  }


  const row & operator[]( int Index ) const {
    return Data[Index];
  }


  matrix_t operator+( const matrix_t &Other ) const {
    matrix_t res = *this;
    for (int i = 0; i < Size; i++)
      for (int j = 0; j < Size; j++)
        res[i][j] += Other[i][j];
    return res;
  }


  matrix_t & operator+=( const matrix_t &Other ) {
    for (int i = 0; i < Size; i++)
      for (int j = 0; j < Size; j++)
        Data[i][j] += Other[i][j];
    return *this;
  }


  matrix_t operator-( const matrix_t &Other ) const {
    matrix_t res = *this;
    for (int i = 0; i < Size; i++)
      for (int j = 0; j < Size; j++)
        res[i][j] -= Other[i][j];
    return res;
  }


  matrix_t & operator-=( const matrix_t &Other ) {
    for (int i = 0; i < Size; i++)
      for (int j = 0; j < Size; j++)
        Data[i][j] -= Other[i][j];
    return *this;
  }


  matrix_t operator*( type &Multiplicator ) const {
    matrix_t Res(*this);
    for (auto &Row : Res.Data)
      for (auto &Cell : Row)
        Cell *= Multiplicator;
    return Res;
  }


  matrix_t & operator*=( type &Multiplicator ) {
    for (auto &Row : Data)
      for (auto &Cell : Row)
        Cell *= Multiplicator;
    return *this;
  }


  matrix_t operator/( type &Divisor ) const {
    matrix_t Res(*this);
    for (auto &Row : Res.Data)
      for (auto &Cell : Row)
        Cell /= Divisor;
    return Res;
  }


  matrix_t & operator/=( type &Multiplicator ) {
    for (auto &Row : Data)
      for (auto &Cell : Row)
        Cell /= Multiplicator;
    return *this;
  }


  matrix_t operator*( const matrix_t &Other ) const {
    matrix_t Res(matrix_t::Zero());
    for (int i = 0; i < Size; i++)
      for (int j = 0; j < Size; j++)
        for (int k = 0; k < Size; k++)
          Res[i][j] += Data[i][k] * Other[k][j];
    return Res;
  }


  matrix_t & operator*=( const matrix_t &Other ) {
    matrix_t Res(matrix_t::Zero());
    for (int i = 0; i < Size; i++)
      for (int j = 0; j < Size; j++)
        for (int k = 0; k < Size; k++)
          Res[i][j] += Data[i][k] * Other[k][j];
    *this = std::move(Res);
    return *this;
  }


  matrix_t & Transpose( void ) {
    for (int i = 0; i < Size; i++)
      for (int j = i + 1; j < Size; j++)
        std::swap(Data[i][j], Data[j][i]);
    return *this;
  }

  /*********
   * Preset matrices
   *********/
  static matrix_t Identity() {
    return matrix_t();
  }


  static matrix_t Zero() {
    return matrix_t(0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 0);
  }


  static matrix_t Translation( const type &Dx, const type &Dy, const type &Dz ) {
    matrix_t Res;
    Res[3][0] = Dx;
    Res[3][1] = Dy;
    Res[3][2] = Dz;
    Res[3][3] = 1;
    return Res;
  }


  static matrix_t RotationX( double Angle ) {
    Angle = DegreesToRadians(Angle);
    matrix_t Res;
    type sine = (type)sin(Angle), cosine = (type)cos(Angle);
    Res[1][1] = (type)cosine;
    Res[1][2] = (type)sine;
    Res[2][1] = (type)-sine;
    Res[2][2] = (type)cosine;
    return Res;
  }


  static matrix_t RotationY( double Angle ) {
    Angle = DegreesToRadians(Angle);
    matrix_t Res;
    type sine = (type)sin(Angle), cosine = (type)cos(Angle);
    Res[0][0] = (type)cosine;
    Res[0][2] = (type)sine;
    Res[2][0] = (type)-sine;
    Res[2][2] = (type)cosine;
    return Res;
  }


  static matrix_t RotationZ( double Angle ) {
    Angle = DegreesToRadians(Angle);
    matrix_t Res;
    type sine = (type)sin(Angle), cosine = (type)cos(Angle);
    Res[0][0] = (type)cosine;
    Res[0][1] = (type)sine;
    Res[1][0] = (type)-sine;
    Res[1][1] = (type)cosine;
    return Res;
  }


  static matrix_t Rotation( const vec_t<type> &Axis, double Angle ) {
    Angle = DegreesToRadians(Angle);
    matrix_t Res;
    double sine = sin(Angle), cosine = cos(Angle);

    Res[0][0] = (type)(cosine + Axis.X * Axis.X * (1 - cosine));
    Res[0][1] = (type)(Axis.X * Axis.Y * (1 - cosine) - Axis.Z * sine);
    Res[0][2] = (type)(Axis.Z * Axis.X * (1 - cosine) + Axis.Y * sine);

    Res[1][0] = (type)(Axis.Y * Axis.X * (1 - cosine) + Axis.Z * sine);
    Res[1][1] = (type)(cosine + Axis.Y * Axis.Y * (1 - cosine));
    Res[1][2] = (type)(Axis.Z * Axis.Y * (1 - cosine) - Axis.X * sine);

    Res[2][0] = (type)(Axis.Z * Axis.X * (1 - cosine) - Axis.Y * sine);
    Res[2][1] = (type)(Axis.Z * Axis.Y * (1 - cosine) + Axis.X * sine);
    Res[2][2] = (type)(cosine + Axis.Z * Axis.Z * (1 - cosine));
    return Res;
  }

private:
  std::array<row, Size> Data;
};


} // End of 'spectral' namespace
