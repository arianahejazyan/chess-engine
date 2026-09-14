#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <cstdint>

namespace athena {

// enum BoardRepresentation {
//     Athena,
//     ChessCom,
//     NoStones,
//     Compressed,
//     BORAD_REPRESENTATION
// };

// constexpr std::size_t BOARD_SIZE[BORAD_REPRESENTATION] = {
//     256, // 16x16 board
//     196, // 14x14 board: first/last row and column removed
//     160, // stone squares removed
//     216, // first/last 20 squares removed; index = sq - 20
// };

constexpr int
MOVETYPE_NB = 5, 
MOVEFLAG_NB = 4, 
MOVE_NB     = 256,
PLAY_NB     = 64,
HOMERANK    = 2, 
PROMOTES    = 11,
CRAWL_NB    = 8,
SLIDE_NB    = 4,
PUSH_NB     = 2, 
TAKE_NB     = 2,
RANK_NB     = 16, 
FILE_NB     = 16, 
STONE_NB    = 40,
VALID_NB    = 216, 
SQUARE_NB   = 256,
CHUNK_NB    = 4,
CHUNK_SIZE  = 64,
PIECE_NB    = 6,
COLOR_NB    = 4,
PIECECOLOR_NB = 64,
SETUP_NB    = 2,
SIDE_NB     = 2,
CASTLE_NB   = 256;

class Color {
public: 
    enum ID : uint8_t {
        Red    = 0,
        Blue   = 1,
        Yellow = 2,
        Green  = 3,
        None   = 4,
    };

    constexpr Color() noexcept = default;
    constexpr Color(ID id) noexcept : id_(id) {}

    Color(char c) noexcept {
        switch (c) {   
            case 'r': id_ = ID::Red   ; break;
            case 'b': id_ = ID::Blue  ; break;
            case 'y': id_ = ID::Yellow; break;
            case 'g': id_ = ID::Green ; break;
            default : id_ = ID::None  ; break;
        }
    }

    char uci() const noexcept {
        switch (id_) {   
            case ID::Red   : return 'r';
            case ID::Blue  : return 'b';
            case ID::Yellow: return 'y';
            case ID::Green : return 'g';
            default        : return '?';
        }
    }

    constexpr Color self() const noexcept { return Color(static_cast<ID>((static_cast<uint8_t>(id_) + 0) & 3)); }
    constexpr Color next() const noexcept { return Color(static_cast<ID>((static_cast<uint8_t>(id_) + 1) & 3)); }
    constexpr Color ally() const noexcept { return Color(static_cast<ID>((static_cast<uint8_t>(id_) + 2) & 3)); }
    constexpr Color prev() const noexcept { return Color(static_cast<ID>((static_cast<uint8_t>(id_) + 3) & 3)); }

    constexpr bool same(Color::ID color) const noexcept { return (static_cast<uint8_t>(id_) & 1) == (static_cast<uint8_t>(color) & 1); }
    constexpr bool diff(Color::ID color) const noexcept { return (static_cast<uint8_t>(id_) & 1) != (static_cast<uint8_t>(color) & 1); }
   
    Color rotate(Color perspective) const noexcept {
        return (id_ - perspective.id()) & 0b11;
    }

    constexpr ID id() const noexcept { return id_; }
    
private:
    ID id_;
};

inline constexpr bool operator==(Color lhs, Color rhs) noexcept { return lhs.id() == rhs.id(); }
inline constexpr bool operator!=(Color lhs, Color rhs) noexcept { return lhs.id() != rhs.id(); }

class Piece {
public: 
    enum ID : uint8_t {
        King   = 0,
        Knight = 1,
        Bishop = 2,
        Rook   = 3,
        Queen  = 4,
        Pawn   = 5,
        Empty  = 6,
        Stone  = 7,
    };

    constexpr Piece() noexcept = default;
    constexpr Piece(ID id) noexcept : id_(id) {}

    Piece(char c) noexcept {
        switch (c) {
            case 'P': id_ = ID::Pawn  ; break;
            case 'N': id_ = ID::Knight; break;
            case 'B': id_ = ID::Bishop; break;
            case 'R': id_ = ID::Rook  ; break;
            case 'Q': id_ = ID::Queen ; break;
            case 'K': id_ = ID::King  ; break;
            default : id_ = ID::Empty ; break;
        }    
    }

