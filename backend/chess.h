/*
 * =====================================================================================
 *
 *       Filename:  chess.h
 *
 *    Description:  Chess engine using bit boards
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

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "compilation_settings.h"


class Board {
public:
    uint64_t board[12];
    // these are just aliases to the different layers
    uint64_t &black_pawn;
    uint64_t &black_rook;
    uint64_t &black_bischops;
    uint64_t &black_knights;
    uint64_t &black_king;
    uint64_t &black_queen;
    uint64_t &white_pawn;
    uint64_t &white_rook;
    uint64_t &white_bischops;
    uint64_t &white_knights;
    uint64_t &white_king;
    uint64_t &white_queen;

	Board();
	uint64_t get_all();
	uint64_t get_white();
	uint64_t get_black();
	uint64_t get_pawn_moves(     int x, int y, int side );
	uint64_t get_pawn_attack(    int x, int y, int side );
	uint64_t get_rook_moves(     int x, int y, int side );
	uint64_t get_rook_attack(    int x, int y, int side );
	uint64_t get_bischop_moves(  int x, int y, int side );
	uint64_t get_bischop_attack( int x, int y, int side );
	uint64_t get_knight_moves(   int x, int y, int side );
	uint64_t get_knight_attack(  int x, int y, int side );
	uint64_t get_king_moves(     int x, int y, int side );
	uint64_t get_king_attack(    int x, int y, int side );
	uint64_t get_queen_moves(    int x, int y, int side );
	uint64_t get_queen_attack(   int x, int y, int side );

	uint64_t get_moves(  int x, int y );
	uint64_t get_attack( int x, int y );

	void reset();
	int get_layer( int x, int y );


	char* convert_bitboard_array( );
	void print_board( );
	void print_bitboard( );
	void print_bitboard( uint64_t board );
};

struct move_data {
    int piece       : 3;
    int from_column : 3;
    int from_row    : 3;
    int to_column   : 3;
    int to_row      : 3;

    int capture : 1; // 0 - false, 1 - true
    int check   : 2; // 0 - false, 1 - check, 2 - mate
    int castle  : 2; // 0 - false, 1 - kingside, 2 - queenside
};

// move is not meant to do error checking only to resolve disambiguity in the notation
class Move {
    Move( int piece, int from_column, int from_row, int to_column, int to_row );
    Move( int piece, char from_column, int from_row, char to_column, int to_row );
    Move( int from_column, int from_row, int to_column, int to_row );
    Move( int from_column, int from_row, char to_column, int to_row );
    Move( int from_column, int to_column, int to_row );
    Move( int from_column, char to_column, int to_row );

    void get_full_algebraic_notation( char note[] );

private:
    move_data *data;

};

class Engine {
public:
	Board *board;

	Engine();
	Engine( Board *existing_board );
	int move( int fx, int fy, int tx, int ty );

};

