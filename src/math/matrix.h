/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <cmath>
#include <cstring>

#include <algorithm>

#include "math.h"
#include "vec.h"

namespace spectral {


template<class type>
class matrix_t {
private:
  using vec = vec_t<type>;
public:
  static const int Size = 4;


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
    std::memcpy(Data, Other.Data, sizeof(type) * Size * Size);
  }


  type * GetData() {
    return (type *)Data;
  }


  /*************
   * Operators
   *************/
  bool operator==( const matrix_t &Other ) const {
    for (int i = 0; i < Size; ++i)
      for (int j = 0; j < Size; ++j)
        if (Data[i][j] != Other[i][j])
          return false;
    return true;
  }

  matrix_t & operator=( const matrix_t &Other ) {
    std::memcpy(Data, Other.Data, sizeof(type) * Size * Size);
    return *this;
  }


  type * operator[]( int Index ) {
    return Data[Index];
  }


  const type * operator[]( int Index ) const {
    return Data[Index];
  }


  matrix_t operator+( const matrix_t &Other ) const {
    matrix_t res = *this;
    for (int i = 0; i < Size; ++i)
      for (int j = 0; j < Size; ++j)
        res[i][j] += Other[i][j];
    return res;
  }


  matrix_t & operator+=( const matrix_t &Other ) {
    for (int i = 0; i < Size; ++i)
      for (int j = 0; j < Size; ++j)
        Data[i][j] += Other[i][j];
    return *this;
  }


  matrix_t operator-( const matrix_t &Other ) const {
    matrix_t res = *this;
    for (int i = 0; i < Size; ++i)
      for (int j = 0; j < Size; ++j)
        res[i][j] -= Other[i][j];
    return res;
  }


  matrix_t & operator-=( const matrix_t &Other ) {
    for (int i = 0; i < Size; ++i)
      for (int j = 0; j < Size; ++j)
        Data[i][j] -= Other[i][j];
    return *this;
  }


  matrix_t operator*( const type &Multiplicator ) const {
    matrix_t Res(*this);
    for (auto &Row : Res.Data)
      for (auto &Cell : Row)
        Cell *= Multiplicator;
    return Res;
  }


  matrix_t & operator*=( const type &Multiplicator ) {
    for (auto &Row : Data)
      for (auto &Cell : Row)
        Cell *= Multiplicator;
    return *this;
  }


  matrix_t operator/( const type &Divisor ) const {
    matrix_t Res(*this);
    for (auto &Row : Res.Data)
      for (auto &Cell : Row)
        Cell /= Divisor;
    return Res;
  }


  matrix_t & operator/=( const type &Multiplicator ) {
    for (auto &Row : Data)
      for (auto &Cell : Row)
        Cell /= Multiplicator;
    return *this;
  }


  matrix_t operator*( const matrix_t &Other ) const {
    matrix_t Res(matrix_t::Zero());
    for (int i = 0; i < Size; ++i)
      for (int j = 0; j < Size; ++j)
        for (int k = 0; k < Size; k++)
          Res[i][j] += Data[i][k] * Other[k][j];
    return Res;
  }


  matrix_t & operator*=( const matrix_t &Other ) {
    matrix_t Res(matrix_t::Zero());
    for (int i = 0; i < Size; ++i)
      for (int j = 0; j < Size; ++j)
        for (int k = 0; k < Size; k++)
          Res[i][j] += Data[i][k] * Other[k][j];
    *this = std::move(Res);
    return *this;
  }


  vec operator*( const vec &Vec) const {
    return vec(
      (Vec.X * Data[0][0] + Vec.Y * Data[1][0] + Vec.Z * Data[2][0] + Data[3][0]),
      (Vec.X * Data[0][1] + Vec.Y * Data[1][1] + Vec.Z * Data[2][1] + Data[3][1]),
      (Vec.X * Data[0][2] + Vec.Y * Data[1][2] + Vec.Z * Data[2][2] + Data[3][2]));
  }


  /*************
   * Transformations
   *************/
  matrix_t & Transpose( void ) {
    for (int i = 0; i < Size; ++i)
      for (int j = i + 1; j < Size; ++j)
        std::swap(Data[i][j], Data[j][i]);
    return *this;
  }


  matrix_t Transposed( void ) const {
    return matrix_t(Data[0][0], Data[1][0], Data[2][0], Data[3][0],
                    Data[0][1], Data[1][1], Data[2][1], Data[3][1],
                    Data[0][2], Data[1][2], Data[2][2], Data[3][2],
                    Data[0][3], Data[1][3], Data[2][3], Data[3][3]);
  }


