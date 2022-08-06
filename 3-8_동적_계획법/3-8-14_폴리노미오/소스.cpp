#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 10 * 1000 * 1000; //큰 수 방지 나눗셈
int cache[101][101];

//n개의 정사각형, 위 가로줄에 first개의 정사각형을 가지는 폴리노미오의 수 반환
int poly(int n, int first) { //n : 이전 줄에서 남은 블럭수, first : 이전 줄 블럭의 갯수
	//기저사례 n == first
	if (n == first) return 1; // 맨 윗줄은 경우의 수가 1가지 (위치를 따지지 않는다.)
	//메모이 제이션
	int& ret = cache[n][first];
	if (ret != -1) return ret;
	ret = 0; //초기화
	//현재 블럭갯수를 1 ~ (n - first) 사이에서 결정
	for (int second = 1; second <= n - first; second++) {
		int add = second + first - 1; //윗 블럭단계와 현재 블럭단계가 겹치는 경우의 수
		add = add * poly(n - first, second); //다음 단계 재귀, add = 현재까지 폴리노미오 경우의수 
		add = add % MOD; 
		ret = ret + add; //메모이제이션에 저장
		ret = ret % MOD;
	}
	return ret; //for문을 모두 돌고 return
}
int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		int n, sum = 0;
		cin >> n;
		for (int j = 0; j < n; j++) { 
			sum = sum + poly(n, j + 1);
			sum = sum % MOD; 
		}
		cout << sum << endl;
	}
}