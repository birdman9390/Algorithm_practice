//8시 7분 시작

#include<iostream>
#include<vector>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;

struct TEAM
{
	vector<int> index;
	int sum;
};

int N;

int **map;
int myMin = 100000000;
TEAM start_team, link_team;

void input()
{
	cin >> N;
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

	start_team.sum = 0;
	link_team.sum = 0;
}
bool outofBound(int a, int b)
{
	return a < 0 || b < 0;
}
void check(int start_num, int link_num, TEAM steam,TEAM lteam, int count)
{
	TEAM tmp;
	int toAdd = 0;
	if (outofBound(start_num, link_num))
		return;
	if (start_num == 0 && link_num == 0)
	{
		int diff = abs(steam.sum - lteam.sum);
		myMin = min(myMin, diff);
		return;
	}
	for (int i = 0; i < steam.index.size(); i++)
	{
		toAdd += map[count][steam.index[i]] + map[steam.index[i]][count];
	}
	tmp = steam;
	tmp.index.push_back(count);
	tmp.sum += toAdd;
	check(start_num - 1, link_num, tmp, lteam, count + 1);


	toAdd = 0;
	for (int i = 0; i < lteam.index.size(); i++)
	{
		toAdd += map[count][lteam.index[i]] + map[lteam.index[i]][count];
	}
	lteam.index.push_back(count);
	lteam.sum += toAdd;
	check(start_num , link_num-1, steam, lteam, count + 1);

}

int main()
{
	input();
	check(N / 2, N / 2, start_team, link_team, 0);
	cout << myMin;
	return 0;
}