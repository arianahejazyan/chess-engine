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

inline static void Generator::leap(std::vector<Position>& list, const Position& pos, const Square& sq)
{
    for (const Move& move: PSEUDO::LEAP[hashSquarePiece(sq, pos.pieces[sq])])
    {
        make_move(list, pos, move);
    }
}

inline static void Generator::slide(std::vector<Position>& list, const Position& pos, const Square& sq)
{
    for (const Ray& ray: PSEUDO::RAY[hashSquarePiece(sq, pos.pieces[sq])])
    {
        for (const Move& move: PSEUDO::SLIDE[hashSquarePieceRay(sq, pos.pieces[sq], ray)])
        {
            make_move(list, pos, move);

            if (pos.pieces[move.to] != Empty) break;
        }
    }
}

inline static void Generator::push(std::vector<Position>& list, const Position& pos, const Square& sq)
{
    for (const Move& move: PSEUDO::PUSH[hashSquarePiecePlayer(sq, pos.pieces[sq], pos.turn)])
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

inline static void Generator::advance(std::vector<Position>& list, const Position& pos, const Square& sq)
{
    for (const Move& move: PSEUDO::ADVANCE[hashSquarePiecePlayer(sq, pos.pieces[sq], pos.turn)])
    {
        if (pos.pieces[move.to] != Empty)
        {
            make_move(list, pos, move);
        }
    }
}

inline static void Generator::enpassant(std::vector<Position>& list, const Position& pos)
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

inline static void Generator::castle(std::vector<Position>& list, const Position& pos)
{
    for (const Side& side: {KingSide, QueenSide})
    {
        /* castle rights */
        if (pos.rights[pos.turn][side] == false) continue;

        /* empty squares */
        for (const Square& sq: PSEUDO::PASSING_SQUARES[hashPlayerSide(pos.turn, side)])
        {
            if (pos.pieces[sq] != Empty) continue;
        }

        /* safe squares */
        for (const Square& sq: PSEUDO::SECURE_SQUARES[hashPlayerSide(pos.turn, side)])
        {
            if (!isSquareSafe(pos, sq)) continue;
        }

        make_move(list, pos, PSEUDO::CASTLE[hashPlayerSide(pos.turn, side)]);
    }
}

inline static void Generator::pass(std::vector<Position>& list, const Position& pos)
{
    if (Config::allow_passing) make_move(list, pos, Move());
}

/* ---------------------------------------------------------------------------- */

static void Generator::make_move(std::vector<Position>& list, const Position& previous, const Move& move)
{
    /* make copy of position */
    Position pos(previous);

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
    pos.safty[pos.turn] = countRoyalChecks(pos, pos.turn);

    if (isRoyalSafe(pos))
    {
        for (const Color& player: PLAYER::OTHERS)
        {
            pos.safty[player] = countRoyalChecks(pos, player);
        }

        list.push_back();
    }
}

/* ---------------------------------------------------------------------------- */

inline static void Generator::place(Position& pos, const Square& sq, const Piece& piece, const Color& player)
{
    pos.pieces[sq] = piece;
    pos.players[sq] = player;
}

inline static void Generator::remove(Position& pos, const Square& sq)
{
    pos.pieces[sq] = Empty;
    pos.players[sq] = None;
}

/* ---------------------------------------------------------------------------- */

inline static bool Generator::isRoyalSafe(const Position& pos)
{
    return Config::capture_the_king || (pos.safty[pos.turn] == 0);
}

inline static bool Generator::isSquareSafe(const Position& pos, const Square& sq)
{
    if (attackedByLeap(pos, sq) != 0) return false;
    if (attackedBySlide(pos, sq) != 0) return false;
    if (attackedByAdvance(pos, sq) != 0) return false;

    return true;
}

inline static unsigned short Generator::countRoyalChecks(Position& pos, const Color& player)
{
    unsigned short count = 0;

    count += attackedByLeap(pos, pos.royals[player]);
    count += attackedBySlide(pos, pos.royals[player]);
    count += attackedByAdvance(pos, pos.royals[player]);

    return count;
}

inline static unsigned short Generator::attackedByLeap(const Position& pos, const Square& sq)
{
    unsigned short count = 0;
    for (const std::pair<Offset, Square>& pair: PSEUDO::LEAP_OFFSETS[sq])
    {
        if (!PLAYER::OPPONENT[pos.turn][pos.players[pair.second]]) continue;

        if (!PSEUDO::VALID_LEAP[pos.pieces[pair.second]][pair.first]) continue;

        count++;
    }

    return count;
}

inline static unsigned short Generator::attackedBySlide(const Position& pos, const Square& sq)
{
    unsigned short count = 0;
    for (const Offset& offset: PSEUDO::SLIDE_OFFSETS[sq])
    {
        for (const Square& loc: PSEUDO::SLIDE_RAY[sq][offset])
        {
            if (pos.pieces[loc] != Empty)
            {
                if (PLAYER::OPPONENT[pos.turn][pos.players[loc]]) break;

                if (PSEUDO::VALID_SLIDE[pos.pieces[loc]][offset]) break;

                count++;
                break;
            }
        }
    }

    return count;
}

inline static unsigned short Generator::attackedByAdvance(const Position& pos, const Square& sq)
{
    unsigned short count = 0;
    for (const Color& opponent: PLAYER::OPPONENT_LIST[pos.turn])
    {
        for (const std::pair<Offset, Square>& pair: PSEUDO::ADVANCE_OFFSETS[sq][opponent])
        {
            if (PLAYER::OPPONENT[pos.turn][pos.players[pair.second]]) continue;

            if (PSEUDO::VALID_ADVANCE[pos.pieces[pair.second]][pair.first]) continue;
            
            count++;
        }
    }

    return count;
}

/* ---------------------------------------------------------------------------- */