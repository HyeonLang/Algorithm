#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int n, capacity; //������ ����, ĳ������ ����
int volume[100], need[100]; //������ ����, ���ڵ�
int cache[1001][100];       
string name[100]; //�̸�

int pack(int capacity, int item) { //���� ����, ���� ������ ����
	//������� �� ���� ������ ���� ��
	if (item == n) return 0;
	int& ret = cache[capacity][item];
	if (ret != -1) return ret;
	
	ret = pack(capacity, item + 1); //item�� ���� ����
	if (volume[item] <= capacity) {
		//max�� item�� ����� ���� ���� �ʾ��� ���� need�� ���Ͽ� �� ū ���� ����
		ret = max(ret, need[item] + pack(capacity - volume[item], item + 1));//item�� ��
	}
	return ret;
}

//pack(capacity, item) �� pack(capacity, item)�� ���Ѵ�.
//need[item, item+1 ... n] == need[item+1 ... n] �̸� item�� ���ڵ� �տ� ���Ե����ʴ´�.
void reconstruct(int capacity, int item, vector<string>& picked) {
	//������� : ��繰���� �����
	if (item == n) return;
	if (pack(capacity, item) == pack(capacity, item + 1)) { //cache�� ����� ���� �ҷ��´�.
		reconstruct(capacity, item + 1, picked); //������ ���� �ʰ� ���� �������� ��ŵ
	}
	else {
		picked.push_back(name[item]);
		reconstruct(capacity - volume[item], item + 1, picked); //������ ���� ������������ ��ŵ
	}
}
int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));

		cin >> n >> capacity;
		for (int j = 0; j < n; j++) {
			cin >> name[j] >> volume[j] >> need[j];
		}
		cout << pack(capacity, 0) << " ";
		vector<string> picked;
		reconstruct(capacity, 0, picked);
		cout << picked.size() << endl;
		for (int j = 0; j < picked.size(); j++) {
			cout << picked[j] << endl;
		}
	}
}