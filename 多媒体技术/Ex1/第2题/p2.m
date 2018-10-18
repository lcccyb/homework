
RGB = imread('redapple.jpg'); 
[x,y,z] = size(RGB); 

R = RGB(:,:,1); 
G = RGB(:,:,2); 
B = RGB(:,:,3); 
 
%��ɫֱ���飬���Դ�Ŷ�Ӧ��ɫ��0-255ֵ�ϵĸ�ֵ������ 
hisR = zeros(256,1); 
hisG = zeros(256,1); 
hisB = zeros(256,1); 
  
%�������ɫ��ֵ���������� 
for i = 1 : x 
    for j = 1 : y 
       hisR(R(i,j)+1) = hisR(R(i,j)+1)+1;  
       hisG(G(i,j)+1) = hisG(G(i,j)+1)+1; 
       hisB(B(i,j)+1) = hisB(B(i,j)+1)+1; 
    end 
end 
 
%��ɫ��3λ8���䣬��ɫ3λ8���䣬��ɫ2λ4���� 
cutR = cut(hisR,3); 
cutG = cut(hisG,3); 
cutB = cut(hisB,2); 

%��ʼ��color LUT������ͼ 
colorMap = zeros(256,3); 
IndexMap = zeros(x,y); 
 
%��������ֺõ�ÿ���������ƽ����ɫ����Ϊ������ɫ 
for i = 1 : 8 
    for j = 1 : 8 
        for k = 1 : 4  
            t = 32*(i-1)+4*(j-1)+k; 
            colorMap(t,1) = average(cutR(i,1),cutR(i,2),hisR); 
            colorMap(t,2) = average(cutG(j,1),cutG(j,2),hisG); 
            colorMap(t,3) = average(cutB(k,1),cutB(k,2),hisB); 
        end 
    end 
end 
 
%��������ͼ������ȷ��ԭͼ����ɫ����һ���䣬Ȼ���Ӧ��colorMap�ϵ�ֵ����¼���� 
for i = 1 : x 
    for j = 1 : y 
        pos = 1; 
        while R(i,j) > cutR(pos,2) 
            pos = pos+1; 
        end 
        r = pos; 
        pos = 1; 
        while G(i,j) > cutG(pos,2) 
            pos = pos+1; 
        end 
        g = pos; 
        pos = 1; 
        while B(i,j) > cutB(pos,2) 
            pos = pos+1; 
        end 
        b = pos; 
        IndexMap(i,j) = 32*(r-1)+4*(g-1)+b-1; 
    end 
end 

%������ɫ���ұ�д����ɫ����ʾ������ֵ��ΧΪ0-255 
for i = 1 : x 
    for j = 1 : y 
        Output(i,j,1) = colorMap(IndexMap(i,j)+1,1)-1; 
        Output(i,j,2) = colorMap(IndexMap(i,j)+1,2)-1; 
        Output(i,j,3) = colorMap(IndexMap(i,j)+1,3)-1; 
    end 
end 

colorMap

figure(1); 
imshow(RGB); 
figure(2); 
Output = uint8(Output); 
imshow(Output); 
imwrite(Output,'redapple2.jpg');