#include <gtest/gtest.h>
#include "parser.h"

using namespace parser;

class ParserTest: public ::testing::Test
{/*
    protected:

        Position pos;

        string fen;

        Position modern;*/
};

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
/*
TEST_F(ParserTest, ParseBoard)
{

}


TEST_F(ParserTest, ParseTurn)
{
    EXPECT_TRUE(parse_turn("B", pos));
    EXPECT_EQ(pos.turn, Blue);
}

TEST_F(ParserTest, ParseRight)
{
    EXPECT_TRUE(parse_right("1-1-0-0", QueenSide, pos));
    EXPECT_EQ(pos.rights[Red][QueenSide], true);
    EXPECT_EQ(pos.rights[Blue][QueenSide], true);
    EXPECT_EQ(pos.rights[Yellow][QueenSide], false);
    EXPECT_EQ(pos.rights[Green][QueenSide], false);
}

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