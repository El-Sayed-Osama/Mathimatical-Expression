#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define stacksize 100

using namespace std;

typedef char elementT;

typedef struct
{
    elementT *contents;
    int Size;
    int top;
}stack_T;

typedef struct tnode
{
    elementT data;
    struct tnode* left;
    struct tnode* right;
} TNode;

typedef struct{
    TNode *root;
} Tree;

typedef struct tnode* BTREE;


void TreeInit(Tree *T)
{
    T->root = NULL;
}

TNode* newNode(elementT x){
    TNode* T =(TNode*) malloc(sizeof(TNode));
    T->data = x;
    T->left = NULL;
    T->right = NULL;
    return T;
}

void show_node(BTREE T)
{
    cout<<" "<<T->data;
}

void preorder(BTREE T)
{
    if (T!=NULL)
    {
        show_node(T);
        preorder(T->left);
        preorder(T->right);
    }
}

void postorder(BTREE T)
{
    if (T!=NULL)
    {
        postorder(T->left);
        postorder(T->right);
        show_node(T);
    }
}

void inorder(BTREE T)
{
    if (T!=NULL)
    {
        inorder(T->left);
        show_node(T);
        inorder(T->right);
    }
}

int StackInit(stack_T *s)
{
    s->contents=(elementT *)malloc(sizeof(elementT)*stacksize);
    if(s->contents==NULL)
    {
        cout<<"Error in Creating Stack"<<endl;
        return 0;
    }
    s->Size=stacksize;
    s->top=-1;
    return 1;
}

int StackIsEmpty(stack_T s)
{
    return s.top<0;
}

int StackIsFull(stack_T s)
{
    return s.top>=s.Size-1;
}

int StackPush(stack_T *s, elementT x)
{
    if(StackIsFull(*s))
    {
        cout<<"Stack is Full"<<endl;
        return 0;
    }
    s->contents[++s->top]=x;
    return 1;
}

int StackPop(stack_T *s, elementT* x)
{
    if(StackIsEmpty(*s))
    {
        cout<<"Stack is Empty"<<endl;
        return 0;
    }
    *x=s->contents[s->top--];
    return 1;
}

bool prcd(char s1,char s2){
    if (s1=='*'||s1=='/'){
        return true;
    }
    else if (s1=='+'||s1=='-'){
        if (s2=='*'||s2=='/')
            return false;
        else
            return true;
    }
}

char top(stack_T s)
{
    char x;
    StackPop(&s,&x);
    StackPush(&s,x);
    return x;
}

string conv(string st){
    stack_T s;
    StackInit(&s);
    string postfix;
    string newStr;
    int i=0;
    char op;
    while (i<st.length()){
        char c=st[i];
        if (c!='*' && c!='/' && c!='+' && c!='-'){
            postfix+=c;
        }

        else{
            while(!StackIsEmpty(s) && prcd(top(s),c)){
                StackPop(&s,&op);
                postfix+=op;
            }
            StackPush(&s,c);
        }
        i++;
    }
    while(!StackIsEmpty(s)){
        StackPop(&s,&op);
        postfix+=op;
    }
    for (int i=postfix.length()-1;i>=0;i--){
        newStr+=postfix[i];
    }
    return newStr;
}

TNode* ins(TNode* T, elementT x, int* flag)
{
    if(!T)
    {
        T=newNode(x);
        *flag=1;
        return T;
    }
    if (*flag==0){
        if (T->right==NULL){
            T->right=ins(T->right,x,flag);
        }
    }

    if (*flag==0){
        if (T->right->data=='*' || T->right->data=='/' || T->right->data=='+' || T->right->data=='-'){
            T->right=ins(T->right,x,flag);
        }
    }

    if (*flag==0){
        if (T->right->data!='*' && T->right->data!='/' && T->right->data!='+' && T->right->data!='-'){
            if (T->left==NULL){
                T->left=ins(T->left,x,flag);
            }
        }
    }

    if (*flag==0){
        if (T->right->data!='*' && T->right->data!='/' && T->right->data!='+' && T->right->data!='-'){
            if (T->left->data=='*' || T->left->data=='/' || T->left->data=='+' || T->left->data=='-'){
                T->left=ins(T->left,x,flag);
            }
        }
    }

    if (*flag==0){
        if (T->left==NULL){
            T->left=ins(T->left,x,flag);
        }
    }

    if (*flag==0){
        if (T->left->data=='*' || T->left->data=='/' || T->left->data=='+' || T->left->data=='-'){
            T->left=ins(T->left,x,flag);
        }
    }

    return T;
}


int main()
{
    Tree T ;
    TreeInit(&T);
    string st;
    cout<<" Enter the Mathematical Expression : ";
    cin>>st;
    string newStr=conv(st);
    int flag=0;
    for (int i=0;i<newStr.length();i++){
        flag=0;
        T.root = ins(T.root,newStr[i],&flag);
    }
    cout<<" ***********************************"<<endl<<endl;
    cout <<" Mathematical Expression is : "<<st<<endl<<endl;
    cout <<" Pre-Order : "<<endl;
    preorder(T.root);
    cout<<endl;
    cout<<" ***********************************"<<endl<<endl;
    cout <<" In Order : "<<endl;
    inorder(T.root);
    cout<<endl;
    cout<<" ***********************************"<<endl<<endl;
    cout <<" Post Order : "<<endl;
    postorder(T.root);
    cout<<endl;
    cout<<" ***********************************"<<endl<<endl;
    return 0;
}

