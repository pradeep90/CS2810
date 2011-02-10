/*
  Title : Big Integer Implementation in C++

  Author : S. Pradeep Kumar
  Date : 16 - 01 - 2011


  To compile:
  Use makefile

  To do:

  * Check input string for non-numeral characters
  * Make from_integer more efficient by inserting after iterator instead of push_back ()
  * Make each node hold 8 digits

  */

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "llist.h"

using namespace std;

class BigInt
{
private:
     IntList l;
     bool sign;
     string str[1000];
public:     
     int len;			// Len of number, excluding preceding zeros, if any
     BigInt () { len = 0; sign = 0; };
     ~BigInt () {};

     // Accessors
     string to_string (int a = 0);
     int length ();
     
     // Modifiers
     void from_string (string str);
     void from_integer (int n);
     
     void add (BigInt a, BigInt b);
     void subtract (BigInt a, BigInt b, int cmp = -1);
     void multiply (BigInt a, BigInt b);
     BigInt division (BigInt a, BigInt b);
     void negation ();
     void factorial ();
     bool operator>= (BigInt b);
     // void operator=(BigInt a);
     
};

// void BigInt::operator=(BigInt a)
// {
//      l.clear ();
     
// }


string BigInt::to_string(int a)
{
     // Parameter a - if non-zero, don't remove preceding zeros
     string s = "";
     
     for (IntList::Iterator iter = l.begin(); iter != l.end (); ++iter){
	  s.insert (s.begin(), *iter + '0');
     }
     int i = 0;

     if (!a){
	  // Remove preceding zeros
	  string::iterator siter = s.begin ();
	  while (*siter == '0'){
	       i++;
	       siter++;
	  }
	  s.erase (0, i);
     }
     
     if (sign)
	  s.insert (s.begin(), '-');
     if (s == "")
	  return "0";
     return s;
}

void BigInt::from_string (string str)
{
     // Will not accept -ve nos properly
     l.clear();
     sign = 0;
     len = 0;
     
     if (str[0] == '-'){
	  sign = 1;
	  str.erase (0, 1);
     }
     else if (str[0] == '+')
	  str.erase (0, 1);
     
     string::iterator iter = str.begin ();
     while (*iter == '0')
	  iter++;
     for (; iter < str.end(); iter++){
	  len++;
     }
     for (iter = str.begin (); iter < str.end(); iter++){
	  l.push_front(int (*iter - int('0'))); // Change this!!
     }
}


int BigInt::length ()
{
     string s = to_string ();
     if (s[0] == '+' || s[0] == '-')
	  return (len = s.length () - 1);
     else
	  return (len = s.length ());
}

void BigInt::from_integer (int n)
{
     l.clear ();
     sign = 0;
     len = 0;
     int curr;
     
     while (n > 0){
	  curr = n % 10;
	  n = n / 10;
	  l.push_back (curr);
	  len++;
     }
     
}

bool BigInt::operator>= (BigInt b)
{
     len = length ();
     b.len = b.length ();
     
     // cout << "Comparison : " << len << b.len << endl;
     if (len > b.len)
	  return 1;
     else if (len < b.len)
	  return 0;

     IntList::Iterator dig_a, dig_b, end_dig;
     dig_a = l.rev_begin ();
     dig_b = b.l.rev_begin ();
     end_dig = l.rev_end ();

     while (*dig_a == 0)
	  --dig_a;
     
     while (*dig_b == 0)
	  --dig_b;

     while (dig_a != end_dig && dig_b != end_dig && *dig_a == *dig_b){
	  --dig_a;
	  --dig_b;
     }

     if ((dig_a == end_dig && dig_b == end_dig) || *dig_a > *dig_b)
	  return 1;
     else
	  return 0;
}


