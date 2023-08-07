#include "../utils/const.cpp"
#include "../utils/init_relevant_squares.cpp"

#define get_source(move) (move & 0xff)
#define get_target(move) ((move >> 8 ) & 0xff)
#define get_flag(move) (move >> 16)

bool make_move(int board[], int colors[], int royals[], int castle, int enpassant[], int turn, const int move)
{
    // parse move
    int source = get_source(move);
    int target = get_target(move);
    int flag   = get_flag(move);

    // place the piece the target square
    board[target] = board[source];
    colors[target] = colors[source];

    // remove the piece from source square
    board[source] = empty;
    colors[source] = none;

    // reset enpassant
    enpassant[turn] = -1;

    // update king positions
    if (royals[turn] == source)
    {
        royals[turn] = target;
    }

    // check special moves
    if (flag)
    {
        switch (flag & 0b11)
        {
            case (doublePush):
                
                switch (turn)
                {
                    case (Red):

                        enpassant[Red] = target;
                        break;

                    case (Blue):

                        enpassant[Blue] = target;
                        break;

                    case (Yellow):
                        
                        enpassant[Yellow] = target;
                        break;

                    case (Green):

                        enpassant[Green] = target;
                        break;
                }

                break;

            case (Castle):

                switch (turn)
                {
                    case (Red):

                        if (flag >> 2)
                        {
                            board[8] = Rook;
                            colors[8] = Red;

                            board[10] = empty;
                            colors[10] = none;
                        }
                        else
                        {
                            board[7] = Rook;
                            colors[7] = Red;

                            board[4] = empty;
                            colors[4] = none;
                        }
                        break;

                    case (Blue):

                        if (flag >> 2)
                        {
                            board[70] = Rook;
                            colors[70] = Blue;

                            board[42] = empty;
                            colors[42] = none;
                        }
                        else
                        {
                            board[98] = Rook;
                            colors[98] = Blue;

                            board[140] = empty;
                            colors[140] = none;
                        }
                        break;

                    case (Yellow):

                        if (flag >> 2)
                        {
                            board[185] = Rook;
                            colors[185] = Yellow;

                            board[183] = empty;
                            colors[183] = none;
                        }
                        else
                        {
                            board[187] = Rook;
                            colors[187] = Yellow;

                            board[190] = empty;
                            colors[190] = none;
                        }
                        break;

                    case (Green):

                        if (flag >> 2)
                        {
                            board[125] = Rook;
                            colors[125] = Blue;

                            board[153] = empty;
                            colors[153] = none;
                        }
                        else
                        {
                            board[111] = Rook;
                            colors[111] = Green;

                            board[55] = empty;
                            colors[55] = none;
                        }
                        break;
                }

                break;

            case (Enpassant):

                board[flag >> 2] = empty;
                colors[flag >> 2] = none;
                break;

            case (Promotion):

                board[target] = flag >> 2;
                break;
        }
    }

    // update castle rights
    castle &= castle_rights[source];
    castle &= castle_rights[target];

    // check if the king is not under attack
    if (is_square_attacked(board, colors, royals[turn], turn))
    {
        return false;
    }

    return true;
}

bool is_square_attacked(int board[], int colors[], int square, int player)
{
    int team = player % 2;

    // rook and queen
    for (const auto &direction: rook_relevant_squares[square])
    {
        for (int i = 0; i < direction[Size]; i++)
        {
            int location = square + i * direction[Step];

            if (board[location] != 0)
            {
                if (colors[location] != team)
                {
                    if (board[location] == Rook || board[location] == Queen)
                    {
                        return true;
                    }
                }

                break;
            }
        }
    }

    // bishop and queen
    for (const auto &direction: bishop_relevant_squares[square])
    {
        for (int i = 0; i < direction[Size]; i++)
        {
            int location = square + i * direction[Step];

            if (board[location] != 0)
            {
                if (colors[location] != team)
                {
                    if (board[location] == Bishop || board[location] == Queen)
                    {
                        return true;
                    }
                }

                break;
            }
        }
    }

    // knight
    for (int location: knight_relevant_squares[square])
    {
        if (board[location] != 0)
        {
            if (colors[location] != team)
            {
                if (board[location] == Knight)
                {
                    return true;
                }
            }
        }  
    }

    // king
    for (int location: king_relevant_squares[square])
    {
        if (board[location] != 0)
        {
            if (colors[location] != team)
            {
                if (board[location] == King)
                {
                    return true;
                }
            }
        }  
    }

    // pawn
    if (team == 0)
    {
        if (board[square + 13] == Pawn && colors[square + 13] == Blue)
        {
            return true;
        }
        if (board[square - 15] == Pawn && colors[square - 15] == Blue)
        {
            return true;
        }
        if (board[square + 15] == Pawn && colors[square + 15] == Green)
        {
            return true;
        }
        if (board[square -13] == Pawn && colors[square - 13] == Green)
        {
            return true;
        }
    }
    else
    {
        if (board[square - 15] == Pawn && colors[square - 15] == Red)
        {
            return true;
        }
        if (board[square - 13] == Pawn && colors[square - 13] == Red)
        {
            return true;
        }
        if (board[square + 15] == Pawn && colors[square + 15] == Yellow)
        {
            return true;
        }
        if (board[square + 13] == Pawn && colors[square + 13] == Yellow)
        {
            return true;
        }
    }

    return false;
}