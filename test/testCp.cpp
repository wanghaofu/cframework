#include <iostream>
#include <string>

using namespace std;

class t
{
public:
    t();
    ~t();
    int setYear(int);
    int getYear() const;
private:
    int year;
};

void printYear(t &);

int main()
{
    t iit;
    printYear(iit);
}


t::t() {}
t::~t()
{
    year = 0;
}
int t::setYear(int y)
{
    year = y;
}
int t::getYear() const
{
    return year;
}
void printYear(t &it)
{
    it.setYear(2013);
    int s;
    s = it.getYear();
    cout << "Current year is :" << s << endl;
}