    char uci() const noexcept {
        switch (id_) {
            case ID::Pawn  : return 'P';
            case ID::Knight: return 'N';
            case ID::Bishop: return 'B';
            case ID::Rook  : return 'R';
            case ID::Queen : return 'Q';
            case ID::King  : return 'K';
            default        : return '?';
        }
    }

    constexpr ID id() const noexcept { return id_; }

private:
    ID id_;
};

inline constexpr bool operator==(Piece lhs, Piece rhs) noexcept { return lhs.id() == rhs.id(); }
inline constexpr bool operator!=(Piece lhs, Piece rhs) noexcept { return lhs.id() != rhs.id(); }

class Square {
public: 
    enum ID : uint8_t {
        A1 , B1 , C1 , D1 , E1 , F1 , G1 , H1 , I1 , J1 , K1 , L1 , M1 , N1 , O1 , P1 ,
        A2 , B2 , C2 , D2 , E2 , F2 , G2 , H2 , I2 , J2 , K2 , L2 , M2 , N2 , O2 , P2 ,
        A3 , B3 , C3 , D3 , E3 , F3 , G3 , H3 , I3 , J3 , K3 , L3 , M3 , N3 , O3 , P3 ,
        A4 , B4 , C4 , D4 , E4 , F4 , G4 , H4 , I4 , J4 , K4 , L4 , M4 , N4 , O4 , P4 ,
        A5 , B5 , C5 , D5 , E5 , F5 , G5 , H5 , I5 , J5 , K5 , L5 , M5 , N5 , O5 , P5 ,
        A6 , B6 , C6 , D6 , E6 , F6 , G6 , H6 , I6 , J6 , K6 , L6 , M6 , N6 , O6 , P6 ,
        A7 , B7 , C7 , D7 , E7 , F7 , G7 , H7 , I7 , J7 , K7 , L7 , M7 , N7 , O7 , P7 ,
        A8 , B8 , C8 , D8 , E8 , F8 , G8 , H8 , I8 , J8 , K8 , L8 , M8 , N8 , O8 , P8 ,
        A9 , B9 , C9 , D9 , E9 , F9 , G9 , H9 , I9 , J9 , K9 , L9 , M9 , N9 , O9 , P9 ,
        A10, B10, C10, D10, E10, F10, G10, H10, I10, J10, K10, L10, M10, N10, O10, P10,
        A11, B11, C11, D11, E11, F11, G11, H11, I11, J11, K11, L11, M11, N11, O11, P11,
        A12, B12, C12, D12, E12, F12, G12, H12, I12, J12, K12, L12, M12, N12, O12, P12,
        A13, B13, C13, D13, E13, F13, G13, H13, I13, J13, K13, L13, M13, N13, O13, P13,
        A14, B14, C14, D14, E14, F14, G14, H14, I14, J14, K14, L14, M14, N14, O14, P14,
        A15, B15, C15, D15, E15, F15, G15, H15, I15, J15, K15, L15, M15, N15, O15, P15,
        A16, B16, C16, D16, E16, F16, G16, H16, I16, J16, K16, L16, M16, N16, O16, P16,
    };

    enum class Offset : int {
        North = +16,
        South = -16,
        East  = +1 ,
        West  = -1 , 
        None  =  0 ,
    };

    using Index = uint8_t;
    using Chunk = uint8_t;
    using Rank  = uint8_t;
    using File  = uint8_t;

    constexpr Square() noexcept = default;
    constexpr Square(ID id) noexcept : id_(id) {}
    constexpr Square(File file, Rank rank) noexcept : id_(static_cast<ID>(file + FILE_NB * rank)) {}

    Square(std::string_view sv, bool board16x16 = false) noexcept {
        int rank = std::stoi(std::string(sv.substr(1))); 
        int file = sv[0] - 'a' + 1;
        if (board16x16) {
            rank--;
            file--;
        }
        *this = Square(static_cast<uint8_t>(file), static_cast<uint8_t>(rank));
    }

    std::string uci(bool board16x16 = false) const noexcept {
        int r = rank();
        int f = file() - 1;
        if (board16x16) {
            r++;
            f++;
        }
        return std::string(1, static_cast<char>('a' + f)) + std::to_string(r);
    }

    constexpr bool isValid() const noexcept { return !isStone(); }  
    constexpr bool isStone() const noexcept {
        auto r = rank();
        auto f = file();
        return 
            (r <= 0  || f <= 0 ) || 
            (r <= 3  && f <= 3 ) || 
            (r >= 12 && f >= 12) ||
            (r >= 15 || f >= 15) || 
            (r <= 3  && f >= 12) || 
            (r >= 12 && f <= 3 );   
    }

