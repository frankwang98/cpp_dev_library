%%�����Ǻ���
function shili02
h0=figure('toolbar','none',...  %���ù�����
    'position',[200 150 450 350],...  %����ͼ���С
    'name','ʵ��02');  %������
x=-pi:0.05:pi;  %x�ķ�Χ
y=sin(x)+cos(x);  %����
plot(x,y,'-*r','linewidth',1);  %��ͼ
grid on  %����
xlabel('�Ա���X');  %x��������
ylabel('����ֵY');  %y��������
title('���Ǻ���');  %����