#include "Al.h"

Points AISetPos(Board board)
{
	int ex, ey;
	double max_weight;

	ex = ey = 0;
	max_weight = 1.0;

	for (int i = 0; i < MAX2; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (board.pos[i][j].weight > max_weight && board.pos[i][j].state == 0)
			{
				ex = i, ey = j;
				max_weight = board.pos[i][j].weight;
			}
		}
	}  //돌을 두지 않은곳의 가장큰 가중치를구해서 좌표를 뽑아낸다...

	Points pt = std::make_pair(ex, ey);
	return pt;
}