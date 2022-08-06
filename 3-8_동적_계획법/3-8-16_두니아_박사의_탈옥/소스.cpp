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
	// d-day�϶� ������ġ�� ������ 1 �ƴϸ� 0�� ���ϵ��� ����

	double& ret = cache[n][d];
	if (ret > -0.5) return ret;
	ret = 0.0;
	
	for (int next = 0; next < N; next++) {
		if (A[n][next] == 1) {
			ret = ret + (search(next, d - 1) / (double)deg[n]); 
			//for���� ���鼭 ������ġ�� �´� ���(1�� return��)�� Ȯ���� ������
			//0�� return �� ��� *0�̹Ƿ� �������� �ʴ´�.
		}
	}
	return ret; //���� ��ο� ������ Ȯ���� ����.
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
			//***�߿� : �Ҽ� 8�ڸ� ����
		}
		cout << endl;		
	}
}