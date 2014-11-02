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
#include <stdio.h>
#include <cstring>


Board::Board() {
	reset();
}

uint64_t Board::get_all() {
	return ( board[6] | board[7] | board[8] | board[9] | board[10] | board[11] ) |
	       ( board[0] | board[1] | board[2] | board[3] | board[4]  | board[5]  );
}

uint64_t Board::get_white() {
	return ( board[6] | board[7] | board[8] | board[9] | board[10] | board[11] );
}

uint64_t Board::get_black() {
	return ( board[0] | board[1] | board[2] | board[3] | board[4]  | board[5] );
}

uint64_t Board::get_color( int color ) {

    switch( color ) {
        case WHITE:
            return ( board[6] | board[7] | board[8] | board[9] | board[10] | board[11] );
        case BLACK:
            return ( board[0] | board[1] | board[2] | board[3] | board[4]  | board[5] );
    }
}

uint64_t Board::get_pawn_moves( int x, int y, int side ) {

    return 0;
}

uint64_t Board::get_pawn_attack( int x, int y, int side ) {

    return 0;
}

uint64_t Board::get_rook_moves( int x, int y, int side ) {
	
	uint64_t movement = ROOK_MOVEMENT( x, y ) & ~get_all();
	uint64_t coord = coord_table[x][y];
    uint64_t temp = coord;
	for( int i = x+1; i < 8; ++i ) { // right
        if( !(movement & (temp <<= 1)) ) {
            // erase from here onward
            movement &= ~FILL_RIGHT( temp, x );
        }
    }
	for( int i = x-1; i >= 0; --i ) { // left
        if( !(movement & (temp /= 2)) ) {
            // erase from here onward
            movement &= ~FILL_LEFT( temp, y );
        }
    }
	//for( int i = y-1; i >= 0; --i ) { // up
    //    if( !(movement & (temp /= 256)) ) {
    //        // erase from here onward
    //        movement = FILL_UP( temp, x, i );
    //    }
    //}
	for( int i = y+1; i < 8; ++i ) { // down
        if( !(movement & (temp *= 256)) ) {
            // erase from here onward
            movement &= ~FILL_DOWN( temp, x );
        }
    }
	return movement;
}

uint64_t Board::get_rook_attack( int x, int y, int side ) {
    return get_rook_moves( x, y, side ) & get_color( 1-side );
}

uint64_t Board::get_bischop_moves( int x, int y, int side ) {
	return BISCHOP_MOVEMENT( x, y );
}

uint64_t Board::get_bischop_attack( int x, int y, int side ) {
    return get_bischop_moves( x, y, side ) & get_color( 1-side );
}

uint64_t Board::get_knight_moves( int x, int y, int side ) {
    return KNIGHT_MOVEMENT( x, y ) & ~get_color( side );
}

uint64_t Board::get_knight_attack( int x, int y, int side ) {
    return get_knight_moves( x, y, side ) & get_color( 1-side );
}

uint64_t Board::get_king_moves( int x, int y, int side ) {
    return KING_MOVEMENT( x, y ) & ~get_color( side );
}

uint64_t Board::get_king_attack( int x, int y, int side ) {
    return get_king_moves( x, y, side ) & get_color( 1-side );
}

uint64_t Board::get_queen_moves( int x, int y, int side ) {
	return QUEEN_MOVEMENT( x, y );
}

uint64_t Board::get_queen_attack( int x, int y, int side ) {
    return get_queen_moves( x, y, side ) & get_color( 1-side );
}

uint64_t Board::get_under_attack( int x, int y, int side ) {

    return get_pawn_attack( x, y, side ) |
            get_rook_attack( x, y, side ) |
            get_bischop_attack( x, y, side ) |
            get_knight_attack( x, y, side ) |
            get_king_attack( x, y, side ) |
            get_queen_attack( x, y, side );
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

    flags = 0xC03; // en passant flags off and castling flags on
}

