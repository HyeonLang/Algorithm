#include <iostream>
#include <cstring>
#include <limits>


using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int A[100], B[100], n, m;
int cache[101][101];

//합친 증가 부분 수열의 최대 길이를 반환
//단, indexA == indexB == -1 or A[indexA] != B[indexB] 라고 가정한다.
int jlis(int indexA, int indexB) { //현재까지 검사(카운트)해본 A,B원소의 인덱스
	                               //검사(카운트)란 인자 max(A[indexA], B[indexB]) > 이전단계 maxElement 이다.
	//메모이제이션
	int& ret = cache[indexA + 1][indexB + 1];
	if (ret != -1) return ret;
	ret = 2; //A와 B가 존재하므로 합친 증가 부분 수열은 최소 2개는있다.

	//인자로 받은 시작위치 인덱스를 배열에 넣어 값 받기
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	//이 중에서 큰 값을 찾기
	long long maxElement = max(a, b);

	//nextA찾기
	for (int nextA = indexA + 1; nextA < n; nextA++) { 
		if (maxElement < A[nextA]) {
			//A[nextA]가 a혹은b보다 큰경우
			ret = max(ret, jlis(nextA, indexB) + 1);   //***리턴 아님!! 리턴하면 B검사 못함.
			//A[nextA] 원소를 카운트하여 진행
		}
	}

	//nextB찾기
	for (int nextB = indexB + 1; nextB < m; nextB++) { 
		if (maxElement < B[nextB]) {
			//B[nextB]가 a혹은b보다 큰경우
			ret = max(ret, jlis(indexA, nextB) + 1); 
			//B[nextB] 원소를 카운트하여 진행
		}
	}
	return ret; //양 배열에서 더이상 더 큰 원소를 찾을 수 없다.
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		cin >> n >> m; //배열 메모리가 고정적이므로 사용할 크기를 입력으로 제어
		for (int j = 0; j < n; j++) {
			cin >> A[j];
		}
		for (int j = 0; j < m; j++) {
			cin >> B[j];
		}
		cout << jlis(-1, -1) - 2 << endl;
	}
}