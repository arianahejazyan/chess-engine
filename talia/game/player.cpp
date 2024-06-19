#include "player.h"
#include "config.h"

/* ---------------------------------------------------------------------------- */

void PLAYER::foo()
{
    for (const Color& p1: COLOR_LIST)
    {
        for (const Color& p2: COLOR_LIST)
        {
            switch (Config::setup)
            {
                case (FFA):
                    TEAMMATE[p1][p2] = (p1 == p2);
                    break;

                case (RB):
                    TEAMMATE[p1][p2] = (p1 == Red || p1 == Blue) ? (p2 == Red || p2 == Blue): (p2 == Yellow || p2 == Green);
                    break;

                case (RY):
                    TEAMMATE[p1][p2] = (p1 == Red || p1 == Yellow) ? (p2 == Red || p2 == Yellow): (p2 == Blue || p2 == Green);
                    break;

                case (RG):
                    TEAMMATE[p1][p2] = (p1 == Red || p1 == Green) ? (p2 == Red || p2 == Green): (p2 == Blue || p2 == Yellow);
                    break;
            
                default: break;
            }

            OPPONENT[p1][p2] = !TEAMMATE[p1][p2];
        }
    }    
}

/* ---------------------------------------------------------------------------- */