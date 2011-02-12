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

  Pradeep:
  1. ( )

*/


#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include"stack.cpp"
using namespace std;

class expression
{
     char infix_arr[100], postfix_arr[100];
     Stack oper_stack;
     Stack value_stack;
     int value;

public:     
     void get_infix_expression (); 		// Which will get user postfix_arr into infix_str //to be done
     void convert_to_postfix ();   		// Which will convert infix_str to postfix and put result in postfix_str
     int evaluate_postfix_expression ();	//to be done
     void evaluate (){
	  convert_to_postfix ();		//to be done
	  evaluate_postfix_expression ();
     }
     
//     void write_to_file (string filename);	//to be done
     void print ();				// Just cout all the value
     void display();				//cout postfix string, for can be removed after whole prgm is written
};

void expression::print ()
{
     cout << "Values : " << endl;
     cout << infix_arr << endl;
     cout << postfix_arr << endl;
     cout << value << endl;
}


int precedence(char c)
{
     int p;
     switch(c)
     {
     case '(':
	  p=1;
	  break;
     case '-':
	  p=2;
	  break;
     case '+':
	  p=2;
	  break;
		
     case '*':
	  p=3;
	  break;
     case '/':
	  p=3;
	  break;
     case '^':
	  p=4;
	  break;
     }

     return p;
}

int eval_operation (int next_token, int value1, int value2)
{
     int result;
     switch(next_token)
     {
     case '-':
	  return (value1 - value2);
	  break;
     case '+':
	  return (value1 + value2);
	  break;
     case '*':
	  return (value1 * value2);
	  break;
     case '/':
	  return (value1 / value2);
	  break;
     case '^':
	  result = 1;
	  for (int i = 0; i < value2; i++){
	       result *= value1;
	  }
	  return result;
	  break;
     default:
	  cerr << "Invalid operator!" << endl;
     }
}

bool is_operator(char a)
{
     if((a!='*')&&(a!='+')&&(a!='-')&&(a!='/')&&(a!='^')&&(a!='(')&&(a!=')'))
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

     cout<<"Given infix expression : " << infix_arr<<endl;

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
	       c = char (oper_stack.pop());
	       while(c!='(')
	       {
		    postfix_arr[j++] = c;
		    postfix_arr[j++] = ' ';
		    c = char (oper_stack.pop());
	       }
	  }

	  else						// operand
	  {
	       c = infix_arr[i];
	       if(oper_stack.isempty())
		    oper_stack.push(c);
	       else
	       {
		    temp = char (oper_stack.pop());
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
			      temp = char (oper_stack.pop());
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
	  c = char (oper_stack.pop());
	  postfix_arr[j++] = c;
	  postfix_arr[j++] = ' ';
     }
     if (j > 0)
	  postfix_arr[--j] = '\0';
     else
	  postfix_arr[0] = '\0';
}

int expression::evaluate_postfix_expression ()
{
     int i, j, arr_size = strlen (postfix_arr);
     cout << postfix_arr << endl;
     int value1, value2, result;
     int next_token;
     if (arr_size == 0){
	  cerr << "Nothing to evaluate" << endl;
	  this->value = 0;
	  return -1;
     }

     i = 0;
     string s;
     while (i < arr_size){
	  cout << "i : " << i << " postfix_arr[i] : " << postfix_arr[i] << endl;
	  if (postfix_arr[i] == ' ')
	       ;
     	  else if (!is_operator (postfix_arr[i])){
	       s = "";
	       j = i;
	       while (j < arr_size && postfix_arr[j] != ' ')
		    s.push_back (postfix_arr[j++]);
	       i = j; 
	       cout << "s : " << s << endl;
	       next_token = atoi (s.c_str ());
	       value_stack.push (next_token);
	  }
	  else{
	       next_token = postfix_arr[i];
	       cout << "next_token : " << next_token << endl;
	       if (value_stack.get_size () < 2){
		    cerr << "Error : Not enough operands!" << endl;
		    value = -1;
		    return -1;
	       }
	       value2 = value_stack.pop ();
	       value1 = value_stack.pop ();
	       result = eval_operation (next_token, value1, value2);
	       value_stack.push (result);
	  }
	  i++;
     }

     if (value_stack.get_size () == 1){
	  this->value = value_stack.pop ();
     }
     else{
	  cerr << "Error : Not enough operators!" << endl;
	  value = 0;
	  return -1;
     }
}


main()
{
     expression e;
     e.get_infix_expression ();
     // e.convert_to_postfix ();		//for testing can be removed later when whole prgm is finished
     // e.display();				//for testing
     // e.print ();
     e.evaluate ();
     e.print ();
//	e.write_to_file (inputFile);
}


