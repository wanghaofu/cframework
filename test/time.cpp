#include  <iostream>
//#include <cstdlib>
#include <time.h>
//#include <unistd.h>  // include the sleep function

using namespace std;

int main()
{
    time_t itime;
    time(&itime);
    cout << itime;
    int i = 0;
    while ( i <= 1000)
    {
        ++i;
        cout << i << endl;
        sleep(1);
    }
}
