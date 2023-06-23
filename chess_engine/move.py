from utils.mask import *

king_mask_table   = generate_mask_table(mask_king_moves)
queen_mask_table  = generate_mask_table(mask_queen_moves)
rook_mask_table   = generate_mask_table(mask_rook_moves)
bishop_mask_table = generate_mask_table(mask_bishop_moves)
knight_mask_table = generate_mask_table(mask_knight_moves)
pawn_mask_table   = generate_mask_table(mask_pawn_moves)
pawn_capture_table = generate_mask_table(mask_pawn_captures)

block = 87927700851497958793422690461569715349321877590330545666055
square = 100433627766186892221372630771322662657637687111424552206335

promote = {
    0: 22834569286720449932986229528799881659529822208,
    1: 6277484882657350768155134829386217820998656632002608890880,
    2: 72053195991416832,
    3: 49042850645760552876211990854579826726552004937520381960,
}

double_push = {
    0: 268419072,
    1: 12260712661440138219052997713644956681638001234380095490,
    2: 6129608019044398722286327965284061366021924570003406848,
    3: 25109939530629403072620539317544871283994626528010435563520,
}

enpass = {
    0: 0,
    1: 0,
}

bitboards = [0,0,0,0,0,0,
             0,0,0,0,0,0,
             0,0,0,0,0,0,
             0,0,0,0,0,0,]

side = 0

def generate_moves(bitboards: list[int], side: int) -> list[int]:

    moves = []

    occupancy = {
        0: block,
        1: block,
    }

    for i, bitboard in enumerate(bitboards):

        occupancy[(i // 6) % 2] ^= bitboards[i]


    #check = None
    #pin = None

    for piece, bitboard in enumerate(bitboards):

        # king
        if piece == side * 6:

            pass
        
        # Queen
        elif piece == (1 + side * 6):

            pass
        
        # Rook
        elif piece == (2 + side * 6):

            pass
        
        # Bishop
        elif piece == (3 + side * 6):

            pass

        # Knight
        elif piece == (4 + side * 6):

            while bitboard:

                source_square = bitboard & -bitboard

                mask = knight_mask_table[source_square]
                mask &= ~occupancy[side % 2]

                while mask:

                    target_square = mask & -mask

                    if target_square & occupancy[(side + 1) % 2]:

                        moves.append(source_square + (target_square << 196) + (piece << 392) + (1 << 397))

                    else:

                        moves.append(source_square + (target_square << 196) + (piece << 392))
                
                    mask &= ~target_square
                
                bitboard &= ~source_square

        # Pawn
        elif piece == (5 + side * 6):

            while bitboard:

                source_square = bitboard & -bitboard

                mask = pawn_mask_table[source_square]
                mask &= ~occupancy[side % 2]

                while mask:

                    target_square = mask & -mask

                    if promote[side] & target_square:

                        moves.append(source_square + (target_square << 196) + (piece << 392) + ((1 + side * 6) << 402))
                        moves.append(source_square + (target_square << 196) + (piece << 392) + ((2 + side * 6) << 402))
                        moves.append(source_square + (target_square << 196) + (piece << 392) + ((3 + side * 6) << 402))
                        moves.append(source_square + (target_square << 196) + (piece << 392) + ((4 + side * 6) << 402))
                    
                    else:

                        moves.append(source_square + (target_square << 196) + (piece << 392))

                    if double_push[side] & source_square:

                        if   side == 0: target_square <<= 14
                        elif side == 0: target_square <<= 1
                        elif side == 0: target_square >>= 14
                        elif side == 0: target_square >>= 1

                        moves.append(source_square + (target_square << 196) + (piece << 392))
                
                capture = pawn_capture_table[source_square]
                capture &= occupancy[(side + 1) % 2]
                capture |= enpass[(side + 1) % 2]

                while capture:

                    target_square = mask & -mask

                    if promote[side] & target_square:
                        
                        if enpass[(side + 1) % 2]:

                            moves.append(source_square + (target_square << 196) + (piece << 392)+ (1 << 397) + ((1 + side * 6) << 402) + (1 << 408))
                            moves.append(source_square + (target_square << 196) + (piece << 392)+ (1 << 397) + ((2 + side * 6) << 402) + (1 << 408))
                            moves.append(source_square + (target_square << 196) + (piece << 392)+ (1 << 397) + ((3 + side * 6) << 402) + (1 << 408))
                            moves.append(source_square + (target_square << 196) + (piece << 392)+ (1 << 397) + ((4 + side * 6) << 402) + (1 << 408))

                        else:

                            moves.append(source_square + (target_square << 196) + (piece << 392) + (1 << 397) + ((1 + side * 6) << 402))
                            moves.append(source_square + (target_square << 196) + (piece << 392) + (1 << 397) + ((2 + side * 6) << 402))
                            moves.append(source_square + (target_square << 196) + (piece << 392) + (1 << 397) + ((3 + side * 6) << 402))
                            moves.append(source_square + (target_square << 196) + (piece << 392) + (1 << 397) + ((4 + side * 6) << 402))

                    else:
                        
                        if enpass[(side + 1) % 2]:

                            moves.append(source_square + (target_square << 196) + (piece << 392) + (1 << 397) + (1 << 408))

                        else:

                            moves.append(source_square + (target_square << 196) + (piece << 392) + (1 << 397))
    
    return moves


def make_move(board: int, move: int) -> int:
        
    # parse move
    source_square  = (move       ) & square
    target_square  = (move >> 196) & square
    piece          = (move >> 392) & 31
    capture        = (move >> 397) & 31
    promoted_piece = (move >> 402) & 31
    double_push    = (move >> 407) & 1
    enpass         = (move >> 408) & 3
    castling       = (move >> 410) & 3
        
    # move piece
    board[piece] &= ~(1 << source_square)
    board[piece] ^=  (1 << target_square)

    if capture:
        
        board[capture] &= ~(1 << target_square)

    if promoted_piece:
        
        board[piece]          &= ~(1 << target_square)
        board[promoted_piece] ^=  (1 << target_square)

    if double_push:
        pass

    if enpass:
        pass

    if castling:
        pass