from typing import Callable

def generate_mask_table(piece: Callable, side: int = -1) -> dict:

    table = {}

    if side == -1:

        for i in range(196):

            key = 1 << i
            mask = piece(i)

            table[key] = mask
    
    else:

        for i in range(196):

            key = 1 << i
            mask = piece(i)

            table[(key, side)] = mask
    
    return table

# ////////////////////  learper pieces masks //////////////////// #

def mask_king_moves(square: int) -> int:

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

def mask_knight_moves(square: int) -> int:

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

def mask_pawn_moves(square: int, side: int) -> int:

    mask = 0

    r = square // 14
    f = square % 14

    if side == 0: 
        if (r < 13)           : mask ^= (1 << square + 14)
    elif side == 1: 
        if            (f < 13): mask ^= (1 << square + 1 )
    elif side == 2:
        if (r > 0 )           : mask ^= (1 << square - 14)
    else: 
        if            (f > 0 ): mask ^= (1 << square - 1 )

    return mask

def mask_pawn_captures(square: int, side: int) -> int:

    mask = 0

    r = square // 14
    f = square % 14

    if side == 0:
        if (r < 13) & (f > 0 ): mask ^= (1 << square + 13) 
        if (r < 13) & (f < 13): mask ^= (1 << square + 15)
    elif side == 1:
        if (r < 13) & (f < 13): mask ^= (1 << square + 15) 
        if (r > 0 ) & (f < 13): mask ^= (1 << square - 13)
    elif side == 2:
        if (r > 0 ) & (f < 13): mask ^= (1 << square - 13)
        if (r > 0 ) & (f > 0 ): mask ^= (1 << square - 15)
    else:
        if (r > 0 ) & (f > 0 ): mask ^= (1 << square - 15) 
        if (r < 13) & (f > 0 ): mask ^= (1 << square + 13)

    return mask

# ////////////////////  sliding pieces masks //////////////////// #

def mask_rook_moves(square: int) -> int:

    mask = 0

    r = square // 14
    f = square % 14

    for d in range(1, 14 - r): mask ^= (1 << square + d * 14)
    for d in range(1, 1  + r): mask ^= (1 << square - d * 14)
    for d in range(1, 14 - f): mask ^= (1 << square + d     )
    for d in range(1, 1  + f): mask ^= (1 << square - d     )

    return mask

def mask_bishop_moves(square: int) -> int:

    mask = 0

    r = square // 14
    f = square % 14

    for d in range(1, min(14 - r,14 - f)): mask ^= (1 << square + d * 15)
    for d in range(1, min(1  + r,1  + f)): mask ^= (1 << square - d * 15)
    for d in range(1, min(14 - r,1  + f)): mask ^= (1 << square + d * 13)
    for d in range(1, min(1  + r,14 - f)): mask ^= (1 << square - d * 13)

    return mask

def mask_queen_moves(square: int) -> int:

    mask = mask_rook_moves(square) ^ mask_bishop_moves(square)

    return mask