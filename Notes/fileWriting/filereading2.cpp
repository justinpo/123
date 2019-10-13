#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream file("filereading2.in");

	if(file.is_open()){
		int cases;
		file>>cases;
		while(cases>0){
			int num;
			string st;
			file>>num>>st;
			cout<<"num: "<<num<<" st: "<<st<<endl;
			cases--;
		}
		file.close();
	}
	return 0;
}