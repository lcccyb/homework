
RGB = imread('redapple.jpg'); 
[x,y,z] = size(RGB); 

R = RGB(:,:,1); 
G = RGB(:,:,2); 
B = RGB(:,:,3); 
 
%三色直方块，用以存放对应颜色在0-255值上的各值的数量 
hisR = zeros(256,1); 
hisG = zeros(256,1); 
hisB = zeros(256,1); 
  
%读入各颜色各值的像素数量 
for i = 1 : x 
    for j = 1 : y 
       hisR(R(i,j)+1) = hisR(R(i,j)+1)+1;  
       hisG(G(i,j)+1) = hisG(G(i,j)+1)+1; 
       hisB(B(i,j)+1) = hisB(B(i,j)+1)+1; 
    end 
end 
 
%红色用3位8区间，绿色3位8区间，蓝色2位4区间 
cutR = cut(hisR,3); 
cutG = cut(hisG,3); 
cutB = cut(hisB,2); 

%初始化color LUT和索引图 
colorMap = zeros(256,3); 
IndexMap = zeros(x,y); 
 
%计算出划分好的每个长方体的平均颜色，作为代表颜色 
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
 
%生成索引图，即先确定原图中颜色在哪一区间，然后对应到colorMap上的值，记录索引 
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

%根据颜色查找表写入颜色，显示的像素值范围为0-255 
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