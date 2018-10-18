function p1()
S = char('诺贝尔.jpg', 'lena.jpg');
Imagename = cellstr(S);
%%读入图片
I1 = imread(Imagename{1});
I2 = imread(Imagename{2});
%转换存储方式为double
I1 = im2double(I1);
I2 = im2double(I2);

I1(:,:,2) = 0;
I1(:,:,3) = 0;
I2(:,:,2) = 0;
I2(:,:,3) = 0;

[x,y,z] = size(I1);
Im = I1;
%创建图形窗口并设置图形初始属性
hFigure = figure('menubar','none','NumberTitle','off','position',[1000 1000 720 450],'name','p1');
movegui(hFigure, 'center');
axes('Visible','off','units','normalized','position',[0 0 1 1]);
%显示图片
hIm = imshow(Im);

step = x/40; %渐变步长

%动画效果
for i = step:step:x
    for alpha = 0:pi/50:2*pi
        Im(x/2:x/2+i*cos(alpha),x/2:x/2+i*sin(alpha),:)=I2(x/2:x/2+i*cos(alpha),x/2:x/2+i*sin(alpha),:);
        Im(x/2-i*cos(alpha):x/2,x/2:x/2+i*sin(alpha),:)=I2(x/2-i*cos(alpha):x/2,x/2:x/2+i*sin(alpha),:);
        Im(x/2-i*cos(alpha):x/2,x/2-i*sin(alpha):x/2,:)=I2(x/2-i*cos(alpha):x/2,x/2-i*sin(alpha):x/2,:);
        Im(x/2:x/2+i*cos(alpha),x/2-i*sin(alpha):x/2,:)=I2(x/2:x/2+i*cos(alpha),x/2-i*sin(alpha):x/2,:);
        set(hIm,'CData',Im); %设置image对象CData属性为Im
    end
    drawnow;%重绘当前图形窗口
end



