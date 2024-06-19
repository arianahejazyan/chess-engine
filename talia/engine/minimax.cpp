#include "minimax.h"
#include "evaluator.h"

int minimax(const Position& pos, int depth, int alpha, int beta, bool maximizing)
{
    if (depth == 0 || state(pos) == gameover)
    {
        return evaluate(pos);
    }

    if (pos.turn == maximizing)
    {
        float maxEval = -INFINITY;

        for (const Position& child: generate_all_positions(pos))
        {
            float eval = minimax(child, depth - 1, alpha, beta, false);

            maxEval = max(maxEval, eval);

            alpha = min(alpha, eval);

            if (beta <= alpha) break;
        }

        return maxEval;
    }

    else
    {
        int minEval = +INFINITY;

        for (const Position& child: generate_all_positions(pos))
        {
            int eval = minimax(child, depth - 1, alpha, beta, true);

            minEval = max(minEval, eval);

            beta = max(beta, eval);

            if (beta <= alpha) break;
        }

        return minEval;
    }
}