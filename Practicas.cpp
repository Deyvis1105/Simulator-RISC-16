#include <iostream>
#include <fstream>
#include <string>
#include <math.h>   
#include <stdlib.h> 
#include <cstdint>
#include <vector>

using namespace std;

int main(){
    vector<string> a = {"a", "b"};

    a[0].swap(a.back());

    cout << a[0] << " " << a[1];

    return 0;
}