    constexpr Index index() const noexcept { return static_cast<uint8_t>(id_) & 63; } 
    constexpr Chunk chunk() const noexcept { return static_cast<uint8_t>(id_) >> 6; } 
    constexpr Rank  rank()  const noexcept { return static_cast<uint8_t>(id_) >> 4; } 
    constexpr File  file()  const noexcept { return static_cast<uint8_t>(id_) & 15; } 

    constexpr Square flip_file() { return static_cast<ID>(static_cast<uint8_t>(id_) ^ 0x0F); }
    constexpr Square flip_rank() { return static_cast<ID>(static_cast<uint8_t>(id_) ^ 0xF0); }
    constexpr Square flip_both() { return static_cast<ID>(static_cast<uint8_t>(id_) ^ 0xFF); }

    constexpr bool homerank(Color::ID color) const noexcept;
    constexpr bool promotes(Color::ID color) const noexcept;

    constexpr ID id() const noexcept { return id_; }
    constexpr std::size_t compact() const noexcept { return static_cast<std::size_t>(static_cast<uint8_t>(id_) - 20); }

    // constexpr Square compress() const noexcept {
    //     alignas(64) constexpr static std::array<uint8_t, SQUARE_NB> table = {
    //         0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    //         0,   0,   0,   0,   0,   1,   2,   3,   4,   5,   6,   7,   0,   0,   0,   0,
    //         0,   0,   0,   0,   8,   9,  10,  11,  12,  13,  14,  15,   0,   0,   0,   0,
    //         0,   0,   0,   0,  16,  17,  18,  19,  20,  21,  22,  23,   0,   0,   0,   0,
    //         0,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,   0,
    //         0,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,   0,
    //         0,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,   0,
    //         0,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,   0,
    //         0,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,   0,
    //         0,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107,   0,
    //         0, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,   0,
    //         0, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,   0,
    //         0,   0,   0,   0, 136, 137, 138, 139, 140, 141, 142, 143,   0,   0,   0,   0,
    //         0,   0,   0,   0, 144, 145, 146, 147, 148, 149, 150, 151,   0,   0,   0,   0,
    //         0,   0,   0,   0, 152, 153, 154, 155, 156, 157, 158, 159,   0,   0,   0,   0,
    //         0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    //   };
    //     return static_cast<Square::ID>(table[static_cast<uint8_t>(id_)]);
    // }

