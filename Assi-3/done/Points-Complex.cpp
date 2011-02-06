//////////////////////////////////////////
// - Print distance only up to 2 digits //
//////////////////////////////////////////

#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

class Pair
{
     int x, y;
public:
     Pair ();
     Pair (int inp_x, int inp_y);
     void set_value (int inp_x, int inp_y);
     int get_x ();
     int get_y ();
};

class Point : public Pair
{
public:
     Point () : Pair () { };
     
     Point (int inp_x, int inp_y) : Pair (inp_x, inp_y) { };
     void print_distance_from_point (Point p1);
     void print_distance_from_origin ();
     void print_Point ();
};



class Complex_Number : public Pair
{
public:
     Complex_Number () : Pair () { };
     Complex_Number (int inp_x, int inp_y) : Pair (inp_x, inp_y) { };

     Complex_Number operator+ (Complex_Number c) ;
     Complex_Number operator- (Complex_Number c) ;
     Complex_Number Conjugate ();
     void print_Complex_Number ();
};

Pair::Pair ()
{
     x = 0;
     y = 0;
}

Pair::Pair (int inp_x, int inp_y)
{
     set_value (inp_x, inp_y);
}

void Pair::set_value (int inp_x, int inp_y)
{
     x = inp_x;
     y = inp_y;
}

int Pair::get_x ()
{
     return x;
}

int Pair::get_y ()
{
     return y;
}


void Point::print_distance_from_point (Point p1)
{
     float dist;
     dist = (p1.get_x () - (*this).get_x ()) * (p1.get_x () - (*this).get_x ()) + (p1.get_y () - (*this).get_y ()) * (p1.get_y () - (*this).get_y ());
     dist = sqrt (dist);
     printf ("Dist = %.2f\n", dist);
     // return dist;
}

void Point::print_distance_from_origin ()
{
     Point origin (0, 0);
     print_distance_from_point (origin);
}

void Point::print_Point ()
{
     printf ("(%d, %d)\n", get_x (), get_y ());
}
     
Complex_Number Complex_Number::operator+ (Complex_Number c)
{
     Complex_Number temp;
     temp.set_value (c.get_x () + this->get_x (), c.get_y () + this->get_y ());
     return temp;
}

Complex_Number Complex_Number::operator- (Complex_Number c)
{
     Complex_Number temp;
     temp.set_value (c.get_x () - this->get_x (), c.get_y () - this->get_y ());
     return temp;
}

Complex_Number Complex_Number::Conjugate ()
{
     Complex_Number temp;
     temp.set_value (get_x (), 0 - get_y () );
     return temp;
}

void Complex_Number::print_Complex_Number ()
{
     printf ("%d%+di\n", get_x (), get_y ());
}


int main ()
{
     Point p1 (3, 0);
     Point p2;
     p2.set_value (0, 4);
     
     p1.print_Point ();
     p2.print_Point ();

     p1.print_distance_from_point (p2) ;
     p1.print_distance_from_origin () ;
     p2.print_distance_from_origin () ;

     Complex_Number c1 (3, 4), c2;
     c2.set_value (-6, -8);

     c1.print_Complex_Number ();
     c2.print_Complex_Number ();
     (c2.Conjugate ()).print_Complex_Number ();
}

     
     
	       
