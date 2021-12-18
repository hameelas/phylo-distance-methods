#include "testlib.h"
#include <vector>
using namespace std;

static string output_secret = "lxndanfdiadsfnslkj_output_phylo_faifnbsidjvnsidjbgsidjgbs";
vector<int> ANS, RES; 
int main(int argc, char * argv[])
{
	registerChecker("phylo", argc, argv);

	ouf.readSecret(output_secret);
	ouf.readGraderResult();

	inf.readLine();

	string found_tree = inf.readLine();
	string og_tree = ouf.readLine();

    ouf.readEof();
    inf.readEof();

    if (found_tree != og_tree)
		quitf(_fail, "wrong tree");

	quitf(_ok, "correct");
}
