#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//auto start = chrono::high_resolution_clock::now();

	
	for(int i=1;i<7;i++)
	{
		string file="input_"+to_string((int)pow(10,i))+".txt";
		ofstream outFile(file);
		
		outFile<<(int)pow(10,i)<<endl;
		
		uniform_int_distribution<> dis(0,pow(10,i));
		for(int j=0;j<pow(10,i);j++)
			outFile<<dis(gen)<<' ';
		outFile<<endl;
		
		outFile.close();
	}
	
	//auto end = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	
    //cout<<"运行时间(μs)："<<duration.count()<<"***"<<endl;
	return 0;
}
 
