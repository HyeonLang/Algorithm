#include <iostream>
#include <vector>
using namespace std;

//a+=b*(10)^k
void addTo(vector<int>& a, const vector<int>& b, int k) {
	int an = a.size(), bn = b.size();
	a.resize(max(an, bn + k)); //***중요
	for (int i = 0; i < bn; i++) {
		a[i + k] += b[i];
	}
}

//a-=b, a>=b
void subFrom(vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	a.resize(max(an, bn + 1));
	for (int i = 0; i < bn; i++) {
		a[i] -= b[i];
	}
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	vector<int> ret(an + bn + 1, 0);
	for (int i = 0; i < an; i++) {
		for (int j = 0; j < bn; j++) {
			ret[i + j] += a[i] * b[j];
		}
	}
	//올림처리 생략
	return ret;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();

	//a가 b보다 짧을 경우 exchange
	if (an < bn) return karatsuba(b, a);

	//기저사례:a,b가 비어있는 경우
	if (an == 0 || bn == 0) return vector<int>();

	//기저사례: a가 비교적 짧은 경우 O(n^2)곱셈으로 변경
	if (an <= 50) return multiply(a, b);

	int half = an / 2; //반으로 쪼갠 자리수
	//a와 b를 half자리로 쪼갠다. [10^0,half-1],[half, end]
	vector<int> a0(a.begin(), a.begin() + half); //vector 복사 생성자 (처음범위, 끝범위+1)
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min(bn, half));
	vector<int> b1(b.begin() + min(bn, half), b.end());

	//z2 = a1*b1
	vector<int> z2 = karatsuba(a1, b1);
	//z0 = a0*b0
	vector<int> z0 = karatsuba(a0, b0);
	//a0 = a0 + a1, b0 = b0 + b1
	addTo(a0, a1, 0);
	addTo(b0, b1, 0);
	//z1 = (a0*b0)-z0-z2
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	//ret = z0 + z1*10^half + z2*10^(half*2)
	vector<int> ret; //size+size+1을 해야 곱셈의 자리수가 나온다.
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half * 2);
	return ret;
}

int hugs(const string& members, const string& fans) {
	int N = members.size(), M = fans.size();
	vector<int> A(N, 0), B(M, 0); //0으로 초기화

	//남자는 1 여자는 0으로 하여 곱하면 남*남 일 경우에만 1이 나온다. 
	//따라서 1일경우엔 모두 허그하는것이 불가능한 경우이다.
	for (int i = 0; i < N; i++) {
		A[i] = (members[i] == 'M'); //bool값 0 or 1
	}
	for (int i = 0; i < M; i++) {
		B[M-i-1] = (fans[i] == 'M'); //팬을 멤버와 거꾸로 배치하여 매칭
	}
	//karatsuba 알고리즘에서 자리올림은 생략
	vector<int> C = karatsuba(A, B); //카라츠바 알고리즘으로 자리값 계산
	int allHugs = 0; //모두 허그한 횟수 카운트 변수
	for (int i = N-1; i < M; i++) { //[첫팬meet마지막멤버, 마지막팬meet첫멤버]
		if (C[i] == 0) //성별 * 성별 = 0 일경우 허그
			allHugs++;
	}
	return allHugs;
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		string members;
		string fans;
		cin >> members;
		cin >> fans;
		cout << hugs(members, fans) << endl;
	}
}