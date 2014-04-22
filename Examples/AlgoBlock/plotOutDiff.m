load out_data_arch.txt
load out_data_func_fix.txt
x=[1:1:size(out_data_arch)]; 
figure(3)
plot(x,out_data_func_fix,x,out_data_arch,'r')
xlabel('Sample N')
ylabel('Fixed point')
title('Functional vs Platform Architecture Model')
figure(4)
format long
%diff=10*log10(power(out_data_func_fix, 2)/power(out_data_func_fix-out_data_arch, 2));
%diff=10*log10(power(out_data_func_fix-out_data_arch, 2)/power(out_data_func_fix, 2));
diff=20*log10(abs(out_data_func_fix-out_data_arch)/out_data_func_fix);
plot(diff)
xlabel('Sample N')
ylabel('Signal-to-error (db)')
title('Difference between models')


