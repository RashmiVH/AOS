#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>

struct node
{
int data;
struct node *right;
struct node *left;
};


void insert(struct node **root, int data)
{
struct node *temp, *cur, *prev;
temp=(struct node *)malloc(sizeof(struct node));
temp->right=temp->left=NULL;
temp->data=data;
if(*root==NULL)
{
*root=temp;
return;
}

prev=NULL;
cur=*root;
while(cur!=NULL)
{
prev=cur;
if(data==cur->data)
{
printf("Duplicate Entry\n");
return;
}
if(data<cur->data)
cur=cur->left;
else
cur=cur->right;
}

if(data<prev->data)
prev->left=temp;
else
prev->right=temp;

return;
}

void search(struct node *root,int data)
{

while(root!=NULL)
{
if(data==root->data)
{
printf("\nNode with data %d present",data);
return;
}
else if(data<root->data)
root=root->left;
else root=root->right;
}
printf("\nNode with data %d not present\n",data);
}


void delete(struct node **root,int data)
{
struct node *parent, *cur, * succ;
parent=NULL;
cur=*root;

while(cur!=NULL)
{
if(data==cur->data)
{
break;
}
else if(data<cur->data)
{
parent=cur;
cur=cur->left;
}
else 
{
parent=cur;
cur=cur->right;
}
}
if(cur==NULL)
{
printf("\nNode with data %d not present\n",data);
return;
}

if(cur->left!=NULL && cur->right!=NULL)
{
parent=cur;
succ=cur->right;
while(succ->left!=NULL)
{
parent=succ;
succ=succ->left;
}
cur->data=succ->data;
cur=succ;
}

if(cur->left==NULL && cur->right!=NULL)
{
if(parent==NULL) /* cur is the root */
{
*root=cur->right;
free(cur);
return;
}
if(cur==parent->left)
parent->left=cur->right;
else
parent->right=cur->right;
free(cur);
return;
}

if(cur->left!=NULL && cur->right==NULL)
{
if(parent==NULL)
{
*root=cur->left;
free(cur);
return;
}
if(cur==parent->left)
parent->left=cur->left;
else
parent->right=cur->left;
free(cur);
return;
}

if(cur->left==NULL && cur->right==NULL)
{
if(parent==NULL)
{
free(cur);
*root=NULL;
return;
}
if(cur==parent->right)
parent->right=NULL;
else
parent->left=NULL;
free(cur);
return;
}
 
}

void display(struct node *root)
{
if(root!=NULL)
{

printf("%d ",root->data);

display(root->left);
display(root->right);
}
}

void createTree(struct node **root)
{
int d,n=0;
FILE *fp;
struct node *temp, *cur, *prev;

fp=fopen("binaryTree","rb");
if(fp!=NULL)
{
if(!feof(fp))
{
fread(&d,sizeof(d),1,fp);
temp=(struct node *)malloc(sizeof(struct node));
temp->right=temp->left=NULL;
temp->data=d;
*root=temp;
}
while(!feof(fp))
{
prev=NULL;
cur=*root;
fread(&d,sizeof(d),1,fp);
temp=(struct node *)malloc(sizeof(struct node));
temp->right=temp->left=NULL;
temp->data=d;

while(cur!=NULL)
{

prev=cur;
if(d<cur->data)
cur=cur->left;
else
cur=cur->right;

}
if(d==prev->data)
continue;
if(d<prev->data)
prev->left=temp;
else
prev->right=temp;

}
 
}

}


void writeToFile(struct node *root,FILE **fp,int *n)
{

//fp=fopen("binaryTree","wb");
if(root!=NULL)
{
fwrite(&(root->data),sizeof(root->data),1,*fp);
(*n)++;
writeToFile(root->left,fp,n);
writeToFile(root->right,fp,n);
}

}

void main()
{
struct node *root = NULL;
int choice,d,n;
createTree(&root);
FILE *fp;
for(;;)
{
printf("\n1. Insert 2.Search 3.Delete 4.Display\n Enter choice : ");
scanf("%d",&choice);
switch(choice)
{
case 1: printf("\nEnter data: ");
	scanf("%d",&d);
	insert(&root,d);
	break;
case 4: printf("\n");
	if(root==NULL)
	{printf("\n Tree empty\n");
	break;
	}
	display(root);
	break;
case 2: if(root==NULL)
        {printf("\n Tree empty\n");
        break;
        }
	printf("\n Enter data: ");
	scanf("%d",&d);
	search(root,d);
	break;
case 3: if(root==NULL)
        {printf("\n Tree empty\n");
        break;
        }
	printf("\n Enter data: ");
        scanf("%d",&d);
        delete(&root,d);
        break;
default:
	if(root==NULL)
	exit(0);
	else
	{ 
	n=0;
	fp=fopen("binaryTree","wb");
	writeToFile(root, &fp,&n);
	fclose(fp);
	printf("**N=%d\n",n);	
	fp=fopen("binaryTree","rb");
//createTree(&root);
exit(0);
}
}
}
}

