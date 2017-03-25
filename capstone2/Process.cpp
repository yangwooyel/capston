#include "Process.h"
#include <cmath>

int checkpos[4][2] = {
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, 0 }

};

int lncheckpos[4][2] = {
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, 0 },
};

void setWeight(Board *board)
{
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < MAX2; i++)
			for (int j = 0; j < MAX; j++)
				board->pos[i][j].checked = false; // false�� �ʱ�ȭ

		for (int i = 0; i < MAX2; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (board->pos[i][j].state == 1 && board->pos[i][j].checked == false)
				{	//�������̰� false �̸�
					int cnt = 0;
					int tx = i, ty = j;
					while (board->pos[tx][ty].state == 1 &&
						tx >= 0 && ty >= 0 && tx <= MAX2 && ty <= MAX)
					{
						cnt++;
						board->pos[tx][ty].checked = true;
						tx += checkpos[k][0];//-1  
						ty += checkpos[k][1];//1   
					}
					if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX2 && j - checkpos[k][1] <= MAX)
					{
						if (board->pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							board->pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(2.1, cnt * cnt);
						else board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.8, cnt * cnt);
					}
					if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX2 && ty + checkpos[k][1] <= MAX)
					{
						if (board->pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							board->pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) board->pos[tx][ty].weight *= pow(2.1, cnt * cnt);
						else board->pos[tx][ty].weight *= pow(1.8, cnt * cnt);
					}
				}  //������ if end

				if (board->pos[i][j].state == 2 && board->pos[i][j].checked == false)
				{	//������̰� false �̸�
					for (int l = 0; l < 8; l++)
					{
						if (i + checkpos[l][0] >= 0 && j + checkpos[l][1] >= 0 && i + checkpos[l][0] <= MAX2 && j + checkpos[l][1] <= MAX)
							board->pos[i + checkpos[l][0]][j + checkpos[l][1]].weight *= 1.08;
					}

					int cnt = 0;
					int tx = i, ty = j;
					while (board->pos[tx][ty].state == 2 &&
						tx >= 0 && ty >= 0 && tx <= MAX2 && ty <= MAX)
					{
						cnt++;
						board->pos[tx][ty].checked = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt > 1)
					{
						if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX2 && j - checkpos[k][1] <= MAX)
							board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.2, cnt * cnt * 2);
						if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX2&& ty + checkpos[k][1] <= MAX)
							board->pos[tx][ty].weight *= pow(1.2, cnt * cnt * 2);
					}
				} //��� if end
			}
		}
	}
}

void doPut(State state, Board *board, Points pt)
{
	board->Put(state, pt.first, pt.second);	 //Board.cpp

}

State getWinner(Board board)
{
	int cnt, tx, ty;
	bool p1win, p2win;

	p1win = p2win = false;

	for (int i = 0; i < MAX2; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (board.pos[i][j].state == BLACK)
			{
				for (int k = 0; k < 8; k++)
				{
					cnt = 0;
					tx = i, ty = j;
					while (board.pos[tx][ty].state == BLACK &&
						tx >= 0 && ty >= 0 && tx < MAX2 && ty < MAX)
					{
						cnt++;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt == 5) p1win = true;
					else cnt = 0;
					if (p1win) break;
				}
			}
			if (p1win) break;
		}
		if (p1win) break;
	}
	if (p1win) return BLACK;


	for (int i = 0; i < MAX2; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (board.pos[i][j].state == WHITE)
			{
				for (int k = 0; k < 8; k++)
				{
					cnt = 0;
					tx = i, ty = j;
					while (board.pos[tx][ty].state == WHITE &&
						tx >= 0 && ty >= 0 && tx < MAX2 && ty < MAX)
					{
						cnt++;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt == 5) p2win = true;
					else cnt = 0;
					if (p2win) break;
				}
			}
			if (p2win) break;
		}
		if (p2win) break;
	}
	if (p2win) return WHITE;
}