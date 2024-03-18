%%%用plot画心：
clc
clear all
close all;
%清屏清除工作区

x1=-3:0.01:0;
x2=0:0.01:3;
hn=figure('name','2020情人节快乐','MenuBar','None');
set(hn,'color','w');

for t=1:50
cla

eval('yleft=(-x1).^(2/3)+(0.9*(3.3-(-x1).^2).^0.5).*sin(t*pi*(-x1)) ');

eval('yright=x2.^(2/3)+(0.9*(3.3-x2.^2).^0.5).*sin(t*pi*x2) ');
%eval函数可以直接把字符串当作命令执行，直接算出左边函数和右边函数的值

plot(x1,yleft,'*r',x2,yright,'*r');
axis([-1.8 1.8 -1.5 2.5]);
axis off; %去除坐标

pause(0.01); %用暂停形成动画效果
title('2020情人节快乐！！！'); %刷新

end
clc;