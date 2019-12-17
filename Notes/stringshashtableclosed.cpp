#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class hashtable{
private:
	string table[1<<10];
	int size;
	int max;
public:
	hashtable();
	~hashtable(){}
	unsigned int hash(int);
	int insert(string);
	int find(string);
	unsigned int hashcode1(string);
	unsigned long hashcode2(string);
};

int main(){
	ifstream file("stringhashwords.in");
	ofstream out("stringhashclosed.out");
	int cases;
	file>>cases;
	for(int i=0; i<cases; i++){
		int words;
		file>>words;
		hashtable h;
		for(int j=0; j<words; j++){
			string word;
			file>>word;
			out<<h.insert(word)<<" ";					
		}
		string search;
		file>>search;
		out<<h.find(search)<<endl;				
	}			
	file.close();
	out.close();
}

hashtable::hashtable(){
	srand((unsigned int)time(NULL));
	size = 0;
	max = 1<<10;
	for(int i=0; i<max; i++)
		table[i] = "-1";
	
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
        if ( high = h & 0xF0000000 )
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
	int i = hashcode2(x);
	i = hash(i);
	int collisions = 0;

	while(table[i].compare("-1")!=0){
		i = (i + 1)%max;
		collisions++;
	}
	table[i] = x;
	size++;
	return collisions;
}

int hashtable::find(string x){
	int i = hash(hashcode2(x));
	int collisions = 0;

	while(table[i].compare("-1")!=0){
		if(table[i].compare(x)==0)
			break;
		i = (i + 1)%max;
		collisions++;
	}
	return collisions;
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