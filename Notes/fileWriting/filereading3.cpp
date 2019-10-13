#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream file("filereading3.in");

	if(file.is_open()){
		string lines;
		while(getline(file,lines)){
			cout<<"line: "<<lines<<endl;
		}
		file.close();
	}
	return 0;
}