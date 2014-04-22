%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  LMSNoiseSupressionSolution
%
%  By Kim Bjerge IHA
%  Implementation of LMS filter 
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

f1 = 8000;              % Undesired signal
f2 = 800;
f3 = 2000;
fs = 96000;             % signal parameters
N = 1000; n = 0:1:N-1;  % length and time index

sn1 = sin(2*pi*f1*n/fs); % generate sinewave 8000 hz
sn2 = sin(2*pi*f2*n/fs); % generate sinewave 800 hz
sn3 = sin(2*pi*f3*n/fs); % generate sinewave 1000 hz 

%noise=randn(size(sn1)); % generate random noise
noise = wgn(N,1,0)';     % generate random noise
dn = 0.3*sn1+0.3*sn2+0.3*sn3+0.01*noise; % mixing desired sinewaves
xn = 0.4*sn1+0.1*noise;  % generate x(n) with noise and undesired signal

L = 64;                  % filter length
mu = 0.004;              % step size mu

[y,e] = LMSFilter(xn,dn,L,mu); % LMS Filter function

figure(1);
plot(dn);
title('Noisy input signal');

figure(2);
title('Frequence response of input');
freqz(dn);

figure(4);
plot(e);
title('Adaptive filter');
xlabel('Time index, n'); ylabel('Amplitude');

figure(5);
title('Frequence response of output');
freqz(e);

SaveAsFixedInFile(xn, 'src\Noise.txt');
SaveAsFixedInFile(dn, 'src\NoiseSignal.txt');
