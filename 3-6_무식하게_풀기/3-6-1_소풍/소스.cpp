/* 테스트케이스 C
학생수 n(2 <= n <= 10), 친구 쌍의 수 m(0 <= m <= n(n - 1) / 2)
 m개의 정수 쌍으로 서로친구인 두 학생의 번호(0 <= <= n-1), 학생수 짝수*/
#include <iostream>

using namespace std;

class Picnic {
	int friendArr[10][10];
	int taken[10];
	int student;
	int friendnum;
public:
	void init(int n, int m) {
		this->student = n;
		this->friendnum = m;
		for (int i = 0; i < n; i++) {
			taken[i] = 0;
			for (int j = 0; j < n; j++) {
				friendArr[i][j] = 0;
			}
		}
	}
	void setArr(int x, int y) { 
		friendArr[x][y] = 1; 
		friendArr[y][x] = 1;
	}

	int getFriendnum() { return friendnum; }
	bool check(int i) {
		if (taken[i] == 0) 
			return false;
		return true;
	}
	int pick() {
		int first = -1;
		for (int i = 0; i < student; i++) {
			if (taken[i] == 0) {
				first = i;
				break;
			}
		}
		if (first == -1) return 1; // 모두 짝을 지어주어서 first할 학생이 없음.
		int ret = 0;
		for (int pair = first + 1; pair < student; pair++) {
			if (taken[pair] == 0 && friendArr[first][pair] == 1) {
				taken[first] = taken[pair] = 1;
				ret += pick(); //재귀 호출의 시작과 끝
				taken[first] = taken[pair] = 0; //초기화
			}
		}
		return ret;
	}
	
};

int main() {
	int C;
	cin >> C;
	Picnic* picArr = new Picnic[C];
	for (int i = 0; i < C; i++) {
		int n, m;
		cin >> n >> m;
		picArr[i].init(n, m);
		for (int j = 0; j < picArr[i].getFriendnum(); j++) {
			int x, y;
			cin >> x >> y;
			picArr[i].setArr(x, y);
		}
	}

	for (int i = 0; i < C; i++) {
		cout << picArr[i].pick() << " ";
	}
	
}