#include "engine.h"
// #include "chess/position.h"
// #include "chess/movegen.h"
#include "perft.h"
#include <chrono>
// #include "nnue/network.h"
// #include "nnue/nnue.h"
// #include "search/eval.h"

namespace athena {

Engine::Engine() { // : nnue_(network_)
    pos_.init(Position::startpos());
//     // pos_.refresh_accumulators();
//     // nnue::nnue.refresh_accumulator(pos_);

    options.addoption(
        "evalfile", UCIOption("xxx.nnue", [this](const UCIOption& option) {
    }));
}

// void Engine::go(Search::Limits& limits) {
//     search_.start_thinking(pos_, limits);
// }

// void Engine::stop() { //threads_.stop = true; 
//     }

void Engine::set_position(const Position::FEN& fen, const std::vector<std::string>& moves) {
    pos_.init(fen);
    for (auto move: moves) pos_.make_move(move);
    // nnue::nnue.refresh_accumulator(pos_);
}

void Engine::perft(int depth) {
    
    auto pos = pos_;
    uint64_t nodes = 0;

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    nodes = perft::perft(pos, depth);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Nodes: " << nodes << '\n';
    std::cout << "Time: " << duration.count() << " seconds\n";
    std::cout << "Nodes/s: " << nodes / duration.count() << '\n';


    // Move moves[MOVE_NB];
    // int num_moves = generate_legal_moves(pos, moves);

    // for (int i = 0; i < num_moves; ++i) {
    //     const auto& move = moves[i];

    //     pos.make_move(move);
    //     uint64_t count = perft::perft(pos, depth - 1);
    //     pos.undo_move(move);

    //     nodes += count;
    //     std::cout << move.uci() << ": " << count << '\n';
    // }

    // std::cout << "Nodes: " << nodes << '\n';
}

} // namespace athena