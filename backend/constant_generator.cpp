/*
 * =====================================================================================
 *
 *       Filename:  knight_calculation.cpp
 *
 *    Description:  calculates knight movement
 *
 *        Version:  1.0
 *        Created:  11/10/2012 06:47:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

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
{0x0000000000000001, 0x0000000000000100, 0x0000000000010000, 0x0000000001000000, 0x0000000100000000, 0x0000010000000000, 0x0001000000000000, 0x0100000000000000, },
{0x0000000000000002, 0x0000000000000200, 0x0000000000020000, 0x0000000002000000, 0x0000000200000000, 0x0000020000000000, 0x0002000000000000, 0x0200000000000000, },
{0x0000000000000004, 0x0000000000000400, 0x0000000000040000, 0x0000000004000000, 0x0000000400000000, 0x0000040000000000, 0x0004000000000000, 0x0400000000000000, },
{0x0000000000000008, 0x0000000000000800, 0x0000000000080000, 0x0000000008000000, 0x0000000800000000, 0x0000080000000000, 0x0008000000000000, 0x0800000000000000, },
{0x0000000000000010, 0x0000000000001000, 0x0000000000100000, 0x0000000010000000, 0x0000001000000000, 0x0000100000000000, 0x0010000000000000, 0x1000000000000000, },
{0x0000000000000020, 0x0000000000002000, 0x0000000000200000, 0x0000000020000000, 0x0000002000000000, 0x0000200000000000, 0x0020000000000000, 0x2000000000000000, },
{0x0000000000000040, 0x0000000000004000, 0x0000000000400000, 0x0000000040000000, 0x0000004000000000, 0x0000400000000000, 0x0040000000000000, 0x4000000000000000, },
{0x0000000000000080, 0x0000000000008000, 0x0000000000800000, 0x0000000080000000, 0x0000008000000000, 0x0000800000000000, 0x0080000000000000, 0x8000000000000000, },
};

/*
void diagnol() {
	for( int i = 0; i < 8; ++i ) {
		printf("{ " );
		uint64_t a = coord_table[i][7];
		printf("0x%016lX, ", a );
		printf("},\n");
	}
}
*/

uint64_t get_file( int x ) {
    uint64_t bitboard = 0;
    for( int k = 0; k < 8; ++k ) {
        bitboard |= coord_table[x][k];
    }
    return bitboard;
}

uint64_t get_rank( int y ) {
    uint64_t bitboard = 0;
    for( int k = 0; k < 8; ++k ) {
        bitboard |= coord_table[k][y];
    }
    return bitboard;
}

void file_generator() {
    printf("const uint64_t file[8] = {\n");
    for( int i = 0; i < 8; ++i ) {
        printf("0x%016lX, // %c file\n", get_file(i), 'a'+i );
    }
    printf("};\n");
}

void rank_generator() {
    printf("const uint64_t rank[8] = {\n");
    for( int i = 0; i < 8; ++i ) {
        printf("0x%016lX, // %d rank\n", get_rank(i), i );
    }
    printf("};\n");
}

void diagnol_generator() {
    printf("const uint64_t diagnol[8] = {\n");
    for( int i = 0; i < 8; ++i ) {

    }
    printf("};\n");

}

void antidiagnol_generator() {
    printf("const uint64_t anitdiagnol[8] = {\n");
    for( int i = 0; i < 8; ++i ) {

    }
    printf("};\n");

}

void initial_generator( ) {

    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "white", "pawns", get_rank(1) );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "white", "bischops", coord_table[3][0] | coord_table[6][0] );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "white", "rooks", coord_table[2][0] | coord_table[5][0] );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "white", "knights", coord_table[1][0] | coord_table[7][0] );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "white", "king", coord_table[5][0] );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "white", "queen", coord_table[4][0] );

    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "black", "pawns", get_rank(6) );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "black", "bischops", coord_table[3][6] | coord_table[6][6] );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "black", "rooks", coord_table[2][6] | coord_table[5][6] );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "black", "knights", coord_table[1][6] | coord_table[7][6] );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "black", "king", coord_table[5][6] );
    printf("const uint64_t initial_%s_%s\t\t= 0x%016lX;\n", "black", "queen", coord_table[4][6] );

}

