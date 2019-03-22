#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
int N, A[21][21], B[21][21], ans = 0;
vector<int> dA;

void move(int d) // 0123 -> 북동남서 
{
	queue<int> q;
	vector<int> v;

	if (d == 0)
	{
		for (int i = 0; i < N; i++) // 열
		{
			v.clear();

			// 벡터에 넣기
			for (int j = 0; j < N; j++) // 행
				if (A[j][i] != 0)
				{
					v.push_back(A[j][i]);
					A[j][i] = 0;
				}	

			// 벡터 처음부터 순회하면서 같은숫자 합쳐서 Q에 넣기
			for (int j = 0; j < v.size(); j++)
			{
				if ( (j + 1 < v.size()) && v[j] == v[j + 1])
				{
					q.push(v[j] * 2);
					j++;
				}
				else
					q.push(v[j]);
			}

			// 큐에 넣은거 맵에 보내기
			int idx = 0;
			while (!q.empty())
			{			
				A[idx++][i] = q.front();
				q.pop();
			}
		}	
	}
	else if (d == 1)
	{
		for (int i = 0; i < N; i++) // 행
		{
			v.clear();

			for (int j = N-1 ; j >= 0; j--) // 열			
				if (A[i][j] != 0)
				{
					v.push_back(A[i][j]);
					A[i][j] = 0;
				}			
			
			for (int j = 0; j < v.size(); j++)
			{
				if ( (j + 1 < v.size()) && v[j] == v[j + 1])
				{
					q.push(v[j] * 2);
					j++;
				}
				else
					q.push(v[j]);
			}
			
			int idx = N-1;
			while (!q.empty())
			{			
				A[i][idx--] = q.front();
				q.pop();
			}
		}
	}
	else if (d == 2)
	{
		for (int i = 0; i < N; i++) // 열
		{
			v.clear();
			
			for (int j = N-1; j >= 0; j--) // 행			
				if (A[j][i] != 0)
				{
					v.push_back(A[j][i]);
					A[j][i] = 0;
				}			
			
			for (int j = 0; j < v.size(); j++)
			{
				if ( (j + 1 < v.size()) && v[j] == v[j + 1])
				{
					q.push(v[j] * 2);
					j++;
				}
				else
					q.push(v[j]);
			}

			int idx = N-1;
			while (!q.empty())
			{			
				A[idx--][i] = q.front();
				q.pop();
			}
		}
	}
	else if (d == 3)
	{
		for (int i = 0; i < N; i++) // 행
		{
			v.clear();

			for (int j = 0; j < N; j++) // 열			
				if (A[i][j] != 0)
				{
					v.push_back(A[i][j]);
					A[i][j] = 0;
				}

			for (int j = 0; j < v.size(); j++)
			{
				if ( (j + 1 < v.size() ) && v[j] == v[j + 1])
				{
					q.push(v[j] * 2);
					j++;
				}
				else
					q.push(v[j]);
			}

			int idx = 0;
			while (!q.empty())
			{			
				A[i][idx++] = q.front();
				q.pop();
			}
		}
	}
}

void d_perm()
{
	if (dA.size() == 5)
	{	
		// 초기 맵복사
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				A[i][j] = B[i][j];

		// 5번 이동
		for (int i = 0; i < dA.size(); i++)
			move(dA[i]);
		
		// 최대값 찾기
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				ans = max(ans, A[i][j]);
		
		return;
	}
	
	for (int i = 0; i < 4; i++)
	{
		dA.push_back(i);
		d_perm();
		dA.pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> B[i][j];

	d_perm();

	cout << ans << '\n';
	return 0;
}

/*
주요한 반례

5
2 2 4 8 16
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
2 2 4 8 16

정답:64  
위로 이동했을 때, 같은 숫자들이 합쳐져야함 



10
0 0 0 0 0 32 8 64 8 16
0 0 0 0 0 0 0 16 8 16
0 0 0 0 0 0 0 0 0 2
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0

정답:128 (위오위왼왼 case)  
빈칸(0)은 큐에 넣으면 안된다
*/