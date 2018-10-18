%将区域A切分为power(2,level)个区间 
function ret = cut(A,level) 
%所要划分的区间数量 
num = power(2,level); 
%初始化
ret = zeros(num,2); 
ret(1,1) = 1; 
ret(num,2) = 256; 
%获得1-256中间的值，划分出两个区间，区间内的像素值相同 
medium = getMedium(A,1,256); 

%判断level的值
if level == 1 
    ret(num/2,2) = medium; 
    ret(1,2) = medium+1; 
end 
if level == 2 
   ret(num/2,2) = medium; 
   ret(num/2+1,1) = medium+1; 
   medium = getMedium(A,1,ret(num/2,2)); 
   ret(num/4,2) = medium; 
   ret(num/4+1,1) = medium+1; 
   medium = getMedium(A,ret(num/2+1,1),ret(num,2)); 
   ret(num/2+1,2) = medium; 
   ret(num,1) = medium+1; 
end 
if level == 3 
   %进一步划分 
   ret(num/2,2) = medium; 
   ret(num/2+1,1) = medium+1; 
   medium = getMedium(A,1,ret(num/2,2)); 
   ret(num/4,2) = medium; 
   ret(num/4+1,1) = medium+1; 
   medium=getMedium(A,1,ret(num/4,2)); 
   ret(num/8,2) = medium; 
   ret(num/8+1,1) = medium+1; 
   medium = getMedium(A,ret(num/4+1,1),ret(num/2,2)); 
   ret(num/4+1,2) = medium; 
   ret(num/2,1) = medium+1; 
   medium = getMedium(A,ret(num/2+1,1),ret(num,2)); 
   ret(num/2+2,2) = medium; 
   ret(num/2+3,1) = medium+1; 
   medium = getMedium(A,ret(num/2+1,1),ret(num/2+2,2)); 
   ret(num/2+1,2) = medium; 
   ret(num/2+2,1) = medium+1; 
   medium = getMedium(A,ret(num/2+3,1),ret(num,2)); 
   ret(num/2+3,2) = medium; 
   ret(num,1) = medium+1; 
end 
 