    constexpr Square rotate(Color color) const noexcept {
        alignas(64) constexpr static std::array<std::array<uint8_t, SQUARE_NB>, COLOR_NB> table = {{
            {
                0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                0,   0,   0,   0,   0,   1,   2,   3,   4,   5,   6,   7,   0,   0,   0,   0,
                0,   0,   0,   0,   8,   9,  10,  11,  12,  13,  14,  15,   0,   0,   0,   0,
                0,   0,   0,   0,  16,  17,  18,  19,  20,  21,  22,  23,   0,   0,   0,   0,
                0,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,   0,
                0,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,   0,
                0,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,   0,
                0,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,   0,
                0,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,   0,
                0,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107,   0,
                0, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,   0,
                0, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,   0,
                0,   0,   0,   0, 136, 137, 138, 139, 140, 141, 142, 143,   0,   0,   0,   0,
                0,   0,   0,   0, 144, 145, 146, 147, 148, 149, 150, 151,   0,   0,   0,   0,
                0,   0,   0,   0, 152, 153, 154, 155, 156, 157, 158, 159,   0,   0,   0,   0,
                0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
            },{
                0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                0,   0,   0,   0,  37,  51,  65,  79,  93, 107, 121, 135,   0,   0,   0,   0,
                0,   0,   0,   0,  36,  50,  64,  78,  92, 106, 120, 134,   0,   0,   0,   0,
                0,   0,   0,   0,  35,  49,  63,  77,  91, 105, 119, 133,   0,   0,   0,   0,
                0,   7,  15,  23,  34,  48,  62,  76,  90, 104, 118, 132, 143, 151, 159,   0,
                0,   6,  14,  22,  33,  47,  61,  75,  89, 103, 117, 131, 142, 150, 158,   0,
                0,   5,  13,  21,  32,  46,  60,  74,  88, 102, 116, 130, 141, 149, 157,   0,
                0,   4,  12,  20,  31,  45,  59,  73,  87, 101, 115, 129, 140, 148, 156,   0,
                0,   3,  11,  19,  30,  44,  58,  72,  86, 100, 114, 128, 139, 147, 155,   0,
                0,   2,  10,  18,  29,  43,  57,  71,  85,  99, 113, 127, 138, 146, 154,   0,
                0,   1,   9,  17,  28,  42,  56,  70,  84,  98, 112, 126, 137, 145, 153,   0,
                0,   0,   8,  16,  27,  41,  55,  69,  83,  97, 111, 125, 136, 144, 152,   0,
                0,   0,   0,   0,  26,  40,  54,  68,  82,  96, 110, 124,   0,   0,   0,   0,
                0,   0,   0,   0,  25,  39,  53,  67,  81,  95, 109, 123,   0,   0,   0,   0,
                0,   0,   0,   0,  24,  38,  52,  66,  80,  94, 108, 122,   0,   0,   0,   0,
                0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
            },{
                0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                0,   0,   0,   0, 159, 158, 157, 156, 155, 154, 153, 152,   0,   0,   0,   0,
                0,   0,   0,   0, 151, 150, 149, 148, 147, 146, 145, 144,   0,   0,   0,   0,
                0,   0,   0,   0, 143, 142, 141, 140, 139, 138, 137, 136,   0,   0,   0,   0,
                0, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122,   0,
                0, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108,   0,
                0, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97,  96,  95,  94,   0,
                0,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81,  80,   0,
                0,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,   0,
                0,  65,  64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,   0,
                0,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,   0,
                0,  37,  36,  35,  34,  33,  32,  31,  30,  29,  28,  27,  26,  25,  24,   0,
                0,   0,   0,   0,  23,  22,  21,  20,  19,  18,  17,  16,   0,   0,   0,   0,
                0,   0,   0,   0,  15,  14,  13,  12,  11,  10,   9,   8,   0,   0,   0,   0,
                0,   0,   0,   0,   7,   6,   5,   4,   3,   2,   1,   0,   0,   0,   0,   0,
                0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
            },{
                0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                0,   0,   0,   0, 122, 108,  94,  80,  66,  52,  38,  24,   0,   0,   0,   0,
                0,   0,   0,   0, 123, 109,  95,  81,  67,  53,  39,  25,   0,   0,   0,   0,
                0,   0,   0,   0, 124, 110,  96,  82,  68,  54,  40,  26,   0,   0,   0,   0,
                0, 152, 144, 136, 125, 111,  97,  83,  69,  55,  41,  27,  16,   8,   0,   0,
                0, 153, 145, 137, 126, 112,  98,  84,  70,  56,  42,  28,  17,   9,   1,   0,
                0, 154, 146, 138, 127, 113,  99,  85,  71,  57,  43,  29,  18,  10,   2,   0,
                0, 155, 147, 139, 128, 114, 100,  86,  72,  58,  44,  30,  19,  11,   3,   0,
                0, 156, 148, 140, 129, 115, 101,  87,  73,  59,  45,  31,  20,  12,   4,   0,
                0, 157, 149, 141, 130, 116, 102,  88,  74,  60,  46,  32,  21,  13,   5,   0,
                0, 158, 150, 142, 131, 117, 103,  89,  75,  61,  47,  33,  22,  14,   6,   0,
                0, 159, 151, 143, 132, 118, 104,  90,  76,  62,  48,  34,  23,  15,   7,   0,
                0,   0,   0,   0, 133, 119, 105,  91,  77,  63,  49,  35,   0,   0,   0,   0,
                0,   0,   0,   0, 134, 120, 106,  92,  78,  64,  50,  36,   0,   0,   0,   0,
                0,   0,   0,   0, 135, 121, 107,  93,  79,  65,  51,  37,   0,   0,   0,   0,
                0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        }}};
        return static_cast<ID>(table[color.id()][id_]);
    }

private:
    ID id_;

public:
    template<Piece::ID piece>
    static constexpr auto offsets() noexcept;

    template<Color::ID color>
    static constexpr auto offsets() noexcept;

    static constexpr Offset push(Color::ID color, int idx) noexcept;
    static constexpr Offset take(Color::ID color, int idx) noexcept;

    static constexpr Square middle(Square a, Square b) noexcept {
        return static_cast<Square::ID>((static_cast<uint8_t>(a.id_) + static_cast<uint8_t>(b.id_)) >> 1
        );
    }

