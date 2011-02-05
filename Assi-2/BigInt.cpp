/*
  Title : Big Integer Implementation in C++

  Author : S. Pradeep Kumar
  Date : 16 - 01 - 2011


  To compile:
  Use makefile

  To do:

  * Check input string for non-numeral characters
  * Make from_integer more efficient by inserting after iterator instead of push_back ()

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
     int len;
     bool sign;
     string str[1000];
public:     
     BigInt () {};
     ~BigInt () {};

     // Accessors
     string to_string (int a = 0);
     
     // Modifiers
     void from_string (string str);
     void from_integer (int n);
     
     void add (BigInt a, BigInt b);
     void multiply (BigInt a, BigInt b);
     void negation ();
     void factorial ();
     // void operator=(BigInt a);
     
};

// void BigInt::operator=(BigInt a)
// {
//      l.clear ();
     
// }


string BigInt::to_string(int a)
{
     string s = "";
     
     for (IntList::Iterator iter = l.begin(); iter != l.end (); ++iter){
	  s.insert (s.begin(), *iter + '0');
     }
     int i = 0;
     
     if (!a){
	  string::iterator siter = s.begin ();
	  while (*siter == '0'){
	       i++;
	       siter++;
	  }
	  s.erase (0, i);
     }
     
     if (sign)
	  s.insert (s.begin(), '-');
     return s;
}

void BigInt::from_string (string str)
{
     l.clear();
     sign = 0;
     
     string::iterator iter;
     for (iter = str.begin(); iter < str.end(); iter++){
	  l.push_front(int (*iter - int('0'))); // Change this!!
     }
}

void BigInt::from_integer (int n)
{
     l.clear ();
     sign = 0;
     
     int curr;
     
     while (n > 0){
	  curr = n % 10;
	  n = n / 10;
	  l.push_back (curr);
     }
     
}


void BigInt::add (BigInt a, BigInt b)
{
     l.clear ();
     
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


void BigInt::multiply (BigInt a, BigInt b)
{
     l.clear();
     sign = 0;
     
     
     string s = a.to_string (1);
     string s2;
     for (string::iterator iter = s.begin(); iter != s.end(); ++iter)
	  s2.insert (s2.begin(), *iter);
     
     a.from_string (s2);
     
     IntList::Iterator dig_a, dig_b, prev_dig_b, prev_dig_a;
     int dprod, carry = 0, i, j;
     int len_a = (a.to_string (1)).length ();
     int len_b = (b.to_string (1)).length ();
     
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
     a.from_string (string ("208340928"));
     b.from_string (string ("2049823424"));
     c.add (a, b);
     cout << c.to_string () << endl;
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
     string s;
     
     infile >> s;
     cout << s << endl;
     
     int i = 1;
     time_t time1, time2, t_taken;
     
     
     while ( s != "$"){
	  if (s == "+"){
	       get_next_input (infile, s);
	       cout << s << endl;
	       a.from_string (s);
	       get_next_input (infile, s);
	       cout << s << endl;
	       b.from_string (s);
	       time1 = time (NULL);
	       c.add (a, b);
	       time2 = time (NULL);
	       t_taken = time2 - time1;
	  }
	  else if (s == "-") {
	       get_next_input (infile, s);
	       cout << s << endl;
	       c.from_string (s);
	       time1 = time (NULL);
	       c.negation ();
	       time2 = time (NULL);
	       t_taken = time2 - time1;
	  }
	  else if (s == "*") {
	       get_next_input (infile, s);
	       cout << s << endl;
	       a.from_string (s);
	       get_next_input (infile, s);
	       cout << s << endl;
	       b.from_string (s);
	       time1 = time (NULL);
	       c.multiply (a, b);
	       time2 = time (NULL);
	       t_taken = time2 - time1;
	  }
	  else if (s == "!") {
	       get_next_input (infile, s);
	       cout << s << endl;
	       c.from_string (s);
	       time1 = time (NULL);
	       c.factorial ();
	       time2 = time (NULL);
	       t_taken = time2 - time1;
	  }

	  outfile << i++ << endl;
	  outfile << t_taken << endl;
	  outfile << c.to_string () << '$' << endl;
	  infile >> s;
     }

     return 0;
     
}



