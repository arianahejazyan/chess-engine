#include <gtest/gtest.h>
#include "parser.h"

using namespace parser;

class ParserTest: public ::testing::Test
{
    protected:

        Position pos;

        Square sq;

        int integer;
        int digit;

        string fen1 = "R-0,0,0,0-1,1,1,1-1,1,1,1-0,0,0,0-0-x,x,x,yR,yN,yB,yK,yQ,yB,yN,yR,x,x,x/x,x,x,yP,yP,yP,yP,yP,1,yP,yP,x,x,x/x,x,x,8,x,x,x/bR,bP,10,gP,gR/bN,bP,6,yP,3,gP,gN/bB,bP,10,gP,gB/bK,bP,10,gP,gQ/bQ,bP,10,gP,gK/bB,bP,10,gP,gB/bN,bP,10,gP,gN/bR,bP,10,gP,gR/x,x,x,8,x,x,x/x,x,x,rP,rP,rP,rP,rP,rP,rP,rP,x,x,x/x,x,x,rR,rN,rB,rQ,rK,rB,rN,rR,x,x,x";
        string fen2 = "B-0,0,0,0-1,1,1,1-1,1,1,1-0,0,0,0-0-{'enPassant':('d3:d4','','','')}-x,x,x,yR,yN,yB,yK,yQ,yB,yN,yR,x,x,x/x,x,x,yP,yP,yP,yP,yP,yP,yP,yP,x,x,x/x,x,x,8,x,x,x/bR,bP,10,gP,gR/bN,bP,10,gP,gN/bB,bP,10,gP,gB/bQ,bP,10,gP,gK/bK,bP,10,gP,gQ/bB,bP,10,gP,gB/bN,bP,10,gP,gN/bR,bP,1,rP,8,gP,gR/x,x,x,8,x,x,x/x,x,x,1,rP,rP,rP,rP,rP,rP,rP,x,x,x/x,x,x,rR,rN,rB,rQ,rK,rB,rN,rR,x,x,x";
};


TEST_F(ParserTest, Lower)
{
    EXPECT_EQ(lower('B'), 'b');
    EXPECT_EQ(lower('r'), 'r');
    EXPECT_EQ(lower('@'), '@');
}

TEST_F(ParserTest, IsInteger)
{
    EXPECT_TRUE(is_integer("3645"));
}

TEST_F(ParserTest, IsIntegerError)
{
    EXPECT_FALSE(is_integer(""));
    EXPECT_FALSE(is_integer("+23"));
    EXPECT_FALSE(is_integer("65a3"));
    EXPECT_FALSE(is_integer("@ds2"));
}

TEST_F(ParserTest, SplitString)
{
    vector<string> parts = split_string("32, one,, @ ,x2z", ',');
    vector<string> expected = {"32", " one", "", " @ ", "x2z"};

    ASSERT_EQ(parts, expected);
}

TEST_F(ParserTest, SplitBoard)
{
    vector<string> parts = split_board("x,@ ,rP/2, /bQ,x,,1");
    vector<string> expected = {"bQ", "x", "", "1", "2", " ", "x", "@ ", "rP"};

    ASSERT_EQ(parts, expected);
}

TEST_F(ParserTest, ParsePiece)
{
    Piece piece;

    EXPECT_TRUE(parse_piece('P', piece));
    EXPECT_EQ(piece, Pawn);

    EXPECT_TRUE(parse_piece('N', piece));
    EXPECT_EQ(piece, Knight);

    EXPECT_TRUE(parse_piece('B', piece));
    EXPECT_EQ(piece, Bishop);

    EXPECT_TRUE(parse_piece('R', piece));
    EXPECT_EQ(piece, Rook);

    EXPECT_TRUE(parse_piece('Q', piece));
    EXPECT_EQ(piece, Queen);

    EXPECT_TRUE(parse_piece('K', piece));
    EXPECT_EQ(piece, King);
}

TEST_F(ParserTest, ParsePieceError)
{
    Piece piece;

    EXPECT_FALSE(parse_piece(' ', piece));
    EXPECT_FALSE(parse_piece('A', piece));
    EXPECT_FALSE(parse_piece('$', piece));
}

TEST_F(ParserTest, ParsePlayer)
{
    Player player;

    EXPECT_TRUE(parse_player('r', player));
    EXPECT_EQ(player, Red);

    EXPECT_TRUE(parse_player('b', player));
    EXPECT_EQ(player, Blue);

    EXPECT_TRUE(parse_player('y', player));
    EXPECT_EQ(player, Yellow);

    EXPECT_TRUE(parse_player('g', player));
    EXPECT_EQ(player, Green);
}

TEST_F(ParserTest, ParsePlayerError)
{
    Player player;

    EXPECT_FALSE(parse_player(' ', player));
    EXPECT_FALSE(parse_player('w', player));
    EXPECT_FALSE(parse_player('#', player));
}


