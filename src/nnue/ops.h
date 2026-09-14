// #pragma once

// #include <algorithm>
// #include <cstddef>
// #include <cstdint>

// namespace athena::nnue::ops {

// template <std::size_t Size>
// inline void add(int16_t* __restrict__ dst, const int16_t* __restrict__ src) noexcept {
//     for (std::size_t i = 0; i < Size; ++i)
//         dst[i] += src[i];
// }

// template <std::size_t Size>
// inline void sub(int16_t* __restrict__ dst, const int16_t* __restrict__ src) noexcept {
//     for (std::size_t i = 0; i < Size; ++i)
//         dst[i] -= src[i];
// }

// template <int16_t Min, int16_t Max>
// inline int32_t screlu(int16_t x) noexcept {
//     x = std::clamp(x, Min, Max);
//     return int32_t(x) * int32_t(x);
// }

// template <std::size_t Size, int16_t Min, int16_t Max>
// inline int32_t screlu_dot(const int16_t* __restrict__ acc,
//                           const int16_t* __restrict__ w) noexcept {
//     int32_t sum = 0;
//     for (std::size_t i = 0; i < Size; ++i)
//         sum += screlu<Min, Max>(acc[i]) * int32_t(w[i]);
//     return sum;
// }

// } // namespace athena