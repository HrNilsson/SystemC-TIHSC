load 'output_double.txt'
load 'output_fixed.txt'
load 'mix_file.txt'
figure(2)

subplot(3,1,1);
plot(mix_file)
title('Mixed input signal')

subplot(3,1,2);
plot(output_fixed)
title('NSDF filter fixed point output')

subplot(3,1,3);
plot(output_double)
title('NSDF floating point output')

figure(3)
plot(abs(output_fixed)-abs(output_double))
title('NSDF float <> fixed difference')
