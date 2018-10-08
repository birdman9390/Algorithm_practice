#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
struct CELL
{
	int row, col;
};

int myMax = -1;
int **map;//맵
int N;//세로
int M;//가로
int safe_count = 0;//입력 데이터의 안전지역 숫자
int cur_count;

//북 동 남 서
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };
vector<CELL> virus_list;
vector<CELL> empty_list;
int **visited;// 빈칸인 경우에만 0이고 벽이면 1 바이러스면 2, 체크된 바이러스면 3

void input()
{
	cin >> N >> M;

	map = new int*[M];
	visited = new int*[M];
	for (int i = 0; i < M; i++)
	{
		map[i] = new int[N];
		visited[i] = new int[N];
	}
	for (int i= 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[j][i];
			if (map[j][i] == 0)
			{
				CELL tmp;
				tmp.row = j;
				tmp.col = i;
				empty_list.push_back(tmp);
				safe_count++;
			}

			else if (map[j][i] == 2)
			{
				CELL tmp;
				tmp.row = j;
				tmp.col = i;
				virus_list.push_back(tmp);
			}
		}
	}
}

bool outofBound(int x, int y)
{
	return x < 0 || y < 0 || x >= M || y >= N;
}

void search(int x, int y)
{
	if (outofBound(x, y))
		return;

	if (visited[x][y]==1 || visited[x][y]==3)
		return;

	if (visited[x][y] == 0)
	{
		visited[x][y] = 1;
		cur_count--;
	}
	else if (visited[x][y] == 2)
	{
		visited[x][y] = 3;
	}
	for (int i = 0; i < 4; i++)
	{
		search(x + dx[i], y + dy[i]);
	}
}
void make_visited(int v1,int v2, int v3)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			visited[j][i] = map[j][i];
		}
	}

	visited[empty_list[v1].row][empty_list[v1].col] = 1;
	visited[empty_list[v2].row][empty_list[v2].col] = 1;
	visited[empty_list[v3].row][empty_list[v3].col] = 1;
}
int main()
{
	input();
	for (int i = 0; i < empty_list.size(); i++)
	{
		for (int j = i + 1; j < empty_list.size(); j++)
		{
			for (int k = j + 1; k < empty_list.size(); k++)
			{
				make_visited(i, j, k);
				cur_count = safe_count;
				for (int l = 0; l < virus_list.size(); l++)
				{
//					search(0, 0);
					search(virus_list[l].row, virus_list[l].col);
				}
				myMax = max(myMax, cur_count);
			}
		}
	}
	cout << myMax-3;
	return 0;
}
