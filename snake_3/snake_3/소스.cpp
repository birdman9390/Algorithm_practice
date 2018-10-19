// 8시 54분 시작


#include<iostream>
#include<queue>

#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3

#define TYPE_EMPTY 0
#define TYPE_APPLE 1
#define TYPE_SNAKE 2
using namespace std;


struct DIR_INFO
{
	int time;
	char turn;
};
struct CELL
{
	int x, y;
};

int N;//보드 크기 NxN

int K;//사과 개수

int L;//뱀의 방향 변환 횟수

int **map;
DIR_INFO* d_info;
int d_index = 0;
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

queue<CELL> snake;
CELL init_head;

void input()
{
	cin >> N;
	map = new int*[N];
	for (int i = 0; i < N; i++)
		map[i] = new int[N] {};


	cin >> K;
	for (int i = 0; i < K; i++)
	{
		int r, c;
		cin >> c >> r;

		map[r-1][c-1] = TYPE_APPLE;
	}

	cin >> L;
	d_info = new DIR_INFO[L];
	for (int i = 0; i < L; i++)
	{
		cin >> d_info[i].time >> d_info[i].turn;
	}

	init_head.x = 0;
	init_head.y = 0;
	snake.push(init_head);
	map[0][0] = TYPE_SNAKE;
}

bool outofBound(int x, int y)
{
	return x < 0 || y < 0 || x >= N || y >= N;
}

void move(int time, int dir)
{
	CELL head = snake.back();

	if (d_index < L && d_info[d_index].time == time)
	{
		switch (d_info[d_index].turn)
		{
		case 'L':
			dir = (dir + 3) % 4;
			break;
		case 'D':
			dir = (dir + 1) % 4;
			break;
		}
		d_index++;
	}
	head.x += dx[dir];
	head.y += dy[dir];

	if (outofBound(head.x, head.y))
	{
		cout << time + 1;
		return;
	}
	else if (map[head.x][head.y] == TYPE_APPLE)
	{
		map[head.x][head.y] = TYPE_SNAKE;
		snake.push(head);
	}
	else if (map[head.x][head.y] == TYPE_EMPTY)
	{
		map[head.x][head.y] = TYPE_SNAKE;
		snake.push(head);
		map[snake.front().x][snake.front().y] = TYPE_EMPTY;
		snake.pop();
	}
	else if (map[head.x][head.y] == TYPE_SNAKE)
	{
		cout << time + 1;
		return;
	}

	move(time + 1, dir);
}

int main()
{
	input();
	move(0, DIR_EAST);
	return 0;
}