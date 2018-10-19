//5시 15분 시작

#include<iostream>
#include<queue>
#include<algorithm>

#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3


using namespace std;

int N;//NxN 보드 크기
int **map;
int myMax = -1;

int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

void input()
{
	cin >> N;

	map = new int*[N];
	for (int i = 0; i < N; i++)
		map[i] = new int[N];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[j][i];
			myMax = max(myMax, map[j][i]);
		}
	}
}
void copyMap(int **from, int **to)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			to[i][j] = from[i][j];
		}
	}
}

void move(int **cur_map, int dir)
{
	int **newMap;
	queue<int> *myqueue, *newqueue;
	myqueue = new queue<int>[N];
	newqueue = new queue<int>[N];

	newMap = new int*[N];
	for (int i = 0; i < N; i++)
		newMap[i] = new int[N] {};

	switch (dir)
	{
	case DIR_NORTH:
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if(cur_map[i][j]!=0)
					myqueue[i].push(cur_map[i][j]);
			}
		}

		for (int i = 0; i < N; i++)
		{
			int index = 0;
			while (!myqueue[i].empty())
			{
				int cur = myqueue[i].front();
				myqueue[i].pop();

				if (myqueue[i].empty())
				{
					newMap[i][index]=cur;
				}
				else if (myqueue[i].front() == cur)
				{
					newMap[i][index] = cur*2;
					myMax = max(myMax, cur * 2);
					myqueue[i].pop();
				}
				else
				{
					newMap[i][index] = cur;
				}
				index++;
			}
		}

		break;
	case DIR_EAST:
		for (int i = 0; i < N; i++)
		{
			for (int j = N-1; j >= 0; j--)
			{
				if (cur_map[j][i] != 0)
					myqueue[i].push(cur_map[j][i]);
			}
		}

		for (int i = 0; i < N; i++)
		{
			int index = 0;
			while (!myqueue[i].empty())
			{
				int cur = myqueue[i].front();
				myqueue[i].pop();

				if (myqueue[i].empty())
				{
					newMap[N - 1 - index][i] = cur;
				}
				else if (myqueue[i].front() == cur)
				{
					newMap[N - 1 - index][i] = cur * 2;
					myMax = max(myMax, cur * 2);
					myqueue[i].pop();
				}
				else
				{
					newMap[N - 1 - index][i] = cur;
				}
				index++;
			}
		}




		break;
	case DIR_SOUTH:
		for (int i = 0; i < N; i++)
		{
			for (int j = N-1; j >=0; j--)
			{
				if (cur_map[i][j] != 0)
					myqueue[i].push(cur_map[i][j]);
			}
		}

		for (int i = 0; i < N; i++)
		{
			int index = 0;
			while (!myqueue[i].empty())
			{
				int cur = myqueue[i].front();
				myqueue[i].pop();

				if (myqueue[i].empty())
				{
					newMap[i][N-1-index] = cur;
				}
				else if (myqueue[i].front() == cur)
				{
					newMap[i][N - 1 - index] = cur * 2;
					myMax = max(myMax, cur * 2);
					myqueue[i].pop();
				}
				else
				{
					newMap[i][N - 1 - index] = cur;
				}
				index++;
			}
		}




		break;
	case DIR_WEST:
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (cur_map[j][i] != 0)
					myqueue[i].push(cur_map[j][i]);
			}
		}

		for (int i = 0; i < N; i++)
		{
			int index = 0;
			while (!myqueue[i].empty())
			{
				int cur = myqueue[i].front();
				myqueue[i].pop();

				if (myqueue[i].empty())
				{
					newMap[index][i] = cur;
				}
				else if (myqueue[i].front() == cur)
				{
					newMap[index][i] = cur * 2;
					myMax = max(myMax, cur * 2);
					myqueue[i].pop();
				}
				else
				{
					newMap[index][i] = cur;
				}
				index++;
			}
		}




		break;
	}


	copyMap(newMap, cur_map);
}

void check(int **myMap, int count)
{
	int** newMap;

	if (count == 5)
	{
		return;
	}

	newMap = new int*[N];
	for (int i = 0; i < N; i++)
	{
		newMap[i] = new int[N];
	}
	
	for (int dir = 0; dir < 4; dir++)
	{
		copyMap(myMap, newMap);
		move(newMap, dir);
		check(newMap, count + 1);
	}
}

int main()
{
	input();
	check(map, 0);
	cout << myMax;
	return 0;
}