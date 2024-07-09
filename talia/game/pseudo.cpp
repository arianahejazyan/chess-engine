#include "pseudo.h"
#include "config.h"

/* ---------------------------------------------------------------------------- */

void PSEUDO::init()
{
    for (const Square& sq: BOARD::VALID_SQUARES)
    {
        for (const Piece& piece: PIECE::PIECE_LIST)
        {
            for (const Direction& dir: PIECE::DIRECTIONS[piece])
            {
                switch (dir.flag)
                {
                    case (Leap):     leap(sq, piece, dir);     break;
                    case (Slide):    slide(sq, piece, dir);    break;
                    case (Push):     push(sq, piece, dir);     break;
                    case (Advance):  advance(sq, piece, dir);  break;

                    default: break;
                }
            }
        }
    }

    PSEUDO::castle();
}

/* ---------------------------------------------------------------------------- */

inline static void PSEUDO::leap(const Square& sq, const Piece& piece, const Direction& dir)
{
    if (BOARD::isValidSquare(Rank(sq) + dir.rank, File(sq) + dir.file))
    {
        Move move;
        move.from = sq;
        move.to = Tile(Rank(sq) + dir.rank, File(sq) + dir.file);
        move.piece = piece;
        move.flag = Leap;

        LEAP[Key(sq, piece)].push_back(move);
    }
}

inline static void PSEUDO::slide(const Square& sq, const Piece& piece, const Direction& dir)
{
    int count = 1;
    while (BOARD::isValidSquare(Rank(sq) + count * dir.rank, File(sq) + count * dir.file))
    {
        Move move;
        move.from = sq;
        move.to = Tile(Rank(sq) + dir.rank, File(sq) + dir.file);
        move.piece = piece;
        move.flag = Slide;

        SLIDE[Key(sq, piece, dir.rank, dir.file)].push_back(move);

        count++;
    }
}

inline static void PSEUDO::push(const Square& sq, const Piece& piece, const Direction& dir)
{
    if (BOARD::isValidSquare(Rank(sq) + dir.rank, File(sq) + dir.file))
    {
        Square midway = Tile(Rank(sq) + dir.rank, File(sq) + dir.file);

        promote(sq, midway, X, piece, dir, Push, PUSH);

        if (BOARD::isValidSquare(Rank(sq) + 2 * dir.rank, File(sq) + 2 * dir.file))
        {
            Square loc = Tile(Rank(sq) + 2 * dir.rank, File(sq) + 2 * dir.file);

            if (BOARD::isHomeRankSquare(sq, dir.player))
            {
                promote(sq, loc, midway, piece, dir, DoublePush, PUSH);
            }
        }
    }
}

inline static void PSEUDO::advance(const Square& sq, const Piece& piece, const Direction& dir)
{
    if (BOARD::isValidSquare(Rank(sq) + dir.rank, File(sq) + dir.file))
    {
        Square loc = Tile(Rank(sq) + dir.rank, File(sq) + dir.file);

        promote(sq, loc, X, piece, dir, Advance, ADVANCE);
    }
}

inline static void PSEUDO::promote(const Square& sq, const Square& loc, const Square& midway, const Piece& piece, const Direction& dir, const Flag& flag, std::unordered_map<Key, std::vector<Move>>& TABLE)
{
    if (BOARD::isPromotionSquare(loc, dir.player))
    {
        for (const Piece& promote: PIECE::PROMOTION_LIST)
        {
            Move move;
            move.from = sq;
            move.to = loc;
            move.midway = midway;
            move.piece = piece;
            move.player = dir.player;
            move.promotion = promote;
            move.flag = static_cast<Flag>(flag ^ Promotion);

            TABLE[Key(sq, piece, dir.player)].push_back(move);
        }
    }

    else
    {
        Move move;
        move.from = sq;
        move.to = loc;
        move.midway = midway;
        move.piece = piece;
        move.player = dir.player;
        move.flag = flag;

        TABLE[Key(sq, piece, dir.player)].push_back(move);
    }
}

inline static void PSEUDO::castle()
{
    
}

/* ---------------------------------------------------------------------------- */