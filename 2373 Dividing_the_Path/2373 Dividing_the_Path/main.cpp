#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<math.h>

using namespace std;

struct Fx {
	int pos, value;
	Fx() { this->pos = -1; this->value = -1; }
	Fx(int p, int v) :pos(p), value(v) {}
	bool operator<(const Fx& a) const {
		return value > a.value;
	}
};

const int MAXN = 1001, MAXL = 1000001;
const int MAX = 0x3f3f3f3f;
int N, L;
int A, B;
int F[MAXL];
int cows[MAXL];
priority_queue<Fx> pq;

int main() {
	cin >> N >> L;
	cin >> A >> B;
	A <<= 1; B <<= 1; // <<= not << !!
	memset(cows, 0, sizeof(cows));
	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;
		cows[a + 1]++;
		cows[b]--;
	}
	int cnt = 0;
	for (int i = 0; i <= L; i++) {
		F[i] = MAX;
		cnt += cows[i];
		cows[i] = cnt > 0;
	}
	//init the priority_queue.
	for (int i = A; i <= B; i+=2) {
		if (!cows[i]) {
			F[i] = 1;
			if (i <= B + 2 - A)
				pq.push(Fx(i, F[i]));
		}
	}
	//
	for (int i = B + 2; i <= L; i += 2) {
		if (!cows[i]) {
			Fx tmp;
			while (!pq.empty()) {
				tmp = pq.top(); //already assigned !!
				if (tmp.pos < i - B)
					pq.pop();
				else
					break;
			}
			//update the F.
			if(!pq.empty()) //note the limitation here!.
				F[i] = tmp.value + 1;
		}
		//update the priority_queue.
		if (F[i + 2 - A] != MAX)
			pq.push(Fx(i + 2 - A, F[i + 2 - A]));
	}
	////debug
	//for (int i = 0; i <= L; i++)
	//	cout << cows[i] << " ";
	//cout << endl;
	//for (int i = 0; i <= L; i++)
	//	cout << F[i] << " ";
	//cout << endl;
	if (F[L] == MAX)
		cout << -1 << endl;
	else
		cout << F[L] << endl;
	system("pause");
}