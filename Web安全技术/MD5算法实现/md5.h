#pragma once
#ifndef _MD5_H_
#define _MD5_H_

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
//函数F是按逐位方式操作：如果X，那么Y，否则Z
//函数H是逐位奇偶操作符
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
using namespace std;

//向右环移n个单位
#define ROTATELEFT(num, n) (((num) << (n)) | ((num) >> (32 - (n)))) 

#define FF(a, b, c, d, x, s, ac)            \
    {                                       \
        (a) += F((b), (c), (d)) + (x) + ac; \
        (a) = ROTATELEFT((a), (s));         \
        (a) += (b);                         \
    }
#define GG(a, b, c, d, x, s, ac)            \
    {                                       \
        (a) += G((b), (c), (d)) + (x) + ac; \
        (a) = ROTATELEFT((a), (s));         \
        (a) += (b);                         \
    }
#define HH(a, b, c, d, x, s, ac)            \
    {                                       \
        (a) += H((b), (c), (d)) + (x) + ac; \
        (a) = ROTATELEFT((a), (s));         \
        (a) += (b);                         \
    }
#define II(a, b, c, d, x, s, ac)            \
    {                                       \
        (a) += I((b), (c), (d)) + (x) + ac; \
        (a) = ROTATELEFT((a), (s));         \
        (a) += (b);                         \
    }

class MD5 {

public:
	MD5(); //构造函数初始化
	void Update(unsigned char*, unsigned int); //对数据进行分组，并进行加密
	void Padding(unsigned char[16]); //数据填充
	void Transform(unsigned int[4], unsigned char[64]); //轮换操作函数
	void Encode(unsigned char*, unsigned int*, unsigned int); //加密信息变为字符
	void Decode(unsigned int*, unsigned char*, unsigned int); //把字符变为数字
private:
	unsigned int count[2]; //记录数据位数
	unsigned int regist[4]; //记录用于保存对512bits信息加密的中间结果或者最终结果 
	unsigned char buffer[64]; //512位缓冲区
	unsigned char PADDING[64] = { 0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //用于数据填充
};

#endif