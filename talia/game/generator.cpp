#include "generator.h"
#include "pseudo.h"
#include "config.h"

/* ---------------------------------------------------------------------------- */

void Generator::generate_all_positions(std::vector<Position>& list, const Position& pos)
{
    for (const Square& sq: BOARD::VALID_SQUARES)
    {
        if (pos.turn == pos.players[sq])
        {
            if (PIECE::LEAPER[pos.pieces[sq]])   leap(list, pos, sq);
            if (PIECE::SLIDER[pos.pieces[sq]])   slide(list, pos, sq);
            if (PIECE::PUSHER[pos.pieces[sq]])   push(list, pos, sq);
            if (PIECE::ADVANCER[pos.pieces[sq]]) advance(list, pos, sq);
        }
    }
    
    enpassant(list, pos);

    castle(list, pos);

    pass(list, pos);
}

/* ---------------------------------------------------------------------------- */

inline void Generator::leap(std::vector<Position>& list, const Position& pos, const Square& sq)
{
    for (const Move& move: Pseudo::LEAP[Key(sq,pos.pieces[sq])])
    {
        make_move(list, pos, move);
    }
}

inline void Generator::slide(std::vector<Position>& list, const Position& pos, const Square& sq)
{
    for (const Offset& offset: Pseudo::RAY[Key(sq,pos.pieces[sq])])
    {
        for (const Move& move: Pseudo::SLIDE[Key(sq,pos.pieces[sq],offset)])
        {
            make_move(list, pos, move);

            if (pos.pieces[move.to] != Empty) break;
        }
    }
}

inline void Generator::push(std::vector<Position>& list, const Position& pos, const Square& sq)
{
    for (const Move& move: Pseudo::PUSH[Key(sq,pos.pieces[sq],pos.turn)])
    {
        if (pos.pieces[move.to] == Empty)
        {
            if (move.flag & DoublePush)
            {
                if (pos.pieces[move.midway] == Empty) 
                {
                    make_move(list, pos, move);
                }
            }

            else
            {
                make_move(list, pos, move);
            }
        }
    }
}

inline void Generator::advance(std::vector<Position>& list, const Position& pos, const Square& sq)
{
    for (const Move& move: Pseudo::ADVANCE[Key(sq,pos.pieces[sq],pos.turn)])
    {
        if (pos.pieces[move.to] != Empty)
        {
            make_move(list, pos, move);
        }
    }
}

inline void Generator::enpassant(std::vector<Position>& list, const Position& pos)
{
  for (const Player opponent: OPPONENTS[pos.turn])
    {
        if (pos.marked[opponent] == to)
        {
            make_move(pos, move, list, true);

            break;
        }
    }
}

inline void Generator::castle(std::vector<Position>& list, const Position& pos)
{
    for (const Side& side: {KingSide, QueenSide})
    {
        /* castle rights */
        if (pos.castle[pos.turn][side] == false) continue;

        /* empty squares */
        for (const Square& sq: PASSING_SQUARES[encodeCastle(pos.turn, side)])
        {
            if (pos.pieces[sq] != Empty) continue;
        }

        /* safe squares */
        for (const Square& sq: SECURE_SQUARES[encodeCastle(pos.turn, move.side)])
        {
            if (!isSquareSafe(pos, sq)) continue;
        }

        make_move(list, pos, Pseudo::CASTLE[Key(pos.turn, move.side)]);
    }
}

inline void Generator::pass(std::vector<Position>& list, const Position& pos)
{
    if (Config::allow_passing) make_move(list, pos, Move());
}

/* ---------------------------------------------------------------------------- */

