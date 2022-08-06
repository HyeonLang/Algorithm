#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m; //문장에 나오는 단어 갯수, 출현 가능한 단어 갯수
int R[100];  //분류기가 반환한 문장. 단어 번호로 변환됨.
double T[501][501]; //T[i][j] = i 단어 이후에 j단어가 나올 확률의 로그값
double M[501][501]; //M[i][j] = i 단어가 j단어로 분류될 확률의 로그값
double B[501]; //처음 나올 단어의 확률;
double cache[102][502]; //확률이므로 1로 초기화
int choice[102][502]; 
string corpus[501]; //입력받은 단어 목록

void init() {
	for (int i = 0; i < 102; ++i)
		for (int j = 0; j < 502; ++j)
			cache[i][j] = 1.0;
}

double recognize(int segment, int previousMatch) { //현재 고른 단어의 갯수, 전에 고른 단어
	if (segment == n) return 0; //0 = log(1);

	double& ret = cache[segment][previousMatch];
	if (ret != 1.0) return ret;

	ret = -1e200;//log(0) = 음의 무한대에 해당
	int& choose = choice[segment][previousMatch];

	//R[segment]에 대응되는 단어를 찾는다.
	for (int thisMatch = 1; thisMatch < m+1; thisMatch++) { //가상의 첫단어 제외하고 현단계 단어고르기
		double cand = T[previousMatch][thisMatch] //전단어 다음으로 고른단어가 될 확률
			+ M[thisMatch][R[segment]] //고른 단어가 분류된 단어 R[seg]가 될 확률 
			+ recognize(segment + 1, thisMatch); //다음 단어 재귀
		if (ret < cand) {
			ret = cand;
			choose = thisMatch; //고른 단어 기록
		}
	}
	return ret;
}

string reconstruct(int segment, int previousMatch) {
	int choose = choice[segment][previousMatch]; //저장해둔 best경로 index
	string ret = corpus[choose]; //best를 받아옴
	if (segment < n - 1) //마지막의 전단계이면
		ret = ret + " " + reconstruct(segment + 1, choose); //단어 결합하고 다음단어 재귀
	return ret; //마지막단계이면 best단어, 그 외에는 best를 결합한 단어 return
}

int main() {
		
		int q; //처리할 문장의 갯수

		//순서만을 이용하는 배열을 제외한 배열의 인덱스를 모두 통일할것
		//여기서는 처음값 확률을 위해 1~m+1로 통일.
		cin >> m >> q;
		for (int j = 1; j < m+1; j++) {
			cin >> corpus[j];
		}
		for (int j = 1; j < m+1; j++) {
			cin >> B[j];
			B[j] = log(B[j]);
		}
		for (int j = 1; j < m+1; j++) {
			T[0][j] = B[j];  //가상의 맨 앞 단어 만들기.
			for (int k = 1; k < m+1; k++) {                 
				cin >> T[j][k];
				T[j][k] = log(T[j][k]);
					
			}
		}
		for (int j = 1; j < m+1; j++) {
			for (int k = 1; k < m+1; k++) {
				cin >> M[j][k];
				M[j][k] = log(M[j][k]);
			}
		}
		vector<string> v;
		for (int j = 0; j < q; j++) {
			init();
			cin >> n;
			for (int k = 0; k < n; k++) {
				string str;
				cin >> str;
				for (int h = 1; h < m+1; h++) {
					if (str == corpus[h]) {
						R[k] = h;
						break;
					}
				}
			}
			recognize(0, 0);
			v.push_back(reconstruct(0, 0));
		}
		for (int y = 0; y < v.size(); y++) {
			cout << v[y] << endl;
		}
	}
