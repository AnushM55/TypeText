/* so you need a function for -
 * 			1. printing that words paragraph
 *			2. get user input
 *			3. convert to array of strings
 *			4. comparision and scoring
 *			5. display results
 *			optional
 *			6. modify that paragraph
 *			
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
/*#include <unistd.h>
#include <termios.h>
*/
#define MENU_SIZE 4
#include<ncurses.h>

/* WORD LIST */
char *words[] = {
"Desert","you","ooh","Hurt","you","We are","no","strangers","to","love","You","know","the","rules","and","so","do","I","A","full","commitment is","what","I am","thinking","of","You","would not","get","this","from","any","other","guy","I","just","wanna","tell","you","how","I am","feeling","Gotta","make","you","understand","Never","gonna","give","you","up","Never","gonna","let","you","down","Never","gonna","run","around","and","desert","you","Never","gonna","make","you","cry","Never","gonna","say","goodbye","Never","gonna","tell","lie","and","hurt","you","We have","known","each","other","for","so","long","Your","heart has","been","aching","but","you","too","shy","to","say","it","Inside","we","both","know","what has","been","going","on","We","know","the","game","and","we are","gonna","play","it","And","if","you","ask","me","how","I am","feeling","Do not","tell","me","you","too","blind","to","see","Never","gonna","give","you","up","Never","gonna","let","you","down","Never","gonna","run","around","and","desert","you","Never","gonna","make","you","cry","Never","gonna","say","goodbye","Never","gonna","tell","lie","and","hurt","you","Never","gonna","give","you","up","Never","gonna","let","you","down","Never","gonna","run","around","and","desert","you","Never","gonna","make","you","cry","Never","gonna","say","goodbye","Never","gonna","tell","lie","and","hurt","you","Ooh","Give","you","up","Oohooh","Give","you","up","Oohooh","Never","gonna","give","never","gonna","give","Give","you","up","Oohooh","Never","gonna","give","never","gonna","give","Give","you","up","We have","known","each","other","for","so","long","Your","heart has","been","aching","but","you","too","shy","to","say","it","Inside","we","both","know","what has","been","going","on","We","know","the","game","and","we are","gonna","play","it","I","just","wanna","tell","you","how","I am","feeling","Gotta","make","you","understand","Never","gonna","give","you","up","Never","gonna","let","you","down","Never","gonna","run","around","and","desert","you","Never","gonna","make","you","cry","Never","gonna","say","goodbye","Never","gonna","tell","lie","and","hurt","you","Never","gonna","give","you","up","Never","gonna","let","you","down","Never","gonna","tell","lie","and","hurt","you"};

/*functions used */
void print_paragraph(char **paragraph, int N); //1. printing that words paragraph

int  userinput(char **paragraph,char* c_arr, float *secs,int *N, int *space_ctr,int *numsec); //2. get user input

void convertToArray(int numchar,int *space_ctr, char **to_str,char *c_arr);//convert user input to an array of strings

void scoring(char **to_str,int *N,char **paragraph, float *secs);//compare array of strings and original para to calculate score

int menu();//display that menu

void welcometext();//display decorative 

int  pos=0;
#define WORDS_SIZE (long)(sizeof words/sizeof(words[0]))

