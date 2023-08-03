enum {invalid=-1, empty=0, Pawn=1, Knight=2, Bishop=3, Rook=4, Queen=5, King=6};

enum {Red, Blue, Yellow, Green};

int board[196];

int colors[196];

int turn;

void generate_moves()
{

    int piece, player;

    for (int square = 0; square < 196; square++) {

        piece = board[square];
        
        player = colors[square];

        if (piece == invalid || piece == empty)
        {
            continue;
        }

        if (player != turn)
        {
            continue;
        }

        int key = generate_key();

        if (piece == Pawn)
        {
            generate_pawn_moves(square, key, turn);
        }

        else if (piece == Knight)
        {
            generate_knight_moves(square, key);
        }

        else if (piece == Bishop)
        {
            generate_bishop_moves(square, key);
        }

        else if (piece == Rook)
        {
            generate_rook_moves(square, key);
        }

        else if (piece == Queen)
        {
            generate_queen_moves(square, key);
        }

        else if (piece == King)
        {
            generate_king_moves(square, key);
        }
    }
}

void generate_pawn_moves(int square, int key, int turn)
{   

}

void generate_knight_moves(int square, int key)
{

}

void generate_bishop_moves(int square, int key)
{

}

void generate_rook_moves(int square, int key)
{

}

void generate_queen_moves(int square, int key)
{

}

void generate_king_moves(int square, int key)
{

}

int generate_key()
{

}