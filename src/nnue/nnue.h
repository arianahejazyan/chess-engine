// #pragma once

// #include <cstdint>
// #include "nnue/accumulator.h"
// #include "nnue/network.h"

// namespace athena::nnue {

// class NNUE {
// public:
//     explicit NNUE(const Network& network) : network_(network) {}

//     int32_t evaluate(
//         const Accumulator& self,
//         const Accumulator& next,
//         const Accumulator& ally,
//         const Accumulator& prev) const noexcept;

// private:
//     const Network& network_;
// };

// } // namespace athena