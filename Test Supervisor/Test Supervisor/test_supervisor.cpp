#include<iostream>


using namespace std;



long long N;//������ ����
long long *num_people;//�����帶�� ��� ��

long long B;//�������� ���ð����� ��
long long C;//�ΰ������� ���ð����� ��

void input()
{
	//������ ���� �Է�
	cin >> N;

	//�����帶�� ������ �� �Է� �� ���� �Ҵ�
	num_people = new long long[N];
	for (int i = 0; i < N; i++)
	{
		cin >> num_people[i];
	}

	//�������� �ΰ������� ���ð����� ������ �� �Է�
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