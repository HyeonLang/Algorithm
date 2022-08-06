#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 10 * 1000 * 1000; //ū �� ���� ������
int cache[101][101];

//n���� ���簢��, �� �����ٿ� first���� ���簢���� ������ ������̿��� �� ��ȯ
int poly(int n, int first) { //n : ���� �ٿ��� ���� ����, first : ���� �� ���� ����
	//������� n == first
	if (n == first) return 1; // �� ������ ����� ���� 1���� (��ġ�� ������ �ʴ´�.)
	//�޸��� ���̼�
	int& ret = cache[n][first];
	if (ret != -1) return ret;
	ret = 0; //�ʱ�ȭ
	//���� �������� 1 ~ (n - first) ���̿��� ����
	for (int second = 1; second <= n - first; second++) {
		int add = second + first - 1; //�� ���ܰ�� ���� ���ܰ谡 ��ġ�� ����� ��
		add = add * poly(n - first, second); //���� �ܰ� ���, add = ������� ������̿� ����Ǽ� 
		add = add % MOD; 
		ret = ret + add; //�޸������̼ǿ� ����
		ret = ret % MOD;
	}
	return ret; //for���� ��� ���� return
}
int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		int n, sum = 0;
		cin >> n;
		for (int j = 0; j < n; j++) { 
			sum = sum + poly(n, j + 1);
			sum = sum % MOD; 
		}
		cout << sum << endl;
	}
}