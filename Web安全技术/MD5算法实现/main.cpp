#include "md5.h"

int main() {
	MD5 md5;       
	int i;
	unsigned char input[1000];
	cin >> input;
	unsigned char output[16];    
	md5.Update(input, strlen((char *)input)); 
	md5.Padding(output);  

	cout << "加密前:" << input << "\n加密后:";
	for (i = 0; i < 16; i++) {
		printf("%02x", output[i]);
	}
	cout << endl;

	system("pause");
	return 0;
}