void Generator::make_move(std::vector<Position>& list, Position pos, const Move move)
{
    /* move piece */
    if (move.from != X)
    {
        place(pos, move.to, pos.pieces[move.from], pos.turn);
        remove(pos, move.from);
    }
    
    /* reset enpassant */
    pos.marked[pos.turn] = X;
    pos.target[pos.turn] = X;

    /* update royal position */
    if (pos.royals[pos.turn] == move.from) pos.royals[pos.turn] = move.to;

    /* handle double push */
    if (move.flag & DoublePush)
    {
        if (pos.pieces[move.midway] == Empty)
        {
            pos.marked[pos.turn] = move.midway;
            pos.target[pos.turn] = move.to;
        }
    }

    /* handle enpassant */
    if (move.flag & Enpassant)
    {
        for (const Color& player: PLAYER::COLOR_LIST)
        {
            if (pos.turn != player && PLAYER::OPPONENT[pos.turn][player])
            {
                if (move.to == pos.marked[player])
                {
                    remove(pos, pos.target[player]);
                }
            }
        }
    } 

    /* handle promotion */
    if (move.flag & Promotion) place(pos, move.to, move.promotion, pos.turn);

    /* handle capture */
    if (pos.pieces[move.to] != Empty)
    {
        if (!Config::any_capture && PLAYER::TEAMMATE[pos.turn][pos.players[move.to]]) return;
    }

    /* handle castle */
    if (move.flag & Castle)
    {
        place(pos, SECURE_SQUARES[], Rook, pos.turn);
        remove(pos, SECURE_SQUARES[]);
    }




    /* handle safty */

    bool check = false;

    for (const Player& player: PLAYERS)
    {
        pos.safty[player] = isSquareSafe(pos, pos.royals[player], player);

        if (isOpponent(pos.turn, player)) check = true;
    }

    if (pos.safty[pos.turn])
    {

    }
}

/* ---------------------------------------------------------------------------- */

inline void Generator::place(Position& pos, const Square& sq, const Piece& piece, const Color& player)
{
    pos.pieces[sq] = piece;
    pos.players[sq] = player;
}

inline void Generator::remove(Position& pos, const Square& sq)
{
    pos.pieces[sq] = Empty;
    pos.players[sq] = None;
}

/* ---------------------------------------------------------------------------- */

inline static countSafty()
{
    for 
}

inline static int attackedByLeap()
{
    int count = 0;
    for (const Offset& offset: LEAP_ATTACK)
    {
        for (const Square& loc: )
        {
            if (PLAYER::OPPONENT[][] && ) count++;
        }
    }

    return count;
}

inline static int attackedBySlide()
{
    int count = 0;
    for (const Offset& offset: LEAP_ATTACK)
    {
        for (const Square& loc: )
        {
            if (pos.pieces[move.to] != Empty)
            {
                if (PLAYER::OPPONENT[][] && ) count++;

                break;
            }
        }
    }

    return count;
}

inline static int attackedByAdvance()
{
    int count = 0;
    for (const Offset& offset: LEAP_ATTACK)
    {
        for (const Square& loc: )
        {
            if (PLAYER::OPPONENT[][] && ) count++;
        }
    }

    return count;
}



inline bool Generator::isSquareSafe(const Position& pos, const Square& sq, const Player& player)
{
    if (Config::capture_the_king) return true;

    /* is attacked by leap */
    for (const Piece& leaper: PIECE_LIST[Leap])
    {
        for (const Move& move: PSEUDO_LEAP_MOVES[encodeLeap(sq, leaper)])
        {
            if (isOpponent(pos.turn, pos.players[move.to]) && pos.pieces[move.to] == leaper) return false;
        }
    }

    /* is attacked by slide */
    for (const Offset& offset: OFFSETS[Slide])
    {
        for (const Move& move: PSEUDO_SLIDE_MOVES[encodeSlide(sq, offset)])
        {
            if (pos.pieces[move.to] != Empty)
            {
                if (isOpponent(pos.turn, pos.players[move.to]) && pos.pieces[move.to] == slider) return false; 

                break;
            }            
        }
    } 

    for (const Piece& slider: PIECE_LIST[Slide])
    {
        for (const Offset& offset: OFFSETS[encodeOffset(Slide, sq, pos.pieces[sq])])
        {
            for (const Move& move: PSEUDO_SLIDE_MOVES[encodeSlide(sq, offset)])
            {
                if (pos.pieces[move.to] != Empty)
                {
                    if (isOpponent(pos.turn, pos.players[move.to]) && pos.pieces[move.to] == slider) return false; 

                    break;
                }
            }
        }
    }

    /* is attacked by advance */
    for (const Player& opponent: OPPONENTS[pos.turn])
    {
        for (const Square& loc: PAWN_ATTACKS[opponent])
        {
            if (isOpponent(pos.turn, pos.players[opponent]) && pos.pieces[loc] == Pawn) return false;
        }
    }

    return true;
}

/* ---------------------------------------------------------------------------- */