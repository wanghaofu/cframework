#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int irand(int maxnum);
void saizi();
int main()
{
  cout << "hi";
  int i=0;
  for(i;i<=10;i++)
  {
    //sleep(1);
   // irand(29);
    if(i%3)
    {
      for(int j=1; j<=i;j++)
      {
        cout << "-";
      }
      cout << endl;
    }
    cout << i;
    cout << endl;
  }
  saizi();
}

int irand(int maxnum)
{
  srand( (unsigned)time( NULL ) );
  int s;
  s= rand()%maxnum;
  cout <<s<<endl;
  return s;
}

void saizi()
{
  for( int counter = 1; counter <= 20; counter++ )
  {
    cout << setw( 10 ) << ( 1 + rand() % 6 );

    if( counter % 5 == 0 )
       cout << endl ;
  }
}
