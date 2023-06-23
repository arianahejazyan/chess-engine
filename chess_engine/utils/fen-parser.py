from bit_tools import b

enum = ['rK','rQ','rR','rB','rN','rP',
        'bK','bQ','bR','bB','bN','bP',
        'yK','yQ','yR','yB','yN','yP',
        'gK','gQ','gR','gB','gN','gP']

def fen2board(fen):

    turn, state, short_castle, long_castle, scores, fifty_rule, position = tuple(fen.replace("\n", "").split("-"))

    board = [0] * 24

    loc = 0
    for rank in reversed(position.split("/")):
        for file in rank.split(","):

            if file.isdigit():
                loc += int(file)

            else:
                board[enum.index(file)] ^= 1 << loc
                loc += 1
        
    return board

def board2fen(turn, state, short_castle, long_castle, scores, fifty_role, board):

    arr = [0] * 196

    for piece, n in enumerate(board):
        for l in [loc for loc, bit in enumerate(reversed(b(n))) if bit == '1']:
            arr[l] = enum[piece]

    s = []
    tmp = []
    counter = 0
    for i, element in enumerate(arr): 
            
            if element == 0:
                counter += 1

            elif counter != 0:
                tmp.extend((counter, element))
                counter = 0
            
            else:
                tmp.append(element)

            if i % 14 == 13:

                if counter != 0:
                    tmp.append(counter)
                    counter = 0

                tmp = ','.join(str(x) for x in tmp)
                s.insert(0, tmp)
                tmp = []
    
    board = '/\n'.join(s)
      
    fen = f'{turn}-{state}-{short_castle}-{long_castle}-{scores}-{fifty_role}-\n{board}'

    return fen