//1�� 30�� ����

#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;


struct CELL
{
	int row, col,distance;
};

int N;//���� ũ��

int M;//ġŲ�� ���ܾ� �� ����

int **map;//���� ��

int myMin = 1000000;

int house_num = 0;
//CELL house[100];

vector<CELL> house;
vector<CELL> chicken_store;

int distance(CELL a, CELL b)
{
	return abs(a.row - b.row) + abs(a.col - b.col);
}

void input()
{
	cin >> N >> M;
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
			//house�ΰ��
			if (map[j][i] == 1)
			{
				CELL tmp;
				tmp.row = j;
				tmp.col = i;
				tmp.distance = 1000;
//				house[house_num] = tmp;
				house_num++;
				house.push_back(tmp);
			}
			//ġŲ���ΰ��
			else if (map[j][i] == 2)
			{
				CELL tmp;
				tmp.row = j;
				tmp.col = i;
				chicken_store.push_back(tmp);
			}
		}
	}
}

bool outofBound(int i)
{
	return i < 0 || i >= chicken_store.size();
}

void check(int index, int count, vector<CELL> myhouse)
{
	//������ ġŲ�� M���� ������
	if (count == M)
	{
		int dis_sum = 0;
		for (int i = 0; i < house_num;i++)
		{
			dis_sum += myhouse[i].distance;
		}
		myMin = min(myMin, dis_sum);
		return;
	}

	//ġŲ�� M���� �ȵƴµ� ���� �ε��� �ʰ��ϴ� ���� ������ �ȵ�
	if (outofBound(index))
	{
		return;
	}

	for (int i = 0; i < house_num; i++)
	{
		//���� �Ÿ��� ������Ʈ������!
		myhouse[i].distance = min(myhouse[i].distance, distance(myhouse[i], chicken_store[index]));
	}

	for (int i = index + 1; i <= chicken_store.size(); i++)
	{
		check(i, count + 1, myhouse);
	}
}

int main()
{
	input();
	for (int i = 0; i < chicken_store.size() - M + 1; i++)
	{
		check(i, 0, house);
	}
	cout << myMin;
	return 0;
}