#include <iostream>
#include <vector>
using namespace std;

vector<int> fence;

/*case1: ���ʿ��� ���� ū ���簢��
 case2 : �����ʿ��� ���� ū ���簢��
 case3 : �Ѵ� ��ġ�� �簢���� ���� ū ���簢��*/


int solve(int left, int right) {
	//���� ��� : ���ڰ� �ϳ��� �ִ°��
	if (left == right) return fence[left];

	//[left, mid], [mid+1, right]�� �� ���� ����
	int mid = (left + right) / 2; //������ Ż���̹Ƿ� Ȧ���̸� ������

	//������ ������ �������� case1,2
	int ret = max(solve(left, mid), solve(mid + 1, right));
	
	//�� �κп� ��� ��ġ�� �簢���� ���� ū�� ã�� case3
	int lo = mid, hi = mid + 1;
	//[left......lo,hi......right]
	int height = min(fence[lo], fence[hi]);
	//[mid, mid+1]�� �����ϴ� �ʺ� 2�� �簢�� ���
	ret = max(ret, height * 2);

	//�簢���� �Է� ��ü�� ���� �� ���� Ȯ��
	//[left <<< lo...hi >>> right] �̷��� ����
	while (left < lo || hi < right) { //lo, hi�� �� ������ �� �� ���� ��� �ѹ��� �ݺ�
		//***�׻� ���̰� ���������� Ȯ��***
		if (hi < right && (lo == left || fence[lo-1] < fence[hi+1])) {//�������� ��� �Ű�ų� ���� ��Ÿ���� ������ ������ ��Ÿ���� ���� ��Ȳ
			hi++;
			height = min(height, fence[hi]);
		}
		else {// �����̳��� ������ ���� ���̰ų� ���������� ��� �Űܺ��� ��.
			lo--;
			height = min(height, fence[lo]);
		}
		ret = max(ret, height * (hi - lo + 1)); //Ȯ�� �� �簢�� ����
	}
	return ret;
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		int n;
		cin >> n;
		for (int j = 0; j < n; j++) {
			int h;
			cin >> h;
			fence.push_back(h);
		}
		cout << solve(0, n - 1) << endl;
		fence.clear();
	}

}