#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
	int f[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
		    int n=i+j;
		    if (n%2==0){
		        f[i][j]=0;
		    }
			cout << f[i][j]<<endl;
		}
	}



}
