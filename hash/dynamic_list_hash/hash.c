#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


struct hashmap_node{
	long key;
	void* val;
	struct hashmap_node* next;
}typedef hashmap_node;

struct hashmap_table{
	int size;
	struct hashmap_node** list;
}typedef hashmap_table;

struct temp{
	int data;
	struct temp* next;
}typedef TEMP;

/*
 * hashmap_table->size
 * 				->list[][]	[0] [][][][][]
 * 							[1] [][][][][
 * 							[2] ...
 * 							...
 */

hashmap_table* createTable(int size){
	hashmap_table* t=(hashmap_table*)malloc(sizeof(hashmap_table));
	t->size=size;
	t->list=(hashmap_node**)malloc(sizeof(hashmap_node*)*size);
	int i;
	for(i=0;i<size;i++)
		t->list[i]=NULL;
	return t;
}

int hashCode(hashmap_table* t, long key){
	if(key<0)
		return -((key)%(t->size));
	return (key)%(t->size);
}

void insertNode(hashmap_table* t,long key, void* val){
	int pos=hashCode(t,key);
	hashmap_node* list=t->list[pos];
	hashmap_node* newnode=(hashmap_node*)malloc(sizeof(hashmap_node));
	hashmap_node* temp=list;
	while(temp!=NULL){
		if(temp->key==key){
			temp->val=val;
			return;
		}
		temp=temp->next;
	}
	newnode->key=key;
	newnode->val=val;
	newnode->next=list;
	t->list[pos]=newnode;
}

void* lookup(hashmap_table* t,long key){
	int pos=hashCode(t,key);
	hashmap_node* list=t->list[pos];
	hashmap_node* temp=list;
	while(temp){
		if(temp->key==key)
			return temp->val;
		temp=temp->next;
	}
	return NULL; /* Failed! */
}

bool deleteNode(hashmap_table* t,long key){
	int pos=hashCode(t,key);
	hashmap_node* list=t->list[pos];
	hashmap_node* temp=list;
	hashmap_node* prev=list;
	while(temp){
		if(temp->key==key){
			prev->next=temp->next;
			free(temp->val);
			free(temp);
			return true;
		}
		temp=temp->next;
		prev=temp;
	}
	return false;
}


int
main(void){
	hashmap_table* table=createTable(7);
	long key=4545;
	TEMP* temp1=(TEMP*)malloc(sizeof(TEMP));
	temp1->data=1;
	TEMP* temp2=(TEMP*)malloc(sizeof(TEMP));
	temp2->data=2;
	temp1->next=temp2;
	TEMP* temp3=(TEMP*)malloc(sizeof(TEMP));
	temp3->data=3;
	temp2->next=temp3;
	temp3->next=NULL;
	insertNode(table,key,temp1);
	TEMP* result=(TEMP*)lookup(table,key);
	if(result==NULL){
		printf("Not Found\n");
	} else {
		printf("%d\n",result->data);
	}



	return 0;
}