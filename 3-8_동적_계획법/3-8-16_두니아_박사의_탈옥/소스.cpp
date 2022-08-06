#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
double cache[51][101];
int A[51][51];
int deg[51];
int N, D, P, T, Q;

void initCache() {
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 101; j++) {
			cache[i][j] = -1;
		}
	}
}

double search(int n, int d) {
	if (d == 0) return (n == Q ? 1.0 : 0.0); 
	// d-day일때 도착위치가 맞으면 1 아니면 0을 곱하도록 리턴

	double& ret = cache[n][d];
	if (ret > -0.5) return ret;
	ret = 0.0;
	
	for (int next = 0; next < N; next++) {
		if (A[n][next] == 1) {
			ret = ret + (search(next, d - 1) / (double)deg[n]); 
			//for문을 돌면서 도착위치가 맞는 경로(1을 return한)의 확률을 더해줌
			//0을 return 한 경우 *0이므로 더해지지 않는다.
		}
	}
	return ret; //다음 경로에 곱해줄 확률을 리턴.
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(deg, 0, sizeof(deg));

		cin >> N >> D >> P;
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				cin >> A[j][k];
				if (A[j][k] == 1) deg[j] = deg[j] + 1;
			}
		}
		cin >> T;
		for (int j = 0; j < T; j++) {
			initCache();
			cin >> Q;
			cout << fixed << setprecision(8) <<search(P, D) << " "; 
			//***중요 : 소수 8자리 맞춤
		}
		cout << endl;		
	}
}