TEST_F(ParserTest, ParseTurn)
{
    EXPECT_TRUE(parse_turn("", pos));
    EXPECT_EQ(pos.turn, Red);

    EXPECT_TRUE(parse_turn("B", pos));
    EXPECT_EQ(pos.turn, Blue);

    EXPECT_FALSE(parse_turn(" ", pos));
    EXPECT_FALSE(parse_turn("x", pos));
}

TEST_F(ParserTest, ParseState)
{
    EXPECT_TRUE(parse_state(pos, ""));

    EXPECT_TRUE(parse_state(pos, ",1,0*,,,"));
    EXPECT_EQ(pos.states[Blue], Alive);
    EXPECT_EQ(pos.states[Yellow], Dead);
    
    EXPECT_FALSE(parse_state(pos, " "));
    EXPECT_FALSE(parse_state(pos, "@"));
}

TEST_F(ParserTest, ParseRight)
{
    EXPECT_TRUE(parse_right(pos, "", KingSide));

    EXPECT_TRUE(parse_right(pos, "0,,1$,,", QueenSide));
    EXPECT_EQ(pos.rights[Red][QueenSide], false);
    EXPECT_EQ(pos.rights[Yellow][QueenSide], true);

    EXPECT_FALSE(parse_right(pos, " ", KingSide));
    EXPECT_FALSE(parse_right(pos, "@", QueenSide));
}

TEST_F(ParserTest, ParseScore)
{
    EXPECT_TRUE(parse_score(pos, ""));

    EXPECT_TRUE(parse_score(pos, "80,0,+32,-40,,#"));
    EXPECT_EQ(pos.scores[Red], 80);
    EXPECT_EQ(pos.scores[Blue], 0);
    EXPECT_EQ(pos.scores[Yellow], 32);
    EXPECT_EQ(pos.scores[Green], -40);

    EXPECT_FALSE(parse_score(pos, " "));
    EXPECT_FALSE(parse_score(pos, "$"));
}

TEST_F(ParserTest, ParseFiftyRule)
{
    EXPECT_TRUE(parse_fifty_rule(pos, "30"));
    EXPECT_EQ(pos.fifty_rule, 30);

    EXPECT_TRUE(parse_fifty_rule(pos, "+20"));
    EXPECT_EQ(pos.fifty_rule, 20);

    EXPECT_FALSE(parse_fifty_rule(pos, ""));
    EXPECT_FALSE(parse_fifty_rule(pos, " "));
    EXPECT_FALSE(parse_fifty_rule(pos, "#"));
    EXPECT_FALSE(parse_fifty_rule(pos, "-3"));
}

TEST_F(ParserTest, ParseBoard)
{
    string board = "2rQ3=,#,x,59,bbN/31,x,9,,@,yP/,wK, v ,gR56,59";

    EXPECT_TRUE(parse_board(board, pos));
    EXPECT_EQ(pos.pieces[0], Rook);
    EXPECT_EQ(pos.players[0], Green);
    EXPECT_EQ(pos.pieces[100], Pawn);
    EXPECT_EQ(pos.players[100], Yellow);
}

TEST_F(ParserTest, Substring)
{
    string str = "{'enPassant':('d3:d4','','','')}";

    EXPECT_EQ(substring(str, '(', ')'), "'d3:d4','','',''");

    EXPECT_EQ(substring("'d3:d4'", '\'', '\''), "d3:d4");
}

TEST_F(ParserTest, ParseDigit)
{
    EXPECT_TRUE(parse_digit('7', digit));
    EXPECT_EQ(digit, 7);
}

TEST_F(ParserTest, ParseDigitError)
{
    EXPECT_FALSE(parse_digit('$', digit));
}

TEST_F(ParserTest, ParseInteger)
{
    EXPECT_TRUE(parse_integer("12", integer));
    EXPECT_EQ(integer, 12);

    EXPECT_TRUE(parse_integer("+9", integer));
    EXPECT_EQ(integer, 9);

    EXPECT_TRUE(parse_integer("-6", integer));
    EXPECT_EQ(integer, -6);

    EXPECT_FALSE(parse_integer("", integer));
    EXPECT_FALSE(parse_integer(" ", integer));
    EXPECT_FALSE(parse_integer("@", integer));
    EXPECT_FALSE(parse_integer("+", integer));
}

TEST_F(ParserTest, ParseLocation)
{
    EXPECT_TRUE(parse_location("d1", sq));
    EXPECT_EQ(sq, 0);

    EXPECT_TRUE(parse_location("k14", sq));
    EXPECT_EQ(sq, 159);

    EXPECT_TRUE(parse_location("g7", sq));
    EXPECT_EQ(sq, 72);
}

TEST_F(ParserTest, ParseLocationError)
{
    EXPECT_FALSE(parse_location("a1", sq));
    EXPECT_FALSE(parse_location("Q5", sq));
    EXPECT_FALSE(parse_location("B15", sq));
}

TEST_F(ParserTest, ParseEnpassant)
{
    EXPECT_TRUE(parse_enpassant("{'enPassant':('d3:d4','','','')}", pos));
    EXPECT_EQ(pos.marked[Red], 16);
    EXPECT_EQ(pos.target[Red], 27);
}

