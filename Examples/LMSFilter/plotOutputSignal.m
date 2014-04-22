load 'src\NoiseSignal.txt'
load 'OutputSignal.txt'
x=[1:1:size(OutputSignal)]; 
figure(1)
plot(OutputSignal);
xlabel('Sample N')
ylabel('Fixed point')
title('LMS Filter output signal')
figure(2)
plot(x,NoiseSignal,x,OutputSignal,'r')
title('LMS Filter input vs. output')
