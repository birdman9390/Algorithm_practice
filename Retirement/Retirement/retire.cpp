#include<iostream>
#include<algorithm>

using namespace std;


int myMax = 0;

int N;// 며칠째 퇴사할건지
int *T;//시간
int *P;//가격

void input()
{
	cin >> N;

	T = new int[N];
	P = new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> T[i] >> P[i];
	}
}


void playgame(int sum,int index)
{
	if (index >= N)
	{
		myMax = max(myMax, sum);
		return;
	}
	if (index + T[index] - 1 >= N)
	{
		myMax = max(myMax, sum);
		return;
	}

	sum += P[index];
	for (int i = index+T[index]; i < N; i++)
	{
		playgame(sum, i);
	}
	if (index + T[index] >= N)
	{
		myMax = max(myMax, sum);
		return;
	}
}

int main()
{
	input();
	for (int i = 0; i < N; i++)
	{
		playgame(0, i);
	}
	cout << myMax;

	return 0;
}