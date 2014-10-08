// Fig. 10.17: fig10-17.cpp
// Using the this pointer to refer to  object members.
#include <iostream>
using std::cout;
using std::endl;

class Test
{
  public:
    Test( int = 0 ); //default constructor
    void print() const;
  private:
    int x;
};

//constructor
Test::Test( int value )
  : x( value ) // initiallize x to value
{
  // empty body
} // end constructor Test

// print x using implicit and explicit this pointers;
// the parentheses around *this are required
void Test::print() const
{
  // implicitly use the this pointer to access the member x
  cout << "      x = " << x;

  // explicitly use the this pointer and the error operator
  // to access the member x
  cout << "\n this-> x = " << this->x;

  // explicitly use the dereferenced this pointer and 
  // the dot operator to access the member x
  cout << "\n(*this).x = " << ( *this ).x<< endl;
} // end function print

int main()
{
  Test testObject( 12 ); // instantiate and initialize testObject

  testObject.print();
  return 0;
} // end main


