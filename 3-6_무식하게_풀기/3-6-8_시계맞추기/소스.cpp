#include <iostream>
#include <vector>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
const int linked[10][16] = {
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0 ,0 ,0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 ,0 ,0},
	{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,1, 1},
	{0, 0, 0, 1, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0 ,0, 0, 0, 1, 1, 0 ,1, 0, 0 ,0, 0, 0, 0, 1, 1},
	{0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0 ,0 ,0 ,1, 1, 1, 0, 0 ,0 ,1, 0, 0, 0, 1, 0, 0}
};
bool areAligned(const vector<int>& clocks) { //��� �ð谡 12�ø� ����Ű�� �ִ��� Ȯ��
	bool ok = true;
	for (int i = 0; i < clocks.size(); i++) {
		if (clocks[i] != 12)
			ok = false;
	}
	return ok;
}

void push(vector<int>& clocks, int swtch) { //swtch��° ����ġ�� ����.
	for (int clock = 0; clock < CLOCKS; clock++) {
		if (linked[swtch][clock] == 1) {
			clocks[clock] = clocks[clock] + 3;
			if (clocks[clock] == 15)
				clocks[clock] = 3;
		}
	}
}

int solve(vector<int>& clocks, int swtch) {
	//������� : ��� ����ġ�� �������� ��� �ð谡 12���̸� 0 ����,�ƴϸ� INF ����
	if (swtch == SWITCHES) return areAligned(clocks) ? 0 : INF; //������ ����ġ�� ��������ġ �̹Ƿ� �������� �ƴϴ�. ���� 0 ����
	int ret = INF;
	for (int cnt = 0; cnt < 4; cnt++) { //4���̻� ������� ���ڸ��̹Ƿ� //���ȣ��� �ݺ��� ��� cnt���� ���� ��ư�� ���� Ƚ���̴�. (�ʱ���� = cnt 0)
		ret = min(ret, cnt + solve(clocks, swtch + 1));
		push(clocks, swtch); //4�� Ǫ���ϸ� ������ ���� �����̹Ƿ� ��� ȣ�� �� cnt�� 0~3�̹Ƿ� 4�� �ݺ� Ǫ���Ǿ� �����·� ȣ��ȴ�.
	}
	return ret; //�ּ� ��ư ���� Ƚ�� ����
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		vector<int> clocks;
		for (int j = 0; j < 16; j++) {
			int clock_time;
			cin >> clock_time;
			clocks.push_back(clock_time);
		}
		int ans = solve(clocks, 0);
		if (ans == INF)
			ans = -1;
		cout << ans << endl;
	}
}