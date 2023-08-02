from mask_methods import mask_bishop_attacks, mask_rook_attacks
from ..utils.bit_tools import set_occupancy, count_bits
import random

def find_magic_number(square: int, bishop: bool) -> int:
    
    occupancies = {}

    attacks = {}

    attack_mask = mask_bishop_attacks(square) if bishop else mask_rook_attacks(square)

    relevant_bits = count_bits(attack_mask)

    occupancy_indicies = 1 << relevant_bits

    for index in range(occupancy_indicies):

        occupancies[index] = set_occupancy(index, relevant_bits, attack_mask)

        attacks[index] = bishop_attacks_on_fly(square, occupancies[index]) if bishop else rook_attacks_on_fly(square, occupancies[index])

    used_attacks = [0] * len(attacks)

    for i in range(100000000):

        magic_number = generate_magic_number()

        if count_bits((attack_mask * magic_number) & 0) < 12: continue 

        index, fail = 0, False
        
        while (not fail) and (index < occupancy_indicies):

            magic_index = (occupancies[index] * magic_number) >> (196 - relevant_bits)

            if (used_attacks[magic_index] == 0): 
                used_attacks[magic_index] = attacks[index]

            elif (used_attacks[magic_index] != attacks[index]):
                fail = True
                print(f'index: {index}')

            index += 1

        if not fail: return magic_number
    
    print('magic number fails')
    return 0

def init_magic_numbers():

    rook_magic_numbers = {}

    bishop_magic_numbers = {}
    
    for square in range(196):

        rook_magic_numbers[square] = find_magic_number(square, False)

        bishop_magic_numbers[square] = find_magic_number(square, True)

    return rook_magic_numbers, bishop_magic_numbers

def rook_attacks_on_fly(square: int, block: int) -> int:

    attacks = 0

    r = square // 14 # rank
    f = square % 14  # file

    for d in range(1, 13 - r): 
        attacks ^= (1 << square + d * 14) # Up-Direction
        if (1 << square + d * 14) & block: break

    for d in range(1, r): 
        attacks ^= (1 << square - d * 14) # Down-Direction
        if (1 << square - d * 14) & block: break

    for d in range(1, 13 - f): 
        attacks ^= (1 << square + d) # Right-Direction
        if (1 << square + d) & block: break

    for d in range(1, f): 
        attacks ^= (1 << square - d) # Left-Direction
        if (1 << square - d) & block: break

    return attacks

def bishop_attacks_on_fly(square: int, block: int) -> int:

    attacks = 0

    r = square // 14 # rank
    f = square % 14  # file

    for d in range(1, min(13 - r,13 - f)): 
        attacks ^= (1 << square + d * 15) # Up-Right Direction
        if (1 << square + d * 15) & block: break

    for d in range(1, min(r,f)): 
        attacks ^= (1 << square - d * 15) # Down-Left Direction
        if (1 << square - d * 15) & block: break

    for d in range(1, min(13 - r,f)): 
        attacks ^= (1 << square + d * 13) # Up-Left Direction
        if (1 << square + d * 13) & block: break

    for d in range(1, min(r,13 - f)): 
        attacks ^= (1 << square - d * 13) # Down-Right Direction
        if (1 << square - d * 13) & block: break

    return attacks

def generate_magic_number():

    return random.getrandbits(196)