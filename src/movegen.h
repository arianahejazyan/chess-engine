#pragma once

#include "chess.h"
#include "position.h"

namespace athena {

[[nodiscard]] int generate_noisy_moves(Position& pos, Move* moves) noexcept;
[[nodiscard]] int generate_quiet_moves(Position& pos, Move* moves) noexcept;
[[nodiscard]] int generate_legal_moves(Position& pos, Move* moves) noexcept;

} // namespace athena