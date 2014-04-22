%% Parameters for test of the pitch detector algorithm
fs = 48000;
f1 = 50;
f2 = 100;
f3 = 200;
A1 = 0.5; 
A2 = 0.3;
gain = 0.3;
N = 1024;
W = 1024; 
tstart = 1024;
k = 0.80; % Ratio for determination of local maximums

%% Noisy test signal that contains a sine wave
tst = gain*A1*sin(2*pi*(f1/fs)*(1:N)) + gain*A2*sin(2*pi*(f2/fs)*(1:N))+ gain*A2*sin(2*pi*(f3/fs)*(1:N));
%tst = A1*sin(2*pi*(f1/fs)*(1:N));
x = [0.1*randn(1,N) (tst + 0.1*randn(1,N)) 0.1*randn(1,N)];
%x = tst;

figure(1);
subplot(3,1,1);
plot(x); 
title('Input signal with noise');

%% Normalized Squared difference function
% From article "A Smarter way to find pitch"
r_tau = zeros(1,W); % Autocorrelation ACF type II
m_tau = zeros(1,W); % Squared difference function modified SDF
n_tau = zeros(1,W); % Normalized squared difference function

t = tstart; % Start at time when periodic signal is avaiable
for tau = 1:W
    for j = t:t+W-1-tau
        r_tau(tau) = r_tau(tau) + x(j)*x(j+tau); % ACF type II (2)
        m_tau(tau) = m_tau(tau) + x(j)^2 + x(j+tau)^2; % SDF modified (6)
        n_tau(tau) = 2*r_tau(tau)/m_tau(tau); % Normalized NSDF (-1 to 1) (9)
    end
end

%%save('tau.txt', 'n_tau', '-ASCII');
save tau.txt n_tau -ASCII

subplot(3,1,2);
plot (r_tau);
title('Autocorrelation - ACF type II');

subplot(3,1,3);
plot (n_tau);
title('Normalized squared difference - NSDF');


%[C, I] = max(n_tau);

%% Find the local maxima
%Test vector
%tau = [5 4 3 2 1 0 -1 -2 -3 -4 -3 -2 -1 0 1 2 3 4 5 4 3 2 1 0];
%W = 24;
tau = n_tau;
n_1 = tau(1); % Treshold for detection of first maximum - parameter
n_2 = n_1;
treshold = n_1*k;

% Initialization
max_samples = zeros(1, 1);
max_value = zeros(1, 1);
samples = 0;
rising = 0;
idx = 1;
maximum = 0;

for n=1:W
    if (tau(n) > 0)
        %disp([num2str(n_2) ' ' num2str(n_1) ' ' num2str(tau(n))]);
        if (n_1 > n_2) && (n_1 > tau(n)) && (n_1 > treshold)
            samples = n - 1;
            max_samples(idx) = samples;
            max_value(idx) = n_1;
            maximum = n_1;
            idx = idx + 1;
            disp(['Maximum: ' num2str(n_1) ' Samples : ' num2str(samples)]);
            treshold = n_1 * k;
        end
    end
    n_2 = n_1;
    n_1 = tau(n);
end

maximum = 0;
tau_max = 0;
for n=1:length(max_samples)
    if max_value(n) > maximum
        maximum = max_value(n);
        tau_max = max_samples(n);
    end
end

disp(['Tau max: ' num2str(tau_max) ' value ' num2str(maximum) ]);
%tau_max = 48
fc = fs/tau_max;
note = log10(fc/27.5)/log10(sqrt(2));
disp(['Pitch frequence detected : ' num2str(fc)]);

