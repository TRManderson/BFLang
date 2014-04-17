//Brainfuck Interpreted
#include <stdio.h>
#include <stdlib.h>

typedef struct blockListing{
	fpos_t *fPointer;
	struct blockListing *next;
}block;

block *addBlock(FILE *infile, block *start){
	block *returnPtr=malloc(sizeof(block));
	while(start->next != 0) start=start->next;
	start->next=returnPtr;
	returnPtr->next=0;
	returnPtr->fPointer=malloc(sizeof(fpos_t));
	fgetpos(infile, returnPtr->fPointer);
	return returnPtr;
}

block *last(block *start){
	while(start->next !=0) start=start->next;
	return start;
}

char *fill(int n, char val){
	char* returnPtr = malloc(n);
	for(;n>0;n--){
		returnPtr[n-1]=val;
	}
	return returnPtr;
}

int main(int argc, char *argv[]){
	//Initialise
	char* buffer;
	int memsize=256;
	buffer=fill(memsize,0);
	int memcell=0;
	FILE *infile;
	infile=fopen(argv[1],"r");
	char inChar;
	block *blockList=0;
	block *curBlock=0;
	block *lastBlock=0;
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
				putchar(buffer[memcell]);
				break;
			case '[':
				if(buffer[memcell]){
					if(blockList==0){
						blockList=malloc(sizeof(block));
						blockList->next=0;
						blockList->fPointer=malloc(sizeof(fpos_t));
						fgetpos(infile,blockList->fPointer);
					}else{
						addBlock(infile, blockList);
					}
				}else{
					while(inChar!=']')inChar=fgetc(infile);
				}
				break;
			case ']':
				lastBlock=last(blockList);
				curBlock=blockList;
				if(buffer[memcell]){
					fsetpos(infile,lastBlock->fPointer);
				}else{
					if(lastBlock==blockList){
						free(blockList);
						blockList=0;
						break;
					}
					while(curBlock->next != lastBlock && curBlock->next !=0) curBlock=curBlock->next;
					curBlock->next=0;
					free(lastBlock);
				}
				break;
			default:
				break;
		}
	}
	return 0;
}