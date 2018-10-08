//8시 35분 시작

#include<iostream>


using namespace std;


int numRoad = 0;
int N;
int L;

int **map;
int **road;

void input()
{
	cin >> N >> L;

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

	road = new int*[2 * N];
	for (int i = 0; i < 2 * N; i++)
	{
		road[i] = new int[N];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			road[i][j] = map[i][j];
			road[i + N][j] = map[j][i];
		}
	}
}
bool outofBound(int index)
{
	return index >= N;
}
void moveRoad(int *cur_road, int count,int last_slope_pos)
{
	if (count == N - 1)
	{
		numRoad++;
		return;
	}

	if (cur_road[count] == cur_road[count + 1])
	{
		moveRoad(cur_road, count + 1,last_slope_pos);
		return;
	}

	//1111000  이런식으로 한단계 낮아지는 경우
	if (cur_road[count] == cur_road[count + 1] + 1)
	{
		//일단 경사면을 놓지 못하면 답없음
		if (outofBound(count + L))
			return;

		for (int i = 1; i <= L; i++)
		{
			//L개가 연속으로 현재꺼보다 1만큼 낮은 높이가 아니면 끝냄
			if (cur_road[count] != cur_road[count + i] + 1)
				return;
		}

		//이제 L개 연속으로 놓을수 있다는걸 검증함


		//만약 딱 다리를 놨는데 거기서 끝이면 성공인거
		if (outofBound(count + L + 1))
		{
			numRoad++;
			return;
		}

		//다리를 놓은곳이 일단 끝은 아니야! 그러면 그 다음 위치가 오르막이면 안됨.
		if (cur_road[count + L + 1] > cur_road[count])
			return;

		//이제 이 모든걸 통과했으면 다음 타자에게 바통을 넘기자
		moveRoad(cur_road, count + L, count + L);
		return;
	}

	//0000011111 이런식으로 한단계 올라가는 경우
	else if(cur_road[count] == cur_road[count + 1] -1)
	{
		//예전 경사면이 보니까 위치가 요상~한 경우
		if (count - last_slope_pos < L)
			return;

		//왼쪽에 경사면을 놓을수 있으니 ㅇㅋ하자

		//count+1 위치부터 경사면을 놓을수 있으니 last_slope_pos도 count위치까지만으로 하자
		moveRoad(cur_road, count + 1, count);
		return;
	}

	//이도 저도 아닌경우
	else
	{
		return;
	}

}


int main()
{
	input();
	for (int i = 0; i < 2 * N; i++)
	{
		moveRoad(road[i], 0, -1);
	}
	cout << numRoad;
	return 0;
}