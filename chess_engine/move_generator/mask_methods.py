# ////////////////////  learper pieces //////////////////// #

def mask_king_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible king attacks from a given square on a chess board.
    """
    mask = 0

    r = square // 14
    f = square % 14

    if (r < 13):            mask ^= (1 << square + 14) 
    if (r < 13) & (f < 13): mask ^= (1 << square + 15)
    if (f < 13):            mask ^= (1 << square + 1 )
    if (r > 0 ) & (f < 13): mask ^= (1 << square - 13)
    if (r > 0 )           : mask ^= (1 << square - 14)
    if (r > 0 ) & (f > 0 ): mask ^= (1 << square - 15)
    if (f > 0 )           : mask ^= (1 << square - 1 )
    if (r < 13) & (f > 0 ): mask ^= (1 << square + 13)

    return mask

def mask_knight_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible knight attacks from a given square on a chess board.
    """

    mask = 0

    r = square // 14
    f = square % 14

    if (r < 12) & (f < 13): mask ^= (1 << square + 29) 
    if (r < 13) & (f < 12): mask ^= (1 << square + 16)
    if (r > 0 ) & (f < 12): mask ^= (1 << square - 12)
    if (r > 1 ) & (f < 13): mask ^= (1 << square - 27)
    if (r > 1 ) & (f > 0 ): mask ^= (1 << square - 29)
    if (r > 0 ) & (f > 1 ): mask ^= (1 << square - 16)
    if (r < 13) & (f > 1 ): mask ^= (1 << square + 12)
    if (r < 12) & (f > 0 ): mask ^= (1 << square + 27)

    return mask

def mask_pawn_attacks(square: int, player: int) -> int:
    """
    Generates a bitboard representing the possible pawn attacks from a given square on a chess board.
    """

    mask = 0

    r = square // 14
    f = square % 14

    if player == 0:
        if (r < 13) & (f > 0 ): mask ^= (1 << square + 13) 
        if (r < 13) & (f < 13): mask ^= (1 << square + 15)
    elif player == 1:
        if (r < 13) & (f < 13): mask ^= (1 << square + 15) 
        if (r > 0 ) & (f < 13): mask ^= (1 << square - 13)
    elif player == 2:
        if (r > 0 ) & (f < 13): mask ^= (1 << square - 13)
        if (r > 0 ) & (f > 0 ): mask ^= (1 << square - 15)
    else:
        if (r > 0 ) & (f > 0 ): mask ^= (1 << square - 15) 
        if (r < 13) & (f > 0 ): mask ^= (1 << square + 13)

    return mask