function shili26
h0=figure('toolbar','none',...
    'position',[200 150 450 250],...
    'name','ʵ��16');
A=[-8/3 0 0;0 -10 10;0 28 -1];
y=[35 -10 -7]';
h=0.01;
P=plot3(y(1),y(2),y(3),'.',...
    'erasemode','none',...
    'markersize',5);
axis([0 50 -25 25 -25 25])
hold on
for i=1:2000
    P=findobj('xdata',y(1),...
        'ydata',y(2),...
        'zdata',y(3));
    A(1,3)=y(2);
    A(3,1)=-y(2);
    ydot=A*y;
    y=y+h*ydot;
    set(P,'xdata',y(1),...
        'ydata',y(2),...
        'zdata',y(3))
    drawnow
    i=i+1;
end
