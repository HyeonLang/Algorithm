#include <iostream>
#include <vector>
using namespace std;

//a+=b*(10)^k
void addTo(vector<int>& a, const vector<int>& b, int k) {
	int an = a.size(), bn = b.size();
	a.resize(max(an, bn + k)); //***�߿�
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
	//�ø�ó�� ����
	return ret;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();

	//a�� b���� ª�� ��� exchange
	if (an < bn) return karatsuba(b, a);

	//�������:a,b�� ����ִ� ���
	if (an == 0 || bn == 0) return vector<int>();

	//�������: a�� ���� ª�� ��� O(n^2)�������� ����
	if (an <= 50) return multiply(a, b);

	int half = an / 2; //������ �ɰ� �ڸ���
	//a�� b�� half�ڸ��� �ɰ���. [10^0,half-1],[half, end]
	vector<int> a0(a.begin(), a.begin() + half); //vector ���� ������ (ó������, ������+1)
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
	vector<int> ret; //size+size+1�� �ؾ� ������ �ڸ����� ���´�.
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half * 2);
	return ret;
}

int hugs(const string& members, const string& fans) {
	int N = members.size(), M = fans.size();
	vector<int> A(N, 0), B(M, 0); //0���� �ʱ�ȭ

	//���ڴ� 1 ���ڴ� 0���� �Ͽ� ���ϸ� ��*�� �� ��쿡�� 1�� ���´�. 
	//���� 1�ϰ�쿣 ��� ����ϴ°��� �Ұ����� ����̴�.
	for (int i = 0; i < N; i++) {
		A[i] = (members[i] == 'M'); //bool�� 0 or 1
	}
	for (int i = 0; i < M; i++) {
		B[M-i-1] = (fans[i] == 'M'); //���� ����� �Ųٷ� ��ġ�Ͽ� ��Ī
	}
	//karatsuba �˰��򿡼� �ڸ��ø��� ����
	vector<int> C = karatsuba(A, B); //ī������ �˰������� �ڸ��� ���
	int allHugs = 0; //��� ����� Ƚ�� ī��Ʈ ����
	for (int i = N-1; i < M; i++) { //[ù��meet���������, ��������meetù���]
		if (C[i] == 0) //���� * ���� = 0 �ϰ�� ���
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