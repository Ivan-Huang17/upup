#include<iostream>
#include<vector>
using namespace std;
void merge(vector<int>& arr,int low,int mid,int high){
    int n1=mid-low+1;
    int n2=high-mid;
    vector<int> arr1(n1);
    vector<int> arr2(n2);
    for(int i=0;i<mid;i++){
        arr1[i]=arr[i];
    }
    for(int i=0;i<high-mid;i++){
        arr2[i]=arr[i+mid];
    }
    int i=0,j=0,k=low;
    while(i<n1&&j<n2){
        if(arr1[i]<=arr[j])
        {
            arr[k]=arr1[i];
            i++;
        }else
        {
            arr[k]=arr2[j];
        }
    }
    while (i < n1) {
        arr[k] = arr1[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = arr2[j];
        j++;
        k++;
    }

}
void MergeSort(vector<int>& arr,int low,int high){
    if(low<high){
        int mid=low+(low+high)/2;
        MergeSort(arr,low,mid);
        MergeSort(arr,mid+1,high);
        merge(arr,low,mid,high);
    }

}
int main()
{
    vector<int> nums={5,2,3,1};
    MergeSort(nums,0,3);
    cout<<"排序后的数组为：";
    for(int i=0;i<3;i++){
        cout<<nums[i]<<",";
    }
    return 0;
}