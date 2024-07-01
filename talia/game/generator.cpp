#include "generator.h"
#include "pseudo.h"
#include "config.h"

/* ---------------------------------------------------------------------------- */

void GENERATOR::generate_all_positions(std::vector<Position>& list, const Position& pos)
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

    castle(list, pos);

    pass(list, pos);
}

/* ---------------------------------------------------------------------------- */

inline static void GENERATOR::leap(std::vector<Position>& list, const Position& pos, const Square& sq)
{
    for (const Move& move: PSEUDO::LEAP[hashSquarePiece(sq, pos.pieces[sq])])
    {
        make_move(list, pos, move);
    }
}

inline static void GENERATOR::slide(std::vector<Position>& list, const Position& pos, const Square& sq)
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

inline static void GENERATOR::push(std::vector<Position>& list, const Position& pos, const Square& sq)
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

        else
        {
            enpassant(list, pos, sq, move.to);
        }
    }
}

inline static void GENERATOR::enpassant(std::vector<Position>& list, const Position& pos, const Square& sq, const Square& loc)
{
    for (const Color& player: PLAYER::OTHERS[pos.turn])
    {
        if (pos.marked[player] != loc) continue;

        if (!(Config::any_capture || PLAYER::OPPONENT[pos.turn][pos.players[loc]])) continue;

        make_move(list, pos, move);

        break;
    }
}

inline static void GENERATOR::castle(std::vector<Position>& list, const Position& pos)
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

inline static void GENERATOR::pass(std::vector<Position>& list, const Position& pos)
{
    if (Config::allow_passing) make_move(list, pos, Move());
}

/* ---------------------------------------------------------------------------- */

static void GENERATOR::make_move(std::vector<Position>& list, const Position& previous, const Move& move)
{
    /* make copy of position */
    Position pos(previous);

    /* move piece */
    if (move.from != X)
    {
        place(pos, move.to, pos.pieces[move.from], pos.turn);
        remove(pos, move.from);
    }
    
    /* update royal position */
    if (pos.royals[pos.turn] == move.from) pos.royals[pos.turn] = move.to;

    /* handle double push */
    if (move.flag & DoublePush)
    {
        pos.marked[pos.turn] = move.midway;
        pos.target[pos.turn] = move.to;
    }
    
    /* reset enpassant */
    else
    {
        pos.marked[pos.turn] = X;
        pos.target[pos.turn] = X;
    }

    /* handle enpassant */
    if (move.flag & Enpassant)
    {
        for (const Color& player: PLAYER::OTHERS[pos.turn])
        {
            if (pos.marked[player] != move.to) continue;

            if (!(Config::any_capture || PLAYER::OPPONENT[pos.turn][pos.players[move.to]])) continue;

            remove(pos, pos.target[player]);
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
        for (const Color& player: PLAYER::OTHERS[pos.turn])
        {
            pos.safty[player] = countRoyalChecks(pos, player);
        }

        list.push_back();
    }
}

/* ---------------------------------------------------------------------------- */

inline static void GENERATOR::place(Position& pos, const Square& sq, const Piece& piece, const Color& player)
{
    pos.pieces[sq] = piece;
    pos.players[sq] = player;
}

inline static void GENERATOR::remove(Position& pos, const Square& sq)
{
    pos.pieces[sq] = Empty;
    pos.players[sq] = None;
}

/* ---------------------------------------------------------------------------- */

inline static bool GENERATOR::isRoyalSafe(const Position& pos)
{
    return Config::capture_the_king || (pos.safty[pos.turn] == 0);
}

inline static bool GENERATOR::isSquareSafe(const Position& pos, const Square& sq)
{
    if (attackedByLeap(pos, sq) != 0) return false;
    if (attackedBySlide(pos, sq) != 0) return false;
    if (attackedByAdvance(pos, sq) != 0) return false;

    return true;
}

inline static unsigned short GENERATOR::countRoyalChecks(Position& pos, const Color& player)
{
    unsigned short count = 0;

    count += attackedByLeap(pos, pos.royals[player]);
    count += attackedBySlide(pos, pos.royals[player]);
    count += attackedByAdvance(pos, pos.royals[player]);

    return count;
}

inline static unsigned short GENERATOR::attackedByLeap(const Position& pos, const Square& sq)
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

inline static unsigned short GENERATOR::attackedBySlide(const Position& pos, const Square& sq)
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

inline static unsigned short GENERATOR::attackedByAdvance(const Position& pos, const Square& sq)
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