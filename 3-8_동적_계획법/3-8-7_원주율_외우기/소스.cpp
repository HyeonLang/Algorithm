#include <iostream>
#include <cstring>

using namespace std;

const int INF = 987654321;
int cache[10002];
string N;

int classify(int start, int end) { //[start, end], 난이도 return
	//숫자 조각 가져옴.
	string M = N.substr(start, end - start + 1); // start 부터 end-start+1 만큼 끊는다.
	//case1 모두 같은 숫자인지 검사
	if (M == string(M.size(), M[0])) return 1; // (M[0]가 M.size()개수로 있는 문자열)조각내 숫자가 모두 같으면 난이도 1 

	//case2,4 등차수열인지 검사
	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++) { //비교이기때문에 -1
		if (M[i+1] - M[i] != M[1] - M[0]){ //아스키코드 연산
			progressive = false;
			break;
		}
	}
	//case2_final 등차수열의 공차가 1, -1 이면 단조 증감 검사
	if (abs(M[1] - M[0]) == 1 && progressive) {
		return 2; //난이도 2
	}
	
	//case3 두수가 번갈아 나오는지 검사
	bool alternating = true;
	for (int i = 0; i < M.size(); i++) {
		if (M[i] != M[i%2]) {
			alternating = false;
			break;
		}
	}
	if (alternating) return 4; //난이도 4

	//case4_final 등차수열이면 (단조 제외) 난이도 5
	if (progressive) return 5;

	//case5 무규칙이면 난이도 10
	return 10;
}

int memorize(int begin) {
	//기저사례 : 수열 끝에 도달
	if (begin == N.size()) return 0;
	//메모이제이션
	int& ret = cache[begin];
	if (ret != -1) return ret;
	ret = INF; //최고 난이도로 초기화해둠 (-1 로 초기화 방지)
	           //***중요*** 끝자리가 1개 혹은 2개가 남을 경우를 난이도를 올려서 ret값이 되지 않도록 방지한다. 
	
	//3~5개씩 쪼개 난이도를 계산한 뒤 나머지 뒷부분을 재귀호출하여 더한다.
	for (int L = 3; L <= 5; L++) { //수열을 3~5개씩 쪼갠다.
		if (begin + L <= N.size())
			ret = min(ret, classify(begin, begin + L - 1) + memorize(begin + L)); //L개만큼 쪼개어 난이도계산 + 나머지 begin+L 부터 재귀호출
	}
	return ret;
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		cin >> N;
		cout << memorize(0) << endl;
	}
}