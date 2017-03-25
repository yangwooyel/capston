#pragma once

#include <utility>  // pair사용
#define MAX 12
#define MAX2 14

typedef enum { BLANK, BLACK, WHITE } State; // State 에 3가지만 들어간다.
typedef std::pair<int, int> Points;  // Point로 재정의해서 x,y를 받는다.

struct Pos
{
	State state;
	bool checked;
	double weight;

};

class Board
{
public:
	Pos pos[MAX2][MAX] = { BLANK, false, 1.0 };  //pos 초기값 할당
public:
	void Put(State state, int x, int y);
};