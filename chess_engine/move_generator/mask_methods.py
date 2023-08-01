def mask_king_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible king attacks from a given square on a chess board.
    """

    mask = 0

    r = square // 14 # rank
    f = square % 14  # file

    if (r < 13)           : mask ^= (1 << square + 14) # Up
    if (r < 13) & (f < 13): mask ^= (1 << square + 15) # Up-Right
    if (f < 13)           : mask ^= (1 << square + 1 ) # Right
    if (r > 0 ) & (f < 13): mask ^= (1 << square - 13) # Down-Right
    if (r > 0 )           : mask ^= (1 << square - 14) # Down
    if (r > 0 ) & (f > 0 ): mask ^= (1 << square - 15) # Down-Left
    if (f > 0 )           : mask ^= (1 << square - 1 ) # Left
    if (r < 13) & (f > 0 ): mask ^= (1 << square + 13) # Up-Left

    return mask

def mask_knight_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible knight attacks from a given square on a chess board.
    """

    mask = 0

    r = square // 14 # rank
    f = square % 14  # file

    if (r < 12) & (f < 13): mask ^= (1 << square + 29) # Up-Up-Right
    if (r < 13) & (f < 12): mask ^= (1 << square + 16) # Up-Right-Right
    if (r > 0 ) & (f < 12): mask ^= (1 << square - 12) # Down-Right-Right
    if (r > 1 ) & (f < 13): mask ^= (1 << square - 27) # Down-Down-Right
    if (r > 1 ) & (f > 0 ): mask ^= (1 << square - 29) # Down-Down-Left
    if (r > 0 ) & (f > 1 ): mask ^= (1 << square - 16) # Down-Left-Left
    if (r < 13) & (f > 1 ): mask ^= (1 << square + 12) # Up-Left-Left
    if (r < 12) & (f > 0 ): mask ^= (1 << square + 27) # Up-Up-Left

    return mask

def mask_pawn_attacks(square: int, player: int) -> int:
    """
    Generates a bitboard representing the possible pawn attacks from a given square on a chess board.
    """

    mask = 0

    r = square // 14 # rank
    f = square % 14  # file

    if player == 0:
        if (r < 13) & (f > 0 ): mask ^= (1 << square + 13) # Up-Left
        if (r < 13) & (f < 13): mask ^= (1 << square + 15) # Up-Right
    elif player == 1:
        if (r < 13) & (f < 13): mask ^= (1 << square + 15) # Up-Right
        if (r > 0 ) & (f < 13): mask ^= (1 << square - 13) # Down-Right
    elif player == 2:
        if (r > 0 ) & (f < 13): mask ^= (1 << square - 13) # Down-Right
        if (r > 0 ) & (f > 0 ): mask ^= (1 << square - 15) # Down-Left
    else:
        if (r > 0 ) & (f > 0 ): mask ^= (1 << square - 15) # Down-Left
        if (r < 13) & (f > 0 ): mask ^= (1 << square + 13) # Up-Left

    return mask