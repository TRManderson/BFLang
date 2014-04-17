//Brainfuck Interpreted
#include <stdio.h>
#include <stdlib.h>

typedef struct blockListing{
	fpos_t *fPointer;
	struct blockListing *next;
}block;

block *last(block *start){
	while(start->next !=0) start=start->next;
	return start;
}

int main(int argc, char *argv[]){
	//Initialise
	int memsize=256;
	char* buffer=malloc(memsize);
	int memcell=0;
	for(memcell=memsize;memcell>0;memcell--)buffer[memcell-1]=0;
	FILE *infile = fopen(argv[1],"r");
	char inChar;
	block *blockList=0;
	block *curBlock=0;
	block *lastBlock=0;
	while((inChar=fgetc(infile)) != EOF){
		switch(inChar){
			case '<':
				memcell-=2;
			case '>':
				memcell+=1;
				memcell%=256;
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
						lastBlock=last(blockList);
						lastBlock->next=malloc(sizeof(block));
						lastBlock=lastBlock->next;
						lastBlock->next=0;
						lastBlock->fPointer=malloc(sizeof(fpos_t));
						fgetpos(infile, lastBlock->fPointer);
					}
				}else while(inChar=fgetc(infile) !=']');
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
			default:
				break;
		}
	}
	return 0;
}