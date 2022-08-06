#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m; //���忡 ������ �ܾ� ����, ���� ������ �ܾ� ����
int R[100];  //�з��Ⱑ ��ȯ�� ����. �ܾ� ��ȣ�� ��ȯ��.
double T[501][501]; //T[i][j] = i �ܾ� ���Ŀ� j�ܾ ���� Ȯ���� �αװ�
double M[501][501]; //M[i][j] = i �ܾ j�ܾ�� �з��� Ȯ���� �αװ�
double B[501]; //ó�� ���� �ܾ��� Ȯ��;
double cache[102][502]; //Ȯ���̹Ƿ� 1�� �ʱ�ȭ
int choice[102][502]; 
string corpus[501]; //�Է¹��� �ܾ� ���

void init() {
	for (int i = 0; i < 102; ++i)
		for (int j = 0; j < 502; ++j)
			cache[i][j] = 1.0;
}

double recognize(int segment, int previousMatch) { //���� �� �ܾ��� ����, ���� �� �ܾ�
	if (segment == n) return 0; //0 = log(1);

	double& ret = cache[segment][previousMatch];
	if (ret != 1.0) return ret;

	ret = -1e200;//log(0) = ���� ���Ѵ뿡 �ش�
	int& choose = choice[segment][previousMatch];

	//R[segment]�� �����Ǵ� �ܾ ã�´�.
	for (int thisMatch = 1; thisMatch < m+1; thisMatch++) { //������ ù�ܾ� �����ϰ� ���ܰ� �ܾ����
		double cand = T[previousMatch][thisMatch] //���ܾ� �������� ���ܾ �� Ȯ��
			+ M[thisMatch][R[segment]] //�� �ܾ �з��� �ܾ� R[seg]�� �� Ȯ�� 
			+ recognize(segment + 1, thisMatch); //���� �ܾ� ���
		if (ret < cand) {
			ret = cand;
			choose = thisMatch; //�� �ܾ� ���
		}
	}
	return ret;
}

string reconstruct(int segment, int previousMatch) {
	int choose = choice[segment][previousMatch]; //�����ص� best��� index
	string ret = corpus[choose]; //best�� �޾ƿ�
	if (segment < n - 1) //�������� ���ܰ��̸�
		ret = ret + " " + reconstruct(segment + 1, choose); //�ܾ� �����ϰ� �����ܾ� ���
	return ret; //�������ܰ��̸� best�ܾ�, �� �ܿ��� best�� ������ �ܾ� return
}

int main() {
		
		int q; //ó���� ������ ����

		//�������� �̿��ϴ� �迭�� ������ �迭�� �ε����� ��� �����Ұ�
		//���⼭�� ó���� Ȯ���� ���� 1~m+1�� ����.
		cin >> m >> q;
		for (int j = 1; j < m+1; j++) {
			cin >> corpus[j];
		}
		for (int j = 1; j < m+1; j++) {
			cin >> B[j];
			B[j] = log(B[j]);
		}
		for (int j = 1; j < m+1; j++) {
			T[0][j] = B[j];  //������ �� �� �ܾ� �����.
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
