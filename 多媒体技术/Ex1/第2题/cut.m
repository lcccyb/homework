%������A�з�Ϊpower(2,level)������ 
function ret = cut(A,level) 
%��Ҫ���ֵ��������� 
num = power(2,level); 
%��ʼ��
ret = zeros(num,2); 
ret(1,1) = 1; 
ret(num,2) = 256; 
%���1-256�м��ֵ�����ֳ��������䣬�����ڵ�����ֵ��ͬ 
medium = getMedium(A,1,256); 

%�ж�level��ֵ
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
   %��һ������ 
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
 