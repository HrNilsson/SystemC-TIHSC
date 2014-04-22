load 'output_double.txt'
load 'output_fixed.txt'
load 'mix_file.txt'
figure(1)
plot(mix_file)
title('FIR filter mixed input signal')
figure(2)
plot(output_fixed)
title('FIR filter fixed point output')
figure(3)
plot(output_double)
title('FIR filter floating point output')
figure(4)
plot(abs(output_fixed)-abs(output_double))
title('FIR filter difference')
