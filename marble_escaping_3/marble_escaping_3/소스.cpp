//4�� 11�� ����

#include<iostream>
#include<queue>

#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3

using namespace std;




struct STATE
{
	int rx, ry, bx, by, count;
};

int N;//����
int M;//����

char **map;

int rx, ry, bx, by, ox, oy;

bool success=false;

queue<STATE> myqueue;
STATE initial_state;

int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

void input()
{
	cin >> N >> M;

	map = new char*[M];
	for (int i = 0; i < M; i++)
	{
		map[i] = new char[N];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[j][i];

			switch (map[j][i])
			{
			case 'R':
				initial_state.rx = j;
				initial_state.ry = i;
				break;
			case 'B':
				initial_state.bx = j;
				initial_state.by = i;
				break;
			case 'O':
				ox = j;
				oy = i;
			}
		}
	}
	initial_state.count = 0;
}

void move(STATE cur_state, int dir)
{
	bool r_in_o, r_collid_b, b_collid_r;

	if (cur_state.count == 10)
	{
		return;
	}
	r_in_o = false;
	r_collid_b = false;
	b_collid_r = false;
	while (1)
	{
		int n_rx, n_ry;
		
		//Ȧ�� �������� ��
		if (map[cur_state.rx][cur_state.ry] == 'O')
		{
			r_in_o = true;
			break;
		}
		//�߰��� �Ķ��̶� �ε����� ��� üũ���ش�.
		else if (cur_state.bx == cur_state.rx && cur_state.by == cur_state.ry)
		{
			r_collid_b = true;
		}

		//�Űܰ� ĭ �������
		n_rx = cur_state.rx + dx[dir];
		n_ry = cur_state.ry + dy[dir];

		//���̶� �ε����� ���
		if (map[n_rx][n_ry] == '#')
		{
			break;
		}
		cur_state.rx = n_rx;
		cur_state.ry = n_ry;
	}

	while (1)
	{
		int n_bx, n_by;

		//Ȧ�� �������� ��
		if (map[cur_state.bx][cur_state.by] == 'O')
		{
			return;
		}
		//�߰��� �����̶� �ε����� ��� üũ���ش�.
		else if (cur_state.bx==cur_state.rx && cur_state.by == cur_state.ry && !r_collid_b)
		{
			b_collid_r = true;
		}

		//�Űܰ� ĭ �������
		n_bx = cur_state.bx + dx[dir];
		n_by = cur_state.by + dy[dir];

		//���̶� �ε����� ���
		if (map[n_bx][n_by] == '#')
		{
			break;
		}
		cur_state.bx = n_bx;
		cur_state.by = n_by;
	}

	//�����Ѱ��
	if (r_in_o)
	{
		cout << cur_state.count + 1;
		success = true;
		return;
	}



	if (r_collid_b)
	{
		cur_state.rx -= dx[dir];
		cur_state.ry -= dy[dir];
	}
	else if (b_collid_r)
	{
		cur_state.bx -= dx[dir];
		cur_state.by -= dy[dir];
	}


	cur_state.count++;
	myqueue.push(cur_state);
}


void check()
{
	myqueue.push(initial_state);
	while (!myqueue.empty())
	{
		STATE cur_state = myqueue.front();
		myqueue.pop();

		if (cur_state.count == 10)
			break;
		for (int i = 0; i < 4; i++)
		{
			move(cur_state, i);
			if (success)
				return;
		}
	}
	cout << "-1";
}



int main()
{
	input();
	check();
	return 0;
}