    static constexpr Square::ID offboard() { return Square::ID::A1; }
};

inline constexpr bool Square::homerank(Color::ID color) const noexcept {
    switch (color) {
        case Color::ID::Red   : return (rank()               == HOMERANK) || (          rank()     == HOMERANK - 1);
        case Color::ID::Blue  : return (file()               == HOMERANK) || (          file()     == HOMERANK - 1);
        case Color::ID::Yellow: return (RANK_NB - rank() - 1 == HOMERANK) || (RANK_NB - rank() - 1 == HOMERANK - 1);
        case Color::ID::Green : return (FILE_NB - file() - 1 == HOMERANK) || (FILE_NB - file() - 1 == HOMERANK - 1);
        default: return false;
    }
}

inline constexpr bool Square::promotes(Color::ID color) const noexcept {
    switch (color) {
        case Color::ID::Red   : return (rank()               == PROMOTES);
        case Color::ID::Blue  : return (file()               == PROMOTES);
        case Color::ID::Yellow: return (RANK_NB - rank() - 1 == PROMOTES);
        case Color::ID::Green : return (FILE_NB - file() - 1 == PROMOTES);
        default: return false;
    }
}

inline constexpr bool operator==(Square lhs, Square rhs) noexcept { return lhs.id() == rhs.id(); }
inline constexpr bool operator!=(Square lhs, Square rhs) noexcept { return lhs.id() != rhs.id(); }

inline constexpr Square operator+(Square lhs, Square::Offset rhs) noexcept { return static_cast<Square::ID>(static_cast<uint8_t>(lhs.id()) + static_cast<int>(rhs)); }
inline constexpr Square operator-(Square lhs, Square::Offset rhs) noexcept { return static_cast<Square::ID>(static_cast<uint8_t>(lhs.id()) - static_cast<int>(rhs)); }

inline constexpr Square::ID operator+(Square::ID lhs, Square::Offset rhs) noexcept { return static_cast<Square::ID>(static_cast<uint8_t>(lhs) + static_cast<int>(rhs)); }
inline constexpr Square::ID operator-(Square::ID lhs, Square::Offset rhs) noexcept { return static_cast<Square::ID>(static_cast<uint8_t>(lhs) - static_cast<int>(rhs)); }

inline constexpr Square::Offset operator+(Square::Offset lhs, Square::Offset rhs) noexcept { return static_cast<Square::Offset>(static_cast<int>(lhs) + static_cast<int>(rhs)); }
inline constexpr Square::Offset operator-(Square::Offset lhs, Square::Offset rhs) noexcept { return static_cast<Square::Offset>(static_cast<int>(lhs) - static_cast<int>(rhs)); }

inline constexpr Square& operator+=(Square& sq, Square::Offset offset) noexcept { sq = sq + offset; return sq; }
inline constexpr Square& operator-=(Square& sq, Square::Offset offset) noexcept { sq = sq - offset; return sq; }

inline constexpr bool operator>(Square::Offset lhs, int rhs) noexcept { return static_cast<int>(lhs) > rhs; }
inline constexpr bool operator<(Square::Offset lhs, int rhs) noexcept { return static_cast<int>(lhs) < rhs; }

template<>
inline constexpr 
auto Square::offsets<Piece::ID::King>() noexcept {
    static constexpr std::array<Square::Offset, CRAWL_NB> offsets = {{
        Square::Offset::South + Square::Offset::West,
        Square::Offset::South                       ,
        Square::Offset::South + Square::Offset::East,
        Square::Offset::West                        ,
        Square::Offset::East                        ,
        Square::Offset::North + Square::Offset::West,
        Square::Offset::North                       ,
        Square::Offset::North + Square::Offset::East,
    }};
    return offsets;
}

template<>
inline constexpr 
auto Square::offsets<Piece::ID::Knight>() noexcept {
    static constexpr std::array<Square::Offset, CRAWL_NB> offsets = {{
        Square::Offset::South + Square::Offset::South + Square::Offset::West,
        Square::Offset::South + Square::Offset::South + Square::Offset::East,
        Square::Offset::South + Square::Offset::West  + Square::Offset::West,
        Square::Offset::South + Square::Offset::East  + Square::Offset::East,
        Square::Offset::North + Square::Offset::West  + Square::Offset::West,
        Square::Offset::North + Square::Offset::East  + Square::Offset::East,
        Square::Offset::North + Square::Offset::North + Square::Offset::West,
        Square::Offset::North + Square::Offset::North + Square::Offset::East,
    }};
    return offsets;
}

template<>
inline constexpr 
auto Square::offsets<Piece::ID::Bishop>() noexcept {
    static constexpr std::array<Square::Offset, SLIDE_NB> offsets = {{
        Square::Offset::South + Square::Offset::West,
        Square::Offset::South + Square::Offset::East,
        Square::Offset::North + Square::Offset::West,
        Square::Offset::North + Square::Offset::East,
    }};
    return offsets;
}

template<>
inline constexpr 
auto Square::offsets<Piece::ID::Rook>() noexcept {
    static constexpr std::array<Square::Offset, SLIDE_NB> offsets = {{
        Square::Offset::South,
        Square::Offset::West ,
        Square::Offset::East ,
        Square::Offset::North,
    }};
    return offsets;
}

template<>
inline constexpr 
auto Square::offsets<Color::ID::Red>() noexcept {
    static constexpr std::array<Square::Offset, TAKE_NB> offsets = {{
        Square::Offset::North + Square::Offset::East ,
        Square::Offset::North + Square::Offset::West ,
    }};
    return offsets;
}

template<>
inline constexpr 
auto Square::offsets<Color::ID::Blue>() noexcept {
    static constexpr std::array<Square::Offset, TAKE_NB> offsets = {{
        Square::Offset::South + Square::Offset::East ,
        Square::Offset::North + Square::Offset::East ,
    }};
    return offsets;
}

template<>
inline constexpr 
auto Square::offsets<Color::ID::Yellow>() noexcept {
    static constexpr std::array<Square::Offset, TAKE_NB> offsets = {{
        Square::Offset::South + Square::Offset::West ,
        Square::Offset::South + Square::Offset::East ,
    }};
    return offsets;
}

template<>
inline constexpr 
auto Square::offsets<Color::ID::Green>() noexcept {
    static constexpr std::array<Square::Offset, TAKE_NB> offsets = {{
        Square::Offset::North + Square::Offset::West,
        Square::Offset::South + Square::Offset::West,
    }};
    return offsets;
}

inline constexpr 
Square::Offset Square::push(Color::ID color, int idx) noexcept { // make function for push instead of doing here
    static constexpr std::array<Square::Offset, COLOR_NB * PUSH_NB> offsets = {
        Square::Offset::North , Square::Offset::North + Square::Offset::North,
        Square::Offset::East  , Square::Offset::East  + Square::Offset::East ,
        Square::Offset::South , Square::Offset::South + Square::Offset::South,
        Square::Offset::West  , Square::Offset::West  + Square::Offset::West ,
    };
    return offsets[static_cast<std::size_t>(static_cast<uint8_t>(color) * PUSH_NB + idx)];
}

inline constexpr 
Square::Offset Square::take(Color::ID color, int idx) noexcept {
    static constexpr std::array<Square::Offset, COLOR_NB * TAKE_NB> offsets = {
        Square::Offset::North + Square::Offset::East, Square::Offset::North + Square::Offset::West,
        Square::Offset::South + Square::Offset::East, Square::Offset::North + Square::Offset::East,
        Square::Offset::South + Square::Offset::West, Square::Offset::South + Square::Offset::East,
        Square::Offset::North + Square::Offset::West, Square::Offset::South + Square::Offset::West,
    };
    return offsets[static_cast<std::size_t>(static_cast<uint8_t>(color) * TAKE_NB + idx)];
}
    
class Castle {
public: 
    enum class Side : uint8_t 
    {
        KingSide  = 0,
        QueenSide = 1,
    };

