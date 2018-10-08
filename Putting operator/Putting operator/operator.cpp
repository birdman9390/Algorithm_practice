#include<iostream>
#include<algorithm>

using namespace std;


int N;

int *A;//input data

int plus_num, minus_num, multi_num, div_num;
int myMin = 1000000001;
int myMax = -1000000001;

void input()
{
	cin >> N;
	A = new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	cin >> plus_num >> minus_num >> multi_num >> div_num;
}

bool outofBound(int a, int b, int c, int d)
{
	return a < 0 || b < 0 || c < 0 || d < 0;
}

void operate(int pl, int mi, int mul, int div,int sum, int count)
{
	if (outofBound(pl, mi, mul, div))
		return;

	if (pl + mi + mul + div == 0)
	{
		myMax = max(myMax, sum);
		myMin = min(myMin, sum);
		return;
	}

	operate(pl - 1, mi, mul, div, sum + A[count], count + 1);
	operate(pl , mi - 1, mul, div, sum - A[count], count + 1);
	operate(pl , mi, mul - 1, div, sum * A[count], count + 1);
	operate(pl , mi, mul, div - 1, sum / A[count], count + 1);
}

int main()
{
	input();
	operate(plus_num, minus_num, multi_num, div_num, A[0], 1);
	cout << myMax << '\n';
	cout << myMin;
	return 0;
}