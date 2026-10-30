#include <stdio.h>


char _chars[255];

int isupper1(unsigned char c);
int isupper2(unsigned char c);

int main() {
	for(int i = 65; i <= 90; i++) {
		_chars[i] = 1;
	}

	return 0;
}

//save time but neeed many space
int isupper1(unsigned char c) {
	return _chars[c] & 1;
}

//save space but need more time (3 comparison)
int isupper2(unsigned char c) {
	return (c >= 65 && c <= 90) ? 1:0;
}
