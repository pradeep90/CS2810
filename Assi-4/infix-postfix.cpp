/*
  tested on
  1) both examples given with problem statement
  2) 1+2*3-4
  3) 1*2+4/5
  4) 1*2+3/4
  5) 2 * (43 + 2/7)
  6) 3 + 4* 2/(1-5) ^ 2 ^ 3
  7) 5+((1+2)*4)-3 gave output 5 1 2 + 4 * + 3 - instead of 5 1 2 + 4 * 3 - + but i think both r same :-)
  8) 3^4+5*6^2-1

*/

#include<iostream>
#include"stack.cpp"
using namespace std;

class expression
{
     char infix_arr[100], postfix_arr[100];
     Stack oper_stack;
     int value;

public:     
     void get_infix_expression (); 		// Which will get user postfix_arr into infix_str //to be done
     void convert_to_postfix ();   		// Which will convert infix_str to postfix and put result in postfix_str
//     void evaluate_postfix_expression ();	//to be done
//     void evaluate (){
//	  convert_to_postfix ();		//to be done
//	  evaluate_postfix_expression ();

//     void write_to_file (string filename);	//to be done
//     void print ();				// Just cout all the value
      void display();				//cout postfix string, for can be removed after whole prgm is written
};

     
int precedence(char c)
{
     int p;
     switch(c)
     {
     case '(':p=1;
	  break;
     case '-':p=2;
	  break;
     case '+':p=2;
	  break;
		
     case '*':p=3;
	  break;
     case '/':p=3;
	  break;
     case '^':p=4;
	  break;
     }

     return p;
}

bool is_operator(char a)
{
	if(((a!='*')&&(a!='+')&&(a!='-')&&(a!='/')&&(a!='^')&&(a!='(')&&(a!=')')))
		return false;
	else
		return true;
}

bool is_end_of_sub_expression (char a)
{
	if (a==')')
		return true;
	else
		 return false;
}

bool is_numeral ( char c)
{ 
       if(c>'9' || c<'0')
		return false;
	else
		return true;
}


void expression::display()
{
     cout<<postfix_arr<<endl;

}
void expression::get_infix_expression()
{
     cout<<"enter expression"<<endl;
     cin.getline(infix_arr,100,'\n');
}

void expression::convert_to_postfix()
{
     char t[100];
     char c,temp;
     int i = 0,j = 0,size=0,flag = 0;

     cout<<infix_arr<<endl;

     while(infix_arr[i]!='\0')
     {
	  if(infix_arr[i]==' ')
	       ;		//do nothing
	  else if (is_operator (infix_arr[i]) == false)
	  {
	       postfix_arr[j++]=infix_arr[i];
	       c=infix_arr[i+1];
	       if (is_numeral (c) == false)
	       	    postfix_arr[j++]=' ';

	  }

	  else if (is_end_of_sub_expression (infix_arr[i]) == true)
	  {
	       c = oper_stack.pop();
	       while(c!='(')
	       {
		    postfix_arr[j++] = c;
		    postfix_arr[j++] = ' ';
		    c = oper_stack.pop();
	       }
	  }

	  else						// operand
	  {
	       c = infix_arr[i];
	       if(oper_stack.isempty())
		    oper_stack.push(c);
	       else
	       {
		    temp = oper_stack.pop();
		    if(precedence(c)==1)
		    {
			 oper_stack.push(temp);
			 oper_stack.push('(');
		    }
		    else if((precedence(c) < precedence(temp)) || (precedence(c)!=4 && precedence(c)==precedence(temp)))
		    {
			 size = oper_stack.get_size();
			 while(oper_stack.get_size()>=1 && precedence(c)<= precedence(temp))		//precedence(c) can't be 4
			 {
			      postfix_arr[j++] = temp;
			      postfix_arr[j++] = ' ';
			      temp = oper_stack.pop();
			 }
			 if(precedence(c)<=precedence(temp))		
			 {
			      postfix_arr[j++] = temp;
			      postfix_arr[j++] = ' ';
			      oper_stack.push(c);
			 }
			 else
			 {
			      oper_stack.push(temp);
			      oper_stack.push(c);
			 }

		    }
		    else if(precedence(c) > precedence(temp))
		    {
			 oper_stack.push(temp);
			 oper_stack.push(c);
		    }
		    else 							
		    {
			 oper_stack.push(temp);					
			 oper_stack.push(c);
		    }
	       }
	  }
	  i++;
		
     }
     while(!oper_stack.isempty())
     {
	  c = oper_stack.pop();
	  postfix_arr[j++] = c;
	  postfix_arr[j++] = ' ';
     }
     postfix_arr[--j] = '\0';
}


main()
{
	expression e;
	e.get_infix_expression ();
	e.convert_to_postfix ();		//for testing can be removed later when whole prgm is finished
	e.display();				//for testing
//	e.evaluate ();
//	e.write_to_file (inputFile);
}


