#include<iostream>
#include<queue>

using namespace std;

struct DIRCHANGE
{
	int second, dir;//dir= -1이면 왼쪽 +1이면 오른쪽
};
struct CELL
{
	int row, col;
};
int N;//보드크기
int K;//사과의 개수
int L;//방향변환 횟수

//북, 동, 남, 서
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

int **map;//애플이 있으면 1 없으면 0 snake 있으면 -1
DIRCHANGE *change_info;
//int second = 0;
queue<CELL> snake;
void input()
{
	//N,K 입력받기
	cin >> N >> K;
	
	//isapple 동적할당
	map = new int*[N];
	for (int i = 0; i < N; i++)
	{
		map[i] = new int[N] {};
	}

	//사과 입력받기
	for (int i = 0; i < K; i++)
	{
		int row, col;
		cin >> row >> col;
		map[col - 1][row - 1] = 1;
	}

	//방향변환횟수 입력
	cin >> L;
	change_info = new DIRCHANGE[L];

	for (int i = 0; i < L; i++)
	{
		char dir;
		cin >> change_info[i].second;
		cin >> dir;
		if (dir == 'L')
			change_info[i].dir = -1;
		else if (dir == 'D')
			change_info[i].dir = 1;
	}
}

void GamePlay()
{
	//처음에는 오른쪽으로 출발
	int dir = 1;
	int second = 0;

	CELL first_snake;
	first_snake.row = 0;
	first_snake.col = 0;

	snake.push(first_snake);

	for (int i = 0; i < L; i++)
	{
		//언제까지 직진할 것인지를 가지고 있음
		DIRCHANGE new_info = change_info[i];
		while (second < new_info.second)
		{
			//어느 셀로 갈것인지
			CELL next_cell = snake.back();
			next_cell.row += dx[dir];
			next_cell.col += dy[dir];

			second++;

			//다음 셀이 벽인 경우
			if (next_cell.row < 0 || next_cell.col < 0 || next_cell.row >= N || next_cell.col >= N)
			{
				cout << second;
				return;
			}
				
			//다음 셀에 사과가 있다
			if (map[next_cell.row][next_cell.col] == 1)
			{
				snake.push(next_cell);
				map[next_cell.row][next_cell.col] = -1;
			}

			//다음 셀에 아무것도없다.
			else if (map[next_cell.row][next_cell.col] == 0)
			{
				CELL pop_cell = snake.front();
				snake.pop();
				snake.push(next_cell);
				
				map[pop_cell.row][pop_cell.col] = 0;//꼬리부분은 빈곳으로 바꿔주고
				map[next_cell.row][next_cell.col] = -1;//머리부분은 snake부분으로 바꿔준다.
			}

			//다음 셀에 뱀꼬리가 있다.
			else if (map[next_cell.row][next_cell.col] == -1)
			{
				cout << second;
				return;
			}
		}
		
		//방향전환해주자
		dir = (dir + new_info.dir + 4) % 4;
	}

	while (second < 10100)
	{
		//어느 셀로 갈것인지
		CELL next_cell = snake.back();
		next_cell.row += dx[dir];
		next_cell.col += dy[dir];

		second++;

		//다음 셀이 벽인 경우
		if (next_cell.row < 0 || next_cell.col < 0 || next_cell.row >= N || next_cell.col >= N)
		{
			cout << second;
			return;
		}

		//다음 셀에 사과가 있다
		if (map[next_cell.row][next_cell.col] == 1)
		{
			snake.push(next_cell);
			map[next_cell.row][next_cell.col] = -1;
		}

		//다음 셀에 아무것도없다.
		else if (map[next_cell.row][next_cell.col] == 0)
		{
			CELL pop_cell = snake.front();
			snake.pop();
			snake.push(next_cell);

			map[pop_cell.row][pop_cell.col] = 0;//꼬리부분은 빈곳으로 바꿔주고
			map[next_cell.row][next_cell.col] = -1;//머리부분은 snake부분으로 바꿔준다.
		}

		//다음 셀에 뱀꼬리가 있다.
		else if (map[next_cell.row][next_cell.col] == -1)
		{
			cout << second;
			return;
		}
	}

	cout << "ERROR OCCUERD";
}





int main()
{
	input();
	GamePlay();
	return 0;
}