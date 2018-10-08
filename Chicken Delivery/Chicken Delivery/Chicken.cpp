//1시 30분 시작

#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;


struct CELL
{
	int row, col,distance;
};

int N;//도시 크기

int M;//치킨집 남겨야 할 숫자

int **map;//도시 맵

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
			//house인경우
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
			//치킨집인경우
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
	//무조건 치킨집 M개를 세야함
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

	//치킨집 M개가 안됐는데 벌써 인덱스 초과하는 경우는 있으면 안됨
	if (outofBound(index))
	{
		return;
	}

	for (int i = 0; i < house_num; i++)
	{
		//집의 거리를 업데이트해주자!
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