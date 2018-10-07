#include<iostream>


using namespace std;



long long N;//시험장 개수
long long *num_people;//시험장마다 사람 수

long long B;//감독관이 감시가능한 수
long long C;//부감독관이 감시가능한 수

void input()
{
	//시험장 개수 입력
	cin >> N;

	//시험장마다 응시자 수 입력 및 동적 할당
	num_people = new long long[N];
	for (int i = 0; i < N; i++)
	{
		cin >> num_people[i];
	}

	//감독관과 부감독관이 감시가능한 응시자 수 입력
	cin >> B >> C;
}





int main()
{
	long long total = 0;
	input();
	for (int i = 0; i < N; i++)
	{
		num_people[i] -= B;
		total++;

		if (num_people[i] > 0)
		{
			total += (((num_people[i] - 1) / C) + 1);
		}
	}
	cout << total;




	return 0;
}