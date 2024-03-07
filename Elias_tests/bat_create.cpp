#include <iostream>
#include <fstream>
using namespace std;
int main() {

    ofstream f;
    
    f.open("sample.bat",ofstream::out );

    if (f){

        f << "Test //Data aus json\n";

        f << flush;

        f.close();
    }
    else {
       cerr << "Datei konnte nicht geschrieben Werden!" << endl;
       return 1; 
    }
    return EXIT_SUCCESS;
}
