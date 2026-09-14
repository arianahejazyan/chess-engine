// #include "nnue/nnue.h"
// #include "nnue/architecture.h"
// #include "nnue/network.h"
// #include "ops.h"
// #include <cstdint>

// namespace athena::nnue {

// int32_t NNUE::evaluate(
//     const Accumulator& self, 
//     const Accumulator& next,
//     const Accumulator& ally, 
//     const Accumulator& prev) const noexcept {

//     int32_t score = 0;
//     score += ops::screlu_dot<arch::HIDDEN, arch::SCRELU_MIN, arch::SCRELU_MAX>(self.data, network_.l2.weights[0 * arch::HIDDEN]);
//     score += ops::screlu_dot<arch::HIDDEN, arch::SCRELU_MIN, arch::SCRELU_MAX>(next.data, network_.l2.weights[1 * arch::HIDDEN]);
//     score += ops::screlu_dot<arch::HIDDEN, arch::SCRELU_MIN, arch::SCRELU_MAX>(ally.data, network_.l2.weights[2 * arch::HIDDEN]);
//     score += ops::screlu_dot<arch::HIDDEN, arch::SCRELU_MIN, arch::SCRELU_MAX>(prev.data, network_.l2.weights[3 * arch::HIDDEN]);

//     score += network_.l2.biases[0];
//     score *= arch::SCALE;
//     score /= (arch::QA * arch::QA * arch::QB);

//     return score;
// }

// } // namespace athena