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

#define PAWN_LAYER    = 0
#define ROOK_LAYER    = 0
#define BISCHOP_LAYER = 0
#define KNIGHT_LAYER  = 0
#define KING_LAYER    = 0
#define QUEEN_LAYER   = 0

#define BLACK_OFFSET = 0
#define WHITE_OFFSET = 6

#define BLACK_PAWN    BLACK_OFFSET + PAWN_LAYER
#define BLACK_ROOK    BLACK_OFFSET + ROOK_LAYER
#define BLACK_BISCHOP BLACK_OFFSET + BISCHOP_LAYER
#define BLACK_KNIGHT  BLACK_OFFSET + KNIGHT_LAYER
#define BLACK_KING    BLACK_OFFSET + KING_LAYER
#define BLACK_QUEEN   BLACK_OFFSET + QUEEN_LAYERS

#define WHITE_PAWN    WHITE_OFFSET + PAWN_LAYER
#define WHITE_ROOK    WHITE_OFFSET + ROOK_LAYER
#define WHITE_BISCHOP WHITE_OFFSET + BISCHOP_LAYER
#define WHITE_KNIGHT  WHITE_OFFSET + KNIGHT_LAYER
#define WHITE_KING    WHITE_OFFSET + KING_LAYER
#define WHITE_QUEEN   WHITE_OFFSET + QUEEN_LAYER

#define INITIAL_BLACK_PAWNS    0x00FF00000000000000
#define INITIAL_BLACK_ROOKS    0x810000000000000000
#define INITIAL_BLACK_BISCHOPS 0x240000000000000000
#define INITIAL_BLACK_KNIGHTS  0x420000000000000000
#define INITIAL_BLACK_KING     0x080000000000000000
#define INITIAL_BLACK_QUEEN    0x100000000000000000

#define INITIAL_WHITE_PAWNS    0x00000000000000FF00
#define INITIAL_WHITE_ROOKS    0x000000000000000081
#define INITIAL_WHITE_BISCHOPS 0x000000000000000024
#define INITIAL_WHITE_KNIGHTS  0x000000000000000042
#define INITIAL_WHITE_KING     0x000000000000000008
#define INITIAL_WHITE_QUEEN    0x000000000000000010

#define RANK_A 
#define RANK_B 
#define RANK_C 
#define RANK_D 
#define RANK_E 
#define RANK_F 
#define RANK_G 
#define RANK_H

#define FILE_A 
#define FILE_B 
#define FILE_C 
#define FILE_D 
#define FILE_E 
#define FILE_F 
#define FILE_G 
#define FILE_H

#define BLACK_SQUARES
#define WHITE_SQUARES

#define BLACK_PIECES ( board[0] | board[1] | board[2] | board[3] | board[4]  | board[5]  )
#define WHITE_PIECES ( board[6] | board[7] | board[8] | board[9] | board[10] | board[11] )

#define PAWN_CHAR    'P'
#define ROOK_CHAR    'R'
#define BISCHOP_CHAR 'B'
#define KNIGHT_CHAR  'H'
#define KING_CHAR    'K'
#define QUEEN_CHAR   'Q'


int board[12] = {

INITIAL_BLACK_PAWNS,
INITIAL_BLACK_ROOKS,
INITIAL_BLACK_BISCHOPS,
INITIAL_BLACK_KNIGHTS,
INITIAL_BLACK_KING,
INITIAL_BLACK_QUEEN,

INITIAL_WHITE_PAWNS,
INITIAL_WHITE_ROOKS,
INITIAL_WHITE_BISCHOPS,
INITIAL_WHITE_KNIGHTS,
INITIAL_WHITE_KING,
INITIAL_WHITE_QUEEN,

};

class Engine {

	int move( char fx, char fy, char tx, char ty ) {
		if( fx > 7 || fy > 7 ) {
			return ERR_BAD_COORDS;
		}
		if( tx > 7 || ty > 7 ) {
			return ERR_BAD_COORDS;
		}

		int from = 1 << ( fx + ( fy << 3 ) );
		int to   = 1 << ( tx + ( ty << 3 ) );

		for( int i = 0; i < 12; ++i ) {
			if( board[i] & ( from ) ) {
				break;
			}
		}
		if( i == 12 ) {
			return ERR_NO_PIECE;
		}

		int black = BLACK_PIECES;
		int white = WHITE_PIECES;
		
		switch( i ) {

		case BLACK_PAWN:
			if( fy == 6 ) {

			}
		case BLACK_ROOK:
		case BLACK_BISCHOPS:
		case BLACK_KNIGHTS:
		case BLACK_KING:
		case BLACK_QUEEN:

		case WHITE_PAWN:
			if( fy == 1 ) {

			}
		case WHITE_ROOK:
		case WHITE_BISCHOPS:
		case WHITE_KNIGHTS:
		case WHITE_KING:
		case WHITE_QUEEN:

		}

	}

	int test( char x, char y ) {
		int coord = 1 << ( x + ( y << 3 ) );

		for( int i = 0; i < 12; ++i ) {
			if( board[i] & coord ) {
				break;
			}
		}
		return i;

	}

	int test_check() {


	}

	void reset_board() {

		board[BLACK_PAWN]     = INITIAL_BLACK_PAWNS;
		board[BLACK_ROOK]     = INITIAL_BLACK_ROOKS;
		board[BLACK_BISCHOPS] = INITIAL_BLACK_BISCHOPS;
		board[BLACK_KNIGHTS]  = INITIAL_BLACK_KNIGHTS;
		board[BLACK_KING]     = INITIAL_BLACK_KING;
		board[BLACK_QUEEN]    = INITIAL_BLACK_QUEEN;

		board[WHITE_PAWN]     = INITIAL_WHITE_PAWNS;
		board[WHITE_ROOK]     = INITIAL_WHITE_ROOKS;
		board[WHITE_BISCHOPS] = INITIAL_WHITE_BISCHOPS;
		board[WHITE_KNIGHTS]  = INITIAL_WHITE_KNIGHTS;
		board[WHITE_KING]     = INITIAL_WHITE_KING;
		board[WHITE_QUEEN]    = INITIAL_WHITE_QUEEN;
	}

	void convert_bitboard_array( ) {
		char arr_board[8][8];
		for( int i = 0; i < 8; ++i ) {
			for( int k = 0; k < 8; ++k ) {
				arr_board[i][k] = test( i, k ); 
			}
		}
	}

	void print_board( char** str_board ) {
		char arr_board[8][8];
		for( int i = 0; i < 8; ++i ) {
			for( int k = 0; k < 8; ++k ) {
				str_board[i+(k*8)] = '#';
			}
		}
	}

}




