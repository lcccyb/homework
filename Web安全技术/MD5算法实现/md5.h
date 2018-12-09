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
//����F�ǰ���λ��ʽ���������X����ôY������Z
//����H����λ��ż������
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
using namespace std;

//���һ���n����λ
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
	MD5(); //���캯����ʼ��
	void Update(unsigned char*, unsigned int); //�����ݽ��з��飬�����м���
	void Padding(unsigned char[16]); //�������
	void Transform(unsigned int[4], unsigned char[64]); //�ֻ���������
	void Encode(unsigned char*, unsigned int*, unsigned int); //������Ϣ��Ϊ�ַ�
	void Decode(unsigned int*, unsigned char*, unsigned int); //���ַ���Ϊ����
private:
	unsigned int count[2]; //��¼����λ��
	unsigned int regist[4]; //��¼���ڱ����512bits��Ϣ���ܵ��м����������ս�� 
	unsigned char buffer[64]; //512λ������
	unsigned char PADDING[64] = { 0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //�����������
};

#endif