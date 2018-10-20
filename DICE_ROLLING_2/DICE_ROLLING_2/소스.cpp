//10시 20분시작



#include<iostream>
#include<algorithm>

#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3

#define BLOCK_NE 1
#define BLOCK_SE 2
#define BLOCK_SW 3
#define BLOCK_NW 4
#define BLOCK_SQUARE 5


using namespace std;

struct CELL
{
	int row, col;
	int score[4];
	CELL()
	{
		score[0] = -1;
		score[1] = -1;
		score[2] = -1;
		score[3] = -1;
	}
};
struct HOLE
{
	int row, col;
};


int N;//판 크기
int **map;
//CELL **score_map;
int maxScore;

int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

HOLE w_Hole[11][2];
int w_count;
bool s_check;

void input()
{
	cin >> N;
	map = new int*[N];
//	score_map = new CELL*[N];
	w_count = 0;
	maxScore = -1;
	for (int i = 0; i < N; i++)
	{
		map[i] = new int[N];
//		score_map[i] = new CELL[N];
	}

	for (int i = 6; i < 11; i++)
	{
		w_Hole[i][0].row = -1;
		w_Hole[i][0].col = -1;
		w_Hole[i][1].row = -1;
		w_Hole[i][1].col = -1;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[j][i];

			//웜홀인 경우
			if (map[j][i] >= 6)
			{
				if (w_Hole[map[j][i]][0].row == -1 && w_Hole[map[j][i]][0].col == -1)
				{
					w_Hole[map[j][i]][0].row = j;
					w_Hole[map[j][i]][0].col = i;
				}
				else
				{
					w_Hole[map[j][i]][1].row = j;
					w_Hole[map[j][i]][1].col = i;
				}
				w_count++;
			}
		}
	}
}
bool outofBound(int x, int y)
{
	return x < 0 || y < 0 || x >= N || y >= N;
}
void changeDir(int row, int col, int &dir)
{
	switch (dir)
	{
	case DIR_NORTH:
		switch (map[row][col])
		{
		case BLOCK_NE:
			dir = DIR_SOUTH;
			break;
		case BLOCK_SE:
			dir = DIR_EAST;
			break;
		case BLOCK_SW:
			dir = DIR_WEST;
			break;
		case BLOCK_NW:
			dir = DIR_SOUTH;
			break;
		case BLOCK_SQUARE:
			dir = DIR_SOUTH;
			break;
		}
		break;
	case DIR_EAST:
		switch (map[row][col])
		{
		case BLOCK_NE:
			dir = DIR_WEST;
			break;
		case BLOCK_SE:
			dir = DIR_WEST;
			break;
		case BLOCK_SW:
			dir = DIR_SOUTH;
			break;
		case BLOCK_NW:
			dir = DIR_NORTH;
			break;
		case BLOCK_SQUARE:
			dir = DIR_WEST;
			break;
		}
		break;
	case DIR_SOUTH:
		switch (map[row][col])
		{
		case BLOCK_NE:
			dir = DIR_EAST;
			break;
		case BLOCK_SE:
			dir = DIR_NORTH;
			break;
		case BLOCK_SW:
			dir = DIR_NORTH;
			break;
		case BLOCK_NW:
			dir = DIR_WEST;
			break;
		case BLOCK_SQUARE:
			dir = DIR_NORTH;
			break;
		}
		break;
	case DIR_WEST:
		switch (map[row][col])
		{
		case BLOCK_NE:
			dir = DIR_NORTH;
			break;
		case BLOCK_SE:
			dir = DIR_SOUTH;
			break;
		case BLOCK_SW:
			dir = DIR_EAST;
			break;
		case BLOCK_NW:
			dir = DIR_EAST;
			break;
		case BLOCK_SQUARE:
			dir = DIR_EAST;
			break;
		}
		break;
	}
}

int move(int row, int col, int dir, int sx, int sy)
{
	int score=0;
	int block_check = 0;
	int nx, ny;

	while (1)
	{
		if (outofBound(row, col))
		{
			dir = (dir + 2) % 4;
			row += dx[dir];
			col += dy[dir];
			score++;
		}

		//두번째 시작점이면 s_check=false;
		if (row == sx&&col == sy)
		{
			if (s_check == false)
				return score;

			//만약 처음 시작부분이면 return하지 않는다
			s_check = false;
		}

		//블랙홀이면 return;
		if (map[row][col] == -1)
		{
			return score;
		}

		//여기서 만약 현재 셀이 블록이라면 방향을 바꿔준다.
		if (map[row][col] >= 1 && map[row][col] <= 5)
		{
			//
			changeDir(row, col, dir);
			score++;
			//block_check = 1;
		}

		//웜홀인 경우 반대 웜홀로 move
		else if (map[row][col] > 5)
		{
			int h_num = map[row][col];
			if (w_Hole[h_num][0].row == row &&w_Hole[h_num][0].col == col)
			{
				//			score = move(w_Hole[h_num][1].row, w_Hole[h_num][1].col, dir, sx, sy);
				row = w_Hole[h_num][1].row;
				col = w_Hole[h_num][1].col;
			}
			else
			{
				row = w_Hole[h_num][0].row;
				col = w_Hole[h_num][0].col;
				//			score = move(w_Hole[h_num][0].row, w_Hole[h_num][0].col, dir, sx, sy);
			}
			//웜홀로 이동
			//score=move(새로운웜홀)
			//		score_map[row][col].score[dir] = score;
			//		return score;
		}
		nx = row + dx[dir];
		ny = col + dy[dir];

		while (!outofBound(nx, ny) && map[nx][ny] == 0)
		{
			if (nx == sx&&ny == sy)
				return score;
			nx += dx[dir];
			ny += dy[dir];
		}
		row = nx;
		col = ny;
//		score = move(nx, ny, dir, sx, sy) + block_check;

		//	score = move(row + dx[dir], col + dy[dir], dir, sx, sy) + block_check;
		//	score_map[row][col].score[dir] = score;
	}
	return score;
}




int main()
{
	int T;
	int *myScore;
	cin >> T;
	myScore = new int[T];
	for (int k = 0; k < T; k++)
	{
		input();
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] == 0)
				{
					for (int d = 0; d < 4; d++)
					{
						s_check = true;
						maxScore = max(maxScore, move(i, j, d, i, j));
					}
				}
			}
		}
		myScore[k] = maxScore;
	}

	for(int i=0;i<T;i++)
	{
		cout<<"#"<<i+1<<" "<<myScore[i]<<'\n';
	}
	return 0;
}