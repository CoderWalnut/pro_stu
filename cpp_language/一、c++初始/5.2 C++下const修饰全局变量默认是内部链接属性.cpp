#include<iostream>
using namespace std;

int main(){

	extern const int g_b;

	cout << "g_b = " << g_b << endl;;

	return EXIT_SUCCESS;
}