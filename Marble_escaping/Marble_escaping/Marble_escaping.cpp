#include<iostream>
#include<string>

using namespace std;
enum DIRECTION
{
	DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN
};
enum TYPE
{
	TYPE_EMPTY, TYPE_WALL, TYPE_HOLE, TYPE_RED, TYPE_BLUE
};
struct MARBLE
{
	int row, col;
};
struct HOLE
{
	int row, col;
};
class Game
{
private:
	int N, M;
	MARBLE init_RED, init_BLUE;
	MARBLE RED, BLUE;
	HOLE hole;
	TYPE **mymap;
public:
	Game()
	{}

	void input()
	{
		cin >> N >> M;
		string *a = new string[N];
		mymap = new TYPE*[N];
		for (int i = 0; i < N; i++)
			mymap[i] = new TYPE[M];


		for (int i = 0; i < N; i++)
		{
			cin >> a[i];
			for (int j = 0; j < M; j++)
			{
				switch (a[i][j])
				{
				case '.':
					mymap[i][j] = TYPE_EMPTY;
				case '#':
					mymap[i][j] = TYPE_WALL;
				case 'O':
					mymap[i][j] = TYPE_HOLE;
					hole.row = i;
					hole.col = j;
				case 'R':
					//mymap[i][j] = TYPE_RED;
					init_RED.row = i;
					init_RED.col = j;
				case 'B':
					//mymap[i][j] = TYPE_BLUE;
					init_BLUE.row = i;
					init_BLUE.col = j;
				}
			}
		}


	}


	int GamePlay(MARBLE r, MARBLE b)
	{
		
	}
	MARBLE* moveMarble(MARBLE r, MARBLE b,DIRECTION dir)
	{
		switch (dir)
		{
		case DIR_LEFT:
			if (r.row < b.row)
			{
				while (mymap[r.row - 1][r.col] == TYPE_EMPTY)
				{
					r.row--;
				}
				while (mymap[b.row - 1][b.col] == TYPE_EMPTY&&!(r.row==b.row-1&&r.col==b.col))
				{
					b.row--;
				}
			}
			else
			{
				while (mymap[b.row - 1][b.col] == TYPE_EMPTY)
				{
					b.row--;
				}
				while (mymap[r.row - 1][r.col] == TYPE_EMPTY && !(b.row == r.row - 1 && b.col == r.col))
				{
					r.row--;
				}
			}
		case DIR_UP:

			if (r.col < b.col)
			{
				while (mymap[r.row][r.col-1] == TYPE_EMPTY)
				{
					r.col--;
				}
				while (mymap[b.row][b.col-1] == TYPE_EMPTY && !(r.col == b.col - 1 && r.col == b.col))
				{
					b.col--;
				}
			}
			else
			{
				while (mymap[b.row][b.col-1] == TYPE_EMPTY)
				{
					b.col--;
				}
				while (mymap[r.row][r.col-1] == TYPE_EMPTY && !(b.col == r.col - 1 && b.col == r.col))
				{
					r.col--;
				}
			}





		case DIR_RIGHT:

			if (r.row > b.row)
			{
				while (mymap[r.row + 1][r.col] == TYPE_EMPTY)
				{
					r.row--;
				}
				while (mymap[b.row + 1][b.col] == TYPE_EMPTY && !(r.row == b.row + 1 && r.col == b.col))
				{
					b.row--;
				}
			}
			else
			{
				while (mymap[b.row + 1][b.col] == TYPE_EMPTY)
				{
					b.row++;
				}
				while (mymap[r.row + 1][r.col] == TYPE_EMPTY && !(b.row == r.row + 1 && b.col == r.col))
				{
					r.row++;
				}
			}



		case DIR_DOWN:

			if (r.col < b.col)
			{
				while (mymap[r.row][r.col + 1] == TYPE_EMPTY)
				{
					r.col++;
				}
				while (mymap[b.row][b.col + 1] == TYPE_EMPTY && !(r.col == b.col + 1 && r.col == b.col))
				{
					b.col++;
				}
			}
			else
			{
				while (mymap[b.row][b.col + 1] == TYPE_EMPTY)
				{
					b.col++;
				}
				while (mymap[r.row][r.col + 1] == TYPE_EMPTY && !(b.col == r.col + 1 && b.col == r.col))
				{
					r.col++;
				}
			}




		}
	}
};


int main()
{
    return 0;
}

