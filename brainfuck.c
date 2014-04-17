//Brainfuck Interpreted
#include <stdio.h>
#include <stdlib.h>

typedef struct blockListing{
	int fPointer;
	struct blockListing *next;
}block;

block *addBlock(FILE *infile, block *start){
	block *returnPtr=malloc(sizeof(block));
	while(start->next != 0) start=start->next;
	start->next=returnPtr;
	returnPtr->next=0;
	returnPtr->fPointer=fgetpos(infile);
}

block *last(block *start){
	while(start->next !=0) start=start->next;
	return start;
}

char* fill(int n, char val){
	char* returnPtr = malloc(n);
	for(;n>0;n--){
		returnPtr[n-1]=val;
	}
}

int main(int argc, char *argv[]){
	//Initialise
	char* buffer;
	int memsize=256;
	buffer=fill(memsize,0);
	int memcell=0;
	FILE *infile;
	infile=fopen(argv[1],'r');
	char inChar;
	block *blockList=0;
	while((inChar=fgetc(infile)) != EOF){
		switch(inChar){
			case '<':
				memcell=(memcell-1)%memsize;
				break;
			case '>':
				memcell=(memcell+1)%memsize;
				break;
			case '+':
				buffer[memcell]++;
				break;
			case '-':
				buffer[memcell]--;
				break;
			case ',':
				buffer[memcell]=getchar();
				break;
			case '.':
				putc(buffer[memcell]);
				break;
			case '[':
				if(buffer[memcell]){
					if(blockList==0){
						blockList=malloc(sizeof(block));
						blockList->next=0;
						blockList->fPointer=fgetpos(infile);
					}else{
						addBlock(infile, blockList);
					}
				}else{
					while(inChar!=']')inChar=fgetc(infile);
				}
				break;
			case ']':
				block *lastBlock=last(blockList)
				block *curBlock=blockList;
				fsetpos(infile,lastBlock->fPointer);
				if(lastBlock==blockList){
					free(blockList);
					blockList=0;
					break;
				}
				while(curBlock->next != last && curBlock->next !=0) curBlock=curBlock->next;
				curBlock->next=0;
				free(lastBlock);
				break;
			default:
		}
	}
	return 0;
}