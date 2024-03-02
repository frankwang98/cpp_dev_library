%%画三角函数
function shili02
h0=figure('toolbar','none',...  %调用工具箱
    'position',[200 150 450 350],...  %设置图框大小
    'name','实例02');  %标题栏
x=-pi:0.05:pi;  %x的范围
y=sin(x)+cos(x);  %函数
plot(x,y,'-*r','linewidth',1);  %画图
grid on  %保持
xlabel('自变量X');  %x坐标名称
ylabel('函数值Y');  %y坐标名称
title('三角函数');  %标题