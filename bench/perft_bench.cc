#include <benchmark/benchmark.h>
#include "perft.h"

using namespace athena;

static void BM_Perft_Modern(benchmark::State& state) {
    const int depth = state.range(0);

    Position base;
    base.set_setup(Castle::Setup::Modern);
    base.init(Position::startpos());

    // Run one perft to get the node count (it's deterministic)
    Position pos = base;
    const uint64_t nodes = perft::perft(pos, depth);

    for (auto _ : state) {
        Position p = base;           // copy each iteration
        uint64_t n = perft::perft(p, depth);

        benchmark::DoNotOptimize(n);
        benchmark::ClobberMemory();
    }

    // === Counters set AFTER the loop ===
    
    // Nodes = nodes from ONE perft call
    state.counters["Nodes"] = nodes;

    // NPS = nodes_per_call / average_time_per_iteration
    // kIsIterationInvariantRate tells Benchmark that the value is per-iteration
    state.counters["NPS"] = benchmark::Counter(
        static_cast<double>(nodes),
        benchmark::Counter::kIsIterationInvariantRate
    );
}

BENCHMARK(BM_Perft_Modern)
    ->DenseRange(1, 5)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();