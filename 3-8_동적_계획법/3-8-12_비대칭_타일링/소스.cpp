#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
int cache[101];
int width;

//2*width크기의 사각형을 채우는 방법의 수를 MOD로 나눈 나머지로 반환
int tiling(int width) {
	//기저사례 : width가 1이하이면 끝에 도달 경우의수 +1 (1인 이유는 마지막 한칸은 어차피 세로블록 고정이기 때문)
	if (width <= 1) return 1;
	//메모이제이션
	int& ret = cache[width];
	if (ret != -1) return ret;
	//타일이 세로로 하나 놓는경우 -1, 가로로 두개 놓는경우 -2 되는 width
	return ret = (tiling(width - 1) + tiling(width - 2)) % MOD; 
}

//전체 경우에서 대칭인경우 빼기
//2*width크기의 비대칭으로 사각형을 채우는 방법의 수를 MOD로 나눈 나머지로 반환
int asymmetric(int width) {
	if (width % 2 == 1) return (tiling(width)-tiling(width / 2) + MOD) % MOD; //홀수인 경우 정가운데에 세로블럭 하나인 경우만 대칭 = 그 블럭 전까지의 경우의수
	int ret = tiling(width);
	//짝수인 경우 누적
	ret = (ret - tiling(width / 2) + MOD) % MOD; //딱 절반으로 나뉘는 경우
	ret = (ret - tiling((width / 2) - 1) + MOD) % MOD; // 중앙이 가로블럭 두개로 걸치는 경우
	return ret;
}

//처음부터 비대칭인 경우 세기 : 양쪽에서 블럭을 채워가며 abcd대칭을 확인
//a : [세로1 .... 세로1] width - 2 : 대칭 >> 안쪽으로 재귀
//b : [가로2 .... 가로2] width - 4 : 대칭 >> 안쪽으로 재귀
//c : [세로1 .... 가로2] width - 3 : 비대칭 >> 바로 count 1
//d : [가로2 .... 세로1] width - 3 : 비대칭 >> 바로 count 1
int cache2[101];
int asymmetric2(int width) {
	//기저사례 너비가 2 이하 경우 : 
	//2 = 중앙 2자리가 남은것이므로 width는 짝수, 가로2 혹은 세로1 * 2 이므로 무조건 대칭
	//1 = 중앙 한자리이므로 width는 홀수, 세로1이므로 무조건 대칭
	if (width <= 2) return 0; //not count
	//메모이제이션
	int& ret = cache2[width];
	if (ret != -1) return ret;

	//ret을 abcd를 검사하며 비대칭인 경우를 더해간다.
	ret = asymmetric2(width - 2) % MOD;        //a 경우
	ret = (ret + asymmetric2(width - 4)) % MOD;//b 경우
	ret = (ret + tiling(width - 3)) % MOD;     //c 경우
	ret = (ret + tiling(width - 3)) % MOD;     //d 경우
	return ret;
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		memset(cache2, -1, sizeof(cache2));
		cin >> width;
		//cout << asymmetric(width) << endl;
		cout << asymmetric2(width) << endl;
	}
}