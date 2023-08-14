#include "board.h"

MoveList Board::getAllMoves()
{
    MoveList move_list;
    int piece, player, key;

    for (int square = 0; square < 196; square++) {

        piece = Pieces[square];
        
        player = Players[square];

        if (piece == invalid || piece == empty)
        {
            continue;
        }

        if (player != Turn)
        {
            continue;
        }

        switch (piece)
        {
            case (Pawn):
                
                key = PawnKey(square);
                move_list.add_pawn_moves(PawnMoves[square][player][key]);
                break;
            
            case (Knight):
                
                key = KnightKey(square);
                move_list.add_knight_moves(KnightMoves[square][key]);
                break;

            case (Bishop):
                
                key = BishopKey(square);
                move_list.add_knight_moves(BishopMoves[square][key]);
                break;
            
            case (Rook):
                
                key = RookKey(square);
                move_list.add_knight_moves(RookMoves[square][key]);
                break;

            case (Queen):
                            
                key = QueenKey(square);
                move_list.add_knight_moves(QueenMoves[square][key]);
                break;

            case (King):
                
                key = KingKey(square);
                move_list.add_knight_moves(KingMoves[square][key]);
                break;
        }
    }
}

bool Board::makeMove(const int& move)
{
    // parse move
    int source = get_source(move);
    int target = get_target(move);
    int flag   = get_flag(move);

    if (Pieces[target] != (empty || invalid)) bool Capture = true;

    int piece  = Pieces[source];
    int player = Players[source];

    placePiece(target, piece, player);
    removePiece(source);

    // reset enpassant
    Enpassant[player] = -1;

    // update king positions 
    if (Royals[player] == source) Royals[player] = target;

    // check special moves
    if (flag)
    {
        switch (flag & 0b11)
        {
            case (doublePush):

                Enpassant[player] = flag >> 2;

                break;

            case (Castle):

                CastleInfo Info;

                auto index = Info.UpdateRooks[player][flag >> 2];

                placePiece(index[0], Rook, player);
                removePiece(index[1]);

                break;

            case (enpassant):

                removePiece(flag >> 2);

                break;

            case (Promotion):

                placePiece(target, flag >> 2, player);

                break;
        }
    }

    // update castle rights
    CastleRights &= castle_rights[source];
    CastleRights &= castle_rights[target];

    // check if the king is not under attack
    if (isKingChecked(player)) return false;

    return true;
}

void Board::placePiece(const int& square, const int& piece, const int& player)
{
    Pieces[square] = piece;
    Players[square] = player;
}

void Board::removePiece(const int& square)
{
    Pieces[square] = empty;
    Players[square] = none;
}

bool Board::isOpponentsPiece(const int& square, const int& player)
{
    return (player == (Red || Yellow)) ? (Players[square] == (Blue || Green)): (Players[square] == (Red || Yellow));
}

bool Board::isSquareAttacked(const int& square, const int& player)
{
    // Rook and Queen
    for (const auto &direction: RookRelevantSquares[square])
    {
        for (int location: direction)
        {
            if (Pieces[location] != empty)
            {
                if (isOpponentsPiece(location, Turn) && Pieces[location] == (Rook || Queen)) return true;

                break;
            }
        }
    }

    // Bishop and Queen
    for (const auto &direction: BishopRelevantSquares[square])
    {
        for (int location: direction)
        {
            if (Pieces[location] != empty)
            {
                if (isOpponentsPiece(location, Turn) && Pieces[location] == (Bishop || Queen)) return true;

                break;
            }
        }
    }

    // Knight
    for (int location: KnightRelevantSquares[square])
    {
        if (Pieces[location] != empty && isOpponentsPiece(location, Turn) && Pieces[location] == Knight) return true;
    }

    // King
    for (int location: KingRelevantSquares[square])
    {   
        if (Pieces[location] != empty && isOpponentsPiece(location, Turn) && Pieces[location] == King) return true;
    }

    // Pawn
    switch (player)
    {
        case (Red):
            
            if (Pieces[square + UpRight]   == Pawn && Players[square + UpRight]   == Green) return true;
            if (Pieces[square + DownRight] == Pawn && Players[square + DownRight] == Green) return true;
            if (Pieces[square + DownLeft]  == Pawn && Players[square + DownLeft]  == Blue)  return true;
            if (Pieces[square + UpLeft]    == Pawn && Players[square + UpLeft]    == Blue)  return true;

            break;
 
        case (Blue):
            
            if (Pieces[square + UpRight]   == Pawn && Players[square + UpRight]   == Yellow) return true;
            if (Pieces[square + DownRight] == Pawn && Players[square + DownRight] == Red)    return true;
            if (Pieces[square + DownLeft]  == Pawn && Players[square + DownLeft]  == Red)    return true;
            if (Pieces[square + UpLeft]    == Pawn && Players[square + UpLeft]    == Yellow) return true;

            break;
        
        case (Yellow):
            
            if (Pieces[square + UpRight]   == Pawn && Players[square + UpRight]   == Green) return true;
            if (Pieces[square + DownRight] == Pawn && Players[square + DownRight] == Green) return true;
            if (Pieces[square + DownLeft]  == Pawn && Players[square + DownLeft]  == Blue)  return true;
            if (Pieces[square + UpLeft]    == Pawn && Players[square + UpLeft]    == Blue)  return true;

            break;

        case (Green):
            
            if (Pieces[square + UpRight]   == Pawn && Players[square + UpRight]   == Yellow) return true;
            if (Pieces[square + DownRight] == Pawn && Players[square + DownRight] == Red)    return true;
            if (Pieces[square + DownLeft]  == Pawn && Players[square + DownLeft]  == Red)    return true;
            if (Pieces[square + UpLeft]    == Pawn && Players[square + UpLeft]    == Yellow) return true;

            break;
    }

    return false;
}

