# ////////////////////  leaper pieces  //////////////////// #

def mask_pawn_attacks(square: int, player: int) -> int:
    """
    Generates a bitboard representing the possible pawn attacks from a given square on a chess board.

    Parameters:
        square (int): The position of the pawn (0-based index) on the chessboard for which to generate attack masks.
        player (int): An integer representing the player to whom the pawn belongs. It can be 0, 1, 2, or 3, representing the players in a game.

    Returns:
        int: A bitboard representing the possible attack squares for the pawn placed at the input square.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (196 squares).
        - The function assumes that the player parameter is an integer in the range of 0 to 3 (inclusive), representing each player.
    """

    # Initialize bitboard mask
    mask = 0

    # Calculate rank and file of the given square
    r = square // 14
    f = square % 14

    # Generate attack mask based on the player's direction
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

def mask_king_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible king attacks from a given square on a chess board.

    Parameters:
        square (int): The position of the king (0-based index) on the chessboard for which to generate attack masks.

    Returns:
        int: A bitboard representing the possible attack squares for the king placed at the input square.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (196 squares).
        - The returned bitboard represents the attack squares the king can move to, considering only the king's movement rules (one square in any direction).
    """

    # Initialize bitboard mask
    mask = 0

    # Calculate rank and file of the given square
    r = square // 14
    f = square % 14 

    # Generate attack masks in all eight possible directions
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

    Parameters:
        square (int): The position of the knight (0-based index) on the chessboard for which to generate attack masks.

    Returns:
        int: A bitboard representing the possible attack squares for the knight placed at the input square.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (196 squares).
        - The returned bitboard represents the attack squares the knight can move to, considering only the knight's movement rules (L-shaped jump).
    """

    # Initialize bitboard mask
    mask = 0

    # Calculate rank and file of the given square
    r = square // 14 # rank
    f = square % 14  # file

    # Generate attack masks for all eight possible knight moves (L-shaped jumps)
    if (r < 12) & (f < 13): mask ^= (1 << square + 29) # Up-Up-Right
    if (r < 13) & (f < 12): mask ^= (1 << square + 16) # Up-Right-Right
    if (r > 0 ) & (f < 12): mask ^= (1 << square - 12) # Down-Right-Right
    if (r > 1 ) & (f < 13): mask ^= (1 << square - 27) # Down-Down-Right
    if (r > 1 ) & (f > 0 ): mask ^= (1 << square - 29) # Down-Down-Left
    if (r > 0 ) & (f > 1 ): mask ^= (1 << square - 16) # Down-Left-Left
    if (r < 13) & (f > 1 ): mask ^= (1 << square + 12) # Up-Left-Left
    if (r < 12) & (f > 0 ): mask ^= (1 << square + 27) # Up-Up-Left

    return mask

# ////////////////////  sliding pieces  //////////////////// #

def mask_ascending_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible ascending diagonal attacks from a given square on a chess board.
    Ascending diagonals move from bottom-left to top-right or vice versa.

    Parameters:
        square (int): The position of the piece (0-based index) on the chessboard for which to generate attack masks.

    Returns:
        int: A bitboard representing the possible attack squares along the ascending diagonal from the input square.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (196 squares).
        - The returned bitboard represents the attack squares along the ascending diagonal, considering only the ascending diagonal movement rules.
    """

    # Initialize bitboard mask
    mask = 0

    # Calculate rank and file of the given square
    r = square // 14
    f = square % 14

    # Generate attack masks for the ascending diagonal in Up-Right direction
    for d in range(1, min(13 - r,13 - f)): 
        mask ^= (1 << square + d * 15)
    
    # Generate attack masks for the ascending diagonal in Down-Left direction
    for d in range(1, min(r,f)): 
        mask ^= (1 << square - d * 15)
    
    return mask

def mask_descending_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible descending diagonal attacks from a given square on a chess board.
    Descending diagonals move from top-left to bottom-right or vice versa.

    Parameters:
        square (int): The position of the piece (0-based index) on the chessboard for which to generate attack masks.

    Returns:
        int: A bitboard representing the possible attack squares along the descending diagonal from the input square.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (196 squares).
        - The returned bitboard represents the attack squares along the descending diagonal, considering only the descending diagonal movement rules.
    """

    # Initialize bitboard mask
    mask = 0

    # Calculate rank and file of the given square
    r = square // 14
    f = square % 14 

    # Generate attack masks for the descending diagonal in Up-Left direction
    for d in range(1, min(13 - r,f)): 
        mask ^= (1 << square + d * 13)

     # Generate attack masks for the descending diagonal in Down-Right direction
    for d in range(1, min(r,13 - f)): 
        mask ^= (1 << square - d * 13)
    
    return mask

