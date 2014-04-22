load out_data_func.txt
load in_data_func.txt
x=[1:1:size(in_data_func)]; 
figure(1)
plot(x,in_data_func,x,out_data_func,'r')
xlabel('N')
ylabel('Floating point')
title('Functional Level')

