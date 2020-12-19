/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "camera.h"

namespace spectral {


camera::camera( float Near, float Far, float Bottom,
                float Top, float LeftP, float RightP,
                const vec &Position, const vec &LookAt,
                const vec &Up0 ) :
    Mode(mode::DIRECTED) {
  Set(Near, Far, Bottom, Top, LeftP, RightP, false);
  Set(Position, LookAt, Up0);
}


camera::camera( float Near, float Far,
                int WinW, int WinH,
                const vec &Position, const vec &LookAt,
                const vec &Up0 ) :
    Mode(mode::DIRECTED) {
  Set(Near, Far, WinW, WinH, false);
  Set(Position, LookAt, Up0);
}


void camera::UpdateMatrices( void ) {
  View = matrix::View(Position, Direction, Up, Right);
  Projection = matrix::Projection(LeftP, RightP, Top, Bottom, Near, Far);
  VP = View * Projection;
}


void camera::Set( float Near, float Far,
                  bool Update ) {
  this->Near = Near;
  this->Far = Far;

  if (Update)
    UpdateMatrices();
}


void camera::Set( float Near, float Far, float Bottom,
                  float Top, float LeftP, float RightP,
                  bool Update ) {
  Set(Near, Far, false);
  Set(Bottom, Top, LeftP, RightP, Update);
}


void camera::Set( float Bottom, float Top,
                  float LeftP, float RightP,
                  bool Update ) {
  this->Bottom = Bottom;
  this->Top = Top;
  this->LeftP = LeftP;
  this->RightP = RightP;

  if (Update)
    UpdateMatrices();
}


void camera::Set( float Near, float Far,
                  int WinW, int WinH,
                  bool Update ) {
  Set(Near, Far, false);
  Set(WinW, WinH, Update);
}


void camera::Set( int WinW, int WinH,
                  bool Update ) {
  float ratio = (float)WinW / WinH;
  float scale = 1;
  Set(-1.f / 2.f * scale, 1.f / 2.f * scale, -ratio / 2.f * scale, ratio / 2.f * scale, Update);
}


void camera::Set( const vec &Pos, const vec &At, const vec &Up,
                  bool Update ) {
  Position = Pos;
  LookAt = At;
  this->Up = Up;
  Direction = (Position - LookAt).Normalized();
  Right = (Direction % Up).Normalized();
  this->Up = (Right % Direction).Normalized();

  if (Update)
    UpdateMatrices();
}


void camera::Set( mode NewMode ) {
  Mode = NewMode;
}

void camera::Move( const vec &Shift ) {
  switch (Mode) {
  case mode::DIRECTED:
    Set(Position + Shift, LookAt + Shift, Up);
    break;
  case mode::FOCUSED:
    Set(Position + Shift, LookAt, Up);
    break;
  }
}


} // End of 'spectral' namespace
