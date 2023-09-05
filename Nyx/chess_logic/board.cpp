#include "board.h"

Move encode_move(Square from, Square to, bool capture, Flag flag, Piece promotion=empty, Square enpass=X, int side=0)
{
    Move move;

    move.from = from;
    move.to = to;
    move.capture = capture;
    move.flag = flag;
    move.enpass = enpass;
    move.side = side;

    return move;
}

void Board::GenerateAllMoves()
{
    int piece, player;

    for (int square = 0; square < 196; square++) {

        piece = position.Pieces[square];
        
        player = position.Players[square];

        if (piece == block || piece == empty)
        {
            continue;
        }

        if (player != position.Turn)
        {
            continue;
        }

        switch (piece)
        {
            case (Pawn):
                
                GeneratePawnMoves(static_cast<Square>(square));
                break;
            
            case (Knight):
                
                GenerateKnightMoves(static_cast<Square>(square));
                break;

            case (Bishop):
                
                GenerateBishopMoves(static_cast<Square>(square));
                break;
            
            case (Rook):
                
                GenerateRookMoves(static_cast<Square>(square));
                break;

            case (Queen):
                            
                GenerateQueenMoves(static_cast<Square>(square));
                break;

            case (King):
                
                GenerateKingMoves(static_cast<Square>(square));
                break;
        }
    }
}

bool Board::makeMove(const Move& move)
{
    Piece piece  = position.Pieces[move.from];
    Player player = position.Players[move.from];

    placePiece(move.to, piece, player);
    removePiece(move.from);

    // reset enpassant
    position.En_passant[player] = X;

    // update king positions 
    if (position.Royals[player] == move.from) position.Royals[player] = move.to;

    // check special moves
    switch (move.flag)
    {
        case (DoublePush):

            int diff = (move.to - move.from)/2;

            position.En_passant[player] = static_cast<Square>(move.from + diff);

            break;

        case (Castle):

            Square PlaceSquare  = UpdateRooks[player][move.side][0];
            Square RemoveSquare = UpdateRooks[player][move.side][1];

            placePiece(PlaceSquare, Rook, player);
            removePiece(RemoveSquare);

            break;

        case (Enpassant):

            removePiece(move.enpass);

            break;

        case (Promotion):

            placePiece(move.to, move.promotion, player);

            break;
    }

    // update castle rights
    position.CastleRights &= castle_rights[source];
    position.CastleRights &= castle_rights[target];

    // check if the king is not under attack
    if (isKingChecked(player)) return false;

    return true;
}

/***************************************\
    
          Board utility methods
                          
\***************************************/

void Board::placePiece(const Square& square, const Piece& piece, const Player& player)
{
    position.Pieces[square] = piece;
    position.Players[square] = player;
}

void Board::removePiece(const Square& square)
{
    position.Pieces[square] = empty;
    position.Players[square] = none;
}

bool Board::isOpponentsPiece(const Square& square, const Player& player)
{
    return (player == (Red || Yellow)) ? (position.Players[square] == (Blue || Green)): (position.Players[square] == (Red || Yellow));
}

