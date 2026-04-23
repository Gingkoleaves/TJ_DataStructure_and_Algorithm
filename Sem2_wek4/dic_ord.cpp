#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream> 

using namespace std;

int my_next_permutation(vector<int>& arr)
{
	if(arr.size()==1)return -2;// 单个元素不存在下一个排序 
	
	int i=arr.size()-2;
	for(;i>=0;i--)
	{
		if(arr[i]>=arr[i+1])continue;
		break;
	}
	if(i==-1)return -1;//已经是最大排序 
	
	int j=arr.size()-1;
	for(;j>i;j--){
		if(arr[j]>arr[i])break;
	} 
	
	swap(arr[i],arr[j]);
	reverse(arr.begin()+i+1,arr.end());
	return 0;
 } 
 
 int factorial(int num1)
 {
 	if(num1<=1)return 1;
 	if(num1==2)return 2;
 	return factorial(num1-1)*num1;
 }
 
 int cal_dict_val(vector<int> v1)
 {
 	if(v1.size()<=1)return 0;
 	
 	if(v1.size()==2)return (v1[0]>v1[1])?1:0;
 	int len=v1.size();
 	
 	vector<int> next;
 	next.assign(v1.begin()+1,v1.end());
 	for(int i=0;i<next.size();i++)
 		if(next[i]>=v1[0])next[i]--;
 	
 	return (v1[0]-1)*factorial(len-1)+cal_dict_val(next);
 }
 
 int main()
 {
	ifstream inFile("input.txt");
	// 检查文件是否成功打开
    if (!inFile.is_open()) {
        cerr << "Failed to open file for reading!" << endl;
        return 1;
    }
    
 	vector<int> v1;
    
	int n;
	inFile>>n;
	for(int i=0;i<n;i++)
	{
		int elem;
		inFile>>elem;
		v1.push_back(elem);
	}
    // 关闭文件
    inFile.close();
 	
 	// 创建一个ofstream对象并打开文件
    ofstream outFile("output.txt");

    // 检查文件是否成功打开
    if (!outFile.is_open()) {
        cerr << "Failed to open file for writing!" << endl;
        return 1;
    }
 	
 	
 	outFile<<cal_dict_val(v1)<<endl;
 	if(!my_next_permutation(v1))
 		for(int i:v1)outFile<<i<<" ";
 	
 	outFile.close();
 	return 0;
 }
