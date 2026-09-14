// #pragma once

// #include <cstring>
// #include "accumulator.h"
// #include "network.h"
// #include "ops.h"

// namespace athena::nnue {

// using FeatureIndex = std::size_t;

// class FeatureTransformer {
// public:
//     explicit FeatureTransformer(const L1& layer) noexcept : layer_(layer) {}

//     void add_feature(Accumulator& acc, FeatureIndex feature) const noexcept {
//         ops::add<arch::HIDDEN>(acc.data, layer_.weights[feature]);
//     }

//     void sub_feature(Accumulator& acc, FeatureIndex feature) const noexcept {
//         ops::sub<arch::HIDDEN>(acc.data, layer_.weights[feature]);
//     }

//     void refresh(Accumulator& acc) const noexcept {
//         std::memcpy(acc.data, layer_.biases, sizeof(acc.data));
//     }

// private:
//     const L1& layer_;
// };

// // class Feature {
// //     public:
// //         Feature(chess::Square sq, chess::Piece piece, chess::Color color, chess::Color perspective) noexcept {
// //             id_ = sq.rotate(perspective).id() +
// //             piece.id() * 160 +
// //             color.rotate(perspective).id() * 160 * chess::PIECE_NB;
// //         }
// //     };

// } // namespace athena