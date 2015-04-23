#pragma once

#define	GET_MASK(mask, color) (mask << color)
#define REV_MASK(mask, color) (mask >> color)
#define REV_COLOR(color) color == BLACK ? WHITE : BLACK

enum eColor
{
	BLACK = 0,
	WHITE = 1
}; 

enum		eMasks
{
	HAS_ONE = 1,
	HAS_ONE_W = 2,
	TWO = 4,
	TWO_W = 8,
	THREE = 16,
	THREE_W = 32,
	FOUR = 64,
	FOUR_W = 128,
	FIVE = 256,
	FIVE_W = 512
};