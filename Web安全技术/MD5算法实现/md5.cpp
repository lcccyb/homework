#include "md5.h"

//初始化
MD5::MD5() {
	count[0] = 0;
	count[1] = 0;
	regist[0] = 0x67452301;
	regist[1] = 0xEFCDAB89;
	regist[2] = 0x98BADCFE;
	regist[3] = 0x10325476;
}

void MD5::Update(unsigned char* input, unsigned int len) {
	unsigned int i = 0, index = 0, templen = 0;

	//当前状态的位数对64取余
	index = (count[0] / 8) % 64;

	templen = 64 - index;

	//解决unsignde int无法储存极大数据导致溢出的问题
	count[0] += len * 8;

	if (count[0] < (len * 8)) {
		count[1]++;
	}

	count[1] += len >> 29;

	//当其输入字节数大于其可以补足64字节的字节数，进行补足
	if (len >= templen) {
		memcpy(&buffer[index], input, templen);
		Transform(regist, buffer);

		for (i = templen; i + 64 <= len; i += 64) {
			Transform(regist, &input[i]);
		}
		index = 0;
	}
	else {
		i = 0;
	}

	//放置剩余数据
	memcpy(&buffer[index], &input[i], len - i);
}

void MD5::Padding(unsigned char digest[16]) {
	unsigned int index = 0, len = 0;
	unsigned char bits[8];

	index = (count[0] / 8) % 64;
	len = (index < 56) ? (56 - index) : (120 - index);

	Encode(bits, count, 8);

	//在信息的后面填充一个1和无数个0
	Update(PADDING, len);

	Update(bits, 8);

	Encode(digest, regist, 16);
}

