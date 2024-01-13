#include "constants.h"

void init_valid_squares()
{
    CONSTANTS::VALID_SQUARES.clear();
    
    for (int sq = 0; sq < CONSTANTS::ROWSIZE * CONSTANTS::COLSIZE; sq++)
    {
        if (config.bricks[sq] != Brick)
        {
            CONSTANTS::VALID_SQUARES.push_back(static_cast<Square>(sq));
        }
    }
}

void CONSTANTS::init_piece_to_string()
{
    PIECE_TO_STRING[King] = "K";
    PIECE_TO_STRING[Queen] = "Q";
    PIECE_TO_STRING[Rook] = "R";
    PIECE_TO_STRING[Bishop] = "B";
    PIECE_TO_STRING[Knight] = "N";
    PIECE_TO_STRING[Pawn] = "P";
    PIECE_TO_STRING[Amazon] = "A";
    PIECE_TO_STRING[Chancellor] = "E";
    PIECE_TO_STRING[Arch_Bishop] = "H";
    PIECE_TO_STRING[General] = "M";
    PIECE_TO_STRING[Wilde_Beest] = "V";
    PIECE_TO_STRING[Camel] = "C";
    PIECE_TO_STRING[Grass_hopper] = "G";
    PIECE_TO_STRING[Ferz] = "F";
    PIECE_TO_STRING[Wazir] = "W";
    PIECE_TO_STRING[Alfil] = "I";
    PIECE_TO_STRING[Dabbaba] = "S";
    PIECE_TO_STRING[Alibaba] = "Y";
    PIECE_TO_STRING[Xianqi_Horse] = "U";
    PIECE_TO_STRING[Dragon_Bishop] = "Δ";
    PIECE_TO_STRING[Knight_Rider] = "O";
    PIECE_TO_STRING[Camel_Rider] = "L";
    PIECE_TO_STRING[Alfil_Rider] = "J";
    PIECE_TO_STRING[Dabbaba_Rider] = "T";
    PIECE_TO_STRING[Alibaba_Rider] = "Z";
    PIECE_TO_STRING[Berolina] = "α";
    PIECE_TO_STRING[Soldier] = "β";
    PIECE_TO_STRING[Stone_General] = "γ";
    PIECE_TO_STRING[Sergeant] = "δ";
    PIECE_TO_STRING[Duck] = "Θ";
}

void CONSTANTS::INIT_STRING_TO_PIECE()
{
    STRING_TO_PIECE["X"] = Brick;
    STRING_TO_PIECE["K"] = King;
    STRING_TO_PIECE["Q"] = Queen;
    STRING_TO_PIECE["R"] = Rook;
    STRING_TO_PIECE["B"] = Bishop;
    STRING_TO_PIECE["N"] = Knight;
    STRING_TO_PIECE["P"] = Pawn;
    STRING_TO_PIECE["A"] = Amazon;
    STRING_TO_PIECE["E"] = Chancellor;
    STRING_TO_PIECE["H"] = Arch_Bishop;
    STRING_TO_PIECE["M"] = General;
    STRING_TO_PIECE["V"] = Wilde_Beest;
    STRING_TO_PIECE["C"] = Camel;
    STRING_TO_PIECE["G"] = Grass_hopper;
    STRING_TO_PIECE["F"] = Ferz;
    STRING_TO_PIECE["W"] = Wazir;
    STRING_TO_PIECE["I"] = Alfil;
    STRING_TO_PIECE["S"] = Dabbaba;
    STRING_TO_PIECE["Y"] = Alibaba;
    STRING_TO_PIECE["U"] = Xianqi_Horse;
    STRING_TO_PIECE["Δ"] = Dragon_Bishop;
    STRING_TO_PIECE["O"] = Knight_Rider;
    STRING_TO_PIECE["L"] = Camel_Rider;
    STRING_TO_PIECE["J"] = Alfil_Rider;
    STRING_TO_PIECE["T"] = Dabbaba_Rider;
    STRING_TO_PIECE["Z"] = Alibaba_Rider;
    STRING_TO_PIECE["α"] = Berolina;
    STRING_TO_PIECE["β"] = Soldier;
    STRING_TO_PIECE["γ"] = Stone_General;
    STRING_TO_PIECE["δ"] = Sergeant;
    STRING_TO_PIECE["Θ"] = Duck;
}


/*
PIECE_TO_STRING = 
    {
        {King, 'K'},
        {Queen, 'Q'},
        {Rook, 'R'},
        {Bishop, 'B'},
        {Knight, 'N'},
        {Pawn, 'P'},
        {Amazon, 'K'},
        {Chancellor, 'K'},
        {Archbishop, 'K'},
        {General, 'K'},
        {Wildebeest, 'K'},
        {Camel, 'K'},
        {Grasshopper, 'K'},
        {Ferz, 'K'},
        {Wazir, 'K'},
        {Alfil, 'K'},
        {Dabbaba, 'K'},
        {Alibaba, 'K'},
        {XianqiHorse, 'K'},
        {Dragon, 'Δ'},
        {KnightRider, 'K'},
        {CamelRider, 'K'},
        {AlfilRider, 'K'},
        {DabbabaRider, 'K'},
        {AlibabaRider, 'K'},
        {Berolina, 'α'},
        {Soldier, 'β'},
        {StoneGeneral, 'γ'},
        {Sergeant, 'δ'},
        {Duck, 'K'},
    };*/