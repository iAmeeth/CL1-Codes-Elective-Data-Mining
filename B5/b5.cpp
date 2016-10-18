#include<iostream>
#include<stdlib.h>
using namespace std;

struct Tree
{
char data;
int label;
struct Tree *right,*left; 
};

typedef Tree node;

class DAG
{
private:
int R[10];
int top;
char *op;
public:
//CHECKED
void push(int x)
{
	top++;
	R[top]=x;
}
//CHECKED
int pop()
{
	int v = R[top];
	top--;
	return(v);
}
//CHECKED
void swap()
{
	int temp;
	temp=R[0];
	R[0]=R[1];
	R[1]=temp;
}
//CHECKED
void inorder(node *root)
{
	
	if(root)
	{
	inorder(root->left);
	cout<<"\nValue:\t"<<root->data<<"\tLabel\t"<<root->label;
	inorder(root->right);
	}
	

}


//CHECKED
void initializeRegister(node *root)
{
	int temp;
	top=root->label-1;
	temp=top;
	
	for(int i=0;i<=top;i++)
	{
		R[i]=temp;
		temp--;
	}

}
//CHECKED
void inserttotree(node **tree,char data)
{
	node *temp=NULL;
	
	if(!(*tree))
	{
		temp=(node *)malloc(sizeof(node));
		temp->data=data;
		temp->left=NULL;
		temp->right=NULL;
		temp->label=-1;
		*tree=temp;
	}

}
//CHECKED
void insert(node **tree,char data)
{
	int numofchildren=0;
	char ldata,rdata;
	inserttotree(tree,data);

	cout<<"Enter Number(0/2) of children of the node with value\t"<<data<<"\n";
	cin>>numofchildren;

	if(numofchildren==2)
	{
		cout<<"Enter Left child of the node with value\t"<<data<<"\n";
		cin>>ldata;
		inserttotree(&(*tree)->left,ldata);

		cout<<"Enter right child of the node with value\t"<<data<<"\n";
		cin>>rdata;
		inserttotree(&(*tree)->right,rdata);

		insert(&(*tree)->left,ldata);
		insert(&(*tree)->right,rdata);
	}

}



//CHECKED
void findleafLable(node *tree,int label_value)
{
	if(tree->left!=NULL && tree->right!=NULL)
	{
		findleafLable(tree->left,1);
		findleafLable(tree->right,0);
	}
	
	else
	{
		tree->label=label_value;
	}

}

//CHECKED ?
void findintermediateLable(node *tree)
{
	if(tree->left->label==-1)
	{
		findintermediateLable(tree->left);
	}

	else if(tree->right->label==-1)
	{
		findintermediateLable(tree->right);
	}
	else
	{
		if(tree->left!=NULL && tree->right!=NULL)
		{
			if(tree->left->label < tree->right->label)
			{
				tree->label=tree->right->label;
			}
			else if(tree->left->label == tree->right->label)
			{
				tree->label=tree->left->label+1;
			}
			else if(tree->left->label > tree->right->label)
			{
				tree->label=tree->left->label;
			}
		}
	}
}

void genCode(node *tree)
{


	if(tree->left!=NULL && tree->right!=NULL)
	{


		if(tree->left->label==1 && tree->right->label==0 && tree->left->left==NULL && tree->left->right==NULL && tree->right->left==NULL && tree->right->right==NULL)
		{
			cout<<"MOV "<<"R["<<R[top]<<"],"<<tree->left->data<<"\n";
			nameofOperation(tree->data);
			cout<<op<<" "<<"R["<<R[top]<<"],"<<tree->right->data<<"\n";

		}


		else if(tree->left->label>=1 && tree->right->label==0)
		{
			genCode(tree->left);
			nameofOperation(tree->data);
			cout<<op<<" "<<"R["<<R[top]<<"],"<<tree->right->data<<"\n";
		}


		else if(tree->left->label < tree->right->label)
		{
			int temp;

			swap();
			genCode(tree->right);
			temp=pop();
			genCode(tree->left);
			push(temp);
			swap();
			nameofOperation(tree->data);
			cout<<op<<" "<<"R["<<R[top]<<"]"<<" ,R["<<R[top-1]<<"]\n";

		}


		else if(tree->left->label >= tree->right->label)
		{
			genCode(tree->left);

			int temp=pop();
			genCode(tree->right);
			push(temp);
			nameofOperation(tree->data);
			cout<<op<<" "<<"R["<<R[top]<<"]"<<" ,R["<<R[top-1]<<"]\n";

		}


	}

	else if(tree->left==NULL && tree->right==NULL && tree->label==1)
	{
		cout<<"MOV "<<"R["<<R[top]<<"],"<<tree->data<<"\n";
	}

}
//CHECKED ?
void nameofOperation(char opr)
{
	switch(opr)
	{
	case '+':
	op=(char *)"ADD";
	break;
	case '-':
	op=(char *)"SUB";
	break;
	case '*':
	op=(char *)"MUL";
	break;
	case '/':
	op=(char *)"DIV";
	break;
	case '=':
	op=(char *)"EQUATE";
	break;
	}

}
//CHECKED
void delTree(node *tree)
{
	if(tree)
	{
		delTree(tree->left);
		delTree(tree->right);
		free(tree);
	}
}



};

int main()
{
DAG d;
char valueofRoot;
node* root=NULL;


cout<<"WELCOME\n";
cout<<"Root value please\n";
cin>>valueofRoot;


d.insert(&root,valueofRoot);

d.findleafLable(root,1);
while(root->label==-1)
{
d.findintermediateLable(root);
}

d.initializeRegister(root);

cout << "\nInorder Display:\n";
d.inorder(root);
cout<<"\n**************************\n";

d.genCode(root);
d.delTree(root);
return 0;
}
