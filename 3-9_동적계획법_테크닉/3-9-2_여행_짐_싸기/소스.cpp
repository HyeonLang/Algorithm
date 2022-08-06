#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int n, capacity; //물건의 갯수, 캐리어의 부피
int volume[100], need[100]; //물건이 무게, 절박도
int cache[1001][100];       
string name[100]; //이름

int pack(int capacity, int item) { //남은 부피, 남은 물건의 갯수
	//기저사례 더 담을 물건이 없을 때
	if (item == n) return 0;
	int& ret = cache[capacity][item];
	if (ret != -1) return ret;
	
	ret = pack(capacity, item + 1); //item을 고르지 않음
	if (volume[item] <= capacity) {
		//max로 item을 골랐을 때와 고르지 않았을 때의 need를 비교하여 더 큰 값을 선택
		ret = max(ret, need[item] + pack(capacity - volume[item], item + 1));//item을 고름
	}
	return ret;
}

//pack(capacity, item) 과 pack(capacity, item)을 비교한다.
//need[item, item+1 ... n] == need[item+1 ... n] 이면 item은 절박도 합에 포함되지않는다.
void reconstruct(int capacity, int item, vector<string>& picked) {
	//기저사례 : 모든물건을 고려함
	if (item == n) return;
	if (pack(capacity, item) == pack(capacity, item + 1)) { //cache에 저장된 값을 불러온다.
		reconstruct(capacity, item + 1, picked); //물건을 고르지 않고 다음 물건으로 스킵
	}
	else {
		picked.push_back(name[item]);
		reconstruct(capacity - volume[item], item + 1, picked); //물건을 고르고 다음물건으로 스킵
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