#include <iostream>
#include <vector>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
const int linked[10][16] = {
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0 ,0 ,0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 ,0 ,0},
	{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,1, 1},
	{0, 0, 0, 1, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0 ,0, 0, 0, 1, 1, 0 ,1, 0, 0 ,0, 0, 0, 0, 1, 1},
	{0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0 ,0 ,0 ,1, 1, 1, 0, 0 ,0 ,1, 0, 0, 0, 1, 0, 0}
};
bool areAligned(const vector<int>& clocks) { //모든 시계가 12시를 가리키고 있는지 확인
	bool ok = true;
	for (int i = 0; i < clocks.size(); i++) {
		if (clocks[i] != 12)
			ok = false;
	}
	return ok;
}

void push(vector<int>& clocks, int swtch) { //swtch번째 스위치를 누름.
	for (int clock = 0; clock < CLOCKS; clock++) {
		if (linked[swtch][clock] == 1) {
			clocks[clock] = clocks[clock] + 3;
			if (clocks[clock] == 15)
				clocks[clock] = 3;
		}
	}
}

int solve(vector<int>& clocks, int swtch) {
	//기저사례 : 모든 스위치를 눌렀을때 모든 시계가 12시이면 0 리턴,아니면 INF 리턴
	if (swtch == SWITCHES) return areAligned(clocks) ? 0 : INF; //마지막 스위치는 오버스위치 이므로 누른것이 아니다. 따라서 0 리턴
	int ret = INF;
	for (int cnt = 0; cnt < 4; cnt++) { //4번이상 누를경우 제자리이므로 //재귀호출시 반복한 모든 cnt값의 합이 버튼을 누른 횟수이다. (초기상태 = cnt 0)
		ret = min(ret, cnt + solve(clocks, swtch + 1));
		push(clocks, swtch); //4번 푸쉬하면 원래와 같은 상태이므로 재귀 호출 시 cnt가 0~3이므로 4번 반복 푸쉬되어 원상태로 호출된다.
	}
	return ret; //최소 버튼 누른 횟수 리턴
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		vector<int> clocks;
		for (int j = 0; j < 16; j++) {
			int clock_time;
			cin >> clock_time;
			clocks.push_back(clock_time);
		}
		int ans = solve(clocks, 0);
		if (ans == INF)
			ans = -1;
		cout << ans << endl;
	}
}