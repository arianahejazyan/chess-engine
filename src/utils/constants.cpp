#include "constants.h"

/* ---------------------------------------------------------------------------- */

void INIT_VALID_SQUARES()
{
    for (int sq = 0; sq < CONSTANTS::BOARD_SIZE; sq++)
    {
        if (config.bricks[sq] != Brick)
        {
            CONSTANTS::VALID_SQUARES.push_back(static_cast<Square>(sq));
        }
    }
}

/* ---------------------------------------------------------------------------- */

void CONSTANTS::GENERATE_MOVES()
{
    for (const Square& sq: VALID_SQUARES)
    {
        for (const Piece& piece: PIECE_LIST)
        {
            for (const Direction& dir: PIECE_DIRECTIONS[piece])
            {
                if      (dir.flag & LEAP)   GENERATE_LEAP_MOVES(sq, piece, dir);
                else if (dir.flag & SLIDE)  GENERATE_SLIDE_MOVES(sq, piece, dir);
                else if (dir.flag & PUSH)   GENERATE_PUSH_MOVES(sq, piece, dir);
                else if (dir.flag & ATTACK) GENERATE_ATTACK_MOVES(sq, piece, dir);
                else if (dir.flag & CRAWL)  GENERATE_CRAWL_MOVES(sq, piece, dir);
                else if (dir.flag & HOP)    GENERATE_HOP_MOVES(sq, piece, dir);
            }
        }
    }

    GENERATE_CASTLE_MOVES();
}

void CONSTANTS::GENERATE_LEAP_MOVES(const Square& sq, const Piece& piece, const Direction& dir)
{
    if (isValidSquare(static_cast<Square>(sq + dir.offset)))
    {
        CONSTANTS::LEAP_MOVES[sq | (piece << SQUARE_SIZE)].push_back(encode_move(sq, static_cast<Square>(sq + dir.offset)));
    }
}

void CONSTANTS::GENERATE_SLIDE_MOVES(const Square& sq, const Piece& piece, const Direction& dir)
{
    Square loc = static_cast<Square>(sq + dir.offset);

    while (isValidSquare(loc))
    {
        CONSTANTS::SLIDE_MOVES[sq | (dir.offset << SQUARE_SIZE)].push_back(encode_move(sq, loc));

        loc = static_cast<Square>(loc + dir.offset);
    }
}

void CONSTANTS::GENERATE_PUSH_MOVES(const Square& sq, const Piece& piece, const Direction& dir)
{
    if (isValidSquare(static_cast<Square>(sq + dir.offset)))     
    {
        GENERATE_PROMOTION_MOVES(sq, static_cast<Square>(sq + dir.offset), dir.player, PUSH);
        
        if (isHomeRankSquare(sq, dir.player) && isValidSquare(static_cast<Square>(sq + 2 *  CONSTANTS::PAWN_PUSH[player])))
        {
            GENERATE_PROMOTION_MOVES(sq, static_cast<Square>(sq + 2 *  CONSTANTS::PAWN_PUSH[player]), player, DOUBLEPUSH);
        }
    }
}

void CONSTANTS::GENERATE_ATTACK_MOVES(const Square& sq, const Piece& piece, const Direction& dir)
{
    if (isValidSquare(static_cast<Square>(sq + dir.offset)))     
    {
        GENERATE_PROMOTION_MOVES(sq, static_cast<Square>(sq + dir.offset), dir.player, static_cast<Flag>(ATTACK ^ CAPTURE));
    }
}

void CONSTANTS::GENERATE_CRAWL_MOVES(const Square& sq, const Piece& piece, const Direction& dir)
{

}

void CONSTANTS::GENERATE_HOP_MOVES(const Square& sq, const Piece& piece, const Direction& dir)
{

}

void CONSTANTS::GENERATE_CASTLE_MOVES()
{

}

void CONSTANTS::GENERATE_PROMOTION_MOVES(const Square& sq, const Square& loc, const Color& player, const Flag& flag)
{
    if (isPromotionSquare(loc, player))
    {
        for (const Piece& promotion: config.promotion_list)
        {
            CONSTANTS::PAWN_MOVES[sq | (flag << SQUARE_SIZE) | (player << FLAG_SIZE)].push_back(encode_move(sq, loc, static_cast<Flag>(flag ^ PROMOTION), promotion));
        }
    }

    else
    {
        CONSTANTS::PAWN_MOVES[sq | (flag << SQUARE_SIZE) | (player << FLAG_SIZE)].push_back(encode_move(sq, loc, flag));
    }
}

/* ---------------------------------------------------------------------------- */

void CONSTANTS::INIT_PIECE_DIRECTIONS()
{
    PIECE_DIRECTIONS[King] = {
        Direction(U, LEAP),
        Direction(D, LEAP),
        Direction(R, LEAP),
        Direction(L, LEAP),
        Direction(U + R, LEAP),
        Direction(U + L, LEAP),
        Direction(D + R, LEAP),
        Direction(D + L, LEAP),
    };

    /* ---------------------------------------------------------------------------- */

    PIECE_DIRECTIONS[Queen] = {
        Direction(U, SLIDE),
        Direction(D, SLIDE),
        Direction(R, SLIDE),
        Direction(L, SLIDE),
        Direction(U + R, SLIDE),
        Direction(U + L, SLIDE),
        Direction(D + R, SLIDE),
        Direction(D + L, SLIDE),
    };
    
    /* ---------------------------------------------------------------------------- */


}