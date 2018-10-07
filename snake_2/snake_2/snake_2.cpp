#include<iostream>
#include<queue>

using namespace std;

struct DIRCHANGE
{
	int second, dir;//dir= -1�̸� ���� +1�̸� ������
};
struct CELL
{
	int row, col;
};
int N;//����ũ��
int K;//����� ����
int L;//���⺯ȯ Ƚ��

//��, ��, ��, ��
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

int **map;//������ ������ 1 ������ 0 snake ������ -1
DIRCHANGE *change_info;
//int second = 0;
queue<CELL> snake;
void input()
{
	//N,K �Է¹ޱ�
	cin >> N >> K;
	
	//isapple �����Ҵ�
	map = new int*[N];
	for (int i = 0; i < N; i++)
	{
		map[i] = new int[N] {};
	}

	//��� �Է¹ޱ�
	for (int i = 0; i < K; i++)
	{
		int row, col;
		cin >> row >> col;
		map[col - 1][row - 1] = 1;
	}

	//���⺯ȯȽ�� �Է�
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
	//ó������ ���������� ���
	int dir = 1;
	int second = 0;

	CELL first_snake;
	first_snake.row = 0;
	first_snake.col = 0;

	snake.push(first_snake);

	for (int i = 0; i < L; i++)
	{
		//�������� ������ �������� ������ ����
		DIRCHANGE new_info = change_info[i];
		while (second < new_info.second)
		{
			//��� ���� ��������
			CELL next_cell = snake.back();
			next_cell.row += dx[dir];
			next_cell.col += dy[dir];

			second++;

			//���� ���� ���� ���
			if (next_cell.row < 0 || next_cell.col < 0 || next_cell.row >= N || next_cell.col >= N)
			{
				cout << second;
				return;
			}
				
			//���� ���� ����� �ִ�
			if (map[next_cell.row][next_cell.col] == 1)
			{
				snake.push(next_cell);
				map[next_cell.row][next_cell.col] = -1;
			}

			//���� ���� �ƹ��͵�����.
			else if (map[next_cell.row][next_cell.col] == 0)
			{
				CELL pop_cell = snake.front();
				snake.pop();
				snake.push(next_cell);
				
				map[pop_cell.row][pop_cell.col] = 0;//�����κ��� ������� �ٲ��ְ�
				map[next_cell.row][next_cell.col] = -1;//�Ӹ��κ��� snake�κ����� �ٲ��ش�.
			}

			//���� ���� �첿���� �ִ�.
			else if (map[next_cell.row][next_cell.col] == -1)
			{
				cout << second;
				return;
			}
		}
		
		//������ȯ������
		dir = (dir + new_info.dir + 4) % 4;
	}

	while (second < 10100)
	{
		//��� ���� ��������
		CELL next_cell = snake.back();
		next_cell.row += dx[dir];
		next_cell.col += dy[dir];

		second++;

		//���� ���� ���� ���
		if (next_cell.row < 0 || next_cell.col < 0 || next_cell.row >= N || next_cell.col >= N)
		{
			cout << second;
			return;
		}

		//���� ���� ����� �ִ�
		if (map[next_cell.row][next_cell.col] == 1)
		{
			snake.push(next_cell);
			map[next_cell.row][next_cell.col] = -1;
		}

		//���� ���� �ƹ��͵�����.
		else if (map[next_cell.row][next_cell.col] == 0)
		{
			CELL pop_cell = snake.front();
			snake.pop();
			snake.push(next_cell);

			map[pop_cell.row][pop_cell.col] = 0;//�����κ��� ������� �ٲ��ְ�
			map[next_cell.row][next_cell.col] = -1;//�Ӹ��κ��� snake�κ����� �ٲ��ش�.
		}

		//���� ���� �첿���� �ִ�.
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