void Board::move( int fx, int fy, int tx, int ty ) {

    move_data new_move;
    new_move.from_column    = fx;
    new_move.from_row       = fy;
    new_move.to_column      = tx;
    new_move.to_row         = ty;

	int layer = get_layer( fx, fy );
    new_move.piece = layer % 6;

	int attack = get_layer( tx, ty );
    if( attack != 12 ) {
        board[attack] &= ~coord_table[tx][ty];
        new_move.capture = 1;
    } else {
        new_move.capture = 0;
    }

    // look for check
    
    // castling
    if( layer == WHITE_KING ) {
        if( coord_table[tx][ty] & WHITE_QUEENSIDE_CASTLE_SQUARE ) {
            if( flags & white_queenside_castle ) {
                new_move.castle = 2;
                flags &= ~white_castle; // no more castling
            }
        } else if( coord_table[tx][ty] & WHITE_KINGSIDE_CASTLE_SQUARE ) {
            if( flags & white_kingside_castle ) {
                new_move.castle = 1;
                flags &= ~white_castle; // no more castling
            }
        }
    }

    if( layer == BLACK_KING ) { // is it a king
        if( coord_table[tx][ty] & BLACK_QUEENSIDE_CASTLE_SQUARE ) {
            if( flags & black_queenside_castle ) {
                new_move.castle = 2;
                flags &= ~black_castle; // no more castling
            }
        } else if( coord_table[tx][ty] & BLACK_KINGSIDE_CASTLE_SQUARE ) {
            if( flags & black_kingside_castle ) {
                new_move.castle = 1;
                flags &= ~black_castle; // no more castling
            }
        }
    }

    // move the actual piece
    board[layer] &= ~coord_table[fx][fy]; // turn off a bit
    board[layer] |= coord_table[tx][ty];  // turn on a bit

}


