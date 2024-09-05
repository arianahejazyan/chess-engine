import re
#from ..parsers.piece_parser import PieceParser

RED = "\033[1;31m" 
GREEN = "\033[1;32m"
RESET = "\033[0m"

Success, Error = True, False

def handle_error(func):
    def wrapper(*args, **kawrgs):
        try:
            return func(*args, **kawrgs)
        except Exception as e:
            return f'Error: {e}'
    return wrapper

def validate_command(func):
    def wrapper(self, command: str):
        for pattern in self.patterns:
            if pattern.match(command):
                return func(self, command)
        return Result(True, 'Invalid command!')
    return wrapper


def log_message(*messages: str):
    def decorator(func):
        def wrapper(*args, **kwargs):
            for message in messages:
                print(message)
            return func(*args, **kwargs)
        return wrapper
    return decorator

promotion_list = []

capture_the_king = False
any_capture = False
allow_passing = False
no_enpassant = False
side_ways = False
torpedo = False
taboo = False
play_for_mate = False
zombies = False

promotion_rank = 10
home_rank = 1
points_for_mate = 10
opposite_multiplier = 2
base_time = 60
time_control_value = 15

time_control = 'delay'
stale_mate = 'draw'

bricks = []

position = None

conditions = [

    ('capture_the_king', lambda x: isinstance(x, bool)),
    ('any_capture', lambda x: isinstance(x, bool)),
    ('allow_passing', lambda x: isinstance(x, bool)),
    ('no_enpassant', lambda x: isinstance(x, bool)),
    ('side_ways', lambda x: isinstance(x, bool)),
    ('torpedo', lambda x: isinstance(x, bool)),
    ('taboo', lambda x: isinstance(x, bool)),
    ('play_for_mate', lambda x: isinstance(x, bool)),
    ('zombies', lambda x: isinstance(x, bool)),

    ('promotion_rank', lambda x: x >= 0 and x <= 13),
    ('home_rank', lambda x: x >= 0 and x <= 13),
    ('points_for_mate', lambda x: x >= 0 and x <= 13),
    ('opposite_multiplier', lambda x: x >= 0 and x <= 13),
    ('base_time ', lambda x: x >= 0 and x <= 13),
    ('time_control_value', lambda x: x >= 0 and x <= 13),

    ('time_control', lambda x: x in ['increament', 'delay']),
    ('stale_mate', lambda x: x in ['win', 'draw', 'lose']),

    ('promotion_rank', lambda x: x >= 0 and x <= 13),
]

display_options = [
    'variable',
    'all',
    'board'
]

#@log_output
def validate_option(func):
    def wrapper(self, option):
        if option in display_option:
            func
            return
        return 
    return wrapper

#@log_output
def validate_parameter_value(func):
    def wrapper(self, parameter, value):
        if parameter not in conditions:
            return
        if type is False:
            return 
        if range is False:
            return
        return 
    return wrapper


class Result:
    def __init__(self, error, message):
        self.error = error
        self.message = message


class Interpreter:

    def __init__(self, app):

        self.app = app

        self.window_registry = {
            'analyze': self.app.analyze_window,
            'board': self.app.board_window,
            'edit': self.app.edit_window,
        }

        self.patterns = {
            re.compile(r'^exit$'),
            re.compile(r'^display\s(\w+)$'),
            re.compile(r'^set\s(\w+)\s(\w+)$'),
            re.compile(r'^config(\s\w+)?$'),
            re.compile(r'^toggle(\s+)(\w+)')
        }

        self.registry = {
            'exit': self._exit,
            'display': self._display,
            'set': self._set,
            'config': self._config,
            'toggle': self._toggle
        }

    def handle_output(func):
        def wrapper(*args, **kwargs):
            output = func(*args, **kwargs)
            if output == None:
                return Output(False, '')

    
    def validate_window(func):
        def wrapper(self, window):
            try:
                func(self, self.window_registry[window])
                return Result(False, '')
            except:
                return Result(True, 'Unkown window')
        return wrapper

    @validate_command
    def process_command(self, command: str):
        parts = command.split()
        func, args = self.registry[parts[0]], parts[1:]
        return func(*args)

    @handle_error
    def _exit(self):
        self.app.command_line.running = False
        return 'exit success!'
    
    @validate_option
    def _display(self, option):
        return f'{option} displayed!'
    
    @validate_parameter_value
    def _set(self, parameter, value):
        #config.setVariable(parameter, value)
        return f'{parameter} is set to {value}!'
    
    def _edit(self, option): # position
        pass

    @validate_window
    def _toggle(self, window):
        if window.isVisible():
            window.hide()
        else:
            window.show()

    @handle_error
    def _config(self, setup = 'custom'):
        return f'{setup} has been configured!'