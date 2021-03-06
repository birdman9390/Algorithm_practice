#include<iostream>
using namespace std;

typedef struct VERTEX
{
	int row, col;
};

class Game
{
private:
	int N, H, M;
	bool **is_unavail;
	bool **is_used;

public:
	Game()
	{
	}
	void input()
	{
		int row, col;
		cin >> N >> M >> H;
		is_unavail = new bool*[N];
		is_used = new bool*[N];
		for (int i = 0; i < N; i++)
		{
			is_unavail[i] = new bool[H] {};
			is_used[i] = new bool[H] {};
		}
		for (int i = 0; i < M; i++)
		{

			cin >> col >> row;
			row--;
			col--;
			is_used[row][col] = true;
			is_unavail[row][col] = true;
			if (row - 1 >= 0)
			{
				is_unavail[row - 1][col] = true;
			}
			if (row + 1 < N)
			{
				is_unavail[row + 1][col] = true;
			}
		}
	}
	bool checkAnswer(VERTEX *vertices, int len)
	{
		switch (len)
		{
		case 0:
			for (int i = 0; i < N; i++)
			{
				int cur_x = i;
				for (int h = 0; h < H; h++)
				{
					if (is_used[cur_x][h])
					{
						cur_x++;
					}
					else if (cur_x > 0 && is_used[cur_x - 1][h])
					{
						cur_x--;
					}
				}
				if (cur_x != i)
					return false;
			}
			return true;
		case 1:
			for (int i = 0; i < N; i++)
			{
				int cur_x = i;
				for (int h = 0; h < H; h++)
				{
					if (is_used[cur_x][h] || ((vertices->row == cur_x)&&(vertices->col==h)))
					{
						cur_x++;
					}
					else if (cur_x > 0 && (is_used[cur_x - 1][h] || ((vertices->row == cur_x - 1) && (vertices->col == h))))
					{
						cur_x--;
					}
				}
				if (cur_x != i)
					return false;
			}
			return true;
		case 2:

			for (int i = 0; i < N; i++)
			{
				int cur_x = i;
				for (int h = 0; h < H; h++)
				{
					if (is_used[cur_x][h] || ((vertices->row == cur_x) && (vertices->col == h)) || (((vertices+1)->row == cur_x) && ((vertices+1)->col == h)))
					{
						cur_x++;
					}
					else if (cur_x > 0 && (is_used[cur_x - 1][h] || ((vertices->row == cur_x - 1) && (vertices->col == h)) || (((vertices + 1)->row == cur_x - 1) && ((vertices + 1)->col == h))))
					{
						cur_x--;
					}
				}
				if (cur_x != i)
					return false;
			}
			return true;
		case 3:
			for (int i = 0; i < N; i++)
			{
				int cur_x = i;
				for (int h = 0; h < H; h++)
				{
					if (is_used[cur_x][h] || ((vertices->row == cur_x) && (vertices->col == h)) || (((vertices + 1)->row == cur_x) && ((vertices + 1)->col == h)) || (((vertices + 2)->row == cur_x) && ((vertices + 2)->col == h)))
					{
						cur_x++;
					}
					else if (cur_x > 0 && (is_used[cur_x - 1][h] || ((vertices->row == cur_x - 1) && (vertices->col == h)) || (((vertices + 1)->row == cur_x - 1) && ((vertices + 1)->col == h)) || (((vertices + 2)->row == cur_x-1) && ((vertices + 2)->col == h))))
					{
						cur_x--;
					}
				}
				if (cur_x != i)
					return false;
			}
			return true;
		}
	}

	int GamePlay()
	{
		if (checkAnswer(NULL, 0))
		{
			return 0;
		}
		for (int row = 0; row < N-1; row++)
		{
			for (int col = 0; col < H; col++)
			{
				if (!is_unavail[row][col])
				{
					VERTEX* vertices = new VERTEX;
					vertices->row = row;
					vertices->col = col;
					if (checkAnswer(vertices, 1))
					{
						return 1;
					}
				}
			}
		}
		for (int row = 0; row < N-1; row++)
		{
			for (int col = 0; col < H; col++)
			{
				if (!is_unavail[row][col])
				{
					int col2, row2;
					if (col == H - 1)
					{
						col2 = 0;
						row2 = row + 1;
					}
					else
					{
						col2 = col + 1;
						row2 = row;
					}
					for (; row2 < N-1; row2++)
					{
						do
						{
							if (!is_unavail[row2][col2])
							{

								VERTEX* vertices = new VERTEX[2];
								vertices[0].row = row;
								vertices[0].col = col;
								vertices[1].row = row2;
								vertices[1].col = col2;
								if (checkAnswer(vertices, 2))
								{
									return 2;
								}
							}
							col2++;
						} while (col2 < H);
						col2 = 0;
					}
				}
			}
		}

		
		for (int row = 0; row < N-1; row++)
		{
			for (int col = 0; col < H; col++)
			{
				if (!is_unavail[row][col])
				{
					int col2,row2;
					if (col == H - 1)
					{
						col2 = 0;
						row2 = row + 1;
					}
					else
					{
						col2 = col + 1;
						row2 = row;
					}
					for (; row2 < N-1; row2++)
					{
						do
						{
							if (!is_unavail[row2][col2])
							{
								int col3, row3;
								if (col2 == H - 1)
								{
									col3 = 0;
									row3 = row2 + 1;
								}
								else
								{
									col3 = col2 + 1;
									row3 = row2;
								}
								for (; row3 < N-1; row3++)
								{
									do
									{
										if (!is_unavail[row3][col3])
										{
											VERTEX* vertices = new VERTEX[3];
											vertices[0].row = row;
											vertices[0].col = col;
											vertices[1].row = row2;
											vertices[1].col = col2;
											vertices[2].row = row3;
											vertices[2].col = col3;
											if (checkAnswer(vertices, 3))
											{
												return 3;
											}
										}
										col3++;
									} while (col3 < H);
									col3 = 0;

								}
							}
							col2++;
						} while (col2 < H);
						col2 = 0;
					}
				}
			}

		}
		return -1;
	}
};


int main()
{
	Game newgame = Game();
	newgame.input();
	cout<<newgame.GamePlay();
	return 0;
}
