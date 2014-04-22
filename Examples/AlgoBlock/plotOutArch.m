load out_data_arch.txt
load in_data_arch.txt
x=[1:1:size(in_data_arch)]; 
figure(2)
plot(x,in_data_arch,x,out_data_arch,'r')
xlabel('Sample N')
ylabel('Fixed point')
title('Platform Architecture Level')