TEST_F(ParserTest, ParseEnpassantError)
{

}





TEST_F(ParserTest, ParseFen)
{
    EXPECT_TRUE(parse_fen(fen1, pos));
    EXPECT_TRUE(parse_fen(fen2, pos));
}





/*







TEST_F(ParserTest, ValidBoard)
{
    EXPECT_TRUE(parse_board(board, pos));
}

TEST_F(ParserTest, InvalidFiles)
{

}

TEST_F(ParserTest, InvalidRanks)
{

}

TEST_F(ParserTest, InvalidBricks)
{

}

TEST_F(ParserTest, UnknownPiece)
{
    string board =  "x,x,x,yR,yN,yB,yK,yQ,yB,yN,yR,x,x,x/"
                    "x,x,x,yP,yP,yP,yP,yP,1,yP,yP,x,x,x/"
                    "x,x,x,8,x,x,x/"
                    "bR,bP,10,gP,gR/"
                    "bN,bP,6,yP,3,gP,gN/"
                    "bB,bP,10,gP,gB/"
                    "bK,bP,10,gP,gQ/"
                    "bQ,bP,10,gP,gK/"
                    "bB,bP,10,gP,gB/"
                    "bN,bP,10,gP,gN/"
                    "bR,bP,10,gP,gR/"
                    "x,x,x,8,x,x,x/"
                    "x,x,x,rP,rP,rP,rP,rP,rP,rP,rP,x,x,x/"
                    "x,x,x,rR,rN,rB,rQ,rK,rB,rN,rR,x,x,x";
}

TEST_F(ParserTest, SplitString)
{
    vector<string> input = split("king,queen", ',');
    vector<string> expected = {"king", "queen"};
    ASSERT_EQ(input, expected);
}

TEST_F(ParserTest, ValidTurns)
{
    EXPECT_TRUE(parse_turn("R", pos));
    EXPECT_EQ(pos.turn, Red);

    EXPECT_TRUE(parse_turn("b", pos));
    EXPECT_EQ(pos.turn, Blue);

    EXPECT_TRUE(parse_turn("Y", pos));
    EXPECT_EQ(pos.turn, Yellow);

    EXPECT_TRUE(parse_turn("G", pos));
    EXPECT_EQ(pos.turn, Green);
}

TEST_F(ParserTest, InvalidTurns)
{
    EXPECT_FALSE(parse_turn("", pos));
    EXPECT_FALSE(parse_turn("R ", pos));
    EXPECT_FALSE(parse_turn("X", pos));
}

TEST_F(ParserTest, ValidRights)
{
    ASSERT_TRUE(parse_right("1,0,1,1", KingSide, pos));

    bool expected[4] = {true, false, true, true};
    for (Player player = Red; player <= Green; ++player)
    {
        ASSERT_EQ(pos.rights[player][KingSide], expected[player]);
    }
}

TEST_F(ParserTest, InvalidRights)
{
    // not enough players
    ASSERT_FALSE(parse_right("1,0,1", KingSide, pos));

    // too many players
    ASSERT_FALSE(parse_right("1,0,1,0,0", KingSide, pos));

    // invalid condition
    ASSERT_FALSE(parse_right("1,true,1,0", KingSide, pos));
}


TEST_F(ParserTest, ParseEnpassants)
{
    // {'enPassant':('d3:d4','','','')}

    
}

TEST_F(ParserTest, ParseBoard)
{
    string board = "x,x,x,yR,yN,yB,yK,yQ,yB,yN,yR,x,x,x/"
                   "x,x,x,yP,yP,yP,yP,yP,yP,yP,yP,x,x,x/"
                   "x,x,x,8,x,x,x/"
                   "bR,bP,10,gP,gR/"
                   "bN,bP,10,gP,gN/"
                   "bB,bP,10,gP,gB/"
                   "bQ,bP,10,gP,gK/"
                   "bK,bP,10,gP,gQ/"
                   "bB,bP,10,gP,gB/"
                   "bN,bP,10,gP,gN/"
                   "bR,bP,1,rP,8,gP,gR/"
                   "x,x,x,8,x,x,x/"
                   "x,x,x,1,rP,rP,rP,rP,rP,rP,rP,x,x,x/"
                   "x,x,x,rR,rN,rB,rQ,rK,rB,rN,rR,x,x,x"



    EXPECT_TRUE(parse_board(board, pos));

    Piece expected_pieces[160] = {};
    Player expected_players[160] = {};

    for (Square sq = 0; sq < 160; ++sq)
    {

    }
}


TEST_F(ParserTest, InvalidBoard)
{
    // not enough rows
    EXPECT_FALSE(parse_board("", pos));

    // not enough columns
    EXPECT_FALSE(parse_board("", pos));

    // too many columns
    EXPECT_FALSE(parse_board("", pos));

    // too many rows
    EXPECT_FALSE(parse_board("", pos));

    
}

TEST_F(ParserTest, ParseFEN)
{
    EXPECT_TRUE(parse_fen(fen, pos));
    EXPECT_EQ(pos, modern);
}*/