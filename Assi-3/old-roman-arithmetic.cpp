/****************************************************************************************************
 *  Title: Convert Roman Numeral to Decimal
 *  Purpose: Ditto
 *  Description: The Program converts the user input string to Decimal, converts that to Roman and
 *  		 compares with the original input
 *  Author: S. Pradeep Kumar
 *  Date :  3 - 3 - 2010
 *
 *  Bug 1 : Length of str[] array was declared to be different in different functions. Gave error
 *  	    after 8 characters were input.................................FIXED! 3-3-2010    
 *
 ****************************************************************************************************/



#include <stdio.h>
#include <string.h>
#include <ncurses.h>

char rnum[][3] ={"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
int val[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
int maxTimes[] = {3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3};
int maxNum = 3999;
bool tdig[] = {0, 1, 0,1,0,1,0,1,0,1,0,1,0}, flag=0;
int numdig = 13;


int convRomanToDecimal(char * inp, int len){
     int sum = 0, i, j;
     for(i=0; i<len; i++){
	  for(j=0; j<numdig; j++){
	       if(!tdig[j]){
		    if(inp[i] == rnum[j][0]){
			 sum += val[j];
			 break;
		    }
	       }
	       else{
		    if(i<len-1 && inp[i] == rnum[j][0] && inp[i+1] == rnum[j][1]){
			 sum += val[j];
			 i++;
			 break;
		    }
	       }
	  }
     }
     //printw("%s\t%d\n", inp, sum);
     //printw("%d\n", sum);
     return sum;
}



int convDecimalToRoman(int deci, char cstr[]){
     int i, j, curr = 0;
     if(deci > maxNum)
	  return -1;
     for(i=0; i<numdig; i++){
	  j = (deci / val[i]) > maxTimes[i] ? maxTimes[i] : (deci/val[i]);
	  //printf("%d ", j);
	  if(j>0){
	       if(tdig[i]){
		    cstr[curr] = rnum[i][0];
		    cstr[++curr] = rnum[i][1];
		    deci -= val[i];
		    curr++;
	       }
	       else 
		    while(j>0){
			 cstr[curr] = rnum[i][0];
			 curr++;
			 deci -= val[i];
			 j--;
		    }
	  }

     }
     cstr[curr] = '\0';
     //printw("%s\n", cstr);
}

/* Get Decimal equivalent of input, convert it to Roman. Compare. */
int isNotRoman(char * str, int len){
     char cstr[20];
     int i;     
     strcpy(cstr, str);
     int t = convRomanToDecimal(str, len);
     if(convDecimalToRoman(t, cstr) == -1) // Too many 'M's
	  return 1;
     for(i=0; i<len; i++){
	  if(cstr[i] != str[i])
	       return 1;
     }
     return 0;
}

int getRoman(char * str){
     bool EOINPUT = 0, flag;
     int ch;
     int curr = 0;
     noecho();
     keypad(stdscr, TRUE);


     do{
	  ch = getch();
	  switch(ch){
	  case 'I':
	  case 'X':
	  case 'V':
	  case 'L':
	  case 'C':
	  case 'D':
	  case 'M':
	       str[curr] = ch;
	       if(isNotRoman(str, curr + 1)){ // Is not a roman number
		    beep();
		    break;
	       }
	       else{
		    curr++;
		    addch(ch);
		    //addch('*');
		    //getch();
	       }
	       break;
	  case '\n':
	       if(curr > 0){
		    EOINPUT = 1;
	       }
	       else 
		    beep();
	       break;
	  case KEY_BACKSPACE:	// Standard Procedure for Backspace
	       if(curr > 0){
		    // if(curr == 1){
			 
// 		    }
// 		    else 
		    if(isNotRoman(str, curr-1)){
			 beep();
		    }
		    else{
			 curr--;
			 echo();
			 printw("\b \b");
			 //refresh();
			 noecho();
		    }
	       }
	       else 
		    beep();
	       break;

	  default:
	       beep();
	       break;
	  }
     }while(!EOINPUT);
     str[curr] = '\0';
}

int main(){
     int tot=0,i=0, j=0, prev=0, ct=0;
     char str[20], c, cstr[20];
     bool flag = 0;
     initscr();
     do{
	  printw("\t\tConvert Roman Numeral to Decimal\t\t\n\n");
	  printw("Please enter the Roman Numeral. \n(Kindly use only I V X L C D M)\n:");
	  refresh();
	  getRoman(str);
	  printw("\nThe Decimal Equivalent is : %d\n", convRomanToDecimal(str, strlen(str)));
	  printw("\n\n\nPress y/Y to try again.\n\nPress any other key to exit.");
	  c = getch();
	  if(c == 'y' || c == 'Y')
	       flag = 0;
	  else 
	       break;
	  clear();
     }while(!flag);
     endwin();
     return 0;
}