// finds the layer that has a piece on the coordinate specified
// returns 12 if there is no piece on that place
int Board::get_layer( int x, int y ) {
	int layer;
	for( layer = 0; layer < 12; ++layer ) {
		if( board[layer] & coord_table[x][y] ) {
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
	for( int x = 0; x <= 7; ++x ) {
		printf("%c ", 'A' + x );
	}
	printf("\n\n");
	for( int y = 0; y < 8; ++y ) {
		printf("%d   ", y );
		for( int x = 0; x < 8; ++x ) {
			switch( arr_board[x+(y*8)] ) {
			// Black layers
			case BLACK_PAWN:     printf("%c ", PAWN_CHAR );       break;
			case BLACK_ROOK:     printf("%c ", ROOK_CHAR );       break;
			case BLACK_BISCHOPS: printf("%c ", BISCHOP_CHAR );    break;
			case BLACK_KNIGHTS:  printf("%c ", KNIGHT_CHAR );     break;
			case BLACK_KING:     printf("%c ", KING_CHAR );       break;
			case BLACK_QUEEN:    printf("%c ", QUEEN_CHAR );      break;

			// White layers
			case WHITE_PAWN:     printf("%c ", PAWN_CHAR+32 );    break;
			case WHITE_ROOK:     printf("%c ", ROOK_CHAR+32 );    break;
			case WHITE_BISCHOPS: printf("%c ", BISCHOP_CHAR+32 ); break;
			case WHITE_KNIGHTS:  printf("%c ", KNIGHT_CHAR+32 );  break;
			case WHITE_KING:     printf("%c ", KING_CHAR+32 );    break;
			case WHITE_QUEEN:    printf("%c ", QUEEN_CHAR+32 );   break;

			case 12: // print checkerboard pattern
				if( (x+y) % 2 == 0 ) {
					printf("%c ", '+' );
				} else {
					printf("%c ", '-' );
				}
				break;
			}
			
		}
		printf("  %d\n", y );
	}
	printf("\n    ");
	for( int x = 0; x <= 7; ++x ) {
		printf("%c ", 'A' + x );
	}
	printf("\n");
}

void Board::print_flags() {
    printf("Flags:\n");
	for( int i = 0; i < 20; ++i ) {
        printf(" [%c]\t%s\n", (flags & 1 << i) ? 'X' : ' ', flag_name[i] );
	}
}

void Board::print_bitboard() {
	for( int i = 0; i < 12; ++i ) {
        printf("%s\n", piece_name[i] );
        print_bitboard( board[i] );
	}
}

void Board::print_bitboard( uint64_t board ) {
    for( int y = 0; y < 8; ++y ) {
        for( int x = 0; x < 8; ++x ) {
            if( board & coord_table[x][y] > 0 ) {
                printf("1 ");
            } else {
                printf("0 ");
            }
            
        }
        printf("\n");
    }
    printf("\n");
}

Engine::Engine() {
	board = new Board();
}

Engine::Engine( Board *existing_board ) {
	board = existing_board;
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
        if( fx == tx ) {
            if( fy == 6 ) { // still in home row
                if( ty == 4 ) {
                    // turn on the proper en passant flag
                    
                    
                }
            }
        }
        break;
	case BLACK_ROOK:
        if( coord_table[tx][ty] & board->get_rook_moves( fx, fy, BLACK ) ) {
            board->move( fx, fy, tx, ty );
        }
        break;
	case BLACK_BISCHOPS:
        if( coord_table[tx][ty] & board->get_bischop_moves( fx, fy, BLACK ) ) {
            board->move( fx, fy, tx, ty );
        }
        break;
	case BLACK_KNIGHTS:
        if( coord_table[tx][ty] & board->get_knight_moves( fx, fy, BLACK ) ) {
            board->move( fx, fy, tx, ty );
        }
        break;
	case BLACK_KING:
        if( coord_table[tx][ty] & board->get_king_moves( fx, fy, BLACK ) ) {
            board->move( fx, fy, tx, ty );
        }
        break;
	case BLACK_QUEEN:
        if( coord_table[tx][ty] & board->get_queen_moves( fx, fy, BLACK ) ) {
            board->move( fx, fy, tx, ty );
        }
        break;

	// White layers
	case WHITE_PAWN:
		if( fy == 1 ) { // still in home row
            if( ty == 3 ) {
                // turn on the proper en passant flag
                
            }
		}
        break;
	case WHITE_ROOK:
        if( coord_table[tx][ty] & board->get_rook_moves( fx, fy, WHITE ) ) {
            board->move( fx, fy, tx, ty );
        }
        break;
	case WHITE_BISCHOPS:
        if( coord_table[tx][ty] & board->get_bischop_moves( fx, fy, WHITE ) ) {
            board->move( fx, fy, tx, ty );
        }
        break;
	case WHITE_KNIGHTS:
        if( coord_table[tx][ty] & board->get_knight_moves( fx, fy, WHITE ) ) {
            board->move( fx, fy, tx, ty );
        }
        break;
	case WHITE_KING:
        if( coord_table[tx][ty] & board->get_king_moves( fx, fy, WHITE ) ) {
            board->move( fx, fy, tx, ty );
        }
        break;
	case WHITE_QUEEN:
        if( coord_table[tx][ty] & board->get_queen_moves( fx, fy, WHITE ) ) {
            board->move( fx, fy, tx, ty );
        }
		break;
	}

	return 0;
}


int to_number( char letter ) {

    if( letter >= 'A' && letter <= 'H' ) {
        return letter - 'A';
    }
    if( letter >= 'a' && letter <= 'h' ) {
        return letter - 'a';
    }
    if( letter >= '0' && letter <= '9' ) {
        return letter - '0';
    }
    return -1; // an error occurred

}

void Move::get_full_algebraic_notation( char note[] ) {

    int index = 0;

    switch( data->castle ) {
    case 0: // no castle
        note[index] = piece_symbols[data->piece];
        index++;
        note[index] = 'A' + data->from_column;
        index++;
        note[index] = data->from_row;
        index++;
        if( data->capture == 1 ) { // capture move
            note[index] = 'X';
            index++;
        }
        note[index] = 'A' + data->to_column;
        index++;
        note[index] = data->to_row;
        index++;
        switch( data->check ) {
        case 0: // no check
            break;
        case 1: // check
            note[index] = '+';
            index++;
            break;
        case 2: // check mate
            note[index] = '#';
            index++;
            break;
        }
        break;
    case 1: // kingside
        strcpy( note+index, "O-O" );
        break;
    case 2: // queenside
        strcpy( note+index, "O-O-O" );
        break;
    }

}

int main() {
    Board *board = new Board();
    Engine *engine = new Engine( board );


    char buffer[32];

    for(;;) {
        printf("> ");
        fgets( buffer, 32, stdin );
        if( strncmp( "show", buffer, 4 ) == 0 ) {
            char second_option[10];
            sscanf( buffer, "%*s %s", second_option );
            printf("%s\n", second_option );
            if( strncmp( "rook", second_option, 4 ) == 0 ) {
                board->print_bitboard( board->get_rook_moves( 4, 4, 0 ) );
            }
            board->print_board();
        } else if( strncmp( "display", buffer, 7 ) == 0 ) {
            board->print_bitboard();
        } else if( strncmp( "flag", buffer, 4 ) == 0 ) {
            board->print_flags();
        } else {
            printf("%d %d %d %d %d\n", to_number(buffer[0]), to_number( buffer[1] ), to_number(buffer[2]), to_number( buffer[3] ),
            engine->move( to_number(buffer[0]), to_number(buffer[1]), to_number(buffer[2]), to_number(buffer[3]) ) );
            // it's a move
        }
    }
}

