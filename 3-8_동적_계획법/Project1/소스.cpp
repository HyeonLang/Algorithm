#include <iostream>
#include <cstring>
#include <limits>


using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int A[100], B[100], n, m;
int cache[101][101];

//��ģ ���� �κ� ������ �ִ� ���̸� ��ȯ
//��, indexA == indexB == -1 or A[indexA] != B[indexB] ��� �����Ѵ�.
int jlis(int indexA, int indexB) { //������� �˻�(ī��Ʈ)�غ� A,B������ �ε���
	                               //�˻�(ī��Ʈ)�� ���� max(A[indexA], B[indexB]) > �����ܰ� maxElement �̴�.
	//�޸������̼�
	int& ret = cache[indexA + 1][indexB + 1];
	if (ret != -1) return ret;
	ret = 2; //A�� B�� �����ϹǷ� ��ģ ���� �κ� ������ �ּ� 2�����ִ�.

	//���ڷ� ���� ������ġ �ε����� �迭�� �־� �� �ޱ�
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	//�� �߿��� ū ���� ã��
	long long maxElement = max(a, b);

	//nextAã��
	for (int nextA = indexA + 1; nextA < n; nextA++) { 
		if (maxElement < A[nextA]) {
			//A[nextA]�� aȤ��b���� ū���
			ret = max(ret, jlis(nextA, indexB) + 1);   //***���� �ƴ�!! �����ϸ� B�˻� ����.
			//A[nextA] ���Ҹ� ī��Ʈ�Ͽ� ����
		}
	}

	//nextBã��
	for (int nextB = indexB + 1; nextB < m; nextB++) { 
		if (maxElement < B[nextB]) {
			//B[nextB]�� aȤ��b���� ū���
			ret = max(ret, jlis(indexA, nextB) + 1); 
			//B[nextB] ���Ҹ� ī��Ʈ�Ͽ� ����
		}
	}
	return ret; //�� �迭���� ���̻� �� ū ���Ҹ� ã�� �� ����.
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		cin >> n >> m; //�迭 �޸𸮰� �������̹Ƿ� ����� ũ�⸦ �Է����� ����
		for (int j = 0; j < n; j++) {
			cin >> A[j];
		}
		for (int j = 0; j < m; j++) {
			cin >> B[j];
		}
		cout << jlis(-1, -1) - 2 << endl;
	}
}