void MD5::Transform(unsigned int regist_[4], unsigned char block[64]) {
	unsigned int a = regist_[0];
	unsigned int b = regist_[1];
	unsigned int c = regist_[2];
	unsigned int d = regist_[3];

	unsigned int x[16];
	Decode(x, block, 64);

	// Round 1 
	FF(a, b, c, d, x[0], S11, 0xd76aa478);
	FF(d, a, b, c, x[1], S12, 0xe8c7b756);
	FF(c, d, a, b, x[2], S13, 0x242070db);
	FF(b, c, d, a, x[3], S14, 0xc1bdceee);
	FF(a, b, c, d, x[4], S11, 0xf57c0faf);
	FF(d, a, b, c, x[5], S12, 0x4787c62a);
	FF(c, d, a, b, x[6], S13, 0xa8304613);
	FF(b, c, d, a, x[7], S14, 0xfd469501);
	FF(a, b, c, d, x[8], S11, 0x698098d8);
	FF(d, a, b, c, x[9], S12, 0x8b44f7af);
	FF(c, d, a, b, x[10], S13, 0xffff5bb1);
	FF(b, c, d, a, x[11], S14, 0x895cd7be);
	FF(a, b, c, d, x[12], S11, 0x6b901122);
	FF(d, a, b, c, x[13], S12, 0xfd987193);
	FF(c, d, a, b, x[14], S13, 0xa679438e);
	FF(b, c, d, a, x[15], S14, 0x49b40821);

	// Round 2 
	GG(a, b, c, d, x[1], S21, 0xf61e2562);
	GG(d, a, b, c, x[6], S22, 0xc040b340);
	GG(c, d, a, b, x[11], S23, 0x265e5a51);
	GG(b, c, d, a, x[0], S24, 0xe9b6c7aa);
	GG(a, b, c, d, x[5], S21, 0xd62f105d);
	GG(d, a, b, c, x[10], S22, 0x2441453);
	GG(c, d, a, b, x[15], S23, 0xd8a1e681);
	GG(b, c, d, a, x[4], S24, 0xe7d3fbc8);
	GG(a, b, c, d, x[9], S21, 0x21e1cde6);
	GG(d, a, b, c, x[14], S22, 0xc33707d6);
	GG(c, d, a, b, x[3], S23, 0xf4d50d87);
	GG(b, c, d, a, x[8], S24, 0x455a14ed);
	GG(a, b, c, d, x[13], S21, 0xa9e3e905);
	GG(d, a, b, c, x[2], S22, 0xfcefa3f8);
	GG(c, d, a, b, x[7], S23, 0x676f02d9);
	GG(b, c, d, a, x[12], S24, 0x8d2a4c8a);

	// Round 3 
	HH(a, b, c, d, x[5], S31, 0xfffa3942);
	HH(d, a, b, c, x[8], S32, 0x8771f681);
	HH(c, d, a, b, x[11], S33, 0x6d9d6122);
	HH(b, c, d, a, x[14], S34, 0xfde5380c);
	HH(a, b, c, d, x[1], S31, 0xa4beea44);
	HH(d, a, b, c, x[4], S32, 0x4bdecfa9);
	HH(c, d, a, b, x[7], S33, 0xf6bb4b60);
	HH(b, c, d, a, x[10], S34, 0xbebfbc70);
	HH(a, b, c, d, x[13], S31, 0x289b7ec6);
	HH(d, a, b, c, x[0], S32, 0xeaa127fa);
	HH(c, d, a, b, x[3], S33, 0xd4ef3085);
	HH(b, c, d, a, x[6], S34, 0x4881d05);
	HH(a, b, c, d, x[9], S31, 0xd9d4d039);
	HH(d, a, b, c, x[12], S32, 0xe6db99e5);
	HH(c, d, a, b, x[15], S33, 0x1fa27cf8);
	HH(b, c, d, a, x[2], S34, 0xc4ac5665);

	// Round 4 
	II(a, b, c, d, x[0], S41, 0xf4292244);
	II(d, a, b, c, x[7], S42, 0x432aff97);
	II(c, d, a, b, x[14], S43, 0xab9423a7);
	II(b, c, d, a, x[5], S44, 0xfc93a039);
	II(a, b, c, d, x[12], S41, 0x655b59c3);
	II(d, a, b, c, x[3], S42, 0x8f0ccc92);
	II(c, d, a, b, x[10], S43, 0xffeff47d);
	II(b, c, d, a, x[1], S44, 0x85845dd1);
	II(a, b, c, d, x[8], S41, 0x6fa87e4f);
	II(d, a, b, c, x[15], S42, 0xfe2ce6e0);
	II(c, d, a, b, x[6], S43, 0xa3014314);
	II(b, c, d, a, x[13], S44, 0x4e0811a1);
	II(a, b, c, d, x[4], S41, 0xf7537e82);
	II(d, a, b, c, x[11], S42, 0xbd3af235);
	II(c, d, a, b, x[2], S43, 0x2ad7d2bb);
	II(b, c, d, a, x[9], S44, 0xeb86d391);

	regist_[0] += a;
	regist_[1] += b;
	regist_[2] += c;
	regist_[3] += d;
}

void MD5::Encode(unsigned char* output, unsigned int* input, unsigned int len) {
	unsigned int i = 0, j = 0;
	while (j < len) {
		//把数字的8、8-16、16-24、24-32分别赋值给字符
		output[j] = input[i] & 0xFF;
		output[j + 1] = (input[i] >> 8) & 0xFF;
		output[j + 2] = (input[i] >> 16) & 0xFF;
		output[j + 3] = (input[i] >> 24) & 0xFF;
		i++;
		j += 4;
	}
}

void MD5::Decode(unsigned int* output, unsigned char* input, unsigned int len) {
	unsigned int i = 0, j = 0;
	while (j < len) {
		//利用位操作，把四个单位为1字节的字符，合成一个单位为4字节的数字
		output[i] = (input[j]) |
			(input[j + 1] << 8) |
			(input[j + 2] << 16) |
			(input[j + 3] << 24);
		i++;
		j += 4;
	}
}