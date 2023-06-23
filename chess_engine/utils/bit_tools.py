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

def v(integer: int) -> bool:
    """
    Checks if the given integer is a valid board
    """

    if integer & int('1' * 196, 2):
        return True
    else:
        return False
    
def square_to_board():
    pass

def board_to_square():
    pass




def pop_bit(board: int, square: int) -> int:
    pass


def set_bit(square):
    pass

def get_bit(square):
    pass