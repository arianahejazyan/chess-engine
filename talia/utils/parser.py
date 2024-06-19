std = 'R-0,0,0,0-1,1,1,1-1,1,1,1-0,0,0,0-0-x,x,x,yR,yN,yB,yK,yQ,yB,yN,yR,x,x,x/x,x,x,yP,yP,yP,yP,yP,yP,yP,yP,x,x,x/x,x,x,8,x,x,x/bR,bP,10,gP,gR/bN,bP,10,gP,gN/bB,bP,10,gP,gB/bQ,bP,10,gP,gK/bK,bP,10,gP,gQ/bB,bP,10,gP,gB/bN,bP,10,gP,gN/bR,bP,10,gP,gR/x,x,x,8,x,x,x/x,x,x,rP,rP,rP,rP,rP,rP,rP,rP,x,x,x/x,x,x,rR,rN,rB,rQ,rK,rB,rN,rR,x,x,x'

class Parser:
    
    def fen2pos(self, fen: str):
        pass

    def pos2move(self, pos) -> str:
        pass

    # fen2pos methods #

    def __turnToPlayer(self, turn: str):
        playerDicts = {'R':0,'B':1}
        return playerDicts[turn]

    def __castleToRight(self, kingSide: str, queenSide: str):
        pass

    def __boardToPos(self, board: str):
        pieces, players = [[]] * 14, [[]] * 14

        for i, row in enumerate(board.split('/')):
            for col in row.split(','):

                if col.isdigit():
                    for _ in range(int(col)):
                        pieces[i].append(-1)
                        players[i].append(-1)
                else:
                    pieces[i].append(pieceDict[col[0]])
                    pieces[i].append(playerDict[col[1]])

        return pieces, players

    
    # pos2move methods #

    def __playerToTurn(self, player) -> str:
        pass

    def __rightToCastle(self, right):
        pass

    def __posToBoard(self, pos):
        pass



def parse(fen):
    s = fen.split('-')
    return s

print(parse(std))


std = 'R-0,0,0,0-1,1,1,1-1,1,1,1-0,0,0,0-0-x,x,x,yR,yN,yB,yK,yQ,yB,yN,yR,x,x,x/x,x,x,yP,yP,yP,yP,yP,yP,yP,yP,x,x,x/x,x,x,8,x,x,x/bR,bP,10,gP,gR/bN,bP,10,gP,gN/bB,bP,10,gP,gB/bQ,bP,10,gP,gK/bK,bP,10,gP,gQ/bB,bP,10,gP,gB/bN,bP,10,gP,gN/bR,bP,10,gP,gR/x,x,x,8,x,x,x/x,x,x,rP,rP,rP,rP,rP,rP,rP,rP,x,x,x/x,x,x,rR,rN,rB,rQ,rK,rB,rN,rR,x,x,x'

pieceDict = {'X':0,'K':1,'Q':2,'R':3,'B':4,'N':5,'P':6}
playerDict = {'R':0,'B':1,'Y':2,'G':3}

def boardToPos(board: str):
    pieces, players = [], []

    for i, row in enumerate(board.split('/')):
        for col in row.split(','):

            if col.isdigit():
                for _ in range(int(col)):
                    pieces.append(0)
                    players.append(-1)

            elif col[0].upper() == 'X':
                pieces.append(-1)
                players.append(-1)

            else:
                players.append(playerDict[col[0].upper()])
                pieces.append(pieceDict[col[1].upper()])

    return pieces, players

x,y = boardToPos(std.split('-')[6])

print(x,'\n')
print(y)