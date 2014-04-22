load 'out_arch_left.txt'
load 'out_data_func_fix.txt'
x=[1:1:size(out_arch_left)]; 
figure(3)
plot(x,out_data_func_fix,x,out_arch_left,'r')
xlabel('Sample N')
ylabel('Fixed point')
title('Functional vs Architecture Model')
figure(4)
format long
diff=20*log10(abs(out_data_func_fix-out_arch_left)/out_data_func_fix);
plot(diff)
xlabel('Sample N')
ylabel('Signal-to-error (db)')
title('Difference between models')


