#include<iostream>
#include<vector>
using namespace std;
void Merge( vector<int>& arr,int left,int mid,int right){
    int n1=mid-left+1;
    int n2=right-mid;
    vector<int> LeftArr(n1);
    vector<int> RightArr(n2);
    for(int i=0;i<n1;i++){
        LeftArr[i]=arr[left+i];
    }
    for(int i=0;i<n2;i++){
        RightArr[i]=arr[mid+i+1];
    }
    int i=0;
    int j=0;
    while(i<n1&&j<n2){
        if(LeftArr[i]>RightArr[j]){
            arr[left]=LeftArr[i++];
            left++;
        }else{
            arr[left]=RightArr[j++];
            left++;
        }
    }
    if(i<n1){
        arr[left]=LeftArr[i];
        i++;
        left++;
    }
    if(j<n2){
        arr[left]=RightArr[j];
        j++;
        left++;
    }
}
void MergeSort(vector<int> &arr,int left,int right){
    if(left<right){
        int mid=left+(right-left);
        MergeSort(arr,left,mid);
        MergeSort(arr,mid+1,right);
        Merge(arr,left,mid,right);

    }

}