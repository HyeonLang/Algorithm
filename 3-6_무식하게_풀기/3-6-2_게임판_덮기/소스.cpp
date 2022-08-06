#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int coverType[4][3][2] = {//덮는 블록 타입의 상대적 위치 (y,x)좌표
	{{0,0},{1,0},{0,1}}, //a
	{{0,0},{0,1},{1,1}}, //b
	{{0,0},{1,0},{1,1}}, //c
	{{0,0},{1,0},{1,-1}} //d
};

class Boardcover {
	vector<vector<int>> board;
	int h, w;
public:
	void init(int h, int w) {
		this->h = h;
		this->w = w;
		for (int i = 0; i < h; i++) {
			board.push_back(vector<int>());
		}
		for (int i = 0; i < h; i++) {
			string str;
			cin >> str;
			for (int j = 0; j < str.length(); j++) {
				if (str[j] == '#')
					board[i].push_back(1);
				else
					board[i].push_back(0);
			}
		}
	}
	vector<vector<int>> getBoard() {
		return this->board;
	}
	bool checkFirst() {
		int count = 0;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (this->board[i][j] == 0) {
					count++;
				}
			}
		}
		if (count % 3 == 0)
			return true;
		else
			return false;
	}
	bool set(int y, int x, int type, int delta) {
		bool ok = true;
		for (int i = 0; i < 3; i++) { //블록의 칸수 만큼 반복
			int ny = y + coverType[type][i][0];
			int nx = x + coverType[type][i][1];
			if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size()) //블록이 보드를 넘어갔을 경우
				ok = false;
			else if ((board[ny][nx] += delta) > 1) //board칸을 덮거나 블록을 치운 후 : 검은칸 혹은 이미 덮힌칸의 경우
				ok = false;
		}
		return ok;
	}
	int cover() {
		int y = -1, x = -1;
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				if (board[i][j] == 0) {
					y = i;
					x = j;
					break;
				}
			}
			if (y != -1) break; //y x가 설정되어 있다면 break
		}
		//기저사례: 모든칸을 채웠으면 1을 반환한다.
		if (y == -1) return 1;
		int ret = 0; //리턴될 횟수 저장 변수
		for (int type = 0; type < 4; type++) {
			if (set(y, x, type, 1))	//만약 board[y][x]를 type형태로 덮을 수 있으면 재귀호출 
				ret += cover();    // 일단 두어보고 아니면 밑밑줄에서 바로 블록을 치울 수 있다.
			set(y, x, type, -1);  //덮은 블록 치우기 : 다음 방법을 위한 초기화
		}
		return ret;
	}
};

int main() {
	int C;
	cin >> C;
	Boardcover* prob = new Boardcover[C];
	for (int i = 0; i < C; i++) {
		int h, w;
		cin >> h >> w;
		prob[i].init(h, w);
	}
	for (int i = 0; i < C; i++) {
		if (!prob[i].checkFirst()) {
			cout << 0 << endl;
			continue;
		}
		cout << prob[i].cover() << endl;
	}
}