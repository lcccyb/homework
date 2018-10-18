%计算[s,e]区间内的平均颜色值 
function ret = average(s,e,A) 
count = 0; 
sum = 0; 
for i = s : e 
    %A(i,1)为i颜色值的个数 
    sum = sum + A(i,1)*i; 
    count = count + A(i,1); 
end 
%总数/个数，结果取整 
ret = round(sum/count); 