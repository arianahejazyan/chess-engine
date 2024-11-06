#include <gtest/gtest.h>
#include "pseudo.h"

using namespace pseudo;

class PseudoTest: public ::testing::Test
{
    protected:

        Square sq;

        vector<Square> expected;

        unsigned int idx = 0;

        static void SetUpTestSuite() 
        {
            initialize();
        }

        static void TearDownTestSuite() 
        {
            // clear();
        }
};

// #define CHECK(_sq, _type, _expected) Square sq = _sq; int type = _type; vector<Square> expected = _expected; EXPECT_EQ(range[sq][t], expected.size()); for (int i = 0; i < expected.size(); ++i){EXPECT_EQ(squares[start[sq][t] + i], expected[i]);}

void check(Square sq, int movement, initializer_list<Square> expected)
{
    EXPECT_EQ(range[sq][movement], expected.size());

    int i = 0;
    for (Square target: expected)
    {
        EXPECT_EQ(squares[start[sq][movement] + i++], target);
    }
}

TEST_F(PseudoTest, King)
{
    check(0,   King - 1, {9, 8, 1});
    check(72,  King - 1, {87, 86, 85, 73, 71, 59, 58, 57});
    check(159, King - 1, {158,151,150});


    /*
    int t = 0;

    sq = 0;
    
    expected = {9, 8, 1};

    EXPECT_EQ(range[sq][t], expected.size());

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(squares[start[sq][t] + i], expected[i]);
    }

    

    EXPECT_EQ(range[0][0], 0);
    EXPECT_EQ(squares[start[0][0]], 0);
    EXPECT_EQ(squares[start[0][0] + 1], 0);
    EXPECT_EQ(squares[start[0][0] + 2], 0);

    Square sq = 0;
    Square expected[range[sq][0]] = {}
    for (int i = 0; i < range[sq][0]; ++i)
    {
        EXPECT_EQ(squares[start[0][0] + 2], 0);
    }
    */

    /*
    crawl(King, idx);

    EXPECT_EQ(squares[0], 0);
    EXPECT_EQ(squares[1], 0);
    EXPECT_EQ(squares[2], 0);
    EXPECT_EQ(squares[3], 0);
    EXPECT_EQ(squares[4], 0);

    //EXPECT_EQ(start[0][0], 20);

    EXPECT_EQ(idx, 5);*/
}

/*
TEST_F(PseudoTest, AllSquares)
{
    // precalculate_all_squares();
}

TEST_F(PseudoTest, CrawlSquares)
{
    init_crawl_squares();

    int count = 0;

    iterate_crawl count += crawl_squares[sq][piece % 5].size();

    EXPECT_EQ(count, 67);
}
*/
/*
TEST_F(PseudoTest, Crawl)
{
    pseudo.init(config);

    EXPECT_EQ(pseudo.crawl[0][0], vector<Square>({9, 8, 1}));
    EXPECT_EQ(pseudo.crawl[72][0], vector<Square>({87, 86, 85, 73, 71, 59, 58, 57}));

    EXPECT_EQ(pseudo.crawl[0][1], vector<Square>({17, 10}));
    EXPECT_EQ(pseudo.crawl[72][1], vector<Square>({101, 99, 88, 84, 60, 56, 45, 43}));
}

TEST_F(PseudoTest, Slide)
{
    pseudo.init(config);

    EXPECT_EQ(pseudo.slide[28][0], vector<Square>({43, 58, 73, 88, 103, 118, 133}));
    EXPECT_EQ(pseudo.slide[28][1], vector<Square>({42, 56, 70, 84, 98, 112, 126, 137, 145, 153}));
    EXPECT_EQ(pseudo.slide[28][2], vector<Square>({41, 54, 67, 80}));
    EXPECT_EQ(pseudo.slide[28][3], vector<Square>({29, 30, 31, 32, 33, 34, 35, 36, 37}));
    EXPECT_EQ(pseudo.slide[28][4], vector<Square>({27, 26, 25, 24}));
    EXPECT_EQ(pseudo.slide[28][5], vector<Square>({18, 11, 4}));
    EXPECT_EQ(pseudo.slide[28][6], vector<Square>({17, 9, 1}));
    EXPECT_EQ(pseudo.slide[28][7], vector<Square>({16}));
}
*/