bool Board::isSquareAttacked(const Square& square, const Player& player)
{
    // Rook and Queen
    for (const auto &direction: RookRelevantSquares[square])
    {
        for (Square location: direction)
        {
            if (position.Pieces[location] != empty)
            {
                if (isOpponentsPiece(location, position.Turn) && position.Pieces[location] == (Rook || Queen)) return true;

                break;
            }
        }
    }

    // Bishop and Queen
    for (const auto &direction: BishopRelevantSquares[square])
    {
        for (Square location: direction)
        {
            if (position.Pieces[location] != empty)
            {
                if (isOpponentsPiece(location, position.Turn) && position.Pieces[location] == (Bishop || Queen)) return true;

                break;
            }
        }
    }

    // Knight
    for (Square location: KnightRelevantSquares[square])
    {
        if (position.Pieces[location] != empty && isOpponentsPiece(location, position.Turn) && position.Pieces[location] == Knight) return true;
    }

    // King
    for (Square location: KingRelevantSquares[square])
    {   
        if (position.Pieces[location] != empty && isOpponentsPiece(location, position.Turn) && position.Pieces[location] == King) return true;
    }

    // Pawn
    switch (player)
    {
        case (Red):
            
            if (position.Pieces[square + UpRight]   == Pawn && position.Players[square + UpRight]   == Green) return true;
            if (position.Pieces[square + DownRight] == Pawn && position.Players[square + DownRight] == Green) return true;
            if (position.Pieces[square + DownLeft]  == Pawn && position.Players[square + DownLeft]  == Blue)  return true;
            if (position.Pieces[square + UpLeft]    == Pawn && position.Players[square + UpLeft]    == Blue)  return true;

            break;
 
        case (Blue):
            
            if (position.Pieces[square + UpRight]   == Pawn && position.Players[square + UpRight]   == Yellow) return true;
            if (position.Pieces[square + DownRight] == Pawn && position.Players[square + DownRight] == Red)    return true;
            if (position.Pieces[square + DownLeft]  == Pawn && position.Players[square + DownLeft]  == Red)    return true;
            if (position.Pieces[square + UpLeft]    == Pawn && position.Players[square + UpLeft]    == Yellow) return true;

            break;
        
        case (Yellow):
            
            if (position.Pieces[square + UpRight]   == Pawn && position.Players[square + UpRight]   == Green) return true;
            if (position.Pieces[square + DownRight] == Pawn && position.Players[square + DownRight] == Green) return true;
            if (position.Pieces[square + DownLeft]  == Pawn && position.Players[square + DownLeft]  == Blue)  return true;
            if (position.Pieces[square + UpLeft]    == Pawn && position.Players[square + UpLeft]    == Blue)  return true;

            break;

        case (Green):
            
            if (position.Pieces[square + UpRight]   == Pawn && position.Players[square + UpRight]   == Yellow) return true;
            if (position.Pieces[square + DownRight] == Pawn && position.Players[square + DownRight] == Red)    return true;
            if (position.Pieces[square + DownLeft]  == Pawn && position.Players[square + DownLeft]  == Red)    return true;
            if (position.Pieces[square + UpLeft]    == Pawn && position.Players[square + UpLeft]    == Yellow) return true;

            break;
    }

    return false;
}

bool Board::isKingChecked(const Player& player)
{
    return isSquareAttacked(position.Royals[player], player);
}

/***************************************\
    
      Handling sliding pieces logic
                          
\***************************************/

void Board::GenerateCrawlingMoves(std::vector<Square> RelevantSquares[196], const Square& square)
{
    for (const Square &location: KnightRelevantSquares[square])
    {
        if (position.Pieces[location] != empty)
        {
            if (isOpponentsPiece(square, position.Turn)) moveList.QuietMoves.push_back(encode_move(square, location, true, null));

            continue;
        }

        moveList.Captures.push_back(encode_move(square, location, false, null));
    }
}

void Board::GenerateCastlingMoves(const Square& square)
{
    bool KingSide, QueenSide, isShortPathEmpty, isLongPathEmpty;

    KingSide  = (position.CastleRights[position.Turn] == (Both | Short));
    QueenSide = (position.CastleRights[position.Turn] == (Both | Long));

    isShortPathEmpty = position.Pieces[PassingSquares[position.Turn][0]] == empty && 
                       position.Pieces[PassingSquares[position.Turn][1]] == empty;

    isLongPathEmpty  = position.Pieces[PassingSquares[position.Turn][2]] == empty &&
                       position.Pieces[PassingSquares[position.Turn][3]] == empty &&
                       position.Pieces[PassingSquares[position.Turn][4]] == empty;

    if (KingSide && isShortPathEmpty && isKingChecked(position.Turn) && isSquareAttacked(PassingSquares[position.Turn][0], position.Turn)) 
    {
        moveList.QuietMoves.push_back(encode_move(square, PassingSquares[position.Turn][1], true, Castle, empty, X, 0));
    }    
        
    if (QueenSide && isLongPathEmpty && isKingChecked(position.Turn) && isSquareAttacked(PassingSquares[position.Turn][2], position.Turn)) 
    {
       moveList.QuietMoves.push_back(encode_move(square, PassingSquares[position.Turn][3], true, Castle, empty, X, 1)); 
    }

}

