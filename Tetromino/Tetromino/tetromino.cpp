#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;


struct CELL
{
	int row, col;
};

int N;//세로크기
int M;//가로크기


int myMax = -1;
int **map;
//bool **visited;

int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

void copyVisited(bool **from, bool **to)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			to[i][j] = from[i][j];
		}
	}
}

bool outofBound(int x, int y)
{
	return x < 0 || y < 0 || x >= M || y >= N;
}

void input()
{
	cin >> N >> M;

	map = new int*[M];
//	visited = new bool*[M];
	for (int i = 0; i < M; i++)
	{
		map[i] = new int[N];
//		visited[i] = new bool[N] {};
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[j][i];
		}
	}
}

void dfs(int x, int y,int sum,int count,vector<CELL> visited_queue)
{
	CELL cur_cell;
	if (count == 4)
	{
		myMax = max(myMax, sum);
		return;
	}
	if (outofBound(x, y))
		return;
	for (int i = 0; i < count; i++)
	{
		if (visited_queue[i].row == x && visited_queue[i].col == y)
			return;
	}
//	if (visited[x][y])
//		return;

	sum += map[x][y];
	cur_cell.row = x;
	cur_cell.col = y;
	visited_queue.push_back(cur_cell);

	for (int i = 0; i < 4; i++)
	{
		dfs(x + dx[i], y + dy[i], sum, count + 1, visited_queue);
	}
}

void fuckyou(int x, int y)
{
	int nx[4], ny[4], value[4];
	int check = 0;
	int sum = 0;
	int mymin = 10000;

	for (int i = 0; i < 4; i++)
	{
		nx[i] = x + dx[i];
		ny[i] = y + dy[i];
	}

	for (int i = 0; i < 4; i++)
	{
		if (outofBound(nx[i], ny[i]))
		{
			value[i] = -1;
			check++;
		}
		else
		{
			value[i] = map[nx[i]][ny[i]];
		}
		sum += value[i];
		mymin = min(mymin, value[i]);
	}

	if (check >= 2)
		return;
	sum -= mymin;

	sum += map[x][y];
	myMax = max(myMax, sum);
}

int main()
{
	vector<CELL> visited_vector;
	input();
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			dfs(i, j, 0, 0, visited_vector);
			fuckyou(i, j);
//			visited[i][j] = true;
		}
	}

	cout << myMax;
	return 0;
}