#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
int cache[101];
int width;

//2*widthũ���� �簢���� ä��� ����� ���� MOD�� ���� �������� ��ȯ
int tiling(int width) {
	//������� : width�� 1�����̸� ���� ���� ����Ǽ� +1 (1�� ������ ������ ��ĭ�� ������ ���κ�� �����̱� ����)
	if (width <= 1) return 1;
	//�޸������̼�
	int& ret = cache[width];
	if (ret != -1) return ret;
	//Ÿ���� ���η� �ϳ� ���°�� -1, ���η� �ΰ� ���°�� -2 �Ǵ� width
	return ret = (tiling(width - 1) + tiling(width - 2)) % MOD; 
}

//��ü ��쿡�� ��Ī�ΰ�� ����
//2*widthũ���� ���Ī���� �簢���� ä��� ����� ���� MOD�� ���� �������� ��ȯ
int asymmetric(int width) {
	if (width % 2 == 1) return (tiling(width)-tiling(width / 2) + MOD) % MOD; //Ȧ���� ��� ������� ���κ� �ϳ��� ��츸 ��Ī = �� �� �������� ����Ǽ�
	int ret = tiling(width);
	//¦���� ��� ����
	ret = (ret - tiling(width / 2) + MOD) % MOD; //�� �������� ������ ���
	ret = (ret - tiling((width / 2) - 1) + MOD) % MOD; // �߾��� ���κ� �ΰ��� ��ġ�� ���
	return ret;
}

//ó������ ���Ī�� ��� ���� : ���ʿ��� ���� ä������ abcd��Ī�� Ȯ��
//a : [����1 .... ����1] width - 2 : ��Ī >> �������� ���
//b : [����2 .... ����2] width - 4 : ��Ī >> �������� ���
//c : [����1 .... ����2] width - 3 : ���Ī >> �ٷ� count 1
//d : [����2 .... ����1] width - 3 : ���Ī >> �ٷ� count 1
int cache2[101];
int asymmetric2(int width) {
	//������� �ʺ� 2 ���� ��� : 
	//2 = �߾� 2�ڸ��� �������̹Ƿ� width�� ¦��, ����2 Ȥ�� ����1 * 2 �̹Ƿ� ������ ��Ī
	//1 = �߾� ���ڸ��̹Ƿ� width�� Ȧ��, ����1�̹Ƿ� ������ ��Ī
	if (width <= 2) return 0; //not count
	//�޸������̼�
	int& ret = cache2[width];
	if (ret != -1) return ret;

	//ret�� abcd�� �˻��ϸ� ���Ī�� ��츦 ���ذ���.
	ret = asymmetric2(width - 2) % MOD;        //a ���
	ret = (ret + asymmetric2(width - 4)) % MOD;//b ���
	ret = (ret + tiling(width - 3)) % MOD;     //c ���
	ret = (ret + tiling(width - 3)) % MOD;     //d ���
	return ret;
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		memset(cache2, -1, sizeof(cache2));
		cin >> width;
		//cout << asymmetric(width) << endl;
		cout << asymmetric2(width) << endl;
	}
}