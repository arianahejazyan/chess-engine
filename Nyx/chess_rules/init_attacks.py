from ..utils.bit_tools import count_bits, set_occupancy
from ..utils.mask_methods import *

def init_pawn_attacks() -> dict:

    attacks = {}

    for square in range(196):

        for player in range(4):

            attacks[(square, player)] = mask_pawn_attacks(square, player)

    return attacks

def init_knight_attacks() -> dict:

    attacks = {}

    for square in range(196):

        attacks[square] = mask_knight_attacks(square)

    return attacks

def init_king_attacks() -> dict:

    attacks = {}

    for square in range(196):

        attacks[square] = mask_king_attacks(square)

    return attacks

def init_ascending_attacks() -> dict:

    attacks = {}

    for square in range(196):

        mask = mask_ascending_attacks(square)

        relevant_bits = count_bits(mask)

        for combination in range(1 << relevant_bits):

            occupancy =  set_occupancy(combination, relevant_bits, mask)

            attacks[(square, occupancy)] = ascending_attacks_on_fly(square, occupancy)

    return attacks

def init_descending_attacks() -> dict:

    attacks = {}

    for square in range(196):

        mask = mask_ascending_attacks(square)

        relevant_bits = count_bits(mask)

        for combination in range(1 << relevant_bits):

            occupancy =  set_occupancy(combination, relevant_bits, mask)

            attacks[(square, occupancy)] = descending_attacks_on_fly(square, occupancy)

    return attacks

def init_vertical_attacks() -> dict:

    attacks = {}

    for square in range(196):

        mask = mask_vertical_attacks(square)

        relevant_bits = count_bits(mask)

        for combination in range(1 << relevant_bits):

            occupancy =  set_occupancy(combination, relevant_bits, mask)

            attacks[(square, occupancy)] = vertical_attacks_on_fly(square, occupancy)

    return attacks

def init_horizontal_attacks() -> dict:

    attacks = {}

    for square in range(196):

        mask = mask_horizontal_attacks(square)

        relevant_bits = count_bits(mask)

        for combination in range(1 << relevant_bits):

            occupancy =  set_occupancy(combination, relevant_bits, mask)

            attacks[(square, occupancy)] = horizontal_attacks_on_fly(square, occupancy)

    return attacks
