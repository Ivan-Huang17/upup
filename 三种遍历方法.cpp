#include<iostream>
#include<stack>
using namespace std;
struct BTNode{
    int val;
    BTNode* left;
    BTNode* right;
};
void PreOrder(BTNode* root){
    if(root!=nullptr){
        cout<<root->val<<",";
        PreOrder(root->left);
        PreOrder(root->right);
    }
}
void InOrder(BTNode* root){
    if(root!=nullptr){
        InOrder(root->left);
        cout<<root->val<<",";
        InOrder(root->right);
    }
}
void PostOrder(BTNode* root){
    if(root!=nullptr){
        PostOrder(root->left);
        PostOrder(root->right);
        cout<<root->val<<",";
    }
}