#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

const int MAX_SIZE = 100;

//char decompressed[MAX_SIZE][MAX_SIZE];


//압축을 다 풀지않고 뒤집기
//안쪽에서 부터 내용을 뒤집고 밖으로 나오면서 위치를 뒤집기
string reverse(string::iterator& it) {
	char head = *it; //head는 현재 it을
	++it; //it은 다음을 가르킴

	//w,b가 나오면 그대로 돌려줌 //reverse 하기 위해
	if (head == 'w' || head == 'b') {
		return string(1, head);
	}

	//재귀 단계
	//위 2개 사분면
	string upperLeft = reverse(it); //2사분면
	string upperRight = reverse(it);//1사분면
	//아래 2개 사분면
	string lowerLeft = reverse(it); //3사분면
	string lowerRight = reverse(it);//4사분면

	//최초 x의 내용을 lower와 upper의 char을 반대로 두어 reverse
	return string("x") + lowerLeft + lowerRight //3, 4사분면을 위로
		               + upperLeft + upperRight;//2, 1사분면을 아래로 하여 x뒤에 붙여 리턴;
}

/*
//모두 압축 풀기
//반복자, 시작 y좌표, 시작 x좌표, 적용될 사이즈
void decompress(string::iterator& it, int y, int x, int size) {
	//한글자 검사시 반복자를 한칸앞으로 옮김
	char head = *(it++); //it은 포인터 재귀 반복시 계속 ++된것이 누적
	//기저사례: 첫글자가 b또는 w인경우
	if (head == 'b' || head == 'w') {
		for (int dy = 0; dy < size; dy++) {
			for (int dx = 0; dx < size; dx++) {
				decompressed[y + dy][x + dx] = head;
			}
		}
	}
	else { //첫글자가 x인경우
		int half = size / 2;
		decompress(it, y, x, half); //2사분면 
		decompress(it, y, x + half, half); //1사분면
		decompress(it, y + half, x, half); //3사분면
		decompress(it, y + half, x + half, half); //4사분면
	}
}
*/

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		string s;
		cin >> s;
		string::iterator it = s.begin();
		cout << reverse(it) << endl;
	}
}