int main(int argc, char **argv) {
	srand(time(NULL));						// seed for randomness
	
int numsec=0;
	/*initialising values*/
	
	int cho=0;
	float secs=0;
	int space_ctr=0;
	
	char **paragraph;	// store words list for later comparison
char **to_str;	
	int N=0;
char c_arr[10000];
	printf("\033c");
	welcometext();
	printf("\n Press any key to continue: ");
	cho=getchar();
	// should be called by ./typingtest
	if(argc>1) {
		fprintf(stderr, "USAGE: %s\n", argv[0]);
		return EXIT_FAILURE;
	}
	printf("\n"); printf("\n"); printf("\n");	// visual
	while((menu())!=4){
	  secs=0;space_ctr=0;N=0;
	printf("\n Enter total seconds: ");
	scanf("%d",&numsec);
	/* CREATE AND PRINT PARAGRAPH */

	// number of words in test
	printf("\n Enter no of words in test: \n");
	scanf("%d",&N);

	secs=0;
	space_ctr=0;
	paragraph=(char**)malloc(N*sizeof(words[0]));	// store words list for later comparison
	print_paragraph(paragraph,N); /* paragraph printed here */

	printf("\n");		// visual

	/* USER INPUT */
	int numchar=0;
	/* user input */
	numchar= userinput(paragraph,c_arr,&secs,&N,&space_ctr,&numsec);

	// convert to array of strings
to_str= (char**)malloc(N*sizeof(words[0]));	
/*	char *to_str[N*sizeof(words[0])];*/
	
	convertToArray(numchar,&space_ctr,to_str,c_arr);

	/* COMPARISON AND SCORING */
	scoring(to_str,&N,paragraph,&secs);
	printf("\n Press any key to continue :");
	cho=getchar();
	cho=getchar();
	
	}
	for(int i=0;i<(N);i++){
		free(to_str[i]); free(paragraph[i]);
	}
	return EXIT_SUCCESS;
}
void welcometext(){
    
    printf("\033[5m+\033[33m-------------------------------------------------------+\033[0m\n");
    printf("\033[5m\033[33m|\033[0m\033[32m ###### \033[0m \033[33m#     #  \033[0m \033[32m######  \033[0m  \033[33m #####   \033[0m                 \033[33m\033[5m|\033[0m\n");
    printf("\033[5m\033[33m|\033[0m\033[32m   ##   \033[0m \033[33m #   #   \033[0m \033[32m#    #  \033[0m  \033[33m ##      \033[0m               \033[33m\033[5m  |\033[0m\n");
    printf("\033[5m\033[33m|\033[0m\033[32m   ##   \033[0m \033[33m  # #    \033[0m \033[32m######  \033[0m  \033[33m #####   \033[0m               \033[33m\033[5m  |\033[0m\n");
    printf("\033[5m\033[33m|\033[0m\033[32m   ##   \033[0m \033[33m  ##     \033[0m \033[32m##      \033[0m  \033[33m ##      \033[0m               \033[33m\033[5m  |\033[0m\n");
    printf("\033[5m\033[33m|\033[0m\033[32m   ##   \033[0m \033[33m  ##     \033[0m \033[32m##      \033[0m  \033[33m #####   \033[0m               \033[33m\033[5m  |\033[0m\n");
    printf("\033[5m\033[33m|\033[0m                                                       \033[5m\033[33m|\033[0m\n");
    printf("\033[5m\033[33m|\033[0m                      \033[32m ###### \033[0m\033[33m ##### \033[0m\033[32m ##   ## \033[0m\033[33m ######  \033[0m\033[33m\033[5m|\033[0m\n");
    printf("\033[5m\033[33m|\033[0m                      \033[32m   ##   \033[0m\033[33m ##    \033[0m\033[32m  ## ##  \033[0m\033[33m   ##    \033[0m\033[33m\033[5m|\033[0m\n");
    printf("\033[5m\033[33m|\033[0m                      \033[32m   ##   \033[0m\033[33m ##### \033[0m\033[32m   ###   \033[0m\033[33m   ##    \033[0m\033[33m\033[5m|\033[0m\n");
    printf("\033[5m\033[33m|\033[0m                      \033[32m   ##   \033[0m\033[33m ##    \033[0m\033[32m  ## ##  \033[0m\033[33m   ##    \033[0m\033[33m\033[5m|\033[0m\n");
    printf("\033[5m\033[33m|\033[0m                      \033[32m   ##   \033[0m\033[33m ##### \033[0m\033[32m ##   ## \033[0m\033[33m   ##    \033[0m\033[33m\033[5m|\033[0m\n");

    printf("\033[5m+\033[33m-------------------------------------------------------+\033[0m\n");
}
/*display menu*/
int menu() {

    WINDOW *w;

    char list[5][25] = { "TYPING AREA", "TYPE LESSONS", "LOGIN", "HELP", "QUIT" };

    char item[50];

    int ch, i = 0, width = 10;

    initscr(); // initialize Ncurses
	       //
    w = newwin( 10, 32, 4, 19 ); // create a new window
				//
    box( w, 0, 0 ); // sets default borders for the window
		    //
    // now print all the menu items and highlight the first one
    for( i=0; i<5; i++ ) {
      if( i == 0 ) 
	wattron( w, A_STANDOUT ); // highlights the first item.
      else
      wattroff( w, A_STANDOUT );

      sprintf(item, "%-7s",  list[i]);

      mvwprintw( w, i+1, 2, "%s", item );

    }
    wrefresh( w ); // update the terminal screen
    i = 0;

    noecho(); // disable echoing of characters on the screen
    keypad( w, TRUE ); // enable keyboard input for the window.
		       //
    curs_set( 0 ); // hide the default screen cursor.
		   //
    // get the input
    while(( ch = wgetch(w)) != '\n'){ 
      // right pad with spaces to make the items appear with even width.
      sprintf(item, "%-7s",  list[i]); 

      mvwprintw( w, i+1, 2, "%s", item ); 

      // use a variable to increment or decrement the value based on the input.
      switch( ch ) {
	case KEY_UP:
	  i--;
	  i = ( i<0 ) ? 4 : i;
       	break;

	case KEY_DOWN:
	  i++;
	  i = ( i>4 ) ? 0 : i;
	break;
      }
	// now highlight the next item in the list.
	wattron( w, A_STANDOUT );

	sprintf(item, "%-7s",  list[i]);

	mvwprintw( w, i+1, 2, "%s", item);

	wattroff( w, A_STANDOUT );

    }

    delwin( w );

    endwin();
    return i;
}
void print_paragraph(char **paragraph, int N) {
	int limit = 40, used = 0;
	// max number of characters per line (visual)
		    // print the top of the box
		    //
/*    int width=4;
    int height=5;
    int x = (COLS - width) / 2;       // the x-coordinate of the box
    int y = (LINES - height) / 2;     // the y-coordinate of the box

    initscr();                        // initialize ncurses
    cbreak();                         // disable line buffering
    noecho();                         // don't echo input
    keypad(stdscr, TRUE);             // enable function keys

    // draw the box
    box(stdscr, '|', '-');
*/	int spaces=0,lines=1;
	printf("\t\t\t\t+");
	for(int i=0;i<55;i++){
	printf("-");
	}
	printf("+\n\t\t\t\t|");
	
	for(int i=0;i<55;i++){
		printf(" ");
	}printf("|\n\t\t\t\t|\t");
	for(int i=0; i<N; i++) {
		char *s=words[rand() % WORDS_SIZE];
		char temp[strlen(s)+1];
		char *n;
		sprintf(temp, "%s ", s);		// test ends with space if last word does not match
		n=strdup(temp);
		paragraph[i]=malloc(strlen(n)*sizeof(char));
		paragraph[i]=n;
		spaces+=1;
		spaces+=strlen(n);
		used += strlen(n);
		if(used<=limit) {
			printf("%s", n);
			if(i+1==N){
				for(int j=0;j<(52-spaces);j++){
					printf(" ");
				}
				printf("\b|\n\t\t\t\t|");	// new line
				break;
		}}
		else if (used>limit) {
			printf("%s\t|\n\t\t\t\t|\t", n);
			used=0;
			spaces=0;
		}}
	int i;
	for(i=0;i<55;i++){
		printf(" ");
	}printf("|\n\t\t\t\t");
	
	printf("+");
	for(int i=0;i<55;i++){
	printf("-");
	}
	printf("+\n");
    /*   mvprintw(y + 1, x + 2,"hello");
    refresh();
    getch();
    endwin(); 
*/	// clean up ncurses

}
int  userinput(char **paragraph,char* c_arr, float *secs,int *N, int *space_ctr,int *numsec){
	int numchar=0;
	struct timeval t1, t2;
	long long msecs;
	bool first=true;

	char c;
	char *last = paragraph[(*N)-1];	// last word
	char last_temp[100];			// stores the user's last word for comparison
	int j=0;						// index for user's last word
	system("stty raw");		// set terminal to raw mode for live char input

	while(((*space_ctr)<(*N))&&((*secs)<=(*numsec))){
		c=getchar();
		numchar++;
		if(c!='\0' && c!=0x7F && first) {	// start time after first input
			(void)gettimeofday(&t1, NULL);
			first=false;
		}
		if(c==' ') {
			(*space_ctr)+=1;
			c_arr[pos] = ' ';
		}
		else if(pos >= 0)
			c_arr[pos]=c;
		if(c==0x7F) {	// 0x7F = backspace key
			printf("\b \b");		// backspace implementation
			printf("\b \b");		// backspace implementation
			if(pos > 0) {
				printf("\b \b");		// backspace implementation
				pos--;
				if(c_arr[pos]==' ')
					(*space_ctr)-=1;
				if(j>0)
					j--;
			}
		} else
			pos++;

		if((*space_ctr)+1==(*N)) {		// get last word
			if(c!=' ' && c!=0x7F)
				last_temp[j++]=c;
			if(j==(int)(strlen(last)-1)) {
				last_temp[j]=' ';			// append space (as test ends with space by default)
				last_temp[j+1]='\0';		// end of string
			}
		}

		if(strcmp(last, last_temp)==0) {	// check for matching last word
			(*space_ctr)+=1;
			c_arr[pos++]=' ';
		}
		if(first==false){
		(void)gettimeofday(&t2, NULL);		// terminate time after last space
		msecs = 1000000*(t2.tv_sec-t1.tv_sec)+(t2.tv_usec-t1.tv_usec);	// milliseconds conversion
		(*secs) = (float)msecs/1000000;		// seconds conversion
	}}
	system("stty cooked");		// back to default terminal mode
	printf("\n"); printf("\n"); printf("\n");		// visual

	(*N)=(*space_ctr);
	return numchar;
}


void convertToArray(int numchar,int *space_ctr, char **to_str,char *c_arr){
	int begin_index=0, end_index, index=0;
	(*space_ctr)=0;
	for (int x=0; x<pos; x++) {
		char word[numchar];
		index++;
		if(c_arr[x]==' ') {
			end_index=index;
			word[0]='\0';
			strncpy(word, c_arr+begin_index, end_index);
			word[(end_index-begin_index)]='\0';
			to_str[(*space_ctr)]=strdup(word);
			(*space_ctr)++;
			begin_index=end_index;
		}
	}
	}

void scoring(char **to_str,int *N,char **paragraph, float *secs){
	int begin_index=0, end_index, index=0;
	int score=0;
	for(int x=0; x<(*N); x++) {
		if(strcmp(to_str[x], paragraph[x])==0)
			score++;
	}
	float accuracy=((float)score/(float)(*N))*100;
	float wpm=(score/(*secs)) * 60;

	printf("\%% correct: %f\n", accuracy);
	printf("WPM: %f\n", wpm);
	printf("\n");
	}

