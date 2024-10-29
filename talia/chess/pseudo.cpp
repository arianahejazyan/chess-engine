#include "pseudo.h"

#define target(sq, offset) int r = Rank(sq) + offset.vertical; int f = File(sq) + offset.horizontal;

#define update(rank, file, offset) rank +=  offset.vertical; file += offset.horizontal;






inline static void calculate_crawl_squares(Square sq, Piece piece, vector<Square>& vec)
{
    for (Offset offset: patterns[piece])
    {
        target(sq, offset)

        if (valid_square(r, f))
        {
            vec.push_back(Spot(r, f));
        }
    }
}

void Pseudo::init(Config config)
{
    for (Square sq = 0; sq < board_size; ++sq)
    {
        for (Piece piece: {King, Knight})
        {
            calculate_crawl_squares(sq, piece, crawl[sq][piece % 3]);
        }

        /*
        for (Offset offset: patterns[King])
        {
            target(sq, offset)

            if (valid_square(r, f)) crawl[sq][King % 4].push_back(Spot(r, f));
        }*/


        /*
        if (valid_square(1, 3))
        {
            crawl[sq][King % 4].push_back(Spot(1,3));
        }
        */
        



        /*
        for (Offset offset: {Offset(S, S, Crawl)}) //patterns[King]
        {
            target(sq, offset)

            if (valid_square(r, f))
            {
                crawl[sq][King % 4].push_back(Spot(r, f));
            }
        }

        */


        /*
*/
    }
}
/*
namespace pseudo
{


void calculate_crawl_squares()
{
    iterate_crawl
    {
        for (Offset offset: patterns[piece])
        {
            target(sq, offset)

            if (valid_square(r, f))
            {
                crawl_squares[sq][piece % 5].push_back(Spot(r, f));
            }
        }
    }
}

void calculate_slide_squares(Piece piece)
{
    iterate_slide
    {
        target(sq, offset)

        while (valid_square(r, f))
        {
            slide_squares[sq][offset].push_back(sq, Spot(r, f));

            update(r, f, offset)
        }
    }
}

void calculate_push_squares()
{
    iterate_march
    {
        for (Offset offset: patterns[Pawn])
        {
            switch (offset.flag)
            {
                case Push:
                {
                    if (valid)
                    {

                    }

                    if (homerank || torpedo && valid1 && valid2)
                    {

                    }

                    break;
                }

                case SideWays:
                {
                    if (rules.sideways && valid)
                    {

                    }

                    break;
                }

                case Advance:
                {
                    if (valid)
                    {

                    }

                    break;
                }
            
                default: break;  
            }
        }
    }
}

void calculate_advance_squares()
{
    iterate_march
    {
        for (Offset offset: patterns[Pawn])
        {
            
        }
    }
}

void calculate_promotion_squares()
{

}

void calculate_passing_squares()
{
    iterate_castle
    {

    }
}

void calculate_secure_squares()
{
    iterate_castle
    {

    }
}

void calculate_castle_squares()
{
    iterate_castle
    {

    }
}

void init()
{

}

void reset()
{
    iterate()
    {

    }
}

}; // namespace
*/

