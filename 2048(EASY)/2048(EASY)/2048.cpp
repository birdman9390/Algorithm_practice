#include<iostream>
#include<queue>
#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3

using namespace std;

struct STATE {
	int **board;
};

int N;//���� ũ��

//��,��,��,��
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

int myMax=0;

STATE initial_state;

void copy_state(STATE &from, STATE &to)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			to.board[i][j] = from.board[i][j];
		}
	}
}

void input()
{
	//���� ũ�� �Է�
	cin >> N;


	//���� �����Ҵ�
	initial_state.board = new int*[N];
	for (int i = 0; i < N; i++)
		initial_state.board[i] = new int[N] {};

	//���� �Է¹ޱ� (��ǥ��)
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> initial_state.board[j][i];
		}
	}
}

int move_block(STATE &state, int dir)
{
	int max_block = -1;
	switch (dir)
	{
	case DIR_NORTH:
		for (int i = 0; i < N; i++)
		{
			queue<int> myqueue;
			int index = 0;
			for (int j = 0; j < N; j++)
			{
				if (state.board[i][j] != 0)
				{
					myqueue.push(state.board[i][j]);
					state.board[i][j] = 0;
				}
			}
			while (!myqueue.empty())
			{
				int cur_elem = myqueue.front();
				myqueue.pop();

				//���� �̰� �������̸� �׳� �ִ´�
				if (myqueue.empty())
				{
					state.board[i][index] = cur_elem;
					max_block = max(max_block, cur_elem);
					break;
				}

				//���� ���� �ΰ��� ���� ��� �Ѵ� ������ �Ѱ��� �����
				else if (cur_elem == myqueue.front())
				{
					state.board[i][index] = cur_elem * 2;
					max_block = max(max_block, cur_elem * 2);
					myqueue.pop();
				}

				//�ٸ� ��� �¸� ������.
				else if (cur_elem != myqueue.front())
				{
					state.board[i][index] = cur_elem;
					max_block = max(max_block, cur_elem);
				}
				index++;
			}
		}
		break;
	case DIR_EAST:
		for (int i = 0; i < N; i++)
		{
			queue<int> myqueue;
			int index = N-1;
			for (int j = N-1; j >=0; j--)
			{
				if (state.board[j][i] != 0)
				{
					myqueue.push(state.board[j][i]);
					state.board[j][i] = 0;
				}
			}
			while (!myqueue.empty())
			{
				int cur_elem = myqueue.front();
				myqueue.pop();

				//���� �̰� �������̸� �׳� �ִ´�
				if (myqueue.empty())
				{
					state.board[index][i] = cur_elem;
					max_block = max(max_block, cur_elem);
					break;
				}

				//���� ���� �ΰ��� ���� ��� �Ѵ� ������ �Ѱ��� �����
				else if (cur_elem == myqueue.front())
				{
					state.board[index][i] = cur_elem * 2;
					max_block = max(max_block, cur_elem * 2);
					myqueue.pop();
				}

				//�ٸ� ��� �¸� ������.
				else if (cur_elem != myqueue.front())
				{
					state.board[index][i] = cur_elem;
					max_block = max(max_block, cur_elem);
				}
				index--;
			}
		}
		break;
	case DIR_SOUTH:
		for (int i = 0; i < N; i++)
		{
			queue<int> myqueue;
			int index = N-1;
			for (int j = N-1; j >=0 ; j--)
			{
				if (state.board[i][j] != 0)
				{
					myqueue.push(state.board[i][j]);
					state.board[i][j] = 0;
				}
			}
			while (!myqueue.empty())
			{
				int cur_elem = myqueue.front();
				myqueue.pop();

				//���� �̰� �������̸� �׳� �ִ´�
				if (myqueue.empty())
				{
					state.board[i][index] = cur_elem;
					max_block = max(max_block, cur_elem);
					break;
				}

				//���� ���� �ΰ��� ���� ��� �Ѵ� ������ �Ѱ��� �����
				else if (cur_elem == myqueue.front())
				{
					state.board[i][index] = cur_elem * 2;
					max_block = max(max_block, cur_elem * 2);
					myqueue.pop();
				}

				//�ٸ� ��� �¸� ������.
				else if (cur_elem != myqueue.front())
				{
					state.board[i][index] = cur_elem;
					max_block = max(max_block, cur_elem);
				}
				index--;
			}
		}
		break;
	case DIR_WEST:
		for (int i = 0; i <N; i++)
		{
			queue<int> myqueue;
			int index = 0;
			for (int j = 0; j < N; j++)
			{
				if (state.board[j][i] != 0)
				{
					myqueue.push(state.board[j][i]);
					state.board[j][i] = 0;
				}
			}
			while (!myqueue.empty())
			{
				int cur_elem = myqueue.front();
				myqueue.pop();

				//���� �̰� �������̸� �׳� �ִ´�
				if (myqueue.empty())
				{
					state.board[index][i] = cur_elem;
					max_block = max(max_block, cur_elem);
					break;
				}

				//���� ���� �ΰ��� ���� ��� �Ѵ� ������ �Ѱ��� �����
				else if (cur_elem == myqueue.front())
				{
					state.board[index][i] = cur_elem * 2;
					max_block = max(max_block, cur_elem * 2);
					myqueue.pop();
				}

				//�ٸ� ��� �¸� ������.
				else if (cur_elem != myqueue.front())
				{
					state.board[index][i] = cur_elem;
					max_block = max(max_block, cur_elem);
				}
				index++;
			}
		}
		break;

	}
	return max_block;
}

void dfs(STATE state, int count)
{
	STATE cur_state;
	if (count >= 5)
		return;

	cur_state.board = new int*[N];
	for (int i = 0; i < N; i++)
		cur_state.board[i] = new int[N];

	copy_state(state, cur_state);
	myMax = max(myMax, move_block(cur_state, DIR_NORTH));
	dfs(cur_state, count + 1);

	copy_state(state, cur_state);
	myMax = max(myMax, move_block(cur_state, DIR_EAST));
	dfs(cur_state, count + 1);

	copy_state(state, cur_state);
	myMax = max(myMax, move_block(cur_state, DIR_SOUTH));
	dfs(cur_state, count + 1);

	copy_state(state, cur_state);
	myMax = max(myMax, move_block(cur_state, DIR_WEST));
	dfs(cur_state, count + 1);
}



int main()
{
	input();
	dfs(initial_state, 0);
	cout << myMax;



	/*
	cout << "FIRST\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << initial_state.board[j][i] << ' ';
		cout << '\n';
	}
	
	move_block(initial_state, DIR_WEST);



	cout << "LAST\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << initial_state.board[j][i] << ' ';
		cout << '\n';
	}
	*/
	return 0;
}