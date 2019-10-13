#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ofstream file("test.out");
	int x = 20;
	file<<"hello world!"<<endl;
	file<<x<<endl;
	file.close();
	return 0;
}