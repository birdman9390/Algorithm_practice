#include<iostream>
#include<queue>
using namespace std;

class state
{
public:
	int rx, ry, bx, by, count;
	state(int _rx, int _ry, int _bx, int _by, int _count)
	{
		rx = _rx;
		ry = _ry;
		bx = _bx;
		by = _by;
		count = _count;
	}
};
bool is_solved = false;
char **map;
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };
queue<state> myqueue;

int moveBall(int rx, int ry, int bx, int by, int direction, int count)
{
	int red_distance = 1;
	int blue_distance = 1;

	bool red_blocked = false;
	bool blue_blocked = false;
	bool red_escape = false;
	bool blue_escape = false;

	int initial_rx = rx;
	int initial_ry = ry;
	int initial_bx = bx;
	int initial_by = by;
	//먼저 빨간공을 움직이자
	while (1)
	{
		//만약 벽이랑 만난경우
		if (map[rx + red_distance * dx[direction]][ry + red_distance * dy[direction]] == '#')
		{
			red_distance--;
			break;
		}
		//벽이랑 만나지 않은 경우
		else
		{
			//그 중에서도 파란공이랑 만난경우
			if (rx + red_distance * dx[direction] == initial_bx && ry + red_distance * dy[direction] == initial_by)
			{
				red_blocked = true;
			}
			//탈출할수 있는 경우
			else if (map[rx + red_distance * dx[direction]][ry + red_distance * dy[direction]] == 'O')
			{
				red_escape = true;
			}
			red_distance++;
		}
	}
	if (red_blocked)
		red_distance--;
	

	//이제 파란공을 움직이자
	while (1)
	{
		//만약 벽이랑 만난경우
		if (map[bx + blue_distance * dx[direction]][by + blue_distance * dy[direction]] == '#')
		{
			blue_distance--;
			break;
		}
		//벽이랑 만나지 않은 경우
		else
		{
			//그 중에서도 빨간공이랑 만난경우
			if (bx + blue_distance * dx[direction] == initial_rx && by + blue_distance * dy[direction] == initial_ry)
			{
				blue_blocked = true;
			}
			//탈출할수 있는 경우
			else if (map[bx + blue_distance * dx[direction]][by + blue_distance * dy[direction]] == 'O')
			{
				blue_escape = true;
			}
			blue_distance++;
		}
	}
	if (blue_blocked)
		blue_distance--;


	rx += red_distance * dx[direction];
	ry += red_distance * dy[direction];
	bx += blue_distance * dx[direction];
	by += blue_distance * dy[direction];

	if (blue_escape)
	{
		return -1;
	}
	else if (red_escape)
	{
		is_solved = true;
	}
	else
	{
		myqueue.push(state(rx, ry, bx, by, count + 1));
		return count + 1;
	}
}


int main()
{
	int N, M;
	int count = 0;
	int rx, ry, bx, by, ox, oy;
	cin >> N >> M;
	
	//맵 동적할당
	map = new char*[N];
	for (int i = 0; i < N; i++)
		map[i] = new char[M];

	//맵 입력받기
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 'B')
			{
				bx = i;
				by = j;
			}
			else if (map[i][j] == 'R')
			{
				rx = i;
				ry = j;
			}
			else if (map[i][j]=='O')
			{
				ox = i;
				oy = j;
			}
		}
	}

	myqueue.push(state(rx, ry, bx, by, 0));

	//알고리즘 시작
	while (!myqueue.empty())
	{
		int cur_rx, cur_ry, cur_bx, cur_by, cur_count;

		cur_rx = myqueue.front().rx;
		cur_ry = myqueue.front().ry;
		cur_bx = myqueue.front().bx;
		cur_by = myqueue.front().by;
		cur_count = myqueue.front().count;

		myqueue.pop();
		if (cur_count >= 10)
		{
			cout << -1;
			return 0;
		}
		for (int i = 0; i < 4; i++)
		{
			moveBall(cur_rx, cur_ry, cur_bx, cur_by, i, cur_count);
		}
		if (is_solved)
		{
			cout << cur_count + 1;
			return 0;
		}
	}


}