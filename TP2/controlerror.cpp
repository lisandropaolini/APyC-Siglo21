#include <stdexcept>
#include <limits>
#include <iostream>

using namespace std;

void MyFunc(int c)
{
    if (c > numeric_limits< char> ::max())
        throw domain_error("MyFunc argument too large.");
        // throw invalid_argument("MyFunc argument too large.");
    
    //...
}

int main()
{
    try
    {
        MyFunc(256); //cause an exception to throw
    }

    catch (invalid_argument& e)
    {
        return -1;
    } catch (exception& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
    //...
    return 0;
}