#include <iostream>
#include <cstring>

using namespace std;

const int INF = 987654321;
int cache[10002];
string N;

int classify(int start, int end) { //[start, end], ���̵� return
	//���� ���� ������.
	string M = N.substr(start, end - start + 1); // start ���� end-start+1 ��ŭ ���´�.
	//case1 ��� ���� �������� �˻�
	if (M == string(M.size(), M[0])) return 1; // (M[0]�� M.size()������ �ִ� ���ڿ�)������ ���ڰ� ��� ������ ���̵� 1 

	//case2,4 ������������ �˻�
	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++) { //���̱⶧���� -1
		if (M[i+1] - M[i] != M[1] - M[0]){ //�ƽ�Ű�ڵ� ����
			progressive = false;
			break;
		}
	}
	//case2_final ���������� ������ 1, -1 �̸� ���� ���� �˻�
	if (abs(M[1] - M[0]) == 1 && progressive) {
		return 2; //���̵� 2
	}
	
	//case3 �μ��� ������ �������� �˻�
	bool alternating = true;
	for (int i = 0; i < M.size(); i++) {
		if (M[i] != M[i%2]) {
			alternating = false;
			break;
		}
	}
	if (alternating) return 4; //���̵� 4

	//case4_final ���������̸� (���� ����) ���̵� 5
	if (progressive) return 5;

	//case5 ����Ģ�̸� ���̵� 10
	return 10;
}

int memorize(int begin) {
	//������� : ���� ���� ����
	if (begin == N.size()) return 0;
	//�޸������̼�
	int& ret = cache[begin];
	if (ret != -1) return ret;
	ret = INF; //�ְ� ���̵��� �ʱ�ȭ�ص� (-1 �� �ʱ�ȭ ����)
	           //***�߿�*** ���ڸ��� 1�� Ȥ�� 2���� ���� ��츦 ���̵��� �÷��� ret���� ���� �ʵ��� �����Ѵ�. 
	
	//3~5���� �ɰ� ���̵��� ����� �� ������ �޺κ��� ���ȣ���Ͽ� ���Ѵ�.
	for (int L = 3; L <= 5; L++) { //������ 3~5���� �ɰ���.
		if (begin + L <= N.size())
			ret = min(ret, classify(begin, begin + L - 1) + memorize(begin + L)); //L����ŭ �ɰ��� ���̵���� + ������ begin+L ���� ���ȣ��
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