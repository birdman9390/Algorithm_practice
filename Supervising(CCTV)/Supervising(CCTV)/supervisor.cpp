//9�� 42�� ����

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct CAMERA
{
	int row, col, type;
};
int N;//����ũ��
int M;//����ũ��

//�� �� �� ��
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

int **map;
vector<CAMERA> cam_list;

int empty_cell=0;//�� ������ ����

int myMin = 1000000;
int myempty;
int pos_case = 1;//������ ȸ������
void copyMap(int **from, int **to)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			to[j][i] = from[j][i];
		}
	}
}

void input()
{
	int camera_count = 0;
	cin >> N >> M;

	map = new int*[M];
	for (int i = 0; i < M; i++)
	{
		map[i] = new int[N];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[j][i];

			//���� ī�޶�� ī�޶� ����Ʈ�� ����
			if (map[j][i] >= 1 && map[j][i]<6)
			{
				CAMERA new_cam;
				new_cam.row = j;
				new_cam.col = i;
				new_cam.type = map[j][i];
				cam_list.push_back(new_cam);
			}

			//������� ������ empty_cell�� �ø���
			if (map[j][i] == 0)
				empty_cell++;

			if (map[j][i] == 4 || map[j][i] == 1 || map[j][i] == 3)
				pos_case *= 4;
			else if (map[j][i] == 2)
				pos_case *= 2;

		}
	}
}

bool outofBound(int x, int y)
{
	return x < 0 || y < 0 || x >= M || y >= N;
}

void checkDir(int **mymap, int x, int y, int dir)
{
	//���࿡ ������ ����� ����
	if (outofBound(x, y))
		return;

	//���� ��쿡�� �׸�
	if (mymap[x][y] == 6)
		return;

	//���� �ƴѰ��!

	//Ư�� ����̾��� ���
	if (mymap[x][y] == 0)
	{
		mymap[x][y] = -1;
		myempty--;
	}

	//CCTV �Ǵ� �̹� Ȯ���Ѱ��� ��� �������⸸����

	checkDir(mymap, x + dx[dir], y + dy[dir], dir);
}

void playGame()
{
	int **camdir;
	int **mymap;
	mymap = new int*[M];
	for (int i = 0; i < M; i++)
		mymap[i] = new int[N];
	camdir = new int*[pos_case];
	for(int i=0;i<pos_case;i++)
		camdir[i] = new int[cam_list.size()];

	//�ϴ� ȸ�� ������ ������� ���� �����!
	for (int i = 0; i < pos_case; i++)
	{
		int num = i;
		for (int j = 0; j < cam_list.size(); j++)
		{
			switch (cam_list[j].type)
			{
			//1,3,4�� 4���� ����
			case 1:
				camdir[i][j] = num % 4;
				num /= 4;
				break;
			case 3:
				camdir[i][j] = num % 4;
				num /= 4;
				break;
			case 4:
				camdir[i][j] = num % 4;
				num /= 4;
				break;
			case 2:
				camdir[i][j] = num % 2;
				num /= 2;
				break;
			case 5:
				camdir[i][j] = 1;
				break;
			}
		}
	}


	for (int i = 0; i < pos_case; i++)
	{
		copyMap(map, mymap);//�� �ʱ�ȭ
		myempty = empty_cell;//�� ���� ���� �ʱ�ȭ
		for (int j = 0; j < cam_list.size(); j++)
		{
			switch (cam_list[j].type)
			{
			case 1:
				checkDir(mymap, cam_list[j].row, cam_list[j].col, camdir[i][j]);
				break;
			case 3:
				checkDir(mymap, cam_list[j].row, cam_list[j].col, camdir[i][j]);
				checkDir(mymap, cam_list[j].row, cam_list[j].col, (camdir[i][j]+1)%4);
				break;
			case 4:
				checkDir(mymap, cam_list[j].row, cam_list[j].col, camdir[i][j]);
				checkDir(mymap, cam_list[j].row, cam_list[j].col, (camdir[i][j]+1)%4);
				checkDir(mymap, cam_list[j].row, cam_list[j].col, (camdir[i][j]+2)%4);
				break;
			case 2:
				checkDir(mymap, cam_list[j].row, cam_list[j].col, camdir[i][j]);
				checkDir(mymap, cam_list[j].row, cam_list[j].col, (camdir[i][j] + 2) % 4);
				break;
			case 5:
				checkDir(mymap, cam_list[j].row, cam_list[j].col, camdir[i][j]);
				checkDir(mymap, cam_list[j].row, cam_list[j].col, (camdir[i][j] + 1) % 4);
				checkDir(mymap, cam_list[j].row, cam_list[j].col, (camdir[i][j] + 2) % 4);
				checkDir(mymap, cam_list[j].row, cam_list[j].col, (camdir[i][j] + 3) % 4);
				break;
			}
		}
		myMin = min(myMin, myempty);
	}
}

int main()
{
	input();
	playGame();
	cout << myMin;
	return 0;
}