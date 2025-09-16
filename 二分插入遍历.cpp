#include<iostream>
#include<vector>
using namespace std;
int  binaryInsert(const vector<int>& arr,int target,int low,int high){
    int mid=low+(high-low)/2;
    if(arr[mid]==target){
        return mid;
    }
    while(low<high){
        if(arr[mid]<target){
            low=mid+1;
        }else{
            high=mid-1;
        }
    }
    return low;
}
void binaryInsertSort(vector<int>& arr,int n){
    for(int i=1;i<n;i++){
        int j=i-1;
        int key=arr[i];
        int mid=binaryInsert(arr,key,0,j);
        while(j>=mid){
            arr[j + 1] = arr[j];
            j--;
        }
        j++;
        arr[j]=key;

    }
}