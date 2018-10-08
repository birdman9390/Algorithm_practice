//9시 9분 시작

#include<iostream>
#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1
#define NOROTATION 0


using namespace std;



int top[4][8];//톱니바퀴 상태 북, 북동, 동, 동남, 남, 남서, 서, 서북

int K;//회전 횟수

int *rot_pos;
int *rot_dir;//1이면 시계방향, -1이면 반시계 방향
int score = 0;

void input()
{
	int input[4];
	for (int i = 0; i < 4; i++)
	{
		cin >> input[i];
	}

	for (int i = 7; i >= 0; i--)
	{
		top[0][i] = input[0] % 10;
		top[1][i] = input[1] % 10;
		top[2][i] = input[2] % 10;
		top[3][i] = input[3] % 10;

		input[0] = input[0] / 10;
		input[1] = input[1] / 10;
		input[2] = input[2] / 10;
		input[3] = input[3] / 10;
	}
	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cin >> top[i][j];
		}
	}
	*/

	cin >> K;

	rot_pos = new int[K];
	rot_dir = new int[K];

	for (int i = 0; i < K; i++)
	{
		cin >> rot_pos[i] >> rot_dir[i];
		rot_pos[i]--;
	}
}

void rotate(int *topni, int dir)
{
	int tmp;
	switch (dir)
	{
	//시계방향 회전
	case CLOCKWISE:
		tmp = topni[7];
		topni[7] = topni[6];
		topni[6] = topni[5];
		topni[5] = topni[4];
		topni[4] = topni[3];
		topni[3] = topni[2];
		topni[2] = topni[1];
		topni[1] = topni[0];
		topni[0] = tmp;
		break;
	case COUNTERCLOCKWISE:
		tmp = topni[0];
		topni[0] = topni[1];
		topni[1] = topni[2];
		topni[2] = topni[3];
		topni[3] = topni[4];
		topni[4] = topni[5];
		topni[5] = topni[6];
		topni[6] = topni[7];
		topni[7] = tmp;
		break;
	case NOROTATION:
		break;
	}
}

void finish()
{
	if (top[0][0] == 1)
		score += 1;
	if (top[1][0] == 1)
		score += 2;
	if (top[2][0] == 1)
		score += 4;
	if (top[3][0] == 1)
		score += 8;
}


void playGame(int count)
{
	int myrotate[4] = { 0,0,0,0 }; //회전 없으면 0

	if (count == K)
	{
		finish();
		return;
	}

	switch (rot_pos[count])
	{
	case 0:
		myrotate[0] = rot_dir[count];
		//0번과 1번  사이의 극이 다른 경우
		if (top[0][2] != top[1][6])
		{
			myrotate[1] = myrotate[0] * (-1);
			//1번과 2번사이의 극이 다른경우
			if (top[1][2] != top[2][6])
			{
				myrotate[2] = myrotate[1] * (-1);
				//2번과 3번 사이의 극이 다른 경우
				if (top[2][2] != top[3][6])
				{
					myrotate[3] = myrotate[2] * (-1);
				}
			}
		}
		break;
	case 1:
		myrotate[1] = rot_dir[count];


		//0번과 1번  사이의 극이 다른 경우
		if (top[0][2] != top[1][6])
		{
			myrotate[0] = myrotate[1] * (-1);
		}

		//1번과 2번 사이의 극이 다른경우
		if (top[1][2] != top[2][6])
		{
			myrotate[2] = myrotate[1] * (-1);
			//2번과 3번 사이의 극이 다른 경우
			if (top[2][2] != top[3][6])
			{
				myrotate[3] = myrotate[2] * (-1);
			}
		}

		break;
	case 2:
		myrotate[2] = rot_dir[count];
		//1번과 2번 사이의 극이 다른 경우
		if (top[1][2] != top[2][6])
		{
			myrotate[1] = myrotate[2] * (-1);
			//0번과 1번  사이의 극이 다른 경우
			if (top[0][2] != top[1][6])
			{
				myrotate[0] = myrotate[1] * (-1);
			}
		}


		//2번과 3번 사이의 극이 다른 경우
		if (top[2][2] != top[3][6])
		{
			myrotate[3] = myrotate[2] * (-1);
		}

		break;
	case 3:

		myrotate[3] = rot_dir[count];

		//2번과 3번 사이의 극이 다른 경우
		if (top[2][2] != top[3][6])
		{
			myrotate[2] = myrotate[3] * (-1);

			//1번과 2번 사이의 극이 다른 경우
			if (top[1][2] != top[2][6])
			{
				myrotate[1] = myrotate[2] * (-1);
				//0번과 1번  사이의 극이 다른 경우
				if (top[0][2] != top[1][6])
				{
					myrotate[0] = myrotate[1] * (-1);
				}
			}
		}
		break;
	}

	for (int i = 0; i < 4; i++)
	{
		rotate(top[i], myrotate[i]);
	}
	playGame(count + 1);
}

int main()
{
	input();
	playGame(0);
	cout << score;
	return 0;
}