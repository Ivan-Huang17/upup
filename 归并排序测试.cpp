#include<iostream>
#include<vector>
using namespace std;
void Merge(const vector<int>& arr,int left,int mid,int right){
    int leftlength=mid-left+1;
    int rightlength=right-mid;
    vector<int> left(leftlength);
    vector<int> right[rightlength];
    for(int i=0;i<leftlength;i++){
        left[i]=arr[left+i];
    }
    
    while(i<rightlength){
        right[i]=arr[i+mid+1];
        i++;
    }
}