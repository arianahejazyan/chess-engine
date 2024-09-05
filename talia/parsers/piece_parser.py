import os
import json

class PieceParser:
    
    def __init__(self):
        pass

    def _parse_file(self, file_path):
        
        with open(file_path, 'r') as json_file:
            data = json.load(json_file)

        print(data)

        # Extract and print piece name
        piece_name = data['name']
        print(f"Piece: {piece_name}")

        # Extract and print moves
        for move_type, moves in data['moves'].items():
            print(f"  Move Type: {move_type}")
            for move in moves:
                vertical = move['vertical']
                horizontal = move['horizontal']
                #player = move['player']
                print(f"    Player: , Vertical: {vertical}, Horizontal: {horizontal}")


    def iterate_over_directory(self, path):
        
        for filename in os.listdir(path):
            if filename.endswith('.json'):
                file_path = os.path.join(path, filename)
                self._parse_file(file_path)


#p = PieceParser()
#p.iterate_over_directory('/external/Projects/chess-engine/talia/data/pieces')