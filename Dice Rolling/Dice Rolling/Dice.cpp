#include<iostream>
#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3

using namespace std;

int dice[3][4] = { {-1,0,-1,-1},{0,0,0,0},{-1,0,-1,-1} };
//x 0 x
//0 0 0
//x 0 x
//x 0 x
//이 모양대로 initializing함.

int N;//세로
int M;//가로
int K;//명령의 개수
int x, y;//주사위 놓은 좌표
int **map;
int *instruction;
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };
void input()
{
	cin >> N >> M >> y >> x >> K;
	map = new int*[M];
	for (int i = 0; i < M; i++)
		map[i] = new int[N] {};
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[j][i];
		}
	}
	instruction = new int[K];
	for (int i = 0; i < K; i++)
	{
		cin >> instruction[i];
		switch (instruction[i])
		{
		case 1:
			instruction[i] = DIR_EAST;
			break;
		case 2:
			instruction[i] = DIR_WEST;
			break;
		case 3:
			instruction[i] = DIR_NORTH;
			break;
		case 4:
			instruction[i] = DIR_SOUTH;
			break;
		}
	}
}

bool isEnableMove(int dir)
{
	int nx, ny;
	nx = x + dx[dir];
	ny = y + dy[dir];
	if (nx < 0 || ny < 0 || nx >= M || ny >= N)
		return false;
	else
		return true;
}

void moveDice(int dir)
{
	int tmp;
	if (!isEnableMove(dir))
		return;
	switch (dir)
	{
	case DIR_NORTH:
		tmp = dice[1][3];
		dice[1][3] = dice[1][2];
		dice[1][2] = dice[1][1];
		dice[1][1] = dice[1][0];
		dice[1][0] = tmp;
		y--;
		break;
	case DIR_SOUTH:
		tmp = dice[1][0];
		dice[1][0] = dice[1][1];
		dice[1][1] = dice[1][2];
		dice[1][2] = dice[1][3];
		dice[1][3] = tmp;
		y++;
		break;
	case DIR_EAST:
		tmp = dice[0][1];
		dice[0][1] = dice[1][1];
		dice[1][1] = dice[2][1];
		dice[2][1] = dice[1][3];
		dice[1][3] = tmp;
		x++;
		break;
	case DIR_WEST:
		tmp = dice[2][1];
		dice[2][1] = dice[1][1];
		dice[1][1] = dice[0][1];
		dice[0][1] = dice[1][3];
		dice[1][3] = tmp;
		x--;
		break;
	}

	if (map[x][y] == 0)
	{
		map[x][y] = dice[1][1];
	}
	else
	{
		dice[1][1] = map[x][y];
		map[x][y] = 0;
	}
	cout << dice[1][3] << '\n';
}


int main()
{
	input();
	for (int i = 0; i < K; i++)
	{
		moveDice(instruction[i]);
	}
	return 0;
}