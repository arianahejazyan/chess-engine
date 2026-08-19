#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <random>
#include <vector>
#include "chess/position.h"
#include "nnue/nnue.h"
#include "nnue/weights.h"

using namespace athena;

class NNUETest : public ::testing::Test {
protected:
    chess::Position pos;
    nnue::NNUE nnue;

    static void SetUpTestSuite() {
        nnue::Weights("nnue_weights.bin", nnue);
    }
};

TEST_F(NNUETest, RandomSequence) {
    std::mt19937 rng(12345);

    // chess::Position pos;
    // pos.set(START_FEN);

    // Accumulator acc;
    // init_accumulator(pos, acc);

    // std::vector<Move> played;

    // // Play up to 60 moves
    // for (int i = 0; i < 60; ++i) {
    //     MoveList moves = generate_legal(pos);
    //     if (moves.empty()) break;

    //     Move m = moves[rng() % moves.size()];
    //     pos.do_move(m, acc);
    //     played.push_back(m);

    //     Accumulator rebuilt;
    //     rebuild_accumulator(pos, rebuilt);
    //     ASSERT_TRUE(accumulators_equal(acc, rebuilt))
    //         << "Make failed at ply " << i;
    // }

    // // Undo everything
    // while (!played.empty()) {
    //     Move m = played.back();
    //     played.pop_back();
    //     pos.undo_move(m, acc);

    //     Accumulator rebuilt;
    //     rebuild_accumulator(pos, rebuilt);
    //     ASSERT_TRUE(accumulators_equal(acc, rebuilt))
    //         << "Undo failed";
    // }
}

struct EvalEntry {
    FEN::BIN fen;
    Score score;
};

static std::vector<EvalEntry> load_eval_bin(const std::string& path) {
    std::ifstream in(std::filesystem::path("bin") / path, std::ios::binary);
    std::vector<EvalEntry> entries;

    EvalEntry entry;
    while (
        in.read(reinterpret_cast<char*>(&entry.fen  ), sizeof(FENBin)) &&
        in.read(reinterpret_cast<char*>(&entry.score), sizeof(Score ))) {
        entries.push_back(entry);
    }

    return entries;
}

TEST_F(NNUETest, Eval) {
    auto entries = load_eval_bin("nnue_eval.bin");
    
    for (const auto& entry : entries) {
        pos.init(entry.fen);
        EXPECT_EQ(nnue.evaluate(pos), entry.score);
    }
}
