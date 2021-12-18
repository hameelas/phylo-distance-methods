#include "testlib.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <cstdio>

using namespace std;

#define Foreach(i, c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))
#define rof(i,a,b) for(int (i)=(a);(i) > (b); --(i))
#define rep(i, c) for(auto &(i) : (c))
#define x first
#define y second
#define pb push_back
#define PB pop_back()
#define iOS ios_base::sync_with_stdio(false)
#define sqr(a) (((a) * (a)))
#define all(a) a.begin() , a.end()
#define error(x) cerr << #x << " = " << (x) <<endl
#define Error(a,b) cerr<<"( "<<#a<<" , "<<#b<<" ) = ( "<<(a)<<" , "<<(b)<<" )\n";
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x) ((x)<<1)
#define R(x) (((x)<<1)+1)
#define umap unordered_map
#define double long double
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
template <class T>  inline void smax(T &x,T y){ x = max((x), (y));}
template <class T>  inline void smin(T &x,T y){ x = min((x), (y));}
const int maxn = 10000 + 10;
double dis[maxn][maxn];
const double eps = 1e-8;

int main() {
    registerValidation();
	int n = inf.readInt(3, 10000, "n");
	inf.readEoln();
	For(i,0,n) {
		string label = inf.readToken();
		For(j,0,n) {
			inf.readSpace();
			dis[i][j] = inf.readDouble();
			if (i == j) {
				ensuref(abs(dis[i][j]) < eps, 
						"Invalid self-distance, i.e., D[i][i] != 0");
			}
		}
		inf.readEoln();
	}
	For(i,0,n) {
		For(j,0,i) {
			ensuref(abs(dis[i][j] - dis[j][i]) < eps, 
					"The input matrix is not symmetric, i.e., D[i][j] != D[j][i]");
		}
	}
	inf.readEof();
	return 0;
}