void king_movement_generator() {
    printf("const uint64_t king_movement[8][8] = {\n");
	for( int i = 0; i < 8; ++i ) {
		printf("{ " );
		for( int k = 0; k < 8; ++k ) { 
			uint64_t a = 
			(coord_table[i][k] << 1) |
			(coord_table[i][k] >> 1) |
			(coord_table[i][k] << 9) |
			(coord_table[i][k] >> 9) |
			(coord_table[i][k] << 8) |
			(coord_table[i][k] >> 8) |
			(coord_table[i][k] << 7) |
			(coord_table[i][k] >> 7);
			printf("0x%016lX, ", a );
			/*for( int y = 0; y < 8; ++y ) {
				for( int x = 0; x < 8; ++x ) {
					if( (a & ((uint64_t) 1) << (x+(y*8))) > 0 ) {
						printf("1 " );
					} else {
						printf("0 " );
					}

				}
				printf("\n");
			}*/
		}
		printf("},\n");
	}
    printf("};\n");
}

void knight_movement_generator() {
    printf("const uint64_t knight_movement[8][8] = {\n");
	for( int i = 0; i < 8; ++i ) {
		printf("{ " );
		for( int k = 0; k < 8; ++k ) { 
			uint64_t a = ((coord_table[i][k] << 17) & ~file[0]) |
			((coord_table[i][k] << 10) & ~(file[0]|file[1])) |
			((coord_table[i][k] >> 6 ) & ~(file[0]|file[1])) |
			((coord_table[i][k] >> 15) & ~file[0]) |
			((coord_table[i][k] << 15) & ~file[7]) |
			((coord_table[i][k] << 6 ) & ~(file[7]|file[6])) |
			((coord_table[i][k] >> 10) & ~(file[7]|file[6])) |
			((coord_table[i][k] >> 17) & ~file[7]);
			printf("0x%016lX, ", a );
			/*for( int y = 0; y < 8; ++y ) {
				for( int x = 0; x < 8; ++x ) {
					if( (a & ((uint64_t) 1) << (x+(y*8))) > 0 ) {
						printf("1 " );
					} else {
						printf("0 " );
					}

				}
				printf("\n");
			}*/
		}
		printf("},\n");
	}
    printf("};\n");
}

uint64_t get_coord( uint64_t x, uint64_t y ) {
    return ((uint64_t) 1) << (x+(y*8));
}

void coord_table_generator() {
    printf("const uint64_t coord_table[8][8] = {\n");
    for( int x = 0; x < 8; ++x ) {
        printf("{ ");
        for( int y = 0; y < 8; ++y ) {
            printf("0x%016lX, ", get_coord( x, y ) );
        }
        printf("},\n");
    }
    printf("};\n");
}

void fill_right_generator() {

}

void fill_left_generator() {

}

void fill_down_generator() {

}

void fill_up_generator() {

}

void fill_diagnol_generator() {

}

void fill_antidiagnol_generator() {

}

int main() {

    file_generator();
    printf("\n");

    rank_generator();
    printf("\n");

    diagnol_generator();
    printf("\n");

    antidiagnol_generator();
    printf("\n");

    initial_generator();
    printf("\n");

	king_movement_generator();
    printf("\n");

	knight_movement_generator();
    printf("\n");

    coord_table_generator();
    printf("\n");

    fill_right_generator();
    printf("\n");

    fill_down_generator();
    printf("\n");

    fill_diagnol_generator();
    printf("\n");

    fill_antidiagnol_generator();
    printf("\n");
}