    enum class Setup : uint8_t
    {
        Modern  = 0,
        Classic = 1,
    };

    using ID = uint8_t;

    constexpr Castle() noexcept = default;
    constexpr Castle(ID id) noexcept : id_(id) {}
    constexpr Castle(Color::ID color, Side side) noexcept 
        : id_(static_cast<uint8_t>(1 << (static_cast<int>(side) * COLOR_NB + static_cast<int>(color)))) {}

    Castle(std::string_view sv, Side side) noexcept {
        id_ = ID(0);
        if (sv[0] == '1') id_ |= Castle(Color::ID::Red   , side).id();
        if (sv[2] == '1') id_ |= Castle(Color::ID::Blue  , side).id();
        if (sv[4] == '1') id_ |= Castle(Color::ID::Yellow, side).id();
        if (sv[6] == '1') id_ |= Castle(Color::ID::Green , side).id();
    }

    std::string uci(Side side) const noexcept {
        std::string output = "";
        output += (id_ & Castle(Color::ID::Red   , side).id() ? '1' : '0'); output += ',';
        output += (id_ & Castle(Color::ID::Blue  , side).id() ? '1' : '0'); output += ',';
        output += (id_ & Castle(Color::ID::Yellow, side).id() ? '1' : '0'); output += ',';
        output += (id_ & Castle(Color::ID::Green , side).id() ? '1' : '0');
        return output; 
    }

