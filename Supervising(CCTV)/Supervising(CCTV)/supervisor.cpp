//9시 42분 시작

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct CAMERA
{
	int row, col, type;
};
int N;//세로크기
int M;//가로크기

//북 동 남 서
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

int **map;
vector<CAMERA> cam_list;

int empty_cell=0;//빈 공간의 개수

int myMin = 1000000;
int myempty;
int pos_case = 1;//가능한 회전종류
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

			//만약 카메라면 카메라 리스트에 넣자
			if (map[j][i] >= 1 && map[j][i]<6)
			{
				CAMERA new_cam;
				new_cam.row = j;
				new_cam.col = i;
				new_cam.type = map[j][i];
				cam_list.push_back(new_cam);
			}

			//빈공간이 있으면 empty_cell를 올리자
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
	//만약에 범위를 벗어나면 무시
	if (outofBound(x, y))
		return;

	//벽인 경우에는 그만
	if (mymap[x][y] == 6)
		return;

	//벽이 아닌경우!

	//특히 빈곳이었던 경우
	if (mymap[x][y] == 0)
	{
		mymap[x][y] = -1;
		myempty--;
	}

	//CCTV 또는 이미 확인한곳인 경우 지나가기만하자

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

	//일단 회전 가능한 방법수를 전부 적어보자!
	for (int i = 0; i < pos_case; i++)
	{
		int num = i;
		for (int j = 0; j < cam_list.size(); j++)
		{
			switch (cam_list[j].type)
			{
			//1,3,4는 4방향 가능
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
		copyMap(map, mymap);//맵 초기화
		myempty = empty_cell;//빈 공간 개수 초기화
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