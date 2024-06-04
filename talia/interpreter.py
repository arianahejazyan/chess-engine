import itertools

def get_user_input():
    
    for i in itertools.count():
        try:
            yield i, input('[%d]: ' % i)
        except KeyboardInterrupt:
            break
        except EOFError:
            break

def exec_function(user_input):

    try:
        compile(user_input, '<stdin>', 'eval')
    except SyntaxError:
        return exec
    return eval
    
def exec_user_input(i, user_input, user_globals):

    try:
        val = exec_function(user_input)(user_input, user_globals)
    except Exception as e:
        print('%s: %s' % (e.__class__.__name__, e))
    else:
        if val is not None:
            print('-> %s' % val)

def main():
    
    user_globals = {}

    for i, user_input in get_user_input():
        exec_user_input(i, user_input, user_globals)

if __name__ == "__main__":
    main()