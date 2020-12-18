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
    Position(Position), LookAt(LookAt),
    Near(Near), Far(Far), LeftP(LeftP), RightP(RightP),
    Up(Up0), Bottom(Bottom), Top(Top),
    Mode(mode::DIRECTED) {
  Direction = (Position - LookAt).Normalized();
  Right = (Direction % Up).Normalized();
  Up = (Right % Direction).Normalized();

  UpdateMatrices();
}


void camera::UpdateMatrices( void ) {
  View = matrix::View(Position, Direction, Up, Right);
  Projection = matrix::Projection(LeftP, RightP, Top, Bottom, Near, Far);
  VP = Projection * View;
}


void camera::Set( float Near, float Far, float Bottom,
                  float Top, float LeftP, float RightP ) {
  this->Near = Near;
  this->Far = Far;
  this->Bottom = Bottom;
  this->Top = Top;
  this->LeftP = LeftP;
  this->RightP = RightP;
  UpdateMatrices();
}


void camera::Set( const vec &Pos, const vec &At, const vec &Up ) {
  Position = Pos;
  LookAt = At;
  this->Up = Up;
  Direction = (Position - LookAt).Normalized();
  Right = (Direction % Up).Normalized();
  this->Up = (Right % Direction).Normalized();

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
