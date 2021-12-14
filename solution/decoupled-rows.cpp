#include <iostream>

using namespace std;

const int MAX_N = 2000;
const int K = 50;
const int INF = 1e9;

int n, d[2 * MAX_N][2 * MAX_N];

typedef pair<int, int> node;
#define COST first
#define COL second

class crossing_lines {
	int n;
	int *mem;

public:
	void init(int n, vector <node> nodes) {
		this->n = n;
		for (int i = 0; i < n; i++) {
			this->mem[2 * i] = nodes[i].COST;
			this->mem[2 * i + 1] = nodes[i].COL;
		}
		this->mem = nodes;
		sort(mem, mem + 2 * n);
		for (int i = 0; i < n; i++) {
			
		}
	}
}

class row {
	crossing_lines L[4 * MAX_N];
	bool active = false;
	int time = 0;
	matrix *parent;

public:
	row(matrix *par) {
		this->parent = par;
		this->time = 0;
	}

	bool isActive() {
		return this->active;
	}

	void setActive(bool val) {
		this->active = val;
	}

	void refresh() {
	}

	void tik_tok() {
		if (this->time % K == 0) {
			this->refresh();
		}
		this->time++;
	}

	node get_min_tree(int x, int s, int e, int l, int r) {
		if (r <= s || e <= l) {
			return INF;
		}
		if (l <= e && s <= r) {
			return this->L[x].get_min(time);
		}
		
		node left = this->get_min_tree (2 * x, s, MID(s, e), l, r);
		node right = this->get_min_tree (2 * x + 1, MID(s, e), e, l, r);
		return min (left, right);
	}

	node get_min() {
		node best = make_pair(INF, -1);
		for (obstacle : 
	}
} rows[2 * MAX_N];

void initialize() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		rows[i].setActive(true);
		for (int j = 0; j < n; j++) {
			cin >> d[i][j];
		}
	}
}

pair<int, int> find_min_coor() {
	int min_dis = INF;
	pair<int, int> min_coor;
	for (int i = 0; i < 2 * n; i++) {
		if (rows[i].isActive()) {
			rows[i].tik_tok();
			node min_row_dis = rows[i].get_min();
			if (min_row_dis.COST < min_dis) {
				min_dis = min_row_dis.COST;
				min_coor = make_pair(i, min_row_dis.COL);
			}
		}
	}
	return min_coor;
}

void join_nodes(int x, int y) {
	rows[x].setActive(false);
	rows[y].setActive(false);
}

int main() {
	initialize();
	
	for (int x = n; x > 1; x--) {
		pair<int, int> join_pair = find_min_coor();
		join_nodes (join_pair.first, join_pair.second);
	}

	return 0;
}
