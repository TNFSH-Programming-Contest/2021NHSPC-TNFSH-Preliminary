// magic.cpp
// By xiplus
#include <bits/stdc++.h>
using namespace std;
int main() {
	mt19937 mt1(7296546);
	for (int i = 0; i < 5; i++) {
		printf("%c", mt1() % 26 + 97);
	}
	printf(", ");

	mt19937 mt2(21535470);
	for (int i = 0; i < 5; i++) {
		printf("%c", mt2() % 26 + 97);
	}
	printf("\n");
}