/*


void calculate_slide_moves(const Square origin, const Piece piece, Offset offset)
{
    Spot destination(origin);

    destination += offset;

    while (destination.valid())
    {
        slide_moves[origin][offset.direction()].emplace(origin, destination.square());

        destination += offset;
    }
}



void pseudo::calculate_crawl_moves(const Square origin, const Piece piece, const Offset offset)
{
    Spot destination(origin);

    destination += offset;

    if (destination.valid())
    {
        crawl_moves[origin][piece].emplace(origin, destination.square());
    }
}



void pseudo::calculate_all_moves()
{
    for (const Piece piece: {King, Queen, Rook, Bishop, Knight, Pawn})
    {
        calculate_moves(piece);
    }



    for (const Square sq: board::valid_squares)
    {
        for (const Piece piece: {King, Queen, Rook, Bishop, Knight, Pawn})
        {
            for (const Offest offset: offsets[piece])
            {
                switch (offset.flag)
                {
                    case Crawl: 
                    case Slide:
                    case Push:
                    case Advance:

                    break;
                
                default:
                    break;
                }
            }





            for (const Direction& dir: directions[piece])
            {
                switch (piece)
                {
                    case Pawn:   calculate_march_moves(sq, piece, dir); break;
                    case Knight: calculate_crawl_moves(sq, piece, dir); break;
                    case Bishop: calculate_slide_moves(sq, piece, dir); break;
                    case Rook:   calculate_slide_moves(sq, piece, dir); break;
                    case Queen:  calculate_slide_moves(sq, piece, dir); break;
                    case King:   calculate_crawl_moves(sq, piece, dir); break;
                
                    default: break;
                }
            }
        }
    }

    calculate_enpassant_moves();

    calculate_castle_moves();
}

inline void pseudo::calculate_moves(Piece piece)
{
    for (const Square sq: board::valid_squares)
    {
        for (const Offset offset: offsets[piece])
        {
            switch (offset.flag)
            {
                case Crawl: calculate_crawl_moves(); break;
                case Slide: calculate_slide_moves(); break;
                case Push:  calculate_push_moves();  break;
                case March: calculate_march_moves(); break;
            
                default: break;
            }
        }
    }
}

void pseudo::calculate_push_moves(const Square origin)
{
    Spot destination(origin);

    destination += offset;

    if (destination.valid())
    {

    }
}

void pseudo::calculate_march_moves(const Square origin)
{
    Spot destination(origin);

    destination += offset;

    if (destination.valid())
    {
        
    }
}

void pseudo::calculate_march_moves(const Square origin, const Piece piece, const Offset offset)
{
    switch (offset.flag)
    {
        case Push:    calculate_push_moves();    break;
        case Advance: calculate_advance_moves(); break;
        
    
        default: break;
    }




    Spot destination(origin);



    switch (offset.flag)
    {
        case Push:
        {

        }

        break;
    
    default:
        break;
    }


    // push
    // double push
    // 




    int r = rank(sq) + dir.horizontal;
    int f = file(sq) + dir.vertical;

    if (is_valid_square(r, f))
    {
        if (dir.flag == Push)
        {
            calculate_promote_moves();
        }

        else if (dir.flag == DoublePush)
        {

        }

        else if (dir.flag == Advance)
        {

        }
    }






    int r1 = rank(sq) + dir.horizontal, f1 = file(sq) + dir.vertical;
    int r2 = rank(sq) + 2 * dir.horizontal, f2 = file(sq) + 2 * dir.vertical;

    if (isValidSquare(r1, f1))
    {
        if (dir.flag == SideWays)
        {
            if (Config::SIDE_WAYS) promote(sq, square(r1, f1), Config::OFFBOARD, piece, dir.player, Flag::Push);
        }

        else if (dir.flag == Push)
        {

            promote(sq, square(r1, f1), Config::OFFBOARD, piece, dir.player, Flag::Push);


            if (isValidSquare(r2, f2) && (Config::TORPERDO || isHomeRankSquare(sq, dir.player))) promote(sq, square(r2, f2), square(r1, f1), piece, dir.player, Flag::DoublePush);
        }
    }


    int r = rank(sq) + dir.horizontal, f = file(sq) + dir.vertical;

    if (isValidSquare(r, f))
    {

        promote(sq, square(r, f), Config::OFFBOARD, piece, dir.player, Flag::Advance);


        if (!Config::NO_ENPASSANT)
        {
            promote(sq, loc, Config::OFFBOARD, piece, dir.player, Flag::Enpassant);
        }
        
    }
}

void pseudo::calculate_promotion_moves()
{



    if (tile.promotion(player))
    {
        for (const Piece promotion: config::promotion_list)
        {
            calculated_march_moves[][].emplace_promotion(from, to, );
        }
    }

    else
    {
        
    }




        if (isPromotionSquare(loc, player))
    {
        for (const Piece promote: Config::PROMOTION_LIST)
        {
            LookupTable::PSEUDO_LEGAL[hashSquarePiecePlayer(sq, piece, player)].emplace_back(sq, loc, piece, player, promote, marked, flag | Promotion);
        }
    }

    else LookupTable::PSEUDO_LEGAL[hashSquarePiecePlayer(sq, piece, player)].emplace_back(sq, loc, piece, player, Piece::Empty, marked, flag);
}














*/


