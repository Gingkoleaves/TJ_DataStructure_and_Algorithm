#include <iostream>
#include <fstream>

using namespace std;

void dc_hanoi(int n,char from,char mid,char end,ofstream& outfile)
{
	if(n==1){
		outfile<<1<<" "<<from<<" "<<end<<endl;
		return;
	}
	
	dc_hanoi(n-1,from,end,mid,outfile);
	outfile<<n<<" "<<from<<" "<<end<<endl;
	dc_hanoi(n-1,mid,from,end,outfile);
}

int main()
{
	ifstream inFile("input.txt");
	// 检查文件是否成功打开
    if (!inFile.is_open()) {
        cerr << "Failed to open file for reading!" << endl;
        return 1;
    }
    
	int n; 	
    inFile>>n;
    
	// 关闭文件
    inFile.close();
 	
 	// 创建一个ofstream对象并打开文件
    ofstream outFile("output.txt");

    // 检查文件是否成功打开
    if (!outFile.is_open()) {
        cerr << "Failed to open file for writing!" << endl;
        return 1;
    }
        
	dc_hanoi(n,'A','C','B',outFile);
    
    outFile.close();    
	return 0;
}