    constexpr bool has(Castle other) const noexcept { return (id_ & other.id_) != 0; }
    constexpr void set(Castle other) noexcept { id_ |=  other.id_; }
    constexpr void pop(Castle other) noexcept { id_ &= ~other.id_; }

    constexpr ID id() const noexcept { return id_; }

private:
    ID id_;

    alignas(64)
    static constexpr 
    std::array<Square::ID, SETUP_NB * COLOR_NB * SIDE_NB * 8> table_ = 
    {
        Square::ID::I2 , Square::ID::K2 , Square::ID::L2 , Square::ID::J2 ,
        Square::ID::I2 , Square::ID::J2 , Square::ID::K2 , Square::ID::K2 ,
        Square::ID::I2 , Square::ID::G2 , Square::ID::E2 , Square::ID::H2 ,
        Square::ID::I2 , Square::ID::H2 , Square::ID::G2 , Square::ID::F2 ,
        Square::ID::B9 , Square::ID::B11, Square::ID::B12, Square::ID::B10,
        Square::ID::B9 , Square::ID::B10, Square::ID::B11, Square::ID::B11,
        Square::ID::B9 , Square::ID::B7 , Square::ID::B5 , Square::ID::B8 ,
        Square::ID::B9 , Square::ID::B8 , Square::ID::B7 , Square::ID::B6 ,
        Square::ID::H15, Square::ID::F15, Square::ID::E15, Square::ID::G15,
        Square::ID::H15, Square::ID::G15, Square::ID::F15, Square::ID::F15,
        Square::ID::H15, Square::ID::J15, Square::ID::L15, Square::ID::I15,
        Square::ID::H15, Square::ID::I15, Square::ID::J15, Square::ID::K15, 
        Square::ID::O8 , Square::ID::O6 , Square::ID::O5 , Square::ID::O7 ,
        Square::ID::O8 , Square::ID::O7 , Square::ID::O6 , Square::ID::O6 ,
        Square::ID::O8 , Square::ID::O10, Square::ID::O12, Square::ID::O9 ,
        Square::ID::O8 , Square::ID::O9 , Square::ID::O10, Square::ID::O11,
        Square::ID::I2 , Square::ID::K2 , Square::ID::L2 , Square::ID::J2 ,
        Square::ID::I2 , Square::ID::J2 , Square::ID::K2 , Square::ID::K2 ,
        Square::ID::I2 , Square::ID::G2 , Square::ID::E2 , Square::ID::H2 ,
        Square::ID::I2 , Square::ID::H2 , Square::ID::G2 , Square::ID::F2 ,
        Square::ID::B8 , Square::ID::B6 , Square::ID::B5 , Square::ID::B7 ,
        Square::ID::B8 , Square::ID::B7 , Square::ID::B6 , Square::ID::B6 ,
        Square::ID::B8 , Square::ID::B10, Square::ID::B12, Square::ID::B9 ,
        Square::ID::B8 , Square::ID::B9 , Square::ID::B10, Square::ID::B11,
        Square::ID::H15, Square::ID::F15, Square::ID::E15, Square::ID::G15,
        Square::ID::H15, Square::ID::G15, Square::ID::F15, Square::ID::F15,
        Square::ID::H15, Square::ID::J15, Square::ID::L15, Square::ID::I15,
        Square::ID::H15, Square::ID::I15, Square::ID::J15, Square::ID::K15, 
        Square::ID::O9 , Square::ID::O11, Square::ID::O12, Square::ID::O10,
        Square::ID::O9 , Square::ID::O10, Square::ID::O11, Square::ID::O11,
        Square::ID::O9 , Square::ID::O7 , Square::ID::O5 , Square::ID::O8 ,
        Square::ID::O9 , Square::ID::O8 , Square::ID::O7 , Square::ID::O6 , 
    };

private:
    static Square::ID square(Setup setup, Color::ID color, Side side,  int idx = 0) noexcept {
        return table_[
            64 * static_cast<int>(setup) +
            16 * static_cast<int>(color) + 
            8  * static_cast<int>(side ) + idx];
    }

public:
    static auto king_source(Setup setup, Color::ID color, Side side, int idx = 0) noexcept { return square(setup, color, side, idx + 0); }
    static auto king_target(Setup setup, Color::ID color, Side side, int idx = 0) noexcept { return square(setup, color, side, idx + 1); }
    static auto rook_source(Setup setup, Color::ID color, Side side, int idx = 0) noexcept { return square(setup, color, side, idx + 2); }
    static auto rook_target(Setup setup, Color::ID color, Side side, int idx = 0) noexcept { return square(setup, color, side, idx + 3); }
    static auto safe_square(Setup setup, Color::ID color, Side side, int idx = 0) noexcept { return square(setup, color, side, idx + 4); }
    static auto path_square(Setup setup, Color::ID color, Side side, int idx = 0) noexcept { return square(setup, color, side, idx + 5); }
};

inline constexpr bool operator==(Castle lhs, Castle rhs) noexcept { return lhs.id() == rhs.id(); }
inline constexpr bool operator!=(Castle lhs, Castle rhs) noexcept { return lhs.id() != rhs.id(); }

class PieceColor {
public:
    using ID = uint8_t;