def mask_vertical_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible vertical attacks from a given square on a chess board.

    Parameters:
        square (int): The position of the rook (0-based index) on the chessboard for which to generate attack masks.

    Returns:
        int: A bitboard representing the possible attack squares along the vertical direction from the input square.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (196 squares).
        - The returned bitboard represents the attack squares along the vertical direction, considering only the rook's vertical movement rules.
    """

    # Initialize bitboard mask
    mask = 0

    # Calculate rank of the given square
    r = square // 14 # rank

    # Generate attack masks for the vertical direction in Up-Direction
    for d in range(1, 13 - r): 
        mask ^= (1 << square + d * 14)

    # Generate attack masks for the vertical direction in Down-Direction
    for d in range(1,r): 
        mask ^= (1 << square - d * 14)

    return mask

def mask_horizontal_attacks(square: int) -> int:
    """
    Generates a bitboard representing the possible horizontal attacks from a given square on a chess board.

    Parameters:
        square (int): The position of the rook (0-based index) on the chessboard for which to generate attack masks.

    Returns:
        int: A bitboard representing the possible attack squares along the horizontal direction from the input square.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (usually 196).
        - The returned bitboard represents the attack squares along the horizontal direction, considering only the rook's horizontal movement rules.
    """

    # Initialize bitboard mask
    mask = 0

    # Calculate file of the given square
    f = square % 14  # file

    # Generate attack masks for the horizontal direction in Right-Direction
    for d in range(1, 13 - f): 
        mask ^= (1 << square + d)

    # Generate attack masks for the horizontal direction in Left-Direction
    for d in range(1,      f): 
        mask ^= (1 << square - d)

    return mask

# ////////////////////  sliding pieces on fly  //////////////////// #

def ascending_attacks_on_fly(square: int, block: int) -> int:
    """
    Generates a bitboard representing the ascending attacks from a given square on a chessboard, while considering blocking pieces.

    Parameters:
        square (int): The position of the attacking piece (0-based index) on the chessboard.
        block (int): A bitboard representing the occupied squares (0-based index) on the chessboard where the attacks may stop.

    Returns:
        int: A bitboard representing the possible attack squares along the ascending diagonal from the input square while considering blocking pieces.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (196 squares).
        - The 'block' parameter represents a bitboard where each bit set to 1 indicates an occupied square where the attack may stop.
        - The returned bitboard represents the attack squares along the ascending diagonal, considering blocking pieces along the way.
    """

    # initialize bitboard mask
    mask = 0

    # calculate rank and file of the given square
    r = square // 14
    f = square % 14

    # generate up-right direction attacks
    for d in range(1, min(13 - r,13 - f)): 
        mask ^= (1 << square + d * 15)
        if (1 << square + d * 15) & block: break

    # generate down-left direction attacks
    for d in range(1, min(r,f)): 
        mask ^= (1 << square - d * 15)
        if (1 << square - d * 15) & block: break

    return mask

def descending_attacks_on_fly(square: int, block: int) -> int:
    """
    Generates a bitboard representing the descending attacks from a given square on a chessboard, while considering blocking pieces.

    Parameters:
        square (int): The position of the attacking piece (0-based index) on the chessboard.
        block (int): A bitboard representing the occupied squares (0-based index) on the chessboard where the attacks may stop.

    Returns:
        int: A bitboard representing the possible attack squares along the descending diagonal from the input square while considering blocking pieces.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (usually 196).
        - The 'block' parameter represents a bitboard where each bit set to 1 indicates an occupied square where the attack may stop.
        - The returned bitboard represents the attack squares along the descending diagonal, considering blocking pieces along the way.
    """

    # initialize bitboard mask
    mask = 0

    # calculate rank and file of the given square
    r = square // 14
    f = square % 14

    # generate up-left direction attacks
    for d in range(1, min(13 - r,f)): 
        mask ^= (1 << square + d * 13)
        if (1 << square + d * 13) & block: break

    # generate down-right direction attacks
    for d in range(1, min(r,13 - f)): 
        mask ^= (1 << square - d * 13)
        if (1 << square - d * 13) & block: break

    return mask

def vertical_attacks_on_fly(square: int, block: int) -> int:
    """
    Generates a bitboard representing the vertical attacks from a given square on a chessboard, while considering blocking pieces.

    Parameters:
        square (int): The position of the attacking piece (0-based index) on the chessboard.
        block (int): A bitboard representing the occupied squares (0-based index) on the chessboard where the attacks may stop.

    Returns:
        int: A bitboard representing the possible attack squares along the vertical direction from the input square while considering blocking pieces.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (196 squares).
        - The 'block' parameter represents a bitboard where each bit set to 1 indicates an occupied square where the attack may stop.
        - The returned bitboard represents the attack squares along the vertical direction, considering blocking pieces along the way.
    """

    # initialize bitboard mask
    mask = 0

    # calculate rank of the given square
    r = square // 14 

    # generate up direction attacks
    for d in range(1, 13 - r): 
        mask ^= (1 << square + d * 14)
        if (1 << square + d * 14) & block: break

    # generate down direction attacks
    for d in range(1,      r): 
        mask ^= (1 << square - d * 14)
        if (1 << square - d * 14) & block: break

    return mask

def horizontal_attacks_on_fly(square: int, block: int) -> int:
    """
    Generates a bitboard representing the horizontal attacks from a given square on a chessboard, while considering blocking pieces.

    Parameters:
        square (int): The position of the attacking piece (0-based index) on the chessboard.
        block (int): A bitboard representing the occupied squares (0-based index) on the chessboard where the attacks may stop.

    Returns:
        int: A bitboard representing the possible attack squares along the horizontal direction from the input square while considering blocking pieces.

    Note:
        - The function assumes that the square parameter is a non-negative integer less than the number of squares on a chessboard (196 squares).
        - The 'block' parameter represents a bitboard where each bit set to 1 indicates an occupied square where the attack may stop.
        - The returned bitboard represents the attack squares along the horizontal direction, considering blocking pieces along the way.
    """

    # initialize bitboard mask
    mask = 0

    # calculate file of the given square
    f = square % 14

    # generate right direction attacks
    for d in range(1, 13 - f): 
        mask ^= (1 << square + d) 
        if (1 << square + d) & block: break

    # generate left direction attacks
    for d in range(1,f): 
        mask ^= (1 << square - d)
        if (1 << square - d) & block: break

    return mask