#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node *left,*right;
    Node(int val){
        data=val;
        left=right=NULL;
    }
};

Node *insert(Node *root,int x){
    if(!root){
        Node *temp=new Node(x);
        return temp;
    }
    if(x<=root->data){
        root->left=insert(root->left,x);
    }
    else{
        root->right=insert(root->right,x);
    }
    return root;
}

bool search(Node *root,int x){
    if(!root) return false;
    if(x<root->data){
        return search(root->left,x);
    }
    else if(x>root->data){
        return search(root->right,x);
    }
    else{
        return true;
    }
    return false;
}

Node *clone(Node *root){
    if(!root) return NULL;
    Node *clonenode=new Node(root->data);
    clonenode->left=clone(root->left);
    clonenode->right=clone(root->right);
    return clonenode;
}

Node *mirror(Node *root){
    if(!root) return NULL;
    Node *mirrornode=new Node(root->data);
    mirrornode->left=mirror(root->right);
    mirrornode->right=mirror(root->left);
    return mirrornode;
}

int height(Node *root){
    if(!root) return 0;
    int leftst=height(root->left);
    int rightst=height(root->right);
    return (1+ max(leftst,rightst));
}

Node *deleteBT(Node *root,int x){
    if(!root) return NULL;
    if(x<root->data){
        root->left=deleteBT(root->left,x);
    }
    else if(x>root->data){
        root->right=deleteBT(root->right,x);
    }
    else{
        if(root->left==NULL){
            Node *temp=root->right;
            delete root;
            return temp;
        }
        if(root->right==NULL){
            Node *temp=root->left;
            delete root;
            return temp;
        }
        if(root->left!=NULL && root->right!=NULL){
            Node *succ=root->right;
            while(succ && succ->left){
                succ=succ->left;
            }
            root->data=succ->data;
            root->right=deleteBT(root->right,succ->data);
        }
    }
}
int prePos = 0;                  // global index in preorder[]
Node* build(int inorder[], int preorder[], int inStart, int inEnd)
{
    if (inStart > inEnd) return nullptr;

    int rootVal = preorder[prePos++];      // next root comes from preorder
    Node* root = new Node(rootVal);

    if (inStart == inEnd) return root;     // leaf node

    // find rootVal inside the inorder slice
    int split = inStart;
    while (inorder[split] != rootVal) ++split;

    root->left  = build(inorder, preorder, inStart, split - 1);
    root->right = build(inorder, preorder, split + 1, inEnd);
    return root;
}

bool checkequal(Node *root1,Node *root2){
    if(root1==NULL && root2==NULL) return true;
    if(root1==NULL || root2==NULL || root1->data !=root2->data) return false;
    return (checkequal(root1->left,root2->left) && checkequal(root1->right,root2->right));
}


void preorderI(Node *root){
    if(!root) return;
    stack<Node *>s;
    s.push(root);
    while(!s.empty()){
        Node *curr=s.top();
        s.pop();
        cout<<curr->data<<" ";
        if(curr->right){
            s.push(curr->right);
        }
        if(curr->left){
            s.push(curr->left);
        }
    }
}

void inorderI(Node *root){
    if(!root) return;
    stack<Node *>s;
    Node *curr=root;
    while(curr!=NULL || !s.empty()){
        while(curr!=NULL){
            s.push(curr);
            curr=curr->left;
        }
        curr=s.top();
        s.pop();
        cout<<curr->data<<" ";
        curr=curr->right; 
    }
}

void postorderI(Node *root){
    if(!root) return;
    stack <Node*>s1,s2;
    s1.push(root);

    while(!s1.empty()){
        Node *curr=s1.top();
        s1.pop();
        s2.push(curr);
        if(curr->left){
            s1.push(curr->left);
        }
        if(curr->right){
            s1.push(curr->right);
        }
    }
    while(!s2.empty()){
        Node *curr=s2.top();
        s2.pop();
        cout<<curr->data<<" ";
    }
}

void preorderR(Node *root){
    if(!root) return ;
    cout<<root->data<<" ";
    preorderR(root->left);
    preorderR(root->right);
}
void inorderR(Node *root){
    if(!root) return ;
    inorderR(root->left);
    cout<<root->data<<" ";
    inorderR(root->right);
}
void postorderR(Node *root){
    if(!root) return ;
    postorderR(root->left);
    postorderR(root->right);
    cout<<root->data<<" ";
}

int main(){

    int arr[7]={5,2,4,8,3,6,1};
    Node *root=NULL;
    
    for(int i=0;i<7;i++){
        root=insert(root,arr[i]);
    }

    cout<<"----------------iterative-------\n";
    cout<<"preorder: ";
    preorderI(root);
    cout<<endl;
    cout<<"inorder: ";
    inorderI(root);
    cout<<endl;
    cout<<"postorder: ";
    postorderI(root);
    cout<<endl;

    cout<<"----------------recursive-------\n";
    cout<<"preorder: ";
    preorderR(root);
    cout<<endl;
    cout<<"inorder: ";
    inorderR(root);
    cout<<endl;
    cout<<"postorder: ";
    postorderR(root);
    cout<<endl;

    cout<<"------------clone------------\n";
    Node *cloneptr=clone(root);
    cout<<"preorder: ";
    preorderR(cloneptr);
    cout<<endl;
    cout<<"inorder: ";
    inorderR(cloneptr);
    cout<<endl;
    cout<<"postorder: ";
    postorderR(cloneptr);
    cout<<endl;

    cout<<"----------mirror------------\n";
    Node *mirrorptr=mirror(root);
    cout<<"preorder: ";
    preorderR(mirrorptr);
    cout<<endl;
    cout<<"inorder: ";
    inorderR(mirrorptr);
    cout<<endl;
    cout<<"postorder: ";
    postorderR(mirrorptr);
    cout<<endl;

    cout<<"----------height---------\n";
    int ht=height(root);
    cout<<"height: "<<ht<<endl;

    cout<<"-----------search--------\n";
    cout<<search(root,12)<<endl;
    cout<<search(root,4)<<endl;

    cout<<"----------checkequal------\n";
    cout<<checkequal(root,cloneptr)<<endl;
    cout<<checkequal(mirrorptr,cloneptr)<<endl;


    cout<<"-----------delete--------\n";
    deleteBT(root,4);
    cout<<"inorder: ";
    inorderR(root);
    cout<<endl;
    deleteBT(root,8);
    cout<<"inorder: ";
    inorderR(root);
    cout<<endl;
    deleteBT(root,3);
    cout<<"inorder: ";
    inorderR(root);
    cout<<endl;

    cout<<"---------build"<<endl;
    int inorder[]  = {2,3,4,6,7,9,13,15,17,18,20};
    int preorder[] = {15,6,3,2,4,7,13,9,18,17,20};
    int n = sizeof(inorder)/sizeof(inorder[0]);

    // build tree from the two traversal arrays
    Node* b = build(inorder, preorder, 0, n - 1);
    inorderR(b);
    


    return 0;
}