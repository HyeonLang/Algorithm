#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//-1:입력전, 0:대응안됨(false), 1:대응됨(true)
int cache[101][101]; //시작 위치에 대응여부를 저장
string W, S;

void cacheInit(int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cache[i][j] = -1;
}

/*
bool match(const string& w, const string& s) {
	int pos = 0;
	//w[pos]와 s[pos]를 맞춰나간다.
	while (pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos])) {
		//pos가 w,s의 길이보다 작으면서 w가 ?이거나 w=s인 경우 다음글자 매칭
		pos++;
	}
	//더이상 대응이 불가능하면 왜 while문 끝났는지 확인
	//2.패턴 끝에 도달해서 끝난경우 : 문자열도 끝났어야 대응됨.
	if (pos == w.size())
		return (pos == s.size()); //bool식 pos == s.size인경우 true 리턴

	//4.*를 만나서 끝난경우 : *에 몇글자를 대응해야할지 재귀호출
	if (w[pos] == '*') {
		//pos+skip == s.size()인 경우 w의 *가 s의 끝까지 대응됨
		for (int skip = 0; pos + skip <= s.size(); skip++) {
			//w의 *다음글자부터와 s가 *로인해 스킵당한 글자 다음부터를 매칭
			if (match(w.substr(pos + 1), s.substr(pos + skip))) { 
				return true; //재귀함수가 모두 true이면 ture결과 리턴
						     //하나라도 false면 false결과 리턴 (다음 코드로 리턴)
			}
		}
	}
	return false;
}
*/

/*
//O(n^3)시스템
bool matchMemoized(int w, int s) { //W와 S의 시작위치 인자 
	//메모이제이션
	int& ret = cache[w][s]; //***중요***참조형으로 받아 변경이 쉽다.
	if (ret != -1) return ret; //이미 저장된 중복값 리턴

	//W[w]와 S[s]를 맞춰나간다,
	while (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])) {
		//pos가 w,s의 길이보다 작으면서 w가 ?이거나 w=s인 경우 다음글자 매칭
		w++;
		s++;
	}
	//더이상 대응이 불가능하면 왜 while문 끝났는지 확인
	//2.패턴 끝에 도달해서 끝난경우 : 문자열도 끝났어야 대응됨.
	if (w == W.size())
		return ret = (s == S.size()); //bool 값 0or1이 cache에 int로 저장

	//4.*를 만나서 끝난 경우 : *에 몇글자가 대응되어 스킵할지 재귀호출하여 확인
	if (W[w] == '*') {
		for (int skip = 0; skip + s <= S.size(); skip++) {
			//w, s의 다음 시작위치를 인자로하여 재귀호출
			if (matchMemoized(w + 1, s + skip)) {
				//재귀함수가 모두 true이면 ture결과 리턴
				//하나라도 false면 false결과 리턴 (다음 코드로 리턴)
				return ret = 1; //true(1) 리턴 + cache도 지정
			}
		}
	}
	return ret = 0; //false(0) 리턴 + cache도 지정
}

*/
//O(n^2)시스템 : for문을 재귀호출로 바꾸어 메모이제이션하는 과정을 늘린다.
bool matchMemoized2(int w, int s) { //W와 S의 시작위치 인자 
	//메모이제이션
	int& ret = cache[w][s]; //***중요***참조형으로 받아 변경이 쉽다.
	if (ret != -1) return ret; //이미 저장된 중복값 리턴

	//W[w]와 S[s]를 맞춰나간다,
	if (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])) {
		//pos가 w,s의 길이보다 작으면서 w가 ?이거나 w=s인 경우 다음 시작위치로 재귀호출
		return ret = matchMemoized2(w + 1, s + 1);
	}
	//더이상 대응이 불가능하면 왜 while문 끝났는지 확인
	//2.패턴 끝에 도달해서 끝난경우 : 문자열도 끝났어야 대응됨.
	if (w == W.size())
		return ret = (s == S.size()); //bool 값 0or1이 cache에 int로 저장

	//4.*를 만나서 끝난 경우 : *에 몇글자가 대응되어 스킵할지 재귀호출하여 확인
	if (W[w] == '*') {
		if (matchMemoized2(w + 1, s) || (s < S.size() && matchMemoized2(w, s + 1))) {
			//1.*에 0글자를 대응시켜 스킵하는경우 or 2.*에 1글자를 대입시켜 스킵하는 경우
			//2번이 반복되면 여러글자를 대입시켜 스킵하는 경우가 된다.
			return ret = 1; //true(1)리턴 + cache도 지정
		}
	}
	return ret = 0; //false(0) 리턴 + cache도 지정
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		string w;
		cin >> w;
		W = w;
		int n;
		cin >> n;
		vector<string> solve;
		for (int j = 0; j < n; j++) {
			//memset(cache, -1, sizeof(cache));
			cacheInit(101);
			string filename;
			cin >> filename;
			S = filename;
			if (matchMemoized2(0, 0) == true) {
				solve.push_back(filename);
			}
		}
		sort(begin(solve), end(solve));
		for (int k = 0; k < solve.size(); k++) {
			cout << solve[k] << endl;
		}
	}
}