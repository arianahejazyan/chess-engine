#pragma once

// #include <vector>
// #include <string>
#include "position.h"
// #include "nnue/feature_transformer.h"
// #include "nnue/network.h"
// #include "nnue/nnue.h"
// #include "nnue/weights.h"
// #include "search.h"
#include "ucioption.h"

namespace athena {

class Engine {
public:
    Engine();

//     void go(Search::Limits&);

//     // non blocking call to stop searching
//     void stop();

//     bool load(const std::string& file) noexcept { return nnue::Weights::load(file, nnue_.network()); }
//     bool save(const std::string& file) noexcept { return nnue::Weights::save(file, nnue_.network()); }

//     // auto evaluate() noexcept {
//     //     return nnue_.evaluate(pos_);
//     // }

    void set_position(const Position::FEN& fen, const std::vector<std::string>& moves);

    void print(bool board16x16 = false) { pos_.print(board16x16); }
    void perft(int depth);

    Options& get_options() { return options; } 

private:

//     // ThreadPool threads_;


//     nnue::Network network_;
//     nnue::NNUE nnue_;
    Position pos_;
//     // search::Search search_;


    Options options;
};

} // namespace athena