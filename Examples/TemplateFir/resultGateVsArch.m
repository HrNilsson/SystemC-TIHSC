load 'output_fixed.txt'
load 'output_rtl.txt'
load 'mix_file.txt'
figure(1)
plot(mix_file)
title('FIR filter mixed input signal')
figure(2)
plot(output_fixed)
title('FIR filter fixed point output - TLM level')
figure(3)
plot(output_rtl)
title('FIR filter fixed point output - RTL level')
figure(4)
plot(abs(output_fixed)-abs(output_rtl))
title('FIR filter difference')
