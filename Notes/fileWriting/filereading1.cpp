#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream file("filereading1.in");

	if(file.is_open()){
		int cases;
		file>>cases;
		while(cases>0){
			int num1, num2;
			file>>num1>>num2;
			cout<<"num1: "<<num1<<" num2: "<<num2<<endl;
			cases--;
		}
		file.close();
	}
	return 0;
}