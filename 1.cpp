#include<iostream>
#include<vector>
using namespace std;
int BinarySearch(vector<int>& arr,int target,int low,int high){
	while(low<high){
		int mid = low+(low+high)/2;
		if(target == arr[mid])
		{
			return mid;
		}
		else if(target < arr[mid])
		{
			high=mid-1;
		}
		else
		{
			low=mid+1;
		}
	
	}
	return low;
}
void insertionSortwithBinary(vector<int>& arr){
	for(int i=1;i<arr.size();i++){
		int key=arr[i];
		int j=i-1;
		int address=BinarySearch(arr,key,j,i);
		while(j<=address){
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=key;
	}
}
int main(){
	vector<int> nums1={5,2,3,1};
	vector<int> nums2={5,1,1,2,0,0};
	insertionSortwithBinary(nums1);
	insertionSortwithBinary(nums2);
	cout<<"排序后的数组为";
	for(int i=0;i<nums1.size();i++)
	{
		cout<<nums1[i]<<",";
	 } 
	cout<<"/n";
	for(int i=0;i<nums2.size();i++)
	{
		cout<<nums2[i]<<",";
	 } 
	 return 0;
}