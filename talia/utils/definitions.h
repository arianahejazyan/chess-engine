#pragma once

/* ---------------------------------------------------------------------------- */

enum Square
{
    a1,  b1,  c1,  d1,  e1,  f1,  g1,  h1,  i1,  j1,  k1,  l1,  m1,  n1,
    a2,  b2,  c2,  d2,  e2,  f2,  g2,  h2,  i2,  j2,  k2,  l2,  m2,  n2,
    a3,  b3,  c3,  d3,  e3,  f3,  g3,  h3,  i3,  j3,  k3,  l3,  m3,  n3,
    a4,  b4,  c4,  d4,  e4,  f4,  g4,  h4,  i4,  j4,  k4,  l4,  m4,  n4,
    a5,  b5,  c5,  d5,  e5,  f5,  g5,  h5,  i5,  j5,  k5,  l5,  m5,  n5,
    a6,  b6,  c6,  d6,  e6,  f6,  g6,  h6,  i6,  j6,  k6,  l6,  m6,  n6,
    a7,  b7,  c7,  d7,  e7,  f7,  g7,  h7,  i7,  j7,  k7,  l7,  m7,  n7,
    a8,  b8,  c8,  d8,  e8,  f8,  g8,  h8,  i8,  j8,  k8,  l8,  m8,  n8,
    a9,  b9,  c9,  d9,  e9,  f9,  g9,  h9,  i9,  j9,  k9,  l9,  m9,  n9,
    a10, b10, c10, d10, e10, f10, g10, h10, i10, j10, k10, l10, m10, n10,
    a11, b11, c11, d11, e11, f11, g11, h11, i11, j11, k11, l11, m11, n11,
    a12, b12, c12, d12, e12, f12, g12, h12, i12, j12, k12, l12, m12, n12,
    a13, b13, c13, d13, e13, f13, g13, h13, i13, j13, k13, l13, m13, n13,
    a14, b14, c14, d14, e14, f14, g14, h14, i14, j14, k14, l14, m14, n14, X
};

enum Player {Zombie=-3, Dead=-2, None=-1, Red=0, Blue=1, Yellow=2, Green=3};

enum Piece {Brick=-1, Empty=0, King=1, Queen=2, Rook=3, Bishop=4, Knight=5, Pawn=6};

enum Offset {S=0, U=14, R=1, D=-14, L=-1};

enum Flag {Null=0, Push=1, DoublePush=2, Advance=4, Enpassant=8, Promotion=16, Leap=32, Slide=64, Castle=128, Capture=256, Check=512};

enum Side {Neither=0, KingSide=1, QueenSide=2};

enum GameState {ongoing, over};

struct Move
{
    Square from;
    Square to;
    Square midway;
    Square target;
    Piece promotion;
    Side side;
    Flag flag;
};

struct Position
{
    Player turn;
    Piece pieces[196];
    Piece players[196];  
    Square royals[4];
    Square marked[4];
    Square target[4];
    GameState state;
    bool kingSide[4];
    bool queenSide[4];
    bool safty[4];
};

/* ---------------------------------------------------------------------------- */