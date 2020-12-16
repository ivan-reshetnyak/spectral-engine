/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <cmath>

namespace spectral {

template<class type>
class vec_t {
public:
  type X, Y, Z;

  explicit vec_t( const type &Value ) : X(Value), Y(Value), Z(Value) {
  }


  vec_t( const type &X, const type &Y, const type &Z) : X(X), Y(Y), Z(Z) {
  }


  // Vector length
  type operator!() const {
    type len = X * X + Y * Y + Z * Z;

    if (len > 0) {
      if (len != 1) {
        len = sqrt(len);
        return len;
      }
      return len;
    }
    return len;
  }


  // Dot product
  type operator&( const vec_t &V ) const {
    return X * V.X + Y * V.Y + Z * V.Z;
  }


  // Cross product
  vec_t operator%( const vec_t &V ) const {
    return vec_t(Y * V.Z - V.Y * Z, V.X * Z - X * V.Z, X * V.Y - V.X * Y);
  }

  // TODO: Compare with threshold
  bool operator==( const vec_t &V ) const {
    return (X == V.X) && (Y == V.Y) && (Z == V.Z);
  }


  bool operator!=( const vec_t &V ) const {
    return (X != V.X) || (Y != V.Y) || (Z != V.Z);
  }


  vec_t operator+( const vec_t &V ) const {
    return vec_t(X + V.X, Y + V.Y, Z + V.Z);
  }


  vec_t operator-( const vec_t &V ) const {
    return vec_t(X - V.X, Y - V.Y, Z - V.Z);
  }


  vec_t operator*( const vec_t &V ) const {
    return vec_t(X * V.X, Y * V.Y, Z * V.Z);
  }


  vec_t operator/( const vec_t &V ) const {
    return vec_t(X / V.X, Y / V.Y, Z / V.Z);
  }


  vec_t operator*( const type &A ) const {
    return vec_t(A * X, A * Y, A * Z);
  }


  vec_t operator/( const type &A ) const {
    return vec_t(X / A, Y / A, Z / A);
  }


  vec_t operator-() const {
    return vec_t(-X, -Y, -Z);
  }


  vec_t & Negate() {
    X = -X;
    Y = -Y;
    Z = -Z;

    return *this;
  }


  vec_t & operator+=( const vec_t &V ) {
    X += V.X;
    Y += V.Y;
    Z += V.Z;

    return *this;
  }


  vec_t & operator-=( const vec_t &V ) {
    X -= V.X;
    Y -= V.Y;
    Z -= V.Z;

    return *this;
  }


  vec_t & operator*=( const type &A )  {
    X *= A;
    Y *= A;
    Z *= A;

    return *this;
  }


  vec_t & operator*=( const vec_t &V ) {
    X *= V.X;
    Y *= V.Y;
    Z *= V.Z;

    return *this;
  }


  vec_t & operator%=( const vec_t &V ) {
    type a, b;

    a = Y * V.Z - V.Y * Z;
    b = V.X * Z - X * V.Z;
    Z = X * V.Y - V.X * Y;
    X = a;
    Y = b;

    return *this;
  }


  vec_t & operator/=( const type &A ) {
    X /= A;
    Y /= A;
    Z /= A;

    return *this;
  }


  type & operator[]( int I ) {
    return *(&X + I);
  }


  /* TODO: When I add matrices
  TVec operator*( const TMatr<TYPE> &Matr ) const
  {
    TVec ret(X * Matr.A[0][0] + Y * Matr.A[1][0] + Z * Matr.A[2][0] + Matr.A[3][0],
              X * Matr.A[0][1] + Y * Matr.A[1][1] + Z * Matr.A[2][1] + Matr.A[3][1],
              X * Matr.A[0][2] + Y * Matr.A[1][2] + Z * Matr.A[2][2] + Matr.A[3][2]);
    TYPE W = X * Matr.A[0][3] + Y * Matr.A[1][3] + Z * Matr.A[2][3] + Matr.A[3][3];
    ret /= W;
    return ret;
  }

  TVec & operator*=( const TMatr<TYPE> &Matr )
  {
    TYPE a, b;

    a = X * Matr.A[0][0] + Y * Matr.A[1][0] + Z * Matr.A[2][0] + Matr.A[3][0];
    b = X * Matr.A[0][1] + Y * Matr.A[1][1] + Z * Matr.A[2][1] + Matr.A[3][1];
    Z = X * Matr.A[0][2] + Y * Matr.A[1][2] + Z * Matr.A[2][2] + Matr.A[3][2];
    X = a;
    Y = b;

    return *this;
  }
  */

  vec_t & Normalize() {
    type len = X * X + Y * Y + Z * Z;

    if (len > 0) {
      if (len != 1) {
        len = sqrt(len);
        X /= len;
        Y /= len;
        Z /= len;
        return *this;
      }
      return *this;
    }
    return *this;
  }

  vec_t Normalized() const {
    type len = X * X + Y * Y + Z * Z;

    if (len > 0) {
      if (len != 1) {
        len = sqrt(len);
        return vec_t(X / len, Y / len, Z / len);
      }
      return *this;
    }
    return *this;
  }
};


using vecf = vec_t<float>;
using vecd = vec_t<double>;


} // End of 'spectral' namespace
