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

/* Find an empty space!! in the hash table by using Linear Search */
int
findEmpty(Student** hashTable, int id){
	int i=id%TABLE_SIZE;
	while(1){
		if(hashTable[i%TABLE_SIZE]==NULL){
			return i % TABLE_SIZE;
		}
		i++;
	}
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
add(Student** hashTable, Student* input, int key){
	hashTable[key]=input;
}

/* Return Data of particular key from the hash table */
Student*
getValue(Student** hashTable,int key){
	return hashTable[key];
}

/* Print All Data in the Hash Table */
void
show(Student** hashTable){
	for(int i=0; i<TABLE_SIZE;i++){
		if(hashTable[i]!=NULL){
			printf("키: [%d] 이름:[%s]\n",i,hashTable[i]->name);
		}
	}
}

int
main(void){
	Student** hashTable;
	hashTable=(Student**)malloc(sizeof(Student)*TABLE_SIZE);
	init(hashTable);

	for(int i=0;i<INPUT_SIZE;i++){
		Student* student=(Student*)malloc(sizeof(Student));
		student->id=rand()%1000000;
		sprintf(student->name,"사람%d",student->id);
		if(search(hashTable,student->id)==-1){ // 중복되는 ID는 존재하지 않도록 함..기초니까
			int index=findEmpty(hashTable,student->id);
			add(hashTable,student,index);
		}
	}
	show(hashTable);
	destructor(hashTable);
	return 0;
}
