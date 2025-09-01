#include<iostream>
#include<vector>
using namespace std;
void swap(int& x,int& y){
	int temp=x;
	x=y;
	y=temp;
}
void partition(vector<int>& arr,int low,int high){
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
}
void QuickSort(vector<int>& arr){
	if(low<high){
		
	}
}