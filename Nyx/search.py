def minimax(position, depth, maximizing_player, alpha=-float('inf'), beta=float('inf')):
    
    if depth == 0:
        return eval(position)
      
    if maximizing_player % 2 == 0:
        max_eval = -float('inf')
        for child in moves(position, maximizing_player):
            eval = minimax(child, depth - 1, (maximizing_player + 1) % 4, alpha, beta)
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval

    else:
        min_eval = float('inf')
        for child in moves(position, maximizing_player):
            eval = minimax(child, depth - 1, (maximizing_player + 1) % 4, alpha, beta)
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval