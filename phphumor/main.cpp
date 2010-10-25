#include "Humor.h"
#include <iostream>
#include <vector>

using namespace std;
int main() {
	string input;
	cin>>input;
	Humor h;
	vector<string> ret = h.getSyns(input);
	for(int i=0; i<ret.size() ;++i) {
		cout<<ret[i]<<" ";
	}
	cout<<std::endl;

	return 0;
}