  type Determinator( void ) const {
    return type(0) +
      Data[0][0] * Data[1][1] * Data[2][2] * Data[3][3] * ( 1) +
      Data[0][0] * Data[1][1] * Data[2][3] * Data[3][2] * (-1) +

      Data[0][0] * Data[1][2] * Data[2][3] * Data[3][1] * ( 1) +
      Data[0][0] * Data[1][2] * Data[2][1] * Data[3][3] * (-1) +

      Data[0][0] * Data[1][3] * Data[2][1] * Data[3][2] * ( 1) +
      Data[0][0] * Data[1][3] * Data[2][2] * Data[3][1] * (-1) +

      //////////////////////////////////////////
      Data[0][1] * Data[1][0] * Data[2][2] * Data[3][3] * (-1) +
      Data[0][1] * Data[1][0] * Data[2][3] * Data[3][2] * ( 1) +

      Data[0][1] * Data[1][2] * Data[2][3] * Data[3][0] * (-1) +
      Data[0][1] * Data[1][2] * Data[2][0] * Data[3][3] * ( 1) +

      Data[0][1] * Data[1][3] * Data[2][0] * Data[3][2] * (-1) +
      Data[0][1] * Data[1][3] * Data[2][2] * Data[3][0] * ( 1) +

      //////////////////////////////////////////
      Data[0][2] * Data[1][0] * Data[2][1] * Data[3][3] * ( 1) +
      Data[0][2] * Data[1][0] * Data[2][3] * Data[3][1] * (-1) +

      Data[0][2] * Data[1][1] * Data[2][3] * Data[3][0] * ( 1) +
      Data[0][2] * Data[1][1] * Data[2][0] * Data[3][3] * (-1) +

      Data[0][2] * Data[1][3] * Data[2][0] * Data[3][1] * ( 1) +
      Data[0][2] * Data[1][3] * Data[2][0] * Data[3][1] * (-1) +

      //////////////////////////////////////////
      Data[0][3] * Data[1][0] * Data[2][1] * Data[3][2] * (-1) +
      Data[0][3] * Data[1][0] * Data[2][2] * Data[3][1] * ( 1) +

      Data[0][3] * Data[1][1] * Data[2][2] * Data[3][0] * (-1) +
      Data[0][3] * Data[1][1] * Data[2][0] * Data[3][2] * (-1) +

      Data[0][3] * Data[1][2] * Data[2][0] * Data[3][1] * (-1) +
      Data[0][3] * Data[1][2] * Data[2][1] * Data[3][0] * ( 1);
  }


  type Conjugate( int X, int Y ) const {
    matrix_t M = *this;
    for (int i = 0; i < 4; i++)
      M[i][X] = 0;
    for (int i = 0; i < 4; i++)
      M[Y][i] = 1;
    M[Y][X] = 1;
    return M.Determinator();
  }


  matrix_t Inverse( void ) const {
    matrix_t Adjoint(Conjugate(0, 0), Conjugate(1, 0), Conjugate(2, 0), Conjugate(3, 0),
                     Conjugate(0, 1), Conjugate(1, 1), Conjugate(2, 1), Conjugate(3, 1),
                     Conjugate(0, 2), Conjugate(1, 2), Conjugate(2, 2), Conjugate(3, 2),
                     Conjugate(0, 3), Conjugate(1, 3), Conjugate(2, 3), Conjugate(3, 3));
    return (Adjoint * (type)1.0 / Determinator()).Transposed();
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


  static matrix_t Rotation( const vec &Axis, double Angle ) {
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


  static matrix_t View( const vec &Loc, const vec &Dir, const vec &Up, const vec &Right ) {
    return matrix_t(Right.X,      Up.X,      Dir.X, (type)0,
                    Right.Y,      Up.Y,      Dir.Y, (type)0,
                    Right.Z,      Up.Z,      Dir.Z, (type)0,
                -Loc & Right, -Loc & Up, -Loc & Dir, (type)1);
  }


  static matrix_t Projection( type Left, type Right, type Top, type Bottom, type Near, type Far ) {
    type
      Width = Right - Left,
      Height = Top - Bottom,
      Depth = Far - Near;

    return
      matrix_t((type)2 * Near / Width,                 (type)0,  (Right + Left) / Width,                       (type)0,
                              (type)0, (type)2 * Near / Height, (Top + Bottom) / Height,                       (type)0,
                              (type)0,                 (type)0,   -(Far + Near) / Depth, (type)2 * Far * Near / -Depth,
                              (type)0,                 (type)0,                (type)-1,                       (type)0);
  }

private:
  type Data[Size][Size];
};


} // End of 'spectral' namespace
