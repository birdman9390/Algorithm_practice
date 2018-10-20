//2시 30분 시작


#include<iostream>
#include<vector>
#include<stack>
#define DIR_NORTH 0
#define DIR_SOUTH 2
#define DIR_WEST 3
#define DIR_EAST 1

using namespace std;

struct CELL
{
	int row, col, dir, energy;
	bool isatom, removecheck;
	CELL()
	{
		isatom = false;
		removecheck = false;
	}
};

int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

int TE;
int N;
CELL mmm[2001][2001];
vector<CELL> atom;

CELL map(int row, int col)
{
	return mmm[row + 1000][col + 1000];
}

void save_dir(int row, int col, int value)
{
	mmm[row + 1000][col + 1000].dir = value;
}
void save_energy(int row, int col, int energy)
{
	mmm[row + 1000][col + 1000].energy = energy;
}
void make_atom(int row, int col,bool isatom)
{
	mmm[row + 1000][col + 1000].isatom =isatom;
}
bool is_atom(int row, int col)
{
	return mmm[row + 1000][col + 1000].isatom;
}
void set_removecheck(int row, int col, bool removecheck)
{
	mmm[row + 1000][col + 1000].removecheck = removecheck;
}
void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		CELL new_in;
		cin >> new_in.row >> new_in.col >> new_in.dir >> new_in.energy;
		if (new_in.dir == 0)
			new_in.dir = DIR_NORTH;
		else if (new_in.dir == 1)
			new_in.dir = DIR_SOUTH;
		else if (new_in.dir == 2)
			new_in.dir = DIR_WEST;
		else if (new_in.dir == 3)
			new_in.dir = DIR_EAST;
		atom.push_back(new_in);
		save_dir(new_in.row, new_in.col, new_in.dir);
		save_energy(new_in.row, new_in.col, new_in.energy);
		make_atom(new_in.row, new_in.col,true);
	}
	TE = 0;
}

bool outofBound(int x, int y)
{
	return x < -1000 || y < -1000 || x>1000 || y>1000;
}

void move()
{
	while (!atom.empty())
	{
		stack<int> out_index;
		stack<int> bound_index;
		for (int i = 0; i < atom.size(); i++)
		{
			CELL cur = atom[i];
			int nx, ny;
			
			nx = cur.row + dx[cur.dir];
			ny = cur.col + dy[cur.dir];


			//일단 맵 밖으로 벗어나가는 놈들은 얄짧없이 컷
			if (outofBound(nx, ny))
			{
				out_index.push(i);
				bound_index.push(i);
			}


			else if (is_atom(nx, ny) && map(nx, ny).dir == (cur.dir + 2) % 4)//선위에서 부딪히는 경우 (0.5초단위)
			{
				set_removecheck(nx, ny, true);
				out_index.push(i);
			}
			
			//선위에서 부딪히지 않는경우에는 점 위에서 부딪히는 경우를 생각하자
			else
			{
				for (int d = 0; d < 4; d++)
				{
					if (d != (cur.dir + 2) % 4)//cur.row와 cur.col에 있는거 말고 다른애들이 여기로 오는지 확인
					{
						if (!outofBound(nx+dx[d],ny+dy[d])&&is_atom(nx+dx[d],ny+dy[d])&&map(nx + dx[d], ny + dy[d]).dir == (d + 2) % 4)//nx,ny로 오는 아톰이 있는 경우
						{
							if (map(nx, ny).isatom == 1 && map(nx, ny).dir == d)
								continue;
							out_index.push(i);
							break;//여러번 볼 필요는 없음
						}
					}
				}
			}
			
			//atom.erase(atom.begin() + i); //i번째 원소 지우는법
		}


		//위에서 out_index를 전부 확인했다

		if (!bound_index.empty())
		{
			int a;
			a = 1;
		}
		//이제 맵에서 아톰을 지워주며 초기화시킨다.
		for (int i = 0; i < atom.size(); i++)
		{
			CELL cur = atom[i];
			make_atom(cur.row, cur.col, false);//맵에서 아톰을 지워준다.
		}

		while (!out_index.empty())
		{
			int index = out_index.top();
			out_index.pop();
			if (!bound_index.empty())
			{
				int b_index = bound_index.top();
				if (b_index == index)
				{
					bound_index.pop();
				}//충돌이 아니라 밖으로 나가서 무시하는건 에너지 증가 
				else
					TE += atom[index].energy;//에너지는 더해주고
			}
			else
			{
				TE += atom[index].energy;//에너지는 더해주고
			}
			atom.erase(atom.begin() + index);//삭제하자
		}

		//이제 atom에는 살아있는 놈들만 남아있다.


		for (int i = 0; i < atom.size(); i++)
		{
			CELL cur;
			atom[i].row += dx[atom[i].dir];
			atom[i].col += dy[atom[i].dir];

			cur = atom[i];
			
			//맵에 정보 저장
			make_atom(cur.row, cur.col, true);
			save_dir(cur.row, cur.col, cur.dir);
			save_energy(cur.row, cur.col, cur.energy);
		}
	}

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
		move();
		answer[i] = TE;
//		cout << "#" << i + 1 << " " << TE<<'\n';
	}
	for (int i = 0; i < T; i++)
	{
		cout << "#" << i + 1 << " " << answer[i] << '\n';
	}
	return 0;
}