void BigInt::add (BigInt a, BigInt b)
{
     l.clear ();
     sign = 0;

     if (a.l.empty ())
	  *this = b;
     else if (b.l.empty ())
	  *this = a;
     else{
	  
	  IntList::Iterator dig_a, dig_b;
	  int dsum, carry = 0;

	  dig_a = a.l.begin ();
	  dig_b = b.l.begin ();
     
	  while (dig_a != a.l.end() && dig_b != b.l.end()){
	       dsum = *dig_a + *dig_b + carry;
	       carry = dsum / 10;
	       dsum = dsum % 10;
	       l.push_back (dsum);
	       ++dig_a;
	       ++dig_b;
	  }

     
	  while (dig_a != a.l.end()){
	       dsum = *dig_a + carry;
	       carry = dsum / 10;
	       dsum = dsum % 10;
	       l.push_back (dsum);
	       ++dig_a;
	  }

	  while (dig_b != b.l.end()){
	       dsum = *dig_b + carry;
	       carry = dsum / 10;
	       dsum = dsum % 10;
	       l.push_back (dsum);
	       ++dig_b;

	  }

	  if (carry)
	       l.push_back (carry);
     }
     
}

void BigInt::subtract (BigInt a, BigInt b, int cmp)
{
     l.clear ();
     sign = 0;
     
     if (a.l.empty ()){
	  *this = b;
	  sign = 1;
     }
     else if (b.l.empty ())
	  *this = a;
     else{
	  bool flag;
	  IntList::Iterator dig_a, dig_b, end_dig;
	  int diff, borrow = 0;

	  switch (cmp){
	  case -1:			// In case, comparison has not been done
	       flag = (a >= b);
	       // cout << "a ? b" << endl;
	       // cout << a.to_string () << endl;
	       // cout << b.to_string () << endl;
	       // cout << "Flag : " << flag << " " << (a >= b) << endl;
	       if (flag){
		    this->subtract (a, b, 1);
		    // cout << to_string () << endl;
	       }
	       else{
		    this->subtract (b, a, 1);
		    // cout << to_string () << endl;
		    sign = 1;
	       }
	       break;
	  case 0:			// b > a
	       // cout << "a < b" << endl;
	       // cout << a.to_string () << endl;
	       // cout << b.to_string () << endl;
	       this->subtract (b, a, 1);
	       // cout << to_string () << endl;
	       sign = 1;
	       break;
	  case 1:			// When a >= b
	       // cout << "a >= b" << endl;
	       // cout << a.to_string () << endl;
	       // cout << b.to_string () << endl;

	       dig_a = a.l.begin ();
	       dig_b = b.l.begin ();
	       end_dig = a.l.end ();
     
	       while (dig_a != end_dig && dig_b != end_dig){
		    diff = *dig_a - *dig_b - borrow;
		    if (diff < 0){
			 borrow = 1;
			 diff += 10;
		    }
		    else{
			 borrow = 0;
		    }
	  
		    l.push_back (diff);
		    ++dig_a;
		    ++dig_b;
	       }

	       // if (dig_a == end_dig && dig_b == end_dig && borrow == 1)
	       //      sign = 1;
	       while (dig_a != end_dig){
		    diff = *dig_a - borrow;
		    if (diff < 0){
			 borrow = 1;
			 diff += 10;
		    }
		    else{
			 borrow = 0;
		    }
		    l.push_back (diff);
		    ++dig_a;
	       }
	       break;
	  }
     }
     
     // from_string (to_string ());
     
}


void BigInt::multiply (BigInt a, BigInt b)
{
     l.clear();
     sign = 0;
     if (a.l.empty () || b.l.empty ())
	  *this = a;
     else{
	  
	  string s = a.to_string ();
	  string s2;
	  for (string::iterator iter = s.begin(); iter != s.end(); ++iter)
	       s2.insert (s2.begin(), *iter);
     
	  a.from_string (s2);
     
	  IntList::Iterator dig_a, dig_b, prev_dig_b, prev_dig_a;
	  int dprod, carry = 0, i, j;
	  int len_a = (a.to_string (1)).length ();
	  // Non-zero parameter because a = 100 would be reversed to 001.
	  // Therefore, 3 is the len, not 1
	  int len_b = (b.to_string (1)).length ();
	  // Here too, Non-zero parameter because b might be 0011 and b.len
	  // should be 4 not 2. We are checking for b.l.end ()
     
	  dig_a = a.l.begin ();
	  dig_b = b.l.begin ();
	  prev_dig_a = a.l.begin ();
	  prev_dig_b = b.l.begin ();
     
	  for (i = 0; i< len_b + len_a; i++){
	       dig_a = a.l.begin ();
	       dprod = carry;
	       dig_b = prev_dig_b;

	       for (j = 0; j < len_a - i - 1; j++)
		    ++dig_a;
	       while (dig_a != a.l.end() && dig_b != b.l.end()){
		    dprod += (*dig_a) * (*dig_b);
		    ++dig_a;
		    ++dig_b;
	       }

	       carry = dprod / 10;
	       dprod = dprod % 10;
	  
	  
	       l.push_back (dprod);

	       if (i >= len_a - 1)
		    ++prev_dig_b;
	  }
     }
     
}

