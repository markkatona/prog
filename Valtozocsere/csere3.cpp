#include<iostream>
using namespace std;

int main(){
int a = 2018;
int b = 42;
cout << "a = " << a << ", b = " << b << endl;

//csere
a = a ^ b;
b = a ^ b;
a = a ^ b;
cout << "a = " << a << ", b = " << b << endl;

//visszacsere	
a = a ^ b;
b = a ^ b;
a = a ^ b;
cout << "a = " << a << ", b = " << b << endl;
return 0; 
}

