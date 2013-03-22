/*
 * =====================================================================================
 *
 *       Filename:  chess.cpp
 *
 *    Description:  Chess engine using bit boards
 *    			I rewrite chess every once in a while. Everytime I see new
 *    			things to add and write it a lot better than the other version.
 *    			This is the first time I'm using bit boards so it will be interesting.
 *
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

#include "chess.h"

int main() {
	Engine *engine = new Engine();
	int fx, fy, tx, ty;
	while( true ) {
		char r, f;
		engine->board->print_board();
		printf("From: ");
		scanf("%c %c", &r, &f );
		fx = (int) r;
		fy = (int) f;
		printf("To: ");
		scanf("%c %c", &r, &f );
		tx = (int) r;
		ty = (int) f;
		printf("%d\r", engine->move( fx, fy, tx, ty ) );
	}

}

Board::Board() {
	reset();
}

uint64_t Board::get_all() {
	return ( board[6] | board[7] | board[8] | board[9] | board[10] | board[11] ) |
	       ( board[0] | board[1] | board[2] | board[3] | board[4]  | board[5] );
}

uint64_t Board::get_white() {
	return ( board[6] | board[7] | board[8] | board[9] | board[10] | board[11] );
}

uint64_t Board::get_black() {
	return ( board[0] | board[1] | board[2] | board[3] | board[4]  | board[5] );
}

void Board::reset() {
	// set the whole board back to the initial starting locations
	board[BLACK_PAWN]     = initial_black_pawns;
	board[BLACK_ROOK]     = initial_black_rooks;
	board[BLACK_BISCHOPS] = initial_black_bischops;
	board[BLACK_KNIGHTS]  = initial_black_knights;
	board[BLACK_KING]     = initial_black_king;
	board[BLACK_QUEEN]    = initial_black_queen;

	board[WHITE_PAWN]     = initial_white_pawns;
	board[WHITE_ROOK]     = initial_white_rooks;
	board[WHITE_BISCHOPS] = initial_white_bischops;
	board[WHITE_KNIGHTS]  = initial_white_knights;
	board[WHITE_KING]     = initial_white_king;
	board[WHITE_QUEEN]    = initial_white_queen;
}

// finds the layer that has a piece on the coordinate specified
// returns 12 if there is no piece on that place
int Board::get_layer( int x, int y ) {
	uint64_t coord = coord_table[x][y];
	int layer;
	for( layer = 0; layer < 12; ++layer ) {
		if( board[layer] & coord ) {
			break;
		}
	}
	return layer;

}

char* Board::convert_bitboard_array( ) {
	char *arr_board = (char*) malloc( sizeof(char) * 8 * 8 );
	for( int x = 0; x < 8; ++x ) {
		for( int y = 0; y < 8; ++y ) {
			arr_board[x+(y*8)] = get_layer( x, y ); 
		}
	}
	return arr_board;
}

void Board::print_board() { 
	char *arr_board = convert_bitboard_array();
	printf("    ");
	for( int x = 1; x <= 8; ++x ) {
		printf("%d ", x );
	}
	printf("\n\n");
	for( int y = 0; y < 8; ++y ) {
		printf("%c   ", 'A' + y );
		for( int x = 0; x < 8; ++x ) {
			switch( arr_board[x+(y*8)] ) {
			// Black layers
			case BLACK_PAWN:
				printf("%c ", PAWN_CHAR );
				break;
			case BLACK_ROOK:
				printf("%c ", ROOK_CHAR );
				break;
			case BLACK_BISCHOPS:
				printf("%c ", BISCHOP_CHAR );
				break;
			case BLACK_KNIGHTS:
				printf("%c ", KNIGHT_CHAR );
				break;
			case BLACK_KING:
				printf("%c ", KING_CHAR );
				break;
			case BLACK_QUEEN:
				printf("%c ", QUEEN_CHAR );
				break;

			// White layers
			case WHITE_PAWN:
				printf("%c ", PAWN_CHAR+32 );
				break;
			case WHITE_ROOK:
				printf("%c ", ROOK_CHAR+32 );
				break;
			case WHITE_BISCHOPS:
				printf("%c ", BISCHOP_CHAR+32 );
				break;
			case WHITE_KNIGHTS:
				printf("%c ", KNIGHT_CHAR+32 );
				break;
			case WHITE_KING:
				printf("%c ", KING_CHAR+32 );
				break;
			case WHITE_QUEEN:
				printf("%c ", QUEEN_CHAR+32 );
				break;
			case 12:
				if( (x+y) % 2 == 0 ) {
					printf("%c ", '+' );
				} else {
					printf("%c ", '-' );
				}
				break;
			}
			
		}
		printf("  %c\n", 'A' + y );
	}
	printf("\n    ");
	for( int x = 1; x <= 8; ++x ) {
		printf("%d ", x );
	}
	printf("\n");
}

void Board::print_bitboard() {
	for( int i = 0; i < 12; ++i ) {
		switch( i ) {
		case BLACK_PAWN:
			printf("BLACK PAWN\n ");
			break;
		case BLACK_ROOK:
			printf("BLACK ROOK\n ");
			break;
		case BLACK_BISCHOPS:
			printf("BLACK BISCHOPS\n ");
			break;
		case BLACK_KNIGHTS:
			printf("BLACK KNIGHT\n ");
			break;
		case BLACK_KING:
			printf("BLACK KING\n ");
			break;
		case BLACK_QUEEN:
			printf("BLACK QUEEN\n " );
			break;

		// White layers
		case WHITE_PAWN:
			printf("WHITE PAWN\n ");
			break;
		case WHITE_ROOK:
			printf("WHITE ROOK\n ");
			break;
		case WHITE_BISCHOPS:
			printf("WHITE BISCHOPS \n");
			break;
		case WHITE_KNIGHTS:
			printf("WHITE KNIGHTS \n");
			break;
		case WHITE_KING:
			printf("WHITE KING \n");
			break;
		case WHITE_QUEEN:
			printf("WHITE QUEEN \n");
			break;
		}
		for( int y = 0; y < 8; ++y ) {
			for( int x = 0; x < 8; ++x ) {
				if( (board[i] & ((uint64_t) 1) << (x+(y*8))) > 0 ) {
					printf("1 " );
				} else {
					printf("0 " );
				}
				
			}
			printf("\n");
		}
		printf("\n");
	}
}

Engine::Engine() {
	board = new Board();
}

int Engine::move( int fx, int fy, int tx, int ty ) {
	// make sure the request is in bounds
	if( fx > 7 || fy > 7 ) {
		return ERR_BAD_COORDS;
	}
	if( tx > 7 || ty > 7 ) {
		return ERR_BAD_COORDS;
	}

	// set up a bit board for the from and to locations
	int layer = board->get_layer( fx, fy );

	if( layer == 12 ) {
		return ERR_NO_PIECE; // there was no piece at the specified location
	}

	switch( layer ) {
	// Black layers
	case BLACK_PAWN:
		if( fy == 6 ) {

		}
	case BLACK_ROOK:
	case BLACK_BISCHOPS:
	case BLACK_KNIGHTS:
	case BLACK_KING:
	case BLACK_QUEEN:

	// White layers
	case WHITE_PAWN:
		if( fy == 1 ) {

		}
	case WHITE_ROOK:
	case WHITE_BISCHOPS:
	case WHITE_KNIGHTS:
	case WHITE_KING:
	case WHITE_QUEEN:
		break;
	}

	return 0;
}

uint64_t Engine::get_pawn_moves() {
}
uint64_t Engine::get_pawn_moves() {
}
uint64_t Engine::get_rook_moves() {
}
uint64_t Engine::get_rook_moves() {
}
uint64_t Engine::get_bischop_moves() {
}
uint64_t Engine::get_bischop_moves() {
}
uint64_t Engine::get_knight_moves() {
}
uint64_t Engine::get_knight_moves() {
}
uint64_t Engine::get_king_moves() {
}
uint64_t Engine::get_king_moves() {
}
uint64_t Engine::get_queen_moves() {
}
uint64_t Engine::get_queen_moves() {
}
