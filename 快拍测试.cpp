#include<iostream>
#include<vector>
using namespace std;
void swap(int &x,int &y){
    int temp;
    temp=x;
    x=y;
    y=temp;
}
int Quick(vector<int>&arr,int low,int high){
    int key=arr[low];
    int *ptr=&arr[low];
    low++;
    while(true){
        while(arr[low]<key){
            low++;
        }
        while(arr[high]>key){
            high--;
        }
        if(low>high){
            break;
        }
        swap(arr[low],arr[high]);
        low++;
        high--;
    }
    swap(arr[high],*ptr);
    return high;
}
void MergeSort(vector<int> &arr,int low,int high){
    if(low<high){
        int mid=Quick(arr,low,high);
        MergeSort(arr,low,mid-1);
        MergeSort(arr,mid+1,high);
    }
}