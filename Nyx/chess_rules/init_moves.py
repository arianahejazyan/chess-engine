from ..utils.bit_tools import mask_pawn_attacks, mask_knight_attacks, mask_king_attacks

def init_leapers_attacks() -> (dict, dict, dict):
    """
    Initialize and generate attack masks for pawn, knight,and king on a chessboard.
    """

    pawn_attacks, knight_attacks, king_attacks = {}, {}, {}

    # loop over all squares
    for square in range(196):

        # init pawn attacks
        for player in range(4):

            pawn_attacks[(player, square)] = mask_pawn_attacks(player, square)

        # init knight attacks
        knight_attacks[square] = mask_knight_attacks(square)

        # init king attacks
        king_attacks[square] = mask_king_attacks(square)

    return pawn_attacks, knight_attacks, king_attacks