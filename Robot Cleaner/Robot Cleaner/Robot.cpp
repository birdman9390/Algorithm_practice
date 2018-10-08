#include<iostream>


using namespace std;







int N;//����ũ��
int M;//����ũ��

int r, c;// �κ�û�ұ� ��ǥ
int d;//�κ�û�ұⰡ �ٶ󺸴� ���� �ϵ�����

int **map;
int clean_count = 0;//û���� ������ ����

//���������� �ϵ�����
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };


bool outofBound(int x, int y)
{
	return x < 0 || y < 0 || x >= M || y >= N;
}
void input()
{
	cin >> N >> M;
	map = new int*[M];
	for (int i = 0; i < M; i++)
	{
		map[i] = new int[N];
	}

	cin >> c >> r >> d;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[j][i];
		}
	}
}


void moveRobot(int x, int y)
{
	int dir;
	if (map[x][y] == 0)
	{
		clean_count++;
		map[x][y] = 2;
	}
	else if (map[x][y] == 1)
	{
		return;
	}
	for (int i = 1; i <= 4; i++)
	{
		dir = (d-i + 4) % 4;
		if (!outofBound(x + dx[dir], y + dy[dir]) && map[x + dx[dir]][y + dy[dir]] == 0)
		{
			d = dir;
			moveRobot(x + dx[dir], y + dy[dir]);
			return;
		}
	}
	dir = (d + 2) % 4;
	if (!outofBound(x + dx[dir], y + dy[dir]))
		moveRobot(x + dx[dir], y + dy[dir]);
}
int main()
{
	input();
	moveRobot(r, c);
	cout << clean_count;
	return 0;
}