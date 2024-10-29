#include <gtest/gtest.h>
#include "pseudo.h"


class PseudoTest: public ::testing::Test
{
    protected:

        Pseudo pseudo;

        Config config;

        /*

        void CleanPseudoCrawl();

        void SetUp() override
        {
            // Initialize or clear crawl_squares before each test
            crawl_squares.assign(board_size, std::vector<std::vector<Spot>>(6));
        }

        void TearDown() override
        {
            // Clean up if necessary
            for (auto& squares_per_piece : crawl_squares) {
                for (auto& piece_moves : squares_per_piece) {
                    piece_moves.clear();
                }
            }
        }
        */
};
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
TEST_F(PseudoTest, Crawl)
{
    pseudo.init(config);

    EXPECT_EQ(pseudo.crawl[0][King % 3], vector<Square>({9, 8, 1}));
    //EXPECT_EQ(pseudo.crawl[0][King % 3], vector<Square>({34, 65, 6}));

    EXPECT_EQ(pseudo.crawl[0][Knight % 3], vector<Square>({17, 10}));
    //EXPECT_EQ(pseudo.crawl[0][Knight], vector<Square>({34, 65, 6}));
}