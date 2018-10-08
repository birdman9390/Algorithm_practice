//12시 14분 시작


#include<iostream>
#include<math.h>
#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3
struct CURVE
{
	int x, y, d, g;
};
struct CELL
{
	int x, y;
};
using namespace std;

bool visited[101][101] = { 0, };

int N;//드래곤 커브의 개수

int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

int rec_num = 0;
CURVE *d_curve;

CELL dragon_curve_model[1025];
CELL dragon_curve_model_north[1025];
CELL dragon_curve_model_west[1025];
CELL dragon_curve_model_south[1025];
bool outofBound(int x, int y)
{
	return x < 0 || y < 0 || x>100 || y>100;
}
void input()
{
	CELL first_point, second_point;
	cin >> N;
	d_curve = new CURVE[N];

	for (int i = 0; i < N; i++)
	{
		cin >> d_curve[i].x >> d_curve[i].y >> d_curve[i].d >> d_curve[i].g;
		switch (d_curve[i].d)
		{
		case 0:
			d_curve[i].d = DIR_EAST;
			break;
		case 1:
			d_curve[i].d = DIR_NORTH;
			break;
		case 2:
			d_curve[i].d = DIR_WEST;
			break;
		case 3:
			d_curve[i].d = DIR_SOUTH;
			break;

		}
	}
	first_point.x = 0;
	first_point.y = 0;
	second_point.x = 1;
	second_point.y = 0;

	dragon_curve_model[0] = first_point;
	dragon_curve_model[1] = second_point;
}
CELL rotate(CELL cell, CELL from)
{
	CELL result;

	//x-x' y-y'
	cell.x -= from.x;
	cell.y -= from.y;

	//(-(y-y'), (x-x'))
	result.x = -cell.y;
	result.y = cell.x;

	//(y-y', -(x-x')) + (x', y')

	result.x += from.x;
	result.y += from.y;

	return result;
}
bool visitedpoint(int x, int y)
{
	return !outofBound(x, y) && visited[x][y];
}
void checkRec(int x, int y)
{
	if (visitedpoint(x, y))
		return;

	if (visitedpoint(x + 1, y) && visitedpoint(x, y + 1) && visitedpoint(x + 1, y + 1))
	{
		rec_num++;
	}
	if (visitedpoint(x + 1, y) && visitedpoint(x, y -1) && visitedpoint(x + 1, y - 1))
	{
		rec_num++;
	}
	if (visitedpoint(x - 1, y) && visitedpoint(x, y + 1) && visitedpoint(x - 1, y + 1))
	{
		rec_num++;
	}
	if (visitedpoint(x - 1, y) && visitedpoint(x, y - 1) && visitedpoint(x - 1, y - 1))
	{
		rec_num++;
	}
	visited[x][y] = true;
}
void make_dragon_curve_model(int generation)//generation 1부터 시작하게하자.
{
	int head = pow(2, generation - 1);//이게 generation-1 세대 커브의 마지막인덱스=현재세대 출발 인덱스
	int tail = pow(2, generation);//이게 마지막 인덱스
	if (generation == 11)
		return;

	for (int i = 0; i < head; i++)
	{
		dragon_curve_model[tail - i] = rotate(dragon_curve_model[i], dragon_curve_model[head]);
	}
	make_dragon_curve_model(generation + 1);
}

void playGame()
{
	CELL basis;
	basis.x = 0;
	basis.y = 0;
	make_dragon_curve_model(1);
	for (int i = 0; i < 1025; i++)
	{
		dragon_curve_model_south[i] = rotate(dragon_curve_model[i],basis);
		dragon_curve_model_west[i] = rotate(dragon_curve_model_south[i], basis);
		dragon_curve_model_north[i] = rotate(dragon_curve_model_west[i], basis);
	}
	for (int i = 0; i < N; i++)
	{
		//세대의 모든좌표를 계산
		for (int j = 0; j <= pow(2, d_curve[i].g); j++)
		{
			int cur_x, cur_y;
			switch (d_curve[i].d)
			{
			case DIR_NORTH:
				cur_x = dragon_curve_model_north[j].x + d_curve[i].x;
				cur_y = dragon_curve_model_north[j].y + d_curve[i].y;
				break;
			case DIR_SOUTH:
				cur_x = dragon_curve_model_south[j].x + d_curve[i].x;
				cur_y = dragon_curve_model_south[j].y + d_curve[i].y;
				break;
			case DIR_WEST:
				cur_x = dragon_curve_model_west[j].x + d_curve[i].x;
				cur_y = dragon_curve_model_west[j].y + d_curve[i].y;
				break;
			case DIR_EAST:
				cur_x = dragon_curve_model[j].x + d_curve[i].x;
				cur_y = dragon_curve_model[j].y + d_curve[i].y;
				break;
			}

			//일단 valid한 좌표여야함
			if (!outofBound(cur_x, cur_y))
			{
				//이미 체크한 좌표가 아니어야함
				if (!visited[cur_x][cur_y])
				{
					//valid하고 빈 좌표라면 사각형 개수를 체크한다.
					checkRec(cur_x, cur_y);
				}
			}
		}
	}
}

int main()
{
	input();
	playGame();
	cout << rec_num;

	return 0;
}