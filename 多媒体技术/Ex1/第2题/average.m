%����[s,e]�����ڵ�ƽ����ɫֵ 
function ret = average(s,e,A) 
count = 0; 
sum = 0; 
for i = s : e 
    %A(i,1)Ϊi��ɫֵ�ĸ��� 
    sum = sum + A(i,1)*i; 
    count = count + A(i,1); 
end 
%����/���������ȡ�� 
ret = round(sum/count); 