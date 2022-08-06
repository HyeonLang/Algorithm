#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 987654321; //최소오류값 초기화
int A[101]; //정렬된 양자화 할 수열
int pSum[101]; //A[]의 부분합 저장 pSum[i] = A[0~i]의 합
int psqSum[101]; //A[]^2의 부분합 저장 psqSum[i] = A[0]^2 ~ A[i]^2의 합
int n;
//A를 정렬하고 부분합을 구한다.
void preclac() {
	sort(A, A + n); //A[0]부터 A[n-1]까지 오름차순 정렬

	//부분합 계산
	pSum[0] = A[0];
	psqSum[0] = A[0] * A[0];
	for (int i = 1; i < n; i++) {
		pSum[i] = A[i] + pSum[i - 1];
		psqSum[i] = (A[i] * A[i]) + psqSum[i - 1];
	}
}

//A[lo]~A[hi] 구간을 하나의 숫자로 표현할 때 최소 오차 합 계산
int minError(int lo, int hi) {
	//부분합을 사용하여 lo~hi구간 sum구하기
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = psqSum[hi] - (lo == 0 ? 0 : psqSum[lo - 1]);
	//평균을 반올림 한 값으로 이 수들을 표현 m = 평균
	int m = int(0.5 + (double)sum / (hi - lo + 1)); //int 형변환은 버림이므로 반올림을 하기 위해서 0.5를 더해준다.
	//sum ((A[i] - m)^2) 을 전개한 결과를 부분합으로 표현 
	int ret = sqSum - 2 * m * sum + (m * m) * (hi - lo + 1);
	return ret;
}

int cache[101][11]; //메모이제이션 여태까지의 최소오차제곱합을 기록 : [여태까지 묶은 수열의 마지막 위치 + 1] [남은 조각 수]

int quantize(int from, int parts) {//이제부터 묶을 위치, 남은 조각 수
	//기저사례 : 모든 숫자를 양자화 했을 때
	if (from == n) return 0;
	//기저사례 : 숫자는 남았는데 더 묶을 수 없을때 : 절대 최소오차제곱합이 될 수 없으니 큰 수 반환
	if (parts == 0) return INF;

	//메모이제이션
	int& ret = cache[from][parts];
	if (ret != -1) return ret;
	//ret 초기화 : 묶음을 시도했으니 -1은 아니므로 큰 수로 초기화
	ret = INF;

	//조각의 길이를 변화시켜 가며 최소치를 찾는다. partSize = 조각의 길이
	for (int partSize = 1; from + partSize <= n; partSize++) { // from+partSize-1 = 조각의 마지막 원소의 인덱스
		//현재조각의 최소오차제곱합을 계산, 다음 조각위 첫위치와 남은 조각수 - 1 을 넘겨서 재귀호출
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
	}
	return ret;
}


int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		int s;
		cin >> n >> s;
		for (int j = 0; j < n; j++) {
			cin >> A[j];
		}
		preclac();
		cout << quantize(0, s) << endl;
	}
}