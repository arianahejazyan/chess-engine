def b(integer: int) -> str:
    """
    Returns the binary representation of an integer as a string with 196 length.
    """

    s = format(integer, 'b')

    s = '0' * (196 - len(s)) + s

    return s

def p(integer: int) -> None:
    """
    Prints the binary representation of an integer as a chessboard.
    """

    s = ''
    tmp = ''
    counter = 0
    for bit in reversed(b(integer)):

        tmp += f'{bit} '

        counter += 1
        if counter == 14:
            s = f'\n{tmp}' + s
            counter = 0
            tmp = ''

    print(s)

def pop_bit(bitboard: int, square: int) -> int:
    """
    Clears a bit in the binary representation of the given integer (bitboard) at the specified position (square).
    """
    
    return bitboard & ~ (1 << square)

def set_bit(bitboard: int, square: int) -> int:
    """
    Sets a bit in the binary representation of the given integer (bitboard).
    """

    return bitboard | (1 << square) 

def count_bits(bitboard: int) -> int:
    """
    Counts the number of set bits (1s) in the binary representation of the given integer (bitboard).
    """

    count = 0

    while bitboard:

        count += 1

        bitboard &= bitboard - 1

    return count

def get_1s1b_index(bitboard: int) -> int:
    """
     Finds the index (position) of the least significant set bit (1-bit) in a given bitboard.
    """
    
    if bitboard:

        return count_bits((bitboard & -bitboard) - 1)
    
    else:

        return -1
    
def set_occupancy(index, bits_in_mask, attack_mask):
    """
    Sets the occupancy of a chessboard for a specific attack_mask at the given index.
    """

    occupancy = 0

    for count in range(bits_in_mask):

        square = get_1s1b_index(attack_mask)

        attack_mask = pop_bit(attack_mask, square)

        if index & (1 << count):

            occupancy |= (1 << square)

    return occupancy

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

def mask_rook_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible rook attacks from a given square on a chess board.
    """

    mask = 0

    r = square // 14 # rank
    f = square % 14  # file

    for d in range(1, 13 - r): mask ^= (1 << square + d * 14) # Up-Direction
    for d in range(1,      r): mask ^= (1 << square - d * 14) # Down-Direction
    for d in range(1, 13 - f): mask ^= (1 << square + d     ) # Right-Direction
    for d in range(1,      f): mask ^= (1 << square - d     ) # Left-Direction

    return mask

def mask_bishop_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible bishop attacks from a given square on a chess board.
    """

    mask = 0

    r = square // 14 # rank
    f = square % 14  # file

    for d in range(1, min(13 - r,13 - f)): mask ^= (1 << square + d * 15) # Up-Right Direction
    for d in range(1, min(     r,     f)): mask ^= (1 << square - d * 15) # Down-Left Direction
    for d in range(1, min(13 - r,     f)): mask ^= (1 << square + d * 13) # Up-Left Direction
    for d in range(1, min(     r,13 - f)): mask ^= (1 << square - d * 13) # Down-Right Direction

    return mask

def mask_queen_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible queen attacks from a given square on a chess board.
    """

    mask = mask_rook_attacks(square) ^ mask_bishop_attacks(square)

    return mask