#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

const int MAX_SIZE = 100;

//char decompressed[MAX_SIZE][MAX_SIZE];


//������ �� Ǯ���ʰ� ������
//���ʿ��� ���� ������ ������ ������ �����鼭 ��ġ�� ������
string reverse(string::iterator& it) {
	char head = *it; //head�� ���� it��
	++it; //it�� ������ ����Ŵ

	//w,b�� ������ �״�� ������ //reverse �ϱ� ����
	if (head == 'w' || head == 'b') {
		return string(1, head);
	}

	//��� �ܰ�
	//�� 2�� ��и�
	string upperLeft = reverse(it); //2��и�
	string upperRight = reverse(it);//1��и�
	//�Ʒ� 2�� ��и�
	string lowerLeft = reverse(it); //3��и�
	string lowerRight = reverse(it);//4��и�

	//���� x�� ������ lower�� upper�� char�� �ݴ�� �ξ� reverse
	return string("x") + lowerLeft + lowerRight //3, 4��и��� ����
		               + upperLeft + upperRight;//2, 1��и��� �Ʒ��� �Ͽ� x�ڿ� �ٿ� ����;
}

/*
//��� ���� Ǯ��
//�ݺ���, ���� y��ǥ, ���� x��ǥ, ����� ������
void decompress(string::iterator& it, int y, int x, int size) {
	//�ѱ��� �˻�� �ݺ��ڸ� ��ĭ������ �ű�
	char head = *(it++); //it�� ������ ��� �ݺ��� ��� ++�Ȱ��� ����
	//�������: ù���ڰ� b�Ǵ� w�ΰ��
	if (head == 'b' || head == 'w') {
		for (int dy = 0; dy < size; dy++) {
			for (int dx = 0; dx < size; dx++) {
				decompressed[y + dy][x + dx] = head;
			}
		}
	}
	else { //ù���ڰ� x�ΰ��
		int half = size / 2;
		decompress(it, y, x, half); //2��и� 
		decompress(it, y, x + half, half); //1��и�
		decompress(it, y + half, x, half); //3��и�
		decompress(it, y + half, x + half, half); //4��и�
	}
}
*/

int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		string s;
		cin >> s;
		string::iterator it = s.begin();
		cout << reverse(it) << endl;
	}
}