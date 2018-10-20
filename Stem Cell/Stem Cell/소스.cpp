//9시 6분 시작


#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
struct CELL
{
	int row, col, duration;
};
bool myOrder(CELL a, CELL b)
{
	return a.duration < b.duration;
}


int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };
int **map;
bool **visited;
int N, M, K;
int cell_num;
int R, C;
//**_list[i]는 i초에 상태가 전환되는 cell들의 집합이다.
vector<CELL> activate_list[310];
vector<CELL> inactivate_list[310];
vector<CELL> next_generation_list;

void input()
{
	cin >> N >> M >> K;
	R = M + K + 10;
	C = N + K + 10;
	cell_num = 0;
	map = new int*[R];
	visited = new bool*[R];
	for (int i = 0; i < R; i++)
	{
		map[i] = new int[C] {};
		visited[i] = new bool[C] {};
	}
	next_generation_list.clear();
	for (int i = 0; i < K; i++)
	{
		activate_list[i].clear();
		inactivate_list[i].clear();
	}


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			CELL tmp;
			cin >> map[j + 5 + K / 2][i + 5 + K / 2];

			//빈곳이 아닌경우 리스트로 쏙 넣어준다.
			if (map[j + 5 + K / 2][i + 5 + K / 2] != 0)
			{
				tmp.row = j + 5 + K / 2;
				tmp.col = i + 5 + K / 2;
				tmp.duration = map[j + 5 + K / 2][i + 5 + K / 2];
				//map[tmp.row][tmp.col]초에 상태가 활성상태로 전환될것임.
				inactivate_list[map[tmp.row][tmp.col]].push_back(tmp);
				visited[tmp.row][tmp.col] = true;
				cell_num++;
			}
		}
	}
}


void check()
{
	for (int i = 0; i <= K; i++)
	{

		int cur_time = i;//현재 시간

						 //일단 활성화되어있던 친구들 중 이제 죽어야 하는애들 죽이자!
						 //죽인 개수만큼 cell 개수에서 차감



		cell_num -= activate_list[cur_time].size();
		activate_list[cur_time].clear();
		sort(next_generation_list.begin(), next_generation_list.end(), myOrder);
		while (!next_generation_list.empty())
		{
			CELL myCell = next_generation_list.back();
			next_generation_list.pop_back();


			for (int dir = 0; dir < 4; dir++)
			{
				int nx, ny;
				nx = myCell.row + dx[dir];
				ny = myCell.col + dy[dir];
				if (!visited[nx][ny])
				{
					int next_time;
					CELL tmp;
					tmp.row = nx;
					tmp.col = ny;
					tmp.duration = myCell.duration;
					next_time = (cur_time + tmp.duration);
					inactivate_list[next_time].push_back(tmp);
					visited[nx][ny] = true;
					cell_num++;
					map[tmp.row][tmp.col] = tmp.duration;
				}
			}
		}

		//그 다음 비활성화된 친구들을 활성화시켜주자.
		while (!inactivate_list[cur_time].empty())
		{
			int next;
			CELL myCell = inactivate_list[cur_time].back();
			inactivate_list[cur_time].pop_back();

			next = (cur_time + myCell.duration);
			activate_list[next].push_back(myCell);
			next_generation_list.push_back(myCell);
		}




		cout << "#" << i << '\n';
		for (int k = 0; k < C; k++)
		{
			for (int j = 0; j < R; j++)
			{
				cout << map[j][k] << " ";
			}
			cout << '\n';
		}

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
		check();
		answer[i] = cell_num;
	}
	for (int i = 0; i < T; i++)
	{
		cout << "#" << i + 1 << " " << answer[i] << '\n';
	}

	return 0;
}