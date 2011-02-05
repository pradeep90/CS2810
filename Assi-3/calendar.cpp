#include<stdio.h>


/*
  Hi. The program seems fine. Could you just break it up into
  different functions so that main () is very simple and consists only
  of function calls?

  For example, you could have a class called Date. It could have a method (and also, constructors) called

  class Date
  {
       int dd, mm, yy, day;
  public:
       // This would get the date from the user in the proper format and
       // give error otherwise
       get_date ()
   
       // This will just contain your algorithm (won't print anything
       // out). It is only supposed to be called by print_day (), not by
       // other programs. It will set value of the variable day
       calculate_day () 
   
       // This will print day
       print_day ()
  };

  so that you can just say

  int main (){
   
       Date d;
       d.get_date ();
       d.print_day ();
  }

  :-)

  You can put that in a while loop or whatever... That's not the point. It's just that it becomes more modular.

  And, could you have a comment box at the top stating exactly what the program does, so that we can explain it if somebody ask for it?

*/

int get_input(char* dd)
{
     /*
      * Could you consider using getline () [with '/' as the
      * parameter, like getline (cin, str, '/') ]  instead of using
      * getchar ()? It might be useful in the future when writing more
      * complex programs Just check out cplusplus.com
      */
	char q;
	int d,i=0;
	q=getchar();
	while(q!='/')
	{
		dd[i++]=q;
		q= getchar() ;	
	}

	/*
	 * To convert a string to a integer, ie. "12" to 12 You could
	 * use atoi () [from stdlib.h]. It's very simple and effective
	 * and can be used in C++ as well
	 */
	If(i==1)
		d=dd[0]-48;

	else
		d=dd[1]-48 + (dd[0]-48)*10;
	return d;
}

main()
{
	int d,m,y,z,t,c,g;
	
	char dd[2],mm[2];
	printf("Enter date in format dd/mm/yyyy ");
	
	d = get_input(dd);
	m = get_input(mm);
	if(m>2)
		m = m -2;
	else
		m = m+10;
	
	scanf("%d",&y);
	if(y%100==0 && (m==11||m==12))
	{
		c = y/100 -1;
		y = 99;
	}
	else
	{
		c=y/100;
//	else
//		c=y/100 -1;
		if(m == 11 || m ==12)
			y=y%100 - 1;
		else
			y=y%100;
	}

	/*
	 * Can you just explain the logic behind the next few lines?
	 * They might ask us questions about what algo we are
	 * using.
	 */
	t=y/4;
	z=2.6*m-.2;
	g=c/4;
	int w = (d + z+y+t + g -2*c)%7;
	printf("Day is : ");
	switch(w)
	{
	case 0:
		printf("Sunday");
		break;
	case 1:
		printf("Monday");
		break;
	case 2:
		printf("Tuesday");
		break;
	case 3:
		printf("Wednesday");
		break;
	case 4:
		printf("Thursday");
		break;
	case 5:
		printf("Friday");
		break;
	case 6:
		printf("Saturday");
		break;		
	}		
printf("\n");
printf("%d",w);
printf("w = %d, z = %d,d = %d,m = %d,t = %d,g = %d,y = %d, ",w,z,d,m,t,g,y);
}


