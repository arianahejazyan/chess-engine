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