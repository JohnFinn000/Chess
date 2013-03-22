/*
 * =====================================================================================
 *
 *       Filename:  constants.h
 *
 *    Description:  This holds a lot of the constants used in the chess engine. 
 *    			Theres a lot of them because having a bunch of stuff precalculated
 *    			makes the program run a lot faster. I probably will never notice the
 *    			speed increase but all the lines and lines of hex stuff look cool.
 *
 *        Version:  1.0
 *        Created:  09/14/2012 03:46:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (JF), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <inttypes.h>

#define PAWN_LAYER    0
#define ROOK_LAYER    1
#define BISCHOP_LAYER 2
#define KNIGHT_LAYER  3
#define KING_LAYER    4
#define QUEEN_LAYER   5

#define BLACK_OFFSET 0
#define WHITE_OFFSET 6

#define BLACK_PAWN    BLACK_OFFSET + PAWN_LAYER
#define BLACK_ROOK    BLACK_OFFSET + ROOK_LAYER
#define BLACK_BISCHOPS BLACK_OFFSET + BISCHOP_LAYER
#define BLACK_KNIGHTS  BLACK_OFFSET + KNIGHT_LAYER
#define BLACK_KING    BLACK_OFFSET + KING_LAYER
#define BLACK_QUEEN   BLACK_OFFSET + QUEEN_LAYER

#define WHITE_PAWN    WHITE_OFFSET + PAWN_LAYER
#define WHITE_ROOK    WHITE_OFFSET + ROOK_LAYER
#define WHITE_BISCHOPS WHITE_OFFSET + BISCHOP_LAYER
#define WHITE_KNIGHTS  WHITE_OFFSET + KNIGHT_LAYER
#define WHITE_KING    WHITE_OFFSET + KING_LAYER
#define WHITE_QUEEN   WHITE_OFFSET + QUEEN_LAYER

const uint64_t initial_black_pawns    = 0x00FF000000000000;
const uint64_t initial_black_rooks    = 0x8100000000000000;
const uint64_t initial_black_bischops = 0x2400000000000000;
const uint64_t initial_black_knights  = 0x4200000000000000;
const uint64_t initial_black_king     = 0x0800000000000000;
const uint64_t initial_black_queen    = 0x1000000000000000;

const uint64_t initial_white_pawns    = 0x000000000000FF00;
const uint64_t initial_white_rooks    = 0x0000000000000081;
const uint64_t initial_white_bischops = 0x0000000000000024;
const uint64_t initial_white_knights  = 0x0000000000000042;
const uint64_t initial_white_king     = 0x0000000000000008;
const uint64_t initial_white_queen    = 0x0000000000000010;

const uint64_t file[8] = {
0x0101010101010101, // a file
0x0202020202020202,
0x0404040404040404,
0x0808080808080808,
0x1010101010101010,
0x2020202020202020,
0x4040404040404040,
0x8080808080808080, // h file
};

const uint64_t rank[8] = {
0x00000000000000FF, // 1 rank
0x000000000000FF00,
0x0000000000FF0000,
0x00000000FF000000,
0x000000FF00000000,
0x0000FF0000000000,
0x00FF000000000000,
0xFF00000000000000, // 8 rank
};

const uint64_t coord_table[8][8] = {
{ 0x0000000000000001, 0x0000000000000002, 0x0000000000000004, 0x0000000000000008, 0x0000000000000010, 0x0000000000000020, 0x0000000000000040, 0x0000000000000080 },
{ 0x0000000000000100, 0x0000000000000200, 0x0000000000000400, 0x0000000000000800, 0x0000000000001000, 0x0000000000002000, 0x0000000000004000, 0x0000000000008000 },
{ 0x0000000000010000, 0x0000000000020000, 0x0000000000040000, 0x0000000000080000, 0x0000000000100000, 0x0000000000200000, 0x0000000000400000, 0x0000000000800000 },
{ 0x0000000001000000, 0x0000000002000000, 0x0000000004000000, 0x0000000008000000, 0x0000000010000000, 0x0000000020000000, 0x0000000040000000, 0x0000000080000000 },
{ 0x0000000100000000, 0x0000000200000000, 0x0000000400000000, 0x0000000800000000, 0x0000001000000000, 0x0000002000000000, 0x0000004000000000, 0x0000008000000000 },
{ 0x0000010000000000, 0x0000020000000000, 0x0000040000000000, 0x0000080000000000, 0x0000100000000000, 0x0000200000000000, 0x0000400000000000, 0x0000800000000000 },
{ 0x0001000000000000, 0x0002000000000000, 0x0004000000000000, 0x0008000000000000, 0x0010000000000000, 0x0020000000000000, 0x0040000000000000, 0x0080000000000000 },
{ 0x0100000000000000, 0x0200000000000000, 0x0400000000000000, 0x0800000000000000, 0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000 },
};

const uint64_t black_squares = 0xAA55AA55AA55AA55;
const uint64_t white_squares = 0x55AA55AA55AA55AA;
const uint64_t universe      = 0xFFFFFFFFFFFFFFFF;
const uint64_t empty         = 0x0000000000000000;

#define PAWN_CHAR    'P'
#define ROOK_CHAR    'R'
#define BISCHOP_CHAR 'B'
#define KNIGHT_CHAR  'N'
#define KING_CHAR    'K'
#define QUEEN_CHAR   'Q'

// errors
#define ERR_BAD_COORDS 1
#define ERR_NO_PIECE   2

struct error_code {
	int error_num;
	char error_name[80];

};

