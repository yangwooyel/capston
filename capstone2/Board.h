#pragma once

#include <utility>  // pair���
#define MAX 12
#define MAX2 14

typedef enum { BLANK, BLACK, WHITE } State; // State �� 3������ ����.
typedef std::pair<int, int> Points;  // Point�� �������ؼ� x,y�� �޴´�.

struct Pos
{
	State state;
	bool checked;
	double weight;

};

class Board
{
public:
	Pos pos[MAX2][MAX] = { BLANK, false, 1.0 };  //pos �ʱⰪ �Ҵ�
public:
	void Put(State state, int x, int y);
};