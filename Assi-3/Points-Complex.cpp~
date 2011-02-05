#include<iostream>
#include<cmath>

using namespace std;

class real_no
{
protected:
     float x;
     float y;
public:
     real_no(){}
     real_no(float a,float b) {x=a;y=b;}
     float get_x();
     float get_y();
};

float real_no::get_x()
{
     return x;
}

float real_no::get_y()
{
     return y;
}

class complex_no : public real_no
{
public:
     complex_no(){}
     void insert_data();
     complex_no(float a, float b):real_no(a,b){}
     complex_no operator+(complex_no &r);
     complex_no operator-(complex_no &r);
//	complex_no add(complex_no q);
//	complex_no sub(complex_no q);
     complex_no conjugate();
     void print_no();
};

complex_no complex_no::conjugate()
{
     return(complex_no(x,-y));
}

void complex_no::print_no()
{
     cout<<x<<" ";
     if(y>0)
	  cout<<"+ "<<y<<"i"<<endl;
     else
	  cout<<y<<"i"<<endl;
}

complex_no complex_no::operator+(complex_no &r)
{
     return( complex_no(x+r.get_x() , y+r.get_y()));
}

complex_no complex_no::operator-(complex_no &r)
{
     return( complex_no(x-r.get_x() , y-r.get_y()));
}


void complex_no::insert_data()
{
//	cout<<"Enter real & imaginary parts"<<endl;
     cin>>x;
     cin>>y;
}

class point : public real_no
{
public:
     point(){}
     void set_data();
     point(float a, float b):real_no(a,b) {}
     void calculate_dist(point);
};

void point::set_data()
{
//	cout<<"Enter coordinates"<<endl;
     cin>>x;
     cin>>y;
}

void point::calculate_dist(point a2)
{
     float q,x2,y2;

     x2=a2.get_x();
     y2=a2.get_y();

     q = sqrt((x-x2)*(x-x2) + (y-y2)*(y-y2));
     cout<<q<<endl;
}

int main()
{
     int c=0,d=0;
     float x1,x2,y1,y2;
     point a,b,e;
     complex_no x,y,z;

     while(c!=3)
     {
	  cout<<"Press 1 for dealing with points '\n' Press 2 for dealing with complex numbers'\n' Press 3 to quit'\n'"<<endl;
	  cin>>c;

	  switch(c)
	  {
	  case 1:
	       while(d!=3)
	       {
		    cout<<"'\n'Press 1 if you want to find distance btw 2 points'\n' Press 2 for distance btw a point and origin'\n' Press 3 to go back'\n'"<<endl;
		    cin>>d;
		
		    switch(d)
		    {
		    case 1:
		    {
			 cout<<"Enter coordinates of 1st point"<<endl;
//					point a,b;
			 a.set_data();
			 cout<<"Enter coordinates of 2nd points"<<endl;
			 b.set_data();
			 a.calculate_dist(b);
		    }
		    break;

		    case 2:
		    {
			 cout<<"Enter coordinates"<<endl;
//					point c;
			 e.set_data();
			 point t(0,0);
			 e.calculate_dist(t);
		    }
		    break;


		    case 3:
			 break;
		    }
	       }
	       break;

	  case 2:
	  {
	       while(d!=4)
	       {
		    cout<<"'\n'Press 1 if you want to add 2 complex numbers'\n' Press 2 for subtraction'\n' Press 3 to find conjugate'\n' Press 4 to go back'\n'"<<endl;
		    cin>>d;
	
		    switch(d)
		    {
		    case 1:
		    {
			 cout<<"Enter 1st number's real & imaginary part"<<endl;
//						complex_no a,b,c;
			 x.insert_data();
			 cout<<"Enter 2nd number's real & imaginary part"<<endl;
			 y.insert_data();
			 z = x+y;
			 z.print_no();
		    }
		    break;

		    case 2:
		    {
			 cout<<"Enter 1st number's real & imaginary part"<<endl;
//							complex_no a,b,c;
			 x.insert_data();
			 cout<<"Enter 2nd number's real & imaginary part"<<endl;
			 y.insert_data();
			 z = x-y;
			 z.print_no();
			 break;
		    }
		    case 3:
			 cout<<"Enter real & imaginary part"<<endl;
			 x.insert_data();
			 x.conjugate().print_no();

		    case 4:
			 break;
		    }
	       }
	       break;
	  }
	  case 3:
	       break;
	  }
     }
}
