//6시 34분 시작


#include<iostream>
#include<vector>
#include<algorithm>



using namespace std;
struct BALL_INFO
{
	vector<int> pos;
};

int myMax;
int total_block;
int remove_count;
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };
int N, W, H;
int **map;
int **zeroMap;
bool **visited;
BALL_INFO *b_info;
bool outofBound(int row, int col)
{
	return row < 0 || col < 0 || row >= W || col >= H;
}

void copyVisited(bool **from, bool **to)
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			to[i][j] = from[i][j];
		}
	}
}
void copyMap(int **from, int **to)
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			to[i][j] = from[i][j];
		}
	}
}
void input()
{
	int aaaa;
	cin >> N >> W >> H;
	total_block = 0;
	myMax = -1;
	map = new int*[W];
	zeroMap = new int*[W];
	for (int i = 0; i < W; i++)
	{
		map[i] = new int[H];
		zeroMap[i] = new int[H] {};
	}
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> map[j][i];
			if (map[j][i] != 0)
				total_block++;
		}
	}
	aaaa = pow(W, N);
	b_info = new BALL_INFO[aaaa];
}
void make_info()
{
	for (int i = 0; i < pow(W, N); i++)
	{
		int cur = i;
		for (int j = 0; j < N; j++)
		{
			b_info[i].pos.push_back(cur%W);
			cur = cur / W;
		}
	}
}
void dfs(int row, int col, bool **visit, int **myMap)
{
	if (outofBound(row, col))
		return;
	if (visit[row][col])
		return;
	if (myMap[row][col] != 0)
	{
		remove_count++;
		visit[row][col] = true;
	}
	if (myMap[row][col] == 1)
	{
		return;
	}

	for (int dir = 0; dir < 4; dir++)
	{
		for (int i = 1; i < myMap[row][col]; i++)
		{
			dfs(row + dx[dir] * i, col + dy[dir] * i, visit, myMap);
		}
	}
}

void check()
{
	int **myMap;
	int **tempMap;
	bool **myvisited;

	myMap = new int*[W];
	tempMap = new int*[W];
	visited = new bool*[W];
	myvisited = new bool*[W];
	for (int i = 0; i < W; i++)
	{
		myMap[i] = new int[H];
		tempMap[i] = new int[H];
		visited[i] = new bool[H] {};
		myvisited[i] = new bool[H] {};
	}
	for (int i = 0; i < pow(W, N); i++)
	{
		BALL_INFO cur_info = b_info[i];
		remove_count = 0;
		copyMap(map, myMap);

		for (int j = 0; j < cur_info.pos.size(); j++)
		{
			int line = cur_info.pos[j];
			int index = 0;
			copyVisited(visited, myvisited);
			while (index<H&&myMap[line][index] == 0)
				index++;
			if(index!=H)
				dfs(line,index,myvisited,myMap);
			copyMap(zeroMap, tempMap);
			for (int k = 0; k < W; k++) {
				int h = H - 1;
				int cc = H - 1;
				while (h>=0&&myMap[k][h] != 0)
				{
					if (myvisited[k][h] == 0)
					{
						tempMap[k][cc] = myMap[k][h];
						cc--;
					}
					h--;
				}
			}
			copyMap(tempMap, myMap);
		}
		
		myMax = max(myMax, remove_count);
		if (myMax == total_block)
			return;
	}
}
int main()
{
	int T;
	int *answer;
	cin >> T;
	answer = new int[T];
	for (int i = 0; i < T; i++)
	{
		input();
		make_info();
		check();
		answer[i] = total_block - myMax;
	}
	for (int i = 0; i < T; i++)
	{
		cout << "#" << i + 1 << " " << answer[i] << '\n';
	}
	return 0;
}