#include "pseudo.h"
#include "config.h"

/* ---------------------------------------------------------------------------- */

void PSEUDO::allocate()
{
    for (const Square& sq: BOARD::VALID_SQUARES)
    {
        for (const Piece& piece: PIECE::PIECE_LIST)
        {
            // allocate leap //
            if (OFFSET::CAN_LEAP(piece))
            {
                LEAP[hashSquarePiece(sq, piece)] = std::vector<Move>();
            }

            // allocate slide //
            for (const Ray& ray: PSEUDO::RAY[hashSquarePiece(sq, piece)])
            {
                SLIDE[hashSquarePieceRay(sq, piece, ray)] = std::vector<Move>();
            }

            // allocate push and advance //
            for (const Color& player: PLAYER::COLOR_LIST)
            {
                PUSH[hashSquarePiecePlayer(sq, piece, player)] = std::vector<Move>();
                ADVANCE[hashSquarePiecePlayer(sq, piece, player)] = std::vector<Move>();
                ENPASSANT[hashSquarePiecePlayer(sq, piece, player)] = std::vector<Move>();
            }
        }
    }

    // allocate castle //
}

void PSEUDO::deallocate()
{
    for (const Square& sq: BOARD::VALID_SQUARES)
    {
        for (const Piece& piece: PIECE::PIECE_LIST)
        {
            
        }
    }
}

void PSEUDO::initialize()
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
                    case (SideWays): push(sq, piece, dir);     break;
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
    const Square loc = tile(row(sq) + dir.rank, col(sq) + dir.file);

    if (BOARD::isValidSquare(loc))
    {
        Move* move = new Move(sq, loc, piece, Leap);

        LEAP[hashSquarePiece(sq, piece)].push_back(*move);
    }
}

inline static void PSEUDO::slide(const Square& sq, const Piece& piece, const Direction& dir)
{
    Square loc = tile(row(sq) + dir.rank, col(sq) + dir.file);

    while (BOARD::isValidSquare(loc))
    {
        Move* move = new Move(sq, loc, piece, Slide);

        SLIDE[hashSquarePieceRay(sq, piece, tile(dir.rank, dir.file))].push_back(*move);

        loc = tile(row(loc) + dir.rank, col(loc) + dir.file);
    }
}

inline static void PSEUDO::push(const Square& sq, const Piece& piece, const Direction& dir)
{
    const Square midway = tile(row(sq) + dir.rank, col(sq) + dir.file);

    if (BOARD::isValidSquare(midway))
    {
        promote(sq, midway, X, piece, dir, Push, PUSH);

        if (dir.flag & Push)
        {
            const Square target = tile(row(sq) + 2 * dir.rank, col(sq) + 2 * dir.file);

            if (BOARD::isValidSquare(target) && (CONFIG::torpedo || BOARD::isHomeRankSquare(sq, dir.player)))
            {
                promote(sq, target, midway, piece, dir, DoublePush, PUSH);
            }
        }
    }
}

inline static void PSEUDO::advance(const Square& sq, const Piece& piece, const Direction& dir)
{
    const Square loc = tile(row(sq) + dir.rank, col(sq) + dir.file);

    if (BOARD::isValidSquare(loc) && CONFIG::enpassant)
    {
        promote(sq, loc, X, piece, dir, Advance, ADVANCE);
        promote(sq, loc, X, piece, dir, Enpassant, ENPASSANT);
    }
}

inline static void PSEUDO::promote(const Square& sq, const Square& loc, const Square& marked, const Piece& piece, const Direction& dir, const Flag& flag, std::unordered_map<Key, std::vector<Move>>& TABLE)
{
    if (BOARD::isPromotionSquare(loc, dir.player))
    {
        for (const Piece& promote: PIECE::PROMOTION_LIST)
        {
            Move* move = new Move(sq, loc, piece, dir.player, promote, marked, static_cast<Flag>(flag ^ Promotion));

            TABLE[hashSquarePiecePlayer(sq, piece, dir.player)].push_back(*move);
        }
    }

    else
    {
        Move* move = new Move(sq, loc, piece, dir.player, Empty, marked, flag);

        TABLE[hashSquarePiecePlayer(sq, piece, dir.player)].push_back(*move);
    }
}

inline static void PSEUDO::castle()
{
    
}

/* ---------------------------------------------------------------------------- */