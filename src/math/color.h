/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

namespace spectral {


template<class type>
class color_t {
public:
  using dword = unsigned long;
  type R, G, B, A;

  explicit color_t() : R(0), G(0), B(0), A(1) {
  }


  explicit color_t( type NewR, type NewG, type NewB, type NewA = 1 ) :
      R(NewR), G(NewG), B(NewB), A(NewA) {
  } /* End of 'color_t' constructor */


  explicit color_t( const type &Value ) : R(Value), G(Value), B(Value), A(1) {
  }

  explicit color_t( dword Value ) :
      R(((Value >> 16) & 0xFF) / 255.0), G(((Value >> 8) & 0xFF) / 255.0),
      B((Value & 0xFF) / 255.0), A(((Value >> 24) & 0xFF) / 255.0) {
  }

  color_t operator+( const color_t &Color ) const {
    return color_t(R + Color.R, G + Color.G, B + Color.B, A + Color.A);
  }

  color_t & operator+=( const color_t &Color ) {
    R += Color.R;
    G += Color.G;
    B += Color.B;
    A += Color.A;
    return *this;
  }

  color_t operator-( const color_t &Color ) const {
    return color_t(R - Color.R, G - Color.G, B - Color.B, A - Color.A);
  }

  color_t & operator-=( const color_t &Color ) {
    R -= Color.R;
    G -= Color.G;
    B -= Color.B;
    A -= Color.A;
    return *this;
  }

  color_t operator*( const type &Multiplier ) const {
    return color_t(R * Multiplier, G * Multiplier, B * Multiplier, A * Multiplier);
  }

  color_t & operator*=( const type &Multiplier ) {
    R *= Multiplier;
    G *= Multiplier;
    B *= Multiplier;
    A *= Multiplier;
    return *this;
  }

  color_t operator*( const color_t &Color ) const {
    return color_t(R * Color.R, G * Color.G, B * Color.B, A * Color.A);
  }

  color_t & operator*=( const color_t &Color ) {
    R *= Color.R;
    G *= Color.G;
    B *= Color.B;
    A *= Color.A;
    return *this;
  }

  color_t operator/( const type &Value ) const {
    return color_t(R / Value, G / Value, B / Value, A / Value);
  }

  color_t & operator/=( type Value ) {
    R /= Value;
    G /= Value;
    B /= Value;
    A /= Value;
    return *this;
  }

  // Return max component
  type Max() const {
    if (R > G)
      if (B > R)
        return B;
      else
        return R;
    else
      if (B > G)
        return B;
      else
        return G;
  }

  void Set( const type &NewR, const type &NewG, const type &NewB, const type &NewA = 1 ) {
    R = NewR;
    G = NewG;
    B = NewB;
    A = NewA;
  }


  static color_t random() {
    return color_t(::spectral::random(-1, 1), ::spectral::random(-1, 1),
                   ::spectral::random(-1, 1), ::spectral::random(-1, 1));
  }


  static color_t random( const type &Alpha ) {
    return color_t(::spectral::random(-1, 1), ::spectral::random(-1, 1),
                   ::spectral::random(-1, 1), Alpha);
  }

  static color_t random( const color_t &Left, const color_t &Right ) {
    return color_t(::spectral::random(Left.R, Right.R), ::spectral::random(Left.G, Right.G),
                   ::spectral::random(Left.B, Right.B), ::spectral::random(Left.A, Right.A));
  }
};


} // End of 'spectral' namespace
