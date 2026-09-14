// #pragma once

// #include <cstdint>
// #include "architecture.h"
// #include "layer.h"

// namespace athena::nnue {

// using L1 = Layer<int16_t, int16_t, arch::INPUTS                         , arch::HIDDEN>;
// using L2 = Layer<int16_t, int32_t, arch::HIDDEN * arch::NUM_PERSPECTIVES, arch::OUTPUT>;

// struct alignas(64) Network {
//     L1 l1;
//     L2 l2;
// };

// } // namespace athena::nnue