BigInt BigInt::division (BigInt a, BigInt b)
{
     l.clear();
     sign = 0;
     bool flag = 0, first = 1;


     IntList::Iterator dig_a, end_dig = a.l.rev_end ();
     dig_a = a.l.rev_begin ();
     a.len = a.length ();
     b.len = b.length ();

     BigInt c, psum, temp, rem, divisor, sum;
     divisor = b;
     rem.from_integer (0);
     c.from_integer (10);
     psum.from_integer (0);
     temp.from_integer (0);

     // cout << rem.to_string () << endl;
     // cout << c.to_string () << endl;
     // cout << temp.to_string () << endl;
     if (a.l.empty ()){
	  *this = temp;
	  return temp;
     }
     if (b.l.empty ()){
	  cout << "Error : Divide by Zero!" << endl;
     }
     

     int quo, carry = 0, i, j, ctr;

     while (1){
	  // this->l.print ();
	  psum = rem;
	  temp.from_integer (0);
	  first = 1;
	  while (!(psum >= divisor)){
	       if (dig_a == end_dig){
		    flag = 1;
		    rem.add (rem, temp);
		    break;
	       }
	       if (first){
		    first = 0;
	       }
	       else
		    this->l.push_front (0);
	       rem.multiply (rem, c);
	       temp.l.push_front (*dig_a);
	       psum.add (rem, temp);
	       --dig_a;
	  }
	  if (flag){
	       break;
	  }
	  sum.from_integer (0);
	  ctr = 0;
	  
	  while (psum >= sum){
	       sum.add (sum, divisor);
	       ctr++;
	  }
	  sum.subtract (sum, divisor);
	  ctr--;
	  this->l.push_front (ctr);
	  // cout << "Rem : " << rem.to_string () << endl;
     	  // cout << "temp : " << temp.to_string () << endl;
	  rem.subtract (psum, sum);
     }
     
     // while (dig_a != end_dig){
     // 	  temp.l.clear ();
     // 	  temp.sign = 0;
     // 	  rem.multiply (rem, c);
     // 	  cout << "Rem : " << rem.to_string () << endl;
     // 	  i = 0;
     // 	  d.from_integer (0);
     // 	  while (dig_a != end_dig && !(d >= b)){
     // 	       temp.l.push_front (*dig_a);
     // 	       d.add (rem, temp);
     // 	       --dig_a;
     // 	       i++;
     // 	  }
     // 	  cout << "temp : " << temp.to_string () << endl;
     // 	  d.add (temp, rem);
     // 	  // if (i < b.len){
     // 	  //      temp.add (rem, temp);
     // 	  //      // flag = 1;
     // 	  //      // break;
     // 	  // }
     // 	  if (!(d >= b)){
     // 	       if (dig_a == end_dig){ // End of story
     // 		    rem.add (rem, temp);
     // 		    flag = 1;
     // 		    break;
     // 	       }
     // 	       temp.l.push_front (*dig_a);
     // 	       --dig_a;
     // 	  }
     // 	  temp.add (temp, rem);
     // 	  cout << "Comp : " << (temp >= b) << endl;
     // 	  div = b;
     // 	  quo = 0;
     // 	  while (temp >= div){
     // 	       div.add (div, b);
     // 	       quo++;
     // 	  }
     // 	  div.subtract(div, b);
     // 	  rem.subtract (temp, div);
     // 	  l.push_front (quo);
     // }

     // cout << "Quo : " << quo << endl;
     // cout << rem.to_string () << endl;
     return rem;
}


void BigInt::negation ()
{
     sign = ~sign;
}

