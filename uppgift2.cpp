#include <iostream>
using namespace std;

int main()
{
    int i = 0x12345678;
    cout << "i: " << i << "\n";     //print hex as decimal
    cout << "Address of i: " << &i << "\n";
    
    int * i1 = &i;
    cout << "Address " << i1 << " and value " << *i1 << " of int pointer before casting" << "\n";
    char* p = (char*)&i;  
    // just for checking:           
    int* i2 = (int*)(p);    
    cout << "Address " << i2 << " and value " << *i2 << " of int pointer after casting" << "\n";
    
    cout << "p: " << *p << "\n";    //ascii character AT pointer
    cout << "p_ff: " << p << "\n";  //ascii characters starting at pointer
    int k = *(p+1)+1;               //take 2nd character (V), cast to int (86) and add '1' (+1 = 87)
    cout << "k: " << k;
    return 0;
}