    constexpr PieceColor() = default;
    constexpr PieceColor(ID id) noexcept : id_(id) {}
    constexpr PieceColor(Color::ID color, Piece::ID piece) 
        noexcept : id_(static_cast<ID>(
            (static_cast<uint8_t>(piece) << 3) | 
            (static_cast<uint8_t>(color)))) {}

    PieceColor(char color, char piece) noexcept {
        id_ = PieceColor(Color(color).id(), Piece(piece).id()).id_;
    }

    std::string uci() const noexcept {
        if (id_ == stone().id()) return "x";
        if (id_ == empty().id()) return "" ;
        return std::string{color().uci(), piece().uci()};
    }

    constexpr Piece piece() const noexcept { return Piece(static_cast<Piece::ID>(static_cast<int>(id_) >> 3)); }
    constexpr Color color() const noexcept { return Color(static_cast<Color::ID>(static_cast<int>(id_) &  7)); }

    constexpr ID id() const noexcept { return id_; }

private:
    ID id_;

public:
    static constexpr PieceColor stone() noexcept { return PieceColor(Color::ID::None, Piece::ID::Stone); };
    static constexpr PieceColor empty() noexcept { return PieceColor(Color::ID::None, Piece::ID::Empty); };
};

inline constexpr bool operator==(PieceColor lhs, PieceColor rhs) noexcept { return lhs.id() == rhs.id(); }
inline constexpr bool operator!=(PieceColor lhs, PieceColor rhs) noexcept { return lhs.id() != rhs.id(); }

class Move {
public: 
    enum class Policy : uint8_t {
        Normal = 0,
        Stride = 1,
        Evolve = 2,
        Enpass = 3,
        Castle = 4,
    };

    enum class Flag : uint8_t {
        Noisy = 0,
        Quiet = 1,
        Legal = 2,
    };

    constexpr Move() noexcept = default;
    constexpr Move(
        Square::ID   source, // 8 bits
        Square::ID   target, // 8 bits
        Piece::ID    evolve, // 3 bits
        Color::ID    enpass, // 3 bits
        Castle::Side castle, // 2 bits
        Move::Policy policy  // 3 bits
            ) noexcept : move_(
            (static_cast<uint32_t>(source) << 0 ) |
            (static_cast<uint32_t>(target) << 24) |
            (static_cast<uint32_t>(evolve) << 8 ) |
            (static_cast<uint32_t>(enpass) << 11) |
            (static_cast<uint32_t>(castle) << 14) |
            (static_cast<uint32_t>(policy) << 16) ) {}
 
    auto source() const noexcept { return static_cast<Square::ID  >((move_ & 255)        ); }
    auto target() const noexcept { return static_cast<Square::ID  >((move_ >> 24)        ); }
    auto evolve() const noexcept { return static_cast<Piece::ID   >((move_ >> 8 ) & 0b111); }
    auto enpass() const noexcept { return static_cast<Color::ID   >((move_ >> 11) & 0b111); }
    auto castle() const noexcept { return static_cast<Castle::Side>((move_ >> 14) & 0b001); }
    auto policy() const noexcept { return static_cast<Move::Policy>((move_ >> 16) & 0b111); } 
    
    std::string uci(bool board16x16 = false) const noexcept {
        std::string str = "";
        str += Square(source()).uci(board16x16);
        str += Square(target()).uci(board16x16);
        str += evolve() == Piece::ID::Empty ? "" : std::to_string(Piece(evolve()).uci());
        return str;
    }

private:
    uint32_t move_;
};

} // namespace athena