/*

#include "lookup_table.h"
#include "config.h"




#define hashPass() (0)
#define hashPlayer(player) (player)
#define hashPlayerSide(player, side) (player << Config::SIDE_BITS ^ side)
#define hashSquarePiece(square, piece) (square << Config::PIECE_BITS ^ piece)
#define hashSquarePieceRay(square, piece, ray) (((square << Config::PIECE_BITS ^ piece) << Config::RAY_BITS) ^ ray)
#define hashSquarePiecePlayer(square, piece, player) (((square << Config::PIECE_BITS ^ piece) << Config::PLAYER_BITS) ^ player)
#define hashSquarePiecePlayerFlag(square, piece, player, flag) (((square << Config::PIECE_BITS ^ piece) << Config::PLAYER_BITS) ^ player)
#define hashSquareOffset(square, offset) (0)
#define hashPieceOffsetFlag(piece, offset, flag) (0)
#define hashSquareFlag(square, flag) (0) // OFFSETS
#define hashSquarePlayerFlag(square, player, flag) (0) // OFFSETS



Ray ray(const int horizontal, const int vertical);




#define rank(sq) (sq / Config::COL_SIZE)
#define file(sq) (sq % Config::COL_SIZE)
#define square(r, f) (static_cast<Square>(r * Config::COL_SIZE + f))

static bool isPromotionSquare(const Square sq, const Player player)
{
    switch (player)
    {
        case (Red):    return rank(sq) == Config::PROMOTION_RANK;
        case (Blue):   return file(sq) == Config::PROMOTION_RANK;
        case (Yellow): return rank(sq) == Config::MAX_RANK - Config::PROMOTION_RANK;
        case (Green):  return file(sq) == Config::MAX_FILE - Config::PROMOTION_RANK;

        default: return false;
    }
}

static bool isHomeRankSquare(const Square sq, const Player player)
{
    switch (player)
    {
        case (Red):    return rank(sq) == Config::HOME_RANK || rank(sq) == (Config::HOME_RANK - 1); 
        case (Blue):   return file(sq) == Config::HOME_RANK || file(sq) == (Config::HOME_RANK - 1);
        case (Yellow): return rank(sq) == Config::MAX_RANK - Config::HOME_RANK || rank(sq) == (Config::MAX_RANK - Config::HOME_RANK + 1);
        case (Green):  return file(sq) == Config::MAX_FILE - Config::HOME_RANK || file(sq) == (Config::MAX_RANK - Config::HOME_RANK + 1);

        default: return false;
    }
}

static bool isValidSquare(const int r, const int f)
{
    if (r < 0) return false;
    if (f < 0) return false;
    if (r > Config::MAX_RANK) return false;
    if (f > Config::MAX_FILE) return false;
    
    return Config::BRICKS[square(r, f)] == false;
}
--------------------------------------------------------------------------

inline static void leap(const Square sq, const Piece piece, const Direction& dir)
{
    const int r = rank(sq) + dir.horizontal, f = file(sq) + dir.vertical;

    if (isValidSquare(r, f))
    {
        LookupTable::PSEUDO_LEGAL[hash(sq, piece)].emplace_back(sq, square(r, f), piece, Flag::Leap);
    }
}

inline static void slide(const Square sq, const Piece piece, const Direction& dir)
{
    int r = rank(sq) + dir.horizontal, f = file(sq) + dir.vertical;

    while (isValidSquare(r, f))
    {
        LookupTable::PSEUDO_LEGAL[hash(sq, piece, ray(dir.horizontal, dir.vertical))].emplace_back(sq, square(r, f), piece, Flag::Slide);

        r += dir.horizontal, f += dir.vertical;
    }
}

inline static void push(const Square sq, const Piece piece, const Direction& dir)
{
    int r1 = rank(sq) + dir.horizontal, f1 = file(sq) + dir.vertical;
    int r2 = rank(sq) + 2 * dir.horizontal, f2 = file(sq) + 2 * dir.vertical;

    if (isValidSquare(r1, f1))
    {
        if (dir.flag == SideWays)
        {
            if (Config::SIDE_WAYS) promote(sq, square(r1, f1), Config::OFFBOARD, piece, dir.player, Flag::Push);
        }

        else if (dir.flag == Push)
        {
       
            promote(sq, square(r1, f1), Config::OFFBOARD, piece, dir.player, Flag::Push);

         
            if (isValidSquare(r2, f2) && (Config::TORPERDO || isHomeRankSquare(sq, dir.player))) promote(sq, square(r2, f2), square(r1, f1), piece, dir.player, Flag::DoublePush);
        }
    }
}

inline static void advance(const Square sq, const Piece piece, const Direction& dir)
{
    int r = rank(sq) + dir.horizontal, f = file(sq) + dir.vertical;

    if (isValidSquare(r, f))
    {
        
        promote(sq, square(r, f), Config::OFFBOARD, piece, dir.player, Flag::Advance);

     
        if (!Config::NO_ENPASSANT)
        {
            promote(sq, loc, Config::OFFBOARD, piece, dir.player, Flag::Enpassant);
        }
        
    }
}

inline static void promote(const Square sq, const Square loc, const Square marked, const Piece piece, const Player player, const Flag flag)
{
    if (isPromotionSquare(loc, player))
    {
        for (const Piece promote: Config::PROMOTION_LIST)
        {
            LookupTable::PSEUDO_LEGAL[hashSquarePiecePlayer(sq, piece, player)].emplace_back(sq, loc, piece, player, promote, marked, flag | Promotion);
        }
    }

    else LookupTable::PSEUDO_LEGAL[hashSquarePiecePlayer(sq, piece, player)].emplace_back(sq, loc, piece, player, Piece::Empty, marked, flag);
}

inline static void castle()
{
    
}


void PSEUDO::allocate()
{
    for (const Square& sq: BOARD::VALID_SQUARES)
    {
        for (const Piece& piece: PIECE::PIECE_LIST)
        {
            // allocate leap //
            if (PIECE::LEAP_ABILITY[piece])
            {
                LEAP[hashSquarePiece(sq, piece)] = std::vector<Move>();
            }

            // allocate slide //
            for (const Ray& ray: PSEUDO::RAY[hashSquarePiece(sq, piece)])
            {
                SLIDE[hashSquarePieceRay(sq, piece, ray)] = std::vector<Move>();
            }

            // allocate push and advance //
            for (const Color& player: PLAYER::COLOR_LIST)
            {
                PUSH[hashSquarePiecePlayer(sq, piece, player)] = std::vector<Move>();
                ADVANCE[hashSquarePiecePlayer(sq, piece, player)] = std::vector<Move>();
                ENPASSANT[hashSquarePiecePlayer(sq, piece, player)] = std::vector<Move>();
            }
        }
    }

    // allocate castle //
}

void PSEUDO::deallocate()
{
    for (const Square& sq: BOARD::VALID_SQUARES)
    {
        for (const Piece& piece: PIECE::PIECE_LIST)
        {
            
        }
    }
}


void LookupTable::initialize()
{
    for (const Square sq: Config::VALID_SQUARES)
    {
        for (const Piece piece: Config::PIECE_LIST)
        {
            for (const Direction& dir: PIECE::DIRECTIONS[piece])
            {
                switch (dir.flag)
                {
                    case (Leap):     leap(sq, piece, dir);     break;
                    case (Slide):    slide(sq, piece, dir);    break;
                    case (Push):     push(sq, piece, dir);     break;
                    case (SideWays): push(sq, piece, dir);     break;
                    case (Advance):  advance(sq, piece, dir);  break;

                    default: break;
                }
            }
        }
    }

    PSEUDO::castle();
}


void init(Piece piece, std::vector<Direction> directions)
{
    for (const Square sq: Config::VALID_SQUARES)
    {  
        for (const Direction& dir: directions)
        {
            switch (dir.flag)
            {
                case (Leap):     leap(sq, piece, dir);     break;
                case (Slide):    slide(sq, piece, dir);    break;
                case (Push):     push(sq, piece, dir);     break;
                case (SideWays): push(sq, piece, dir);     break;
                case (Advance):  advance(sq, piece, dir);  break;

                default: break;
            }
        }
    }
}

*/