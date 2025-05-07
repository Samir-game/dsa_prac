#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
    int freq;
    char data;
    Node *left,*right;
    Node(char c,int f){
        data=c;
        freq=f;
        left=right=NULL;
    }
};

class compare{
    public:
    bool operator()(Node *a,Node *b){
        return a->freq > b->freq;
    }
};

void print(Node *root,string ans){
    if(!root) return;
    
    if(root->data!='$'){
        cout<<"data: "<<root->data<<" freq: "<<root->freq<<" code: "<<ans<<endl;
    }
    print(root->left,ans+'0');
    print(root->right,ans+'1');
}

void huffman(char c[], int freq[], int size){
    priority_queue<Node*,vector<Node*>,compare>pq;
    for(int i=0;i<size;i++){
        Node *temp=new Node(c[i],freq[i]);
        pq.push(temp);
    }

    while(pq.size()>1){
        Node *first=pq.top();
        pq.pop();
        Node *second=pq.top();
        pq.pop();

        Node *newnode=new Node('$',first->freq+second->freq);
        pq.push(newnode);
        newnode->left=first;
        newnode->right=second;
    }
    print(pq.top(),"");

}

int main(){
    char c[6] = {'e', 'h', 'q', 'j', 'n', 'k'};
    int freq[6] = {5, 7, 9, 21, 65, 7};
    

    huffman(c, freq, 6);
    return 0;
}