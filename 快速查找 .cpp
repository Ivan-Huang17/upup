#include<iostream>
#include<vector>
using namespace std;
void swap(int& x,int& y){
	int temp=x;
	x=y;
	y=temp;
}
int partition(vector<int>& arr,int low,int high){
	int i=low,j=high;
	int temp=arr[low];
	while(i<j){
		while(j>i&&arr[j]<=temp)
		{
			j--;
		}arr[i]=arr[j];
		while(i<j&&arr[i>=temp])
		{
			i--;
		}
		arr[j]=arr[i];

		
	}
	arr[i]=temp;
	return i;
	
}
void QuickSort(vector<int>& arr,int low,int,high){
	int address;
	if(low<high){
		int address=partition(arr,low,high);
		QuickSort(arr,low,address-1);
		QuickSort(arr,address,high+1);

	}
}
int main(){
	vector<int> nums={5,2,3,1};
	QuickSort(arr,0,nums.size());
	cout<<"排序后的数组是："；
	for(int i=0;i<nums.size());
	{
		cout<<nums[i]<<",";

	}
	return 0;
}