#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	FILE *infile=fopen(argv[1],"r");
	FILE *outfile=fopen(argv[2],"w");
	char inchar;
	int memlen=256;
	fprintf(outfile,"#include <stdio.h>\n#include <stdlib.h>\nint main(){int n;char *ptr=malloc(%d);for(n=%d;n>0;n--)ptr[n-1]=0;",memlen,memlen);
	while((inchar=fgetc(infile)) != EOF){
		switch(inchar){
			case '>':
				fprintf(outfile,"n=(n+1)%%%d;",memlen);
				break;
			case '<':
				fprintf(outfile,"n=(n-1)%%%d;",memlen);
				break;
			case '+':
				fprintf(outfile,"ptr[n]++;");
				break;
			case '-':
				fprintf(outfile,"ptr[n]--;");
				break;
			case ',':
				fprintf(outfile,"ptr[n]=getchar();");
				break;
			case '.':
				fprintf(outfile,"putchar(ptr[n]);");
				break;
			case '[':
				fprintf(outfile,"while(ptr[n]){");
				break;
			case ']':
				fprintf(outfile,"}");
			default:
				break;
		}
		putc('\n',outfile);
	}
	fprintf(outfile, "}");
}