load 'output_fixed.txt'
load 'output_rtl.txt'
load 'mix_file.txt'
figure(4)

subplot(3,1,1);
plot(mix_file)
title('Mixed input signal')

subplot(3,1,2);
plot(output_rtl)
title('NSDF fixed gate output')

subplot(3,1,3);
plot(output_fixed)
title('NSDF fixed point output')

figure(3)
plot(abs(output_fixed)-abs(output_rtl))
title('NSDF fixed <> gate difference')
