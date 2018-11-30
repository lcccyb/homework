RGB = imread('C:\Users\lcccy\Desktop\������Ƭ.bmp');%��ȡͼƬ

R = RGB(:,:,1);
G = RGB(:,:,2);
B = RGB(:,:,3);

figure,imshow(RGB),title('ԭʼͼ��');

%RGB->YUV
Y = 0.299 * double(R) + 0.587 * double(G) + 0.114 * double(B);
U = -0.169 * double(R) - 0.3316 * double(G) + 0.5 * double(B);
V = 0.5 * double(R) - 0.4186 * double(G) - 0.0813 * double(B);
YUV = cat(3,Y,U,V); %YUVͼ��
figure,imshow(uint8(YUV)),title('ԭʼYUVͼ��')

T = dctmtx(8);%����һ��8*8��DCT�任����

%����DCT�任
BY = blkproc(Y,[8 8],'P1*x*P2',T,T');
BU = blkproc(U,[8 8],'P1*x*P2',T,T');
BV = blkproc(V,[8 8],'P1*x*P2',T,T');

a = [16 11 10 16 24 40 51 61;
12 12 14 19 26 58 60 55;
14 13 16 24 40 57 69 55;
14 17 22 29 51 87 80 62;
18 22 37 56 68 109 103 77;
24 35 55 64 81 104 113 92;
49 64 78 87 103 121 120 101;
72 92 95 98 112 100 103 99;]; %����������

b = [17 18 24 47 99 99 99 99;
18 21 26 66 99 99 99 99;
24 26 56 99 99 99 99 99;
47 66 99 99 99 99 99 99;
99 99 99 99 99 99 99 99;
99 99 99 99 99 99 99 99;
99 99 99 99 99 99 99 99;
99 99 99 99 99 99 99 99;]; %ɫ��`������

BY2 = blkproc(BY,[8 8],'x./P1',a);
BU2 = blkproc(BU,[8 8],'x./P1',b);
BV2 = blkproc(BV,[8 8],'x./P1',b);

%�������ȡ������
BY3 = int8(BY2);
BU3 = int8(BU2);
BV3 = int8(BV2);

BY4 = blkproc(double(BY3),[8 8],'x.*P1',a);
BU4 = blkproc(double(BU3),[8 8],'x.*P1',b);
BV4 = blkproc(double(BV3),[8 8],'x.*P1',b);

mask = [
1 1 1 1 1 1 1 1;
1 1 1 1 1 1 1 1;
1 1 1 1 1 1 1 1;
1 1 1 1 1 1 1 1;
1 1 1 1 1 1 1 1;
1 1 1 1 1 1 1 1;
1 1 1 1 1 1 1 1;
1 1 1 1 1 1 1 1;];

BY5 = blkproc(BY4,[8 8],'P1.*x',mask);
BU5 = blkproc(BU4,[8 8],'P1.*x',mask);
BV5 = blkproc(BV4,[8 8],'P1.*x',mask);

%DCT��任
YI = blkproc(double(BY5),[8 8],'P1*x*P2',T',T);
UI = blkproc(double(BU5),[8 8],'P1*x*P2',T',T);
VI = blkproc(double(BV5),[8 8],'P1*x*P2',T',T);

YUVI = cat(3,uint8(YI),uint8(UI),uint8(VI)); %����DCT�任���������YUVͼ��
figure,imshow(YUVI),title('ѹ����YUVͼ��');

RI = YI - 0.001 * UI + 1.402 * VI;
GI = YI - 0.344 * UI - 0.714 * VI;
BI = YI + 1.772 * UI + 0.001 * VI;
RGBI = cat(3,RI,GI,BI);%����DCT�任���������RGBͼ��
RGBI = uint8(RGBI);
figure,imshow(RGBI),title('ѹ����JPEGͼ��');
imwrite(RGBI,'C:\Users\lcccy\Desktop\result.jpg'); %����ѹ��ͼ��