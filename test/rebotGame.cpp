#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void moveTortoise(int *);
void moveHare(int *);
int irand(int);
int tzs = 1;
int wgs = 1;
int *tzPtr;
int *wgPtr;

bool status;
int main()
{
    tzPtr = &tzs;
    wgPtr = &wgs;
    status = true;
    cout << "BANG !!!!!" << endl;
    cout << "AND THEY'RE OFF !!!!!" << endl;
    int allNum = 0;
    int wgNum = 0;
    int tzNum = 0;
    const int  LINE = 70;
    while (status == true)
    {
        moveTortoise(wgPtr);
        moveHare(tzPtr);
        for (int runStep = 1; runStep <= LINE; runStep++ )
        {
            if (*tzPtr == runStep && *wgPtr != runStep )
            {
                cout << "H";
            }
            else
            {
                cout << " ";
            }
            if (*wgPtr == runStep && *tzPtr != runStep )
            {
                cout << "T" ;
            }
            else
            {
                cout << " ";
            }
            if (*wgPtr == runStep && *tzPtr == runStep )
            {
                cout << "OUCH!!!";
            }
            else
            {
                cout << " ";
            }

        }
        cout << endl;
        if (*wgPtr == 70 && *tzPtr != 70 )
        {
            ++wgNum;
            ++allNum;
            cout << "TORTOISE WINS!!!YAY!!!";
            status = false;
        }
        else if (*tzPtr == 70 && *wgPtr != 70)
        {
            ++tzNum;
            ++allNum;
            cout << "Hare wins. Yuch.";
            status = false;
        }
        else if (*tzPtr == 70 && *wgPtr == 70 )
        {
            ++allNum;
            cout << "It's a tie";
            status = false;
        }
        usleep(200000);
        if ( status == false && allNum < 3)
        {
            *tzPtr = 1;
            *wgPtr = 1;
            status = true;
            cout << endl << "  Game over !  Restarting...." << endl ;

        }
        if (status == false && allNum == 3)
        {
            cout << endl << "AllNum [" << allNum << "] : tzNum VS wgNum  [" << tzNum << "] ： [" << wgNum << "]" << endl;
        }
    }
}

void moveTortoise(int *wgPtr)
{
    int hrn = irand(10);
    if (hrn >= 1 && hrn <= 5 )
    {
        *wgPtr += 3;
    }
    else if (hrn >= 6 && hrn <= 7 )
    {
        *wgPtr -= 6;
    }
    else if (hrn >= 8 && hrn <= 10)
    {
        *wgPtr += 1;
    }

    if (*wgPtr <= 0)
    {
        *wgPtr = 1;
    }
    if (*wgPtr > 70)
    {
        *wgPtr = 70;
    }

}

void moveHare(int *tzPtr)
{
    int hrn = irand(10);
    if (hrn >= 1 && hrn <= 2)
    {
        *tzPtr += 0;
    }
    else if (hrn >= 3 && hrn <= 4)
    {
        *tzPtr += 9;
    }
    else if (hrn == 5 )
    {
        *tzPtr -= 12;
    }
    else if (hrn >= 6 && hrn <= 8)
    {
        *tzPtr += 1;
    }
    else if (hrn >= 9 && hrn <= 10)
    {
        *tzPtr -= 2;
    }

    if (*tzPtr < 0)
    {
        *tzPtr = 1;
    }
    if (*tzPtr > 70)
    {
        *tzPtr = 70;
    }



}



int irand(int maxnum)
{
    // srand( (unsigned)time( NULL ) );
    int s;
    //微秒级随机数产生
    struct timeval tpTime;
    float timeuse;
    gettimeofday(&tpTime, NULL);
    srand(tpTime.tv_usec);

    s = rand() % maxnum + 1;
    return s;
}





