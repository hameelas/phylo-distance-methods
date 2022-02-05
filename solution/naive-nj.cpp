#include <iostream>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

const int MAX_N = 2000;
const double INF = 1e18;

typedef pair<int, int> node_pair;

int n;
double d[2 * MAX_N][2 * MAX_N], rowsum[2 * MAX_N];
string labels[2 * MAX_N];
bool active[2 * MAX_N];
vector <pair<int, double> > g[MAX_N];

node_pair normalize(node_pair join_pair) {
	if (join_pair.first > join_pair.second) {
		swap(join_pair.first, join_pair.second);
	}
	return join_pair;
}

double calc_cost(int nn, int i, int j) {
	//cerr << nn << ' ' << labels[i] << " -> " << labels[j] << ' ' << d[i][j] << ' ' << rowsum[i] << ' ' << rowsum[j] << ' ' << (nn - 2) * d[i][j] - rowsum[i] - rowsum[j] << endl;
	return (nn - 2) * d[i][j] - rowsum[i] - rowsum[j]; 
}

void initialize() {
	cin >> n;
	for (int i = n; i < 2 * n; i++) {
		stringstream ss; ss << i + 100;
		string x; ss >> x;
		labels[i] = x;
	}
	for (int i = 0; i < n; i++) {
		active[i] = true;
		cin >> labels[i];
		for (int j = 0; j < n; j++) {
			cin >> d[i][j];
			rowsum[i] += d[i][j];
		}
	}
}

pair<int, int> find_min_coor_naive(int nn) {
	int min_cost = INF;
	node_pair min_coor;
	
	for (int x = 0; x < 2 * n; x++) if (active[x]) {
		for (int y = 0; y < x; y++) if (active[y]) {
			double cost = calc_cost(nn, x, y);
			if (nn == 4) {
				//cerr << x << ' ' << y << ' ' << cost << ' ' << d[x][y] << endl;
			}
			if (min_cost > cost) {
				min_cost = cost;
				min_coor = make_pair(y, x);
			}
		}
	}
	//cerr << min_cost << ' ' << INF << ' ' << min_coor.first << ' ' << min_coor.second << endl;
	return min_coor;
}

void join_nodes(int nn, int x, int y, int z) {
	double min_cost = INF;

	active[x] = active[y] = false;
	active[z] = true;

	for (int k = 0; k < 2 * n; k++) if (active[k] && k != z) {
		d[z][k] = d[k][z] = (d[k][x] + d[k][y] - d[x][y]) / 2.0;
	}

	for (int k = 0; k < 2 * n; k++) if (active[k] && k != z) {
		rowsum[z] += d[z][k];
		rowsum[k] += d[k][z] - d[k][x] - d[k][y];
		//rowsum[k] -= (d[z][x] + d[z][y] + d[x][y]) / 2;
	}
	
	g[z].push_back(make_pair(x, d[x][y] / 2 + (rowsum[x] - rowsum[y]) / (2 * (nn - 2))));
	g[z].push_back(make_pair(y, d[x][y] - g[z].back().second));
}

string newick = "";
void find_newick (int v) {
	int children = (int)g[v].size();
	if (children == 0) {
		newick += labels[v];
		return;
	}
	newick += "(";
	for (int i = 0; i < children; i++) {
		find_newick (g[v][i].first);
		stringstream ss; ss << g[v][i].second;
		string length; ss >> length;
		newick += ":" + length;
		if (i < children - 1) {
			newick += ",";
		}
	}
	newick += ")";
}

string active_string() {
	string res (3 * n, ' ');
	for (int i = 0; i < 2 * n; i++) {
		res[i + i/5] = active[i] ? '1' : '0';
	}
	return res;
}

int main() {
	initialize();
	
	int next_node = n;
	for (int x = n; x > 3; x--) {
		pair<int, int> join_pair = find_min_coor_naive(x);
		//cerr << x << "/" << n << ' ' << labels[join_pair.first] << '=' << labels[join_pair.second] << 
		//	' ' << next_node << '\t' << active_string() << endl << endl;
		join_nodes (x, join_pair.first, join_pair.second, next_node);
		next_node++;
	}
	
	for (int i = 0; i < 2 * n; i++) if (active[i]) {
		g[next_node].push_back(make_pair(i, 0));
	}
	double sum = 0;
	//cerr << (int)g[next_node].size() << endl;
	assert((int)g[next_node].size() == 3);
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < x; y++) {
			int X = g[next_node][x].first;
			int Y = g[next_node][y].first;
			sum += d[X][Y];
		}
	}
	for (int i = 0; i < 3; i++) {
		double others_dis = d[g[next_node][(i + 1) % 3].first][g[next_node][(i + 2) % 3].first];
		g[next_node][i].second = (sum - 2.0 * others_dis) / 2.0; 
	}

	find_newick(next_node);
	cout << newick << endl;

	return 0;
}
