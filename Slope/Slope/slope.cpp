//8�� 35�� ����

#include<iostream>


using namespace std;


int numRoad = 0;
int N;
int L;

int **map;
int **road;

void input()
{
	cin >> N >> L;

	map = new int*[N];
	for (int i = 0; i < N; i++)
	{
		map[i] = new int[N];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[j][i];
		}
	}

	road = new int*[2 * N];
	for (int i = 0; i < 2 * N; i++)
	{
		road[i] = new int[N];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			road[i][j] = map[i][j];
			road[i + N][j] = map[j][i];
		}
	}
}
bool outofBound(int index)
{
	return index >= N;
}
void moveRoad(int *cur_road, int count,int last_slope_pos)
{
	if (count == N - 1)
	{
		numRoad++;
		return;
	}

	if (cur_road[count] == cur_road[count + 1])
	{
		moveRoad(cur_road, count + 1,last_slope_pos);
		return;
	}

	//1111000  �̷������� �Ѵܰ� �������� ���
	if (cur_road[count] == cur_road[count + 1] + 1)
	{
		//�ϴ� ������ ���� ���ϸ� �����
		if (outofBound(count + L))
			return;

		for (int i = 1; i <= L; i++)
		{
			//L���� �������� ���粨���� 1��ŭ ���� ���̰� �ƴϸ� ����
			if (cur_road[count] != cur_road[count + i] + 1)
				return;
		}

		//���� L�� �������� ������ �ִٴ°� ������


		//���� �� �ٸ��� ���µ� �ű⼭ ���̸� �����ΰ�
		if (outofBound(count + L + 1))
		{
			numRoad++;
			return;
		}

		//�ٸ��� �������� �ϴ� ���� �ƴϾ�! �׷��� �� ���� ��ġ�� �������̸� �ȵ�.
		if (cur_road[count + L + 1] > cur_road[count])
			return;

		//���� �� ���� ��������� ���� Ÿ�ڿ��� ������ �ѱ���
		moveRoad(cur_road, count + L, count + L);
		return;
	}

	//0000011111 �̷������� �Ѵܰ� �ö󰡴� ���
	else if(cur_road[count] == cur_road[count + 1] -1)
	{
		//���� ������ ���ϱ� ��ġ�� ���~�� ���
		if (count - last_slope_pos < L)
			return;

		//���ʿ� ������ ������ ������ ��������

		//count+1 ��ġ���� ������ ������ ������ last_slope_pos�� count��ġ���������� ����
		moveRoad(cur_road, count + 1, count);
		return;
	}

	//�̵� ���� �ƴѰ��
	else
	{
		return;
	}

}


int main()
{
	input();
	for (int i = 0; i < 2 * N; i++)
	{
		moveRoad(road[i], 0, -1);
	}
	cout << numRoad;
	return 0;
}