void Board::GeneratePawnMoves(const Square& square)
{
    Player rightEnpass, leftEnpass;
        
    Square push,
           doublePush,
           captureRight, 
           captureLeft;
    
    bool notMoved;

    switch (position.Turn)
    {
        case (Red):

            push         = static_cast<Square>(square + Up); 
            doublePush   = static_cast<Square>(square + UpUp); 
            captureRight = static_cast<Square>(square + UpRight); 
            captureLeft  = static_cast<Square>(square + UpLeft);
            rightEnpass  = Green;
            leftEnpass   = Blue;
            notMoved     = rank(square) == 1;

            break;

        case (Blue):

            push         = static_cast<Square>(square + Right); 
            doublePush   = static_cast<Square>(square + RightRight); 
            captureRight = static_cast<Square>(square + DownRight); 
            captureLeft  = static_cast<Square>(square + UpRight);
            rightEnpass  = Red;
            leftEnpass   = Yellow;
            notMoved     = file(square) == 1;

            break;

        case (Yellow):

            push         = static_cast<Square>(square + Down); 
            doublePush   = static_cast<Square>(square + DownDown); 
            captureRight = static_cast<Square>(square + DownLeft); 
            captureLeft  = static_cast<Square>(square + DownRight);
            rightEnpass  = Blue;
            leftEnpass   = Green;
            notMoved     = rank(square) == 12;

            break;

        case (Green):

            push         = static_cast<Square>(square + Left); 
            doublePush   = static_cast<Square>(square + LeftLeft); 
            captureRight = static_cast<Square>(square + UpLeft); 
            captureLeft  = static_cast<Square>(square + DownLeft);
            rightEnpass  = Yellow;
            leftEnpass   = Red;
            notMoved     = file(square) == 12;

            break;
    }

    if (position.Pieces[push] == empty)
    {
        if (PromotionRank == (position.Turn == (Red || Yellow)) ? rank(square): file(square))
        {
            moveList.QuietMoves.push_back(encode_move(square, push, false, null)); 
        }
        else
        {
            moveList.QuietMoves.push_back(encode_move(square, push, false, null, Knight));
            moveList.QuietMoves.push_back(encode_move(square, push, false, null, Bishop)); 
            moveList.QuietMoves.push_back(encode_move(square, push, false, null, Rook)); 
            moveList.QuietMoves.push_back(encode_move(square, push, false, null, Queen)); 
        }

        if (notMoved && position.Pieces[doublePush] == empty)
        {
            moveList.QuietMoves.push_back(encode_move(square, doublePush, false, DoublePush)); 
        }
    }

    if (position.Pieces[captureRight] != empty && isOpponentsPiece(captureRight, position.Turn)) 
    {
        moveList.Captures.push_back(encode_move(square, captureRight, true, null)); 
    }
    
    if (position.Pieces[captureLeft] != empty && isOpponentsPiece(captureLeft, position.Turn)) 
    {
        moveList.Captures.push_back(encode_move(square, captureLeft, true, null));
    }

    if (position.En_passant[rightEnpass] == captureRight)
    {
        moveList.QuietMoves.push_back(encode_move(square, captureRight, false, Enpassant, empty, doublePush));
    }

    if (position.En_passant[leftEnpass] == captureLeft) 
    {
        moveList.QuietMoves.push_back(encode_move(square, captureLeft, false, Enpassant, empty, doublePush));
    }
}

void Board::GenerateKnightMoves(const Square& square)
{
    GenerateCrawlingMoves(KnightRelevantSquares, square);
}

void Board::GenerateKingMoves(const Square& square)
{
    GenerateCrawlingMoves(KingRelevantSquares, square);
    GenerateCastlingMoves(square);
}

/***************************************\
    
       Handling sliding pieces logic
                          
\***************************************/

void Board::GenerateSlidingMoves(std::vector<Square> RelevantSquares[196][4], const Square& square)
{
    for (const auto &direction: RelevantSquares[square])
    {
        for (Square location: direction)
        {
            if (position.Pieces[location] != empty) 
            {
                if (isOpponentsPiece(location, position.Turn)) moveList.Captures.push_back(encode_move(square, location, true, none));

                break;
            }

            moveList.QuietMoves.push_back(encode_move(square, location, false, none));
        }
    }
}

void Board::GenerateBishopMoves(const Square& square)
{
    GenerateSlidingMoves(BishopRelevantSquares, square);
}

void Board::GenerateRookMoves(const Square& square)
{
    GenerateSlidingMoves(RookRelevantSquares, square);
}

void Board::GenerateQueenMoves(const Square& square)
{
    GenerateSlidingMoves(QueenRelevantSquares, square);
}