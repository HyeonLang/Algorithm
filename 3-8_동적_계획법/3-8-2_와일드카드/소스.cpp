#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//-1:�Է���, 0:�����ȵ�(false), 1:������(true)
int cache[101][101]; //���� ��ġ�� �������θ� ����
string W, S;

void cacheInit(int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cache[i][j] = -1;
}

/*
bool match(const string& w, const string& s) {
	int pos = 0;
	//w[pos]�� s[pos]�� ���糪����.
	while (pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos])) {
		//pos�� w,s�� ���̺��� �����鼭 w�� ?�̰ų� w=s�� ��� �������� ��Ī
		pos++;
	}
	//���̻� ������ �Ұ����ϸ� �� while�� �������� Ȯ��
	//2.���� ���� �����ؼ� ������� : ���ڿ��� ������� ������.
	if (pos == w.size())
		return (pos == s.size()); //bool�� pos == s.size�ΰ�� true ����

	//4.*�� ������ ������� : *�� ����ڸ� �����ؾ����� ���ȣ��
	if (w[pos] == '*') {
		//pos+skip == s.size()�� ��� w�� *�� s�� ������ ������
		for (int skip = 0; pos + skip <= s.size(); skip++) {
			//w�� *�������ں��Ϳ� s�� *������ ��ŵ���� ���� �������͸� ��Ī
			if (match(w.substr(pos + 1), s.substr(pos + skip))) { 
				return true; //����Լ��� ��� true�̸� ture��� ����
						     //�ϳ��� false�� false��� ���� (���� �ڵ�� ����)
			}
		}
	}
	return false;
}
*/

/*
//O(n^3)�ý���
bool matchMemoized(int w, int s) { //W�� S�� ������ġ ���� 
	//�޸������̼�
	int& ret = cache[w][s]; //***�߿�***���������� �޾� ������ ����.
	if (ret != -1) return ret; //�̹� ����� �ߺ��� ����

	//W[w]�� S[s]�� ���糪����,
	while (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])) {
		//pos�� w,s�� ���̺��� �����鼭 w�� ?�̰ų� w=s�� ��� �������� ��Ī
		w++;
		s++;
	}
	//���̻� ������ �Ұ����ϸ� �� while�� �������� Ȯ��
	//2.���� ���� �����ؼ� ������� : ���ڿ��� ������� ������.
	if (w == W.size())
		return ret = (s == S.size()); //bool �� 0or1�� cache�� int�� ����

	//4.*�� ������ ���� ��� : *�� ����ڰ� �����Ǿ� ��ŵ���� ���ȣ���Ͽ� Ȯ��
	if (W[w] == '*') {
		for (int skip = 0; skip + s <= S.size(); skip++) {
			//w, s�� ���� ������ġ�� ���ڷ��Ͽ� ���ȣ��
			if (matchMemoized(w + 1, s + skip)) {
				//����Լ��� ��� true�̸� ture��� ����
				//�ϳ��� false�� false��� ���� (���� �ڵ�� ����)
				return ret = 1; //true(1) ���� + cache�� ����
			}
		}
	}
	return ret = 0; //false(0) ���� + cache�� ����
}

*/
//O(n^2)�ý��� : for���� ���ȣ��� �ٲپ� �޸������̼��ϴ� ������ �ø���.
bool matchMemoized2(int w, int s) { //W�� S�� ������ġ ���� 
	//�޸������̼�
	int& ret = cache[w][s]; //***�߿�***���������� �޾� ������ ����.
	if (ret != -1) return ret; //�̹� ����� �ߺ��� ����

	//W[w]�� S[s]�� ���糪����,
	if (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])) {
		//pos�� w,s�� ���̺��� �����鼭 w�� ?�̰ų� w=s�� ��� ���� ������ġ�� ���ȣ��
		return ret = matchMemoized2(w + 1, s + 1);
	}
	//���̻� ������ �Ұ����ϸ� �� while�� �������� Ȯ��
	//2.���� ���� �����ؼ� ������� : ���ڿ��� ������� ������.
	if (w == W.size())
		return ret = (s == S.size()); //bool �� 0or1�� cache�� int�� ����

	//4.*�� ������ ���� ��� : *�� ����ڰ� �����Ǿ� ��ŵ���� ���ȣ���Ͽ� Ȯ��
	if (W[w] == '*') {
		if (matchMemoized2(w + 1, s) || (s < S.size() && matchMemoized2(w, s + 1))) {
			//1.*�� 0���ڸ� �������� ��ŵ�ϴ°�� or 2.*�� 1���ڸ� ���Խ��� ��ŵ�ϴ� ���
			//2���� �ݺ��Ǹ� �������ڸ� ���Խ��� ��ŵ�ϴ� ��찡 �ȴ�.
			return ret = 1; //true(1)���� + cache�� ����
		}
	}
	return ret = 0; //false(0) ���� + cache�� ����
}

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		string w;
		cin >> w;
		W = w;
		int n;
		cin >> n;
		vector<string> solve;
		for (int j = 0; j < n; j++) {
			//memset(cache, -1, sizeof(cache));
			cacheInit(101);
			string filename;
			cin >> filename;
			S = filename;
			if (matchMemoized2(0, 0) == true) {
				solve.push_back(filename);
			}
		}
		sort(begin(solve), end(solve));
		for (int k = 0; k < solve.size(); k++) {
			cout << solve[k] << endl;
		}
	}
}