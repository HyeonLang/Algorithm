#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 987654321; //�ּҿ����� �ʱ�ȭ
int A[101]; //���ĵ� ����ȭ �� ����
int pSum[101]; //A[]�� �κ��� ���� pSum[i] = A[0~i]�� ��
int psqSum[101]; //A[]^2�� �κ��� ���� psqSum[i] = A[0]^2 ~ A[i]^2�� ��
int n;
//A�� �����ϰ� �κ����� ���Ѵ�.
void preclac() {
	sort(A, A + n); //A[0]���� A[n-1]���� �������� ����

	//�κ��� ���
	pSum[0] = A[0];
	psqSum[0] = A[0] * A[0];
	for (int i = 1; i < n; i++) {
		pSum[i] = A[i] + pSum[i - 1];
		psqSum[i] = (A[i] * A[i]) + psqSum[i - 1];
	}
}

//A[lo]~A[hi] ������ �ϳ��� ���ڷ� ǥ���� �� �ּ� ���� �� ���
int minError(int lo, int hi) {
	//�κ����� ����Ͽ� lo~hi���� sum���ϱ�
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = psqSum[hi] - (lo == 0 ? 0 : psqSum[lo - 1]);
	//����� �ݿø� �� ������ �� ������ ǥ�� m = ���
	int m = int(0.5 + (double)sum / (hi - lo + 1)); //int ����ȯ�� �����̹Ƿ� �ݿø��� �ϱ� ���ؼ� 0.5�� �����ش�.
	//sum ((A[i] - m)^2) �� ������ ����� �κ������� ǥ�� 
	int ret = sqSum - 2 * m * sum + (m * m) * (hi - lo + 1);
	return ret;
}

int cache[101][11]; //�޸������̼� ���±����� �ּҿ����������� ��� : [���±��� ���� ������ ������ ��ġ + 1] [���� ���� ��]

int quantize(int from, int parts) {//�������� ���� ��ġ, ���� ���� ��
	//������� : ��� ���ڸ� ����ȭ ���� ��
	if (from == n) return 0;
	//������� : ���ڴ� ���Ҵµ� �� ���� �� ������ : ���� �ּҿ����������� �� �� ������ ū �� ��ȯ
	if (parts == 0) return INF;

	//�޸������̼�
	int& ret = cache[from][parts];
	if (ret != -1) return ret;
	//ret �ʱ�ȭ : ������ �õ������� -1�� �ƴϹǷ� ū ���� �ʱ�ȭ
	ret = INF;

	//������ ���̸� ��ȭ���� ���� �ּ�ġ�� ã�´�. partSize = ������ ����
	for (int partSize = 1; from + partSize <= n; partSize++) { // from+partSize-1 = ������ ������ ������ �ε���
		//���������� �ּҿ����������� ���, ���� ������ ù��ġ�� ���� ������ - 1 �� �Ѱܼ� ���ȣ��
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
	}
	return ret;
}


int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		int s;
		cin >> n >> s;
		for (int j = 0; j < n; j++) {
			cin >> A[j];
		}
		preclac();
		cout << quantize(0, s) << endl;
	}
}