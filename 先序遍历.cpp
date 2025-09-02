#include<iostream>
#include<vector>
#include<stack>
using namespace std;
struct ListNode{
    int val;
    ListNode* left;
    ListNode* right;
};
void PreorderTraversal(ListNode* root){
    stack<ListNode*> arr;
    ListNode* ptr;
    if(root==nullptr){
        return ;
    }
    arr.push(root);
    if(root->left!=nullptr){
        arr.push(root->left);
       // ptr++;
        PreorderTraversal(root->left);
        cout<<root->left->val;
    }
    cout<<root->val;
    if(root->right!=nullptr){
        arr.push(root->right);
        PreorderTraversal(root->right);
        cout<<root->right->val;
        //ptr++;
    }
    arr.pop();
    ptr=arr.top();
    PreorderTraversal(ptr);
}