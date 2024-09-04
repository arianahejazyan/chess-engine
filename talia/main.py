from interface.command_line import CommandLine
from interface.interpreter import Interpreter
from parsers.piece_parser import PieceParser

class Application:

    def __init__(self):

        self.interpreter = Interpreter(self)
        self.command_line = CommandLine(self)
        #self.piece_parser = PieceParser()
        #self.fen_parser = FenParser()

    def _create_components(self):

        pass
    
    def run(self):
        
        self.command_line.run()

if __name__ == '__main__':

    app = Application()
    app.run()