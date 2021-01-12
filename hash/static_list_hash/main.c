#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 10007
#define INPUT_SIZE 5000

struct student{
	int id;
	char name[20];
}typedef Student;

struct bucket{
	Student* data;
	struct bucket* next;
}typedef Bucket;

/* Initiate Hash Table */
void
init(Student** hashTable){
	for(int i=0;i<TABLE_SIZE;i++)
		hashTable[i]=NULL;
}

/* free the memory of the hash table */
void
destructor(Student** hashTable){
	for(int i=0;i<TABLE_SIZE;i++){
		if(hashTable[i]!=NULL)
			free(hashTable[i]);
	}
}

/* Find Key data!! in the hash table by using Linear Search */
int
isExist(Bucket** hashTable, int id){
	int i=id%TABLE_SIZE;
	if(hashTable[i]==NULL) return 0; // Is not exist
	else{
		Bucket* cur=hashTable[i];
		while(cur!=NULL){
			if(cur->data->id==id) return 1;
			cur=cur->next;
		}
	}
	return 0;
}

/* Find matched data with particular ID KEY in the hash table */
int
search(Student** hashTable, int id){
	int i=id%TABLE_SIZE;
	while(1){
		if(hashTable[i%TABLE_SIZE]==NULL) return -1;
		else if (hashTable[i%TABLE_SIZE]->id==id) return i;
		i++;
	}
}

/* Insert data in particular key index */
void
add(Bucket** hashTable, Student* input){
	int i=input->id%TABLE_SIZE;
	if(hashTable[i]==NULL){
		hashTable[i]=(Bucket*)malloc(sizeof(Bucket));
		hashTable[i]->data=input;
		hashTable[i]->next=NULL;
	}
	else{
		Bucket* cur=(Bucket*)malloc(sizeof(Bucket));
		cur->data=input;
		cur->next=hashTable[i];
		hashTable[i]=cur;
	}
}

/* Return Data of particular key from the hash table */
Student*
getValue(Student** hashTable,int key){
	return hashTable[key];
}

/* Print All Data in the Hash Table */
void
show(Bucket** hashTable){
	for(int i=0; i<TABLE_SIZE;i++){
		if(hashTable[i]!=NULL){
			Bucket* cur=hashTable[i];
			while(cur!=NULL){
				printf("키: [%d] 이름: [%s]\n",i,cur->data->name);
				cur=cur->next;
			}
		}
	}
}

int
main(void){
	Bucket** hashTable;
	hashTable=(Bucket**)malloc(sizeof(Bucket)*TABLE_SIZE);
	init(hashTable);

	for(int i=0;i<INPUT_SIZE;i++){
		Student* student=(Student*)malloc(sizeof(Student));
		student->id=rand() % 1000000;
		sprintf(student->name, "사람%d",student->id);
		if(!isExist(hashTable,student->id)){ // 중복되는 ID는 존재하지 않도록 함..
			add(hashTable,student);
		}
	}
	show(hashTable);
	destructor(hashTable);
	return 0;
}
