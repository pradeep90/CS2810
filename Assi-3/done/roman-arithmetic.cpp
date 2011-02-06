/****************************************************************************************************
 *  Title: Convert Roman Numeral to Decimal
 *  Purpose: Ditto
 *  Description: The Program converts the user input string to Decimal, converts that to Roman and
 *  		 compares with the original input
 *  Author: S. Pradeep Kumar
 *  Date :  
 *
 *  Bug 1 : Length of str[] array was declared to be different in different functions. Gave error
 *  	    after 8 characters were input.................................FIXED! 3-3-2010    
 *
 ****************************************************************************************************/



#include <iostream>
#include <string.h>
using namespace std;


char rnum[][3] ={"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
int val[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
int maxTimes[] = {3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3};
int maxNum = 3999;
bool tdig[] = {0, 1, 0,1,0,1,0,1,0,1,0,1,0}, flag=0;
int numdig = 13;


class r2d
{
	char str[20];
	int len;
	int sum;
public:
	void getRoman();
	void convRomanToDecimal();
	int get_sum();
	void print_deci();
};

int r2d::get_sum()
{
	return sum;
}

void r2d::print_deci()
{
	cout<<sum<<endl;
}
void r2d::getRoman()
{
     bool EOINPUT = 0, flag;
     int ch;
     int curr = 0;

	cin>>str;
	len=strlen(str);
}

void r2d::convRomanToDecimal()
{
      sum = 0;
	int  i, j;
     for(i=0; i<len; i++)
     {
	  for(j=0; j<numdig; j++)
	  {
	       if(!tdig[j])
	       {
		    if(str[i] == rnum[j][0])
		    {
			 sum += val[j];
			 break;
		    }
	       }
	       else
	       {
		    if(i<len-1 && str[i] == rnum[j][0] && str[i+1] == rnum[j][1])
		    {
			 sum += val[j];
			 i++;
			 break;
	            }



	       }
          }
     }
}

class d2r
{
	int deci;
	char cstr[];

public:
	void get_input();
	void convDecimalToRoman();
	int is_error();
	void set_deci(int );
	void print_output();
};
void d2r::set_deci(int a)
{
	deci= a;
}
void d2r::get_input()
{
	cout<<"Enter number btw 1 & 3999"<<endl;
	cin>>deci;
}

void d2r::convDecimalToRoman()
{
     int i, j, curr = 0;
     for(i=0; i<numdig; i++)
     {
	  j = (deci / val[i]) > maxTimes[i] ? maxTimes[i] : (deci/val[i]);
	  if(j>0)
	  {
	       if(tdig[i])
	       {
		    cstr[curr] = rnum[i][0];
		    cstr[++curr] = rnum[i][1];
		    deci -= val[i];
		    curr++;
	       }
	       else 
		    while(j>0)
		    {
			 cstr[curr] = rnum[i][0];
			 curr++;
			 deci -= val[i];
			 j--;
		    }
	  }

     }
     cstr[curr] = '\0';
}

int d2r::is_error()
{
	if(deci<1|| deci>3999)
		return 1;
	else 
		return 0;
}

void d2r::print_output()
{
	cout<<cstr<<endl;
}



main()
{

	int q=0,i=0,u,t;

	cout<<"Enter:\n 1 for converting roman to decimal \n 2 for decimal to roman\n 3 for arithmetic among roman numbers\n"<<endl;
	cin>>i;
	switch(i)
	{
	case 1:
	{
		r2d c;
		cout<<"enter the Roman Numeral. \n(Kindly use only I V X L C D M)\n:\n";
		c.getRoman();
		c.convRomanToDecimal();
		c.print_deci();
	}
	break;

	case 2:
	{
		d2r s;
		s.get_input();
		 while(s.is_error())
		{
			cout<<"no. should be btw 1 & 3999"<<endl;
			s.get_input();
		}
		s.convDecimalToRoman();
		s.print_output();
	}
	break;

	case 3:
	{
		cout<<"for addition press 1"<<endl<<" for subtraction press 2"<<endl<<"for multiplication press 3 "<<endl;
		cin>>q;
		r2d a,b;
		cout<<"enter the Roman Numeral. \n(Kindly use only I V X L C D M)\n:"<<endl;
		a.getRoman();
		a.convRomanToDecimal();
		cout<<"enter the Roman Numeral. \n(Kindly use only I V X L C D M)\n:"<<endl;
		b.getRoman();
		b.convRomanToDecimal();
		u=a.get_sum();
		t=b.get_sum();
		switch(q)
		{
		case 1:
		{
			if(u+t>3999)
			{
				cout<<"Sorry no. out of range"<<endl;
			}
			else
			{
				d2r s;
				s.set_deci(u+t);
				s.convDecimalToRoman();
				s.print_output();			
			}
		}
		break;
		case 2:
		{
			d2r s;
			if(t>u && 0<t-u <4000)
			{
				cout<<"subtracting bigger from smaller"<<endl;
				s.set_deci(t-u);
				s.convDecimalToRoman();
				s.print_output();			
			}
			else if(t<u && 0<u-t<4000)
			{
				s.set_deci(u-t);
				s.convDecimalToRoman();
				s.print_output();			
			}
			else
				cout<<"No. out of range"<<endl;
		}
		break;
		case 3:
		{
			d2r s;
			if(t>0 && u>0 && t*u<4000)
			{
				s.set_deci(t*u);
				s.convDecimalToRoman();
				s.print_output();			
			}
			else
				cout<<"No. out of range"<<endl;
		}
		break;
		}
		
	}
	break;		
	}		
}
