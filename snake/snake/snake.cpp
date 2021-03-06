#include<iostream>
#include<queue>

using namespace std;
struct ROTATION
{
	int time, dir;
};
struct VERTEX
{
	int row, col;
};

class Game
{
private:
	int N, K, L;
	int **map;//1은 사과 있음, 0은 아무것도 없음, -1은 snake있음
	ROTATION *rot;
	queue<VERTEX> snake;
	int snake_dir;//0 : 북, 1: 동, 2: 남, 3: 서
public:
	void input()
	{
		VERTEX snake_init;
		snake_init.row = 0;
		snake_init.col = 0;

		cin >> N;
		cin >> K;
		map = new int*[N];
		rot = new ROTATION[L+1];
		for (int i = 0; i < N; i++)
		{
			map[i] = new int[N] {};
		}
		for (int i = 0; i < K; i++)
		{
			int row, col;
			cin >> row >> col;
			map[row-1][col-1] = 1;
		}
		map[0][0] = -1;
		snake.push(snake_init);
		cin >> L;
		for (int i = 0; i < L; i++)
		{
			char direction;
			cin >> rot[i].time;
			cin >> direction;
			if (direction == 'D') rot[i].dir = 1;//오른쪽
			else if (direction == 'L') rot[i].dir = -1;//왼쪽
		}
		for (int i = L - 1; i > 0; i--)
		{
			rot[i].time -= rot[i - 1].time;
		}
		rot[L].time = 100;
		rot[L].dir = 0;
	}
	int GamePlay()
	{
		int dx[] = {0,1,0,-1};//북 동 남 서
		int dy[] = {-1,0,1,0};
		int num = 0;
		snake_dir = 1;//동쪽
		for (int i = 0; i < L+1; i++)
		{
			for (int j = 0; j < rot[i].time; j++)
			{
				VERTEX head = snake.back();
				VERTEX tail = snake.front();
				head.col += dx[snake_dir];
				head.row += dy[snake_dir];
				snake.push(head);
				num++;
				if (head.row == -1 || head.col == -1 || head.row == N || head.col == N)
					return num;
				else if (map[head.row][head.col] == 0)
				{
					map[tail.row][tail.col] = 0;
					map[head.row][head.col] = -1;
					snake.pop();
				}
				else if (map[head.row][head.col] == -1)
					return num;
				else if (map[head.row][head.col] == 1)
				{
					map[head.row][head.col] = -1;
				}
			}
			snake_dir = (snake_dir + rot[i].dir+4) % 4;
		}
	}
};

int main()
{
	Game mygame;
	mygame.input();
	cout << mygame.GamePlay();
	return 0;
}

