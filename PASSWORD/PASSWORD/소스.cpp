//4시 22분 시작


#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

bool myOrder(int a, int b)
{
	return a > b;
}

int N;
int K;
int r_num;
char *num;
int side[4];
vector<int> max_list;
void input()
{
	cin >> N;
	cin >> K;
	r_num = N / 4;
	
	num = new char[N];

	for (int i = 0; i < N; i++)
	{
		cin >> num[i];
	}

	side[0] = 0;
	side[1] = 0;
	side[2] = 0;
	side[3] = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < r_num; j++)
		{
			switch (num[i*r_num + j])
			{
			case '0':
				side[i] += 0;
				break;
			case '1':
				side[i] += 1 * pow(16, r_num - 1 - j);
				break;
			case '2':
				side[i] += 2 * pow(16, r_num - 1 - j);
				break;
			case '3':
				side[i] += 3 * pow(16, r_num - 1 - j);
				break;
			case '4':
				side[i] += 4 * pow(16, r_num - 1 - j);
				break;
			case '5':
				side[i] += 5 * pow(16, r_num - 1 - j);
				break;
			case '6':
				side[i] += 6 * pow(16, r_num - 1 - j);
				break;
			case '7':
				side[i] += 7 * pow(16, r_num - 1 - j);
				break;
			case '8':
				side[i] += 8 * pow(16, r_num - 1 - j);
				break;
			case '9':
				side[i] += 9 * pow(16, r_num - 1 - j);
				break;
			case 'A':
				side[i] += 10 * pow(16, r_num - 1 - j);
				break;
			case 'B':
				side[i] += 11 * pow(16, r_num - 1 - j);
				break;
			case 'C':
				side[i] += 12 * pow(16, r_num - 1 - j);
				break;
			case 'D':
				side[i] += 13 * pow(16, r_num - 1 - j);
				break;
			case 'E':
				side[i] += 14 * pow(16, r_num - 1 - j);
				break;
			case 'F':
				side[i] += 15 * pow(16, r_num - 1 - j);
				break;
			}
		}
	}
}

void check()
{
	for (int i = 0; i < r_num; i++)
	{
//		int cur_max = 0;
		int residual[4];
		for (int i = 0; i < 4; i++)
		{
			bool check = true;
			for (int j = 0; j < max_list.size(); j++)
			{
				if (max_list[j] == side[i])
				{
					check = false;
					break;
				}
			}
			if(check)
				max_list.push_back(side[i]);
//			cur_max += side[i];
		}
//		myMax = max(myMax, cur_max);
	//	max_list.push_back(cur_max);
		for (int i = 0; i < 4; i++)
		{
			residual[i] = (side[i] % 16)*(pow(16,r_num-1));
			side[i] = side[i] / 16;
		}
		side[0] += residual[3];
		side[1] += residual[0];
		side[2] += residual[1];
		side[3] += residual[2];
	}
//	cout << myMax;
	sort(max_list.begin(), max_list.end(), myOrder);
//	cout << max_list[K - 1];
}



int main()
{
	int T;
	int *answer;
	cin >> T;
	answer = new int[T];
	for (int i = 0; i < T; i++)
	{
		input();
		check();
		answer[i] = max_list[K - 1];
		max_list.clear();
	}
	for (int i = 0; i < T; i++)
	{
		cout << "#" << i + 1 << " " << answer[i] << '\n';
	}
	return 0;
}