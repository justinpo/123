#include <bitset>
#include <iostream>

using namespace std;

int main(){
	bitset<8> bits1;
	bitset<16> bits2(39);
	bitset<16> bits3("0110110010010010");

	cout<<"bits1: "<<bits1<<endl;
	cout<<"bits2: "<<bits2<<endl;
	cout<<"bits3: "<<bits3<<endl;

	return 0;
}