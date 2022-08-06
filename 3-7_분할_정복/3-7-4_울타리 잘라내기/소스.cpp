#include <iostream>
#include <vector>
using namespace std;

vector<int> fence;

/*case1: 왼쪽에서 가장 큰 직사각형
 case2 : 오른쪽에서 가장 큰 직사각형
 case3 : 둘다 걸치는 사각형중 가장 큰 직사각형*/


int solve(int left, int right) {
	//기저 사례 : 판자가 하나만 있는경우
	if (left == right) return fence[left];

	//[left, mid], [mid+1, right]로 두 구간 분할
	int mid = (left + right) / 2; //나머지 탈락이므로 홀수이면 버림수

	//분할한 구간을 각개격파 case1,2
	int ret = max(solve(left, mid), solve(mid + 1, right));
	
	//두 부분에 모두 걸치는 사각형중 가장 큰것 찾기 case3
	int lo = mid, hi = mid + 1;
	//[left......lo,hi......right]
	int height = min(fence[lo], fence[hi]);
	//[mid, mid+1]만 포함하는 너비 2인 사각형 고려
	ret = max(ret, height * 2);

	//사각형이 입력 전체를 덮을 때 까지 확장
	//[left <<< lo...hi >>> right] 이렇게 진행
	while (left < lo || hi < right) { //lo, hi가 양 끝으로 갈 때 까지 모두 한번씩 반복
		//***항상 높이가 높은쪽으로 확장***
		if (hi < right && (lo == left || fence[lo-1] < fence[hi+1])) {//왼쪽으로 모두 옮겼거나 왼쪽 울타리가 낮을때 오른쪽 울타리가 남은 상황
			hi++;
			height = min(height, fence[hi]);
		}
		else {// 왼쪽이남고 왼쪽이 높을 때이거나 오른쪽으로 모두 옮겨봤을 때.
			lo--;
			height = min(height, fence[lo]);
		}
		ret = max(ret, height * (hi - lo + 1)); //확장 후 사각형 넓이
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