void BigInt::factorial ()
{
     BigInt fact, temp, temp2;
     fact.from_integer (1);
     temp.from_integer (1);     
     temp2.from_integer (1);
     string s = to_string ();
     int num = atoi (s.c_str ());
     
     for (int i = 1; i <= num; i++){
	  temp.from_integer (i);
	  temp2.multiply (fact, temp);
	  fact = temp2;
	  
     }
     *this = fact;
     
}
     
void get_next_input (fstream &infile ,string &str)
{
     getline (infile, str, '$');
     int found = str.find_first_of('\n');
     while (found != string::npos)
     {
	  str.erase (found, 1);
	  found = str.find_first_of('\n',found);
     }
}


int main()
{
     BigInt a, b, c;
     // a.from_integer (1);
     // b.from_integer (245);
     // c.from_integer (123);
     // cout << "Comp : " << endl;
     // cout << (a >= a) << endl;
     // cout << (a >= b) << endl;
     // cout << (a >= c) << endl;
     // cout << (b >= b) << endl;
     // cout << (b >= c) << endl;
     // cout << (c >= c) << endl;
     
     // a.from_string (string ("208340928"));
     // b.from_string (string ("2049823424"));
     // a.from_string (string ("100"));
     // b.from_string (string ("1224"));
     a.from_string (string ("100"));
     b.from_string (string ("100000000000220000000000040000000000039824200000000000432"));
     // (- 1224398242432.0 (* 5 240982409100.0))
     BigInt d;
     string s;
     for (int i = 0; i < 3; i++) {
     	  cout << "Enter a : " << endl;
     	  cin >> s;
     	  a.from_string (s);
     	  cout << "Enter b : " << endl;
     	  cin >> s;
     	  b.from_string (s);
	  d = c.division (b, a);
	  cout << "Quotient : " << c.to_string () << endl;
	  cout << "Remainder : " << d.to_string () << endl;
     }
     
     c.add (a, b);
     cout << c.to_string () << endl;
     c.subtract (b, c);
     cout << c.to_string () << endl;
     c.subtract (a, b);
     cout << "Subtract : " << c.to_string () << endl;
     // c.subtract (b, a);
     // cout << "Subtract : "<< c.to_string () << endl;
     c.multiply (b, a);
     cout << c.to_string () << endl;
     c.negation ();
     cout << c.to_string () << endl;
     c.from_integer (10);
     cout << c.to_string () << endl;
     c.factorial ();
     cout << c.to_string () << endl;
     
     fstream infile, outfile;
     infile.open ("inputFile");
     outfile.open ("outputFile", fstream::out);
     
     infile >> s;
     cout << "Input : " << s << endl;
     
     int i = 1;
     time_t time1, time2, t_taken;
     
     
     while ( s != "$"){
	  if (s == "+"){
	       get_next_input (infile, s);
	       cout << "Input : " << s << endl;
	       a.from_string (s);
	       get_next_input (infile, s);
	       cout << "Input : " << s << endl;
	       b.from_string (s);
	       time1 = time (NULL);
	       c.add (a, b);
	       time2 = time (NULL);
	       t_taken = time2 - time1;
	  }
	  else if (s == "-") {
	       get_next_input (infile, s);
	       cout << "Input : " << s << endl;
	       c.from_string (s);
	       time1 = time (NULL);
	       c.negation ();
	       time2 = time (NULL);
	       t_taken = time2 - time1;
	  }
	  else if (s == "*") {
	       get_next_input (infile, s);
	       cout << "Input : " << s << endl;
	       a.from_string (s);
	       get_next_input (infile, s);
	       cout << "Input : " << s << endl;
	       b.from_string (s);
	       time1 = time (NULL);
	       c.multiply (a, b);
	       time2 = time (NULL);
	       t_taken = time2 - time1;
	  }
	  else if (s == "!") {
	       get_next_input (infile, s);
	       cout << "Input : " << s << endl;
	       c.from_string (s);
	       time1 = time (NULL);
	       c.factorial ();
	       time2 = time (NULL);
	       t_taken = time2 - time1;
	  }

	  outfile << i++ << endl;
	  outfile << t_taken << endl;
	  cout << "Time : " << t_taken << endl;
	  outfile << c.to_string () << '$' << endl;
	  cout << c.to_string () << '$' << endl;
	  infile >> s;
     }

     return 0;
     
}



