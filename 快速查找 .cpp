#include<iostream>
#include<vector>
using namespace std;
void swap(int& x,int& y){
	int temp=x;
	x=y;
	y=temp;
}
int partition(vector<int>& arr,int low,int high){
	int temp=arr[low];
	while(low<high){
		while(arr[high]>temp){
			high--;
		}
		swap(arr[high],arr[low]);
		while(arr[low]<temp){
			low++;
			
		}
		swap(arr[low],arr[high])
	}
	arr[low]=temp;
	return low;
}
void QuickSort(vector<int>& arr,int low,int,high){
	if(low<high){
		int address=partition(arr,low,high);
		QuickSort(arr,low,address);
		QuickSort(arr,address,high);

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