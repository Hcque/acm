
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    fstream F;
    F.open("test", ios::in);

    // 1
    // string ss;
    // while (getline(F,ss))
    // {
    //     cout << ss << "\n";
    // }

    // char buf[1024];
    // while (F.getline(buf, 1024))
    // {
    //     cout << buf << "\n";
    // }

    // char buf[1024], c;
    // while ( (c = F.get()) != EOF)
    // {
    //     cout << c << "\n";
    // }

    ofstream newF;
    newF.open("test2", ios::ate);
    newF << "666";


}