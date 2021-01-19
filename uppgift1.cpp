#include <iostream>
using namespace std;

int main()    {
    char s[9] = {'u','p','p','g','i','f','t','1','x','\0'};    // create array for string with 1 extra place
    cout << s << "\n";                              // check string output
    for (int i = 0; i < (sizeof(s)-2)/2; i++)       // only "official" string values, half times (always switch 2)
    {
        s[sizeof(s)-2] = s[i];                      // save first replace value temporarily
        s[i] = s[sizeof(s)-3-i];                    // overwrite first replace value by second             
        s[sizeof(s)-3-i] = s[sizeof(s)-2];          // overwrite second replace value by first from temp
        
        cout << i+1 << ". iteration: " << s << "\n";            // debug info
    }
    for (int j = 0; j < sizeof(s)-2; j++) cout << s[j];         // print result
    return 0;
}