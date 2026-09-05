#include <iostream>
using namespace std;
int main() {
    #ifndef DEBUG
    cout << "Che do binh thuong" << endl;
    #else
    cout << "Che do debug" << endl;
    #ifdef VER
    cout << "Version: " << VER << endl;
    #endif
    #endif

    
}
