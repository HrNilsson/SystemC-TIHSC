load 'output_fixed.txt'
load 'output_nsdf.txt'
load 'output_acf.txt'
load 'output_sdf.txt'
load 'mix_file.txt'
figure(4)

subplot(3,1,1);
plot(mix_file)
title('Mixed input signal')

subplot(3,1,2);
plot(output_nsdf)
title('NSDF fixed arch output')

subplot(3,1,3);
plot(output_fixed)
title('NSDF fixed point output')

figure(3)
plot(abs(output_fixed)-abs(output_nsdf))
title('NSDF fixed <> arch difference')

figure(5)

subplot(3,1,1);
plot(output_acf)
title('ACF')

subplot(3,1,2);
plot(output_sdf)
title('SDF')

subplot(3,1,3);
plot(output_nsdf)
title('NSDF')