int Board::PawnKey(const int& square)
{
    int key = 0,
        push, 
        doublePush, 
        captureRight, 
        captureLeft,
        rightEnpass,
        leftEnpass,
        notMoved;

    switch (Turn)
    {
        case (Red):

            push         = square + Up; 
            doublePush   = square + UpUp; 
            captureRight = square + UpRight; 
            captureLeft  = square + UpLeft;
            rightEnpass  = Green;
            leftEnpass   = Blue;
            notMoved     = rank(square) == 1;

            break;

        case (Blue):

            push         = square + Right; 
            doublePush   = square + RightRight; 
            captureRight = square + DownRight; 
            captureLeft  = square + UpRight;
            rightEnpass  = Red;
            leftEnpass   = Yellow;
            notMoved     = file(square) == 1;

            break;

        case (Yellow):

            push         = square + Down; 
            doublePush   = square + DownDown; 
            captureRight = square + DownLeft; 
            captureLeft  = square + DownRight;
            rightEnpass  = Blue;
            leftEnpass   = Green;
            notMoved     = rank(square) == 12;

            break;

        case (Green):

            push         = square + Left; 
            doublePush   = square + LeftLeft; 
            captureRight = square + UpLeft; 
            captureLeft  = square + DownLeft;
            rightEnpass  = Yellow;
            leftEnpass   = Red;
            notMoved     = file(square) == 12;

            break;
    }

    if (Pieces[push] == empty)
    {
        key ^= 1;

        if (notMoved && Pieces[doublePush] == empty)
        {
            key ^= 1 << 1;
        }
    }

    if (Pieces[captureRight] != empty && isOpponentsPiece(captureRight, Turn)) key ^= 1 << 2; 

    if (Pieces[captureLeft] != empty && isOpponentsPiece(captureLeft, Turn)) key ^= 1 << 3; 

    if (Enpassant[rightEnpass] == captureRight) key ^= 1 << 4;

    if (Enpassant[leftEnpass] == captureLeft) key ^= 1 << 5;

    return key;
}

bool Board::isKingChecked(const int& player)
{
    return isSquareAttacked(Royals[player], player);
}

int Board::KnightKey(const int& square)
{
    int key = 0, shift = 0;

    for (const int &location: KnightRelevantSquares[square])
    {
        if (Pieces[location] != empty && !isOpponentsPiece(square, Turn)) key ^= 1 << shift;

        shift++;
    }

    return key;
}

int Board::KingKey(const int& square)
{
    int key = 0, shift = 0, KingSide, QueenSide; 
    
    bool isShortPathEmpty, isLongPathEmpty;

    for (const int &location: KingRelevantSquares[square])
    {
        if (Pieces[location] != empty && !isOpponentsPiece(square, Turn)) key ^= 1 << shift;

        shift++;
    }

    CastleInfo Info;

    KingSide  = CastleRights & Info.Rights[Turn][0];
    QueenSide = CastleRights & Info.Rights[Turn][1];

    isShortPathEmpty = Pieces[Info.PassingSquares[Turn][3]] == empty && 
                       Pieces[Info.PassingSquares[Turn][4]] == empty;

    isLongPathEmpty  = Pieces[Info.PassingSquares[Turn][0]] == empty &&
                       Pieces[Info.PassingSquares[Turn][1]] == empty &&
                       Pieces[Info.PassingSquares[Turn][2]] == empty;

    if (KingSide && isShortPathEmpty && isKingChecked(Turn) && isSquareAttacked(Info.PassingSquares[Turn][3], Turn)) key ^= 1 << 8;

    if (QueenSide && isLongPathEmpty && isKingChecked(Turn) && isSquareAttacked(Info.PassingSquares[Turn][2], Turn)) key ^= 1 << 9;

    return key;
}

int Board::BishopKey(const int& square)
{   
    int key = 0, shift = 0;

    for (const auto &direction: BishopRelevantSquares[square])
    {
        for (int location: direction)
        {
            if (Pieces[location] != empty) 
            {
                if (isOpponentsPiece(location, Turn)) key ^= 1 << shift;

                break;
            }

            shift++;
        }
    }

    return key;
}

int Board::RookKey(const int& square)
{   
    int key = 0, shift = 0;

    for (const auto &direction: RookRelevantSquares[square])
    {
        for (int location: direction)
        {
            if (Pieces[location] != empty) 
            {
                if (isOpponentsPiece(location, Turn)) key ^= 1 << shift;

                break;
            }

            shift++;
        }
    }

    return key;
}

int Board::QueenKey(const int& square)
{   
    int key = 0, shift = 0;

    for (const auto &direction: QueenRelevantSquares[square])
    {
        for (int location: direction)
        {
            if (Pieces[location] != empty) 
            {
                if (isOpponentsPiece(location, Turn)) key ^= 1 << shift;

                break;
            }

            shift++;
        }
    }

    return key;
}