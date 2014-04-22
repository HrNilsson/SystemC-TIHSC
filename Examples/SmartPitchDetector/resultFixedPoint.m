load 'mix_file.txt'
load 'acf_file.txt'
load 'output_fixed.txt'
figure(2)

subplot(3,1,1);
plot(mix_file)
title('Mixed input signal')

subplot(3,1,2);
plot(acf_file)
title('ACF 2 fixed point output')

subplot(3,1,3);
plot(output_fixed)
title('NSDF fixed point output')

%figure(4)
%plot(abs(output_fixed)-abs(output_double))
%title('FIR filter difference')
