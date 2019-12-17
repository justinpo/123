#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class hashtable{
private:
	vector<string> table[1<<10];
	int size;
	int max;
	int type;
public:
	hashtable(int);
	~hashtable(){}
	unsigned int hash(int);
	int insert(string);
	int find(string);
	unsigned int hashcode1(string);
	unsigned long hashcode2(string);
};

int main(){
	ifstream file("stringhashwords.in");
	ofstream out("stringhashopen.out");
	int cases;
	file>>cases;
	for(int i=0; i<cases; i++){
		int words;
		file>>words;
		hashtable h1(1),h2(2);
		for(int j=0; j<words; j++){
			string word;
			file>>word;
			int count = h1.insert(word);
			h2.insert(word);
			out<<count<<" ";
		}
		string search;
		file>>search;
		out<<h1.find(search)<<" "<<h2.find(search)<<endl;
		cout<<search<<" "<<h1.find(search)<<" "<<h2.find(search)<<endl;				
	}	
	file.close();
	out.close();
}

hashtable::hashtable(int t){
	
	size = 0;
	max = 1<<10;
	type = t;
}

unsigned int hashtable::hashcode1(string st){
	int len = st.length();
	unsigned int h = 0;
	for(int i=0; i<len; i++){
		h = 31*h + st[i];
	}	
	return h;
}

unsigned long hashtable::hashcode2(string s){
    unsigned long   h = 0, high, i = 0;
    while ( s[i] !='\0'){
        h = ( h << 4 ) + s[i++];
        if ( high = (h & 0xF0000000) )
            h ^= high >> 24;
        h &= ~high;

    }
    return h;
}

unsigned int hashtable::hash(int x){
	unsigned int z = 60147, d=10, w=31;
	unsigned themod = 1 << w, thediv = 2 << (w - d);
	
	return (((z * x)%themod) >> (w - d));
}

int hashtable::insert(string x){
	int i;
	if(type == 1) 
		i = hash(hashcode1(x));
	else
		i = hash(hashcode2(x));
	
	table[i].push_back(x);
	size++;
	return table[i].size();
}

int hashtable::find(string x){
	int i,j,len;
	if(type == 1) 
		i = hash(hashcode1(x));
	else
		i = hash(hashcode2(x));
	len = table[i].size();
	for(j=0; j<len; j++){
		if(table[i][j].compare(x)==0)
			break;
	}
	return j+1;
}
/* 
578
578
580
577
578
579
576
579
579
468
*/