function [y,e] = LMSFilter(x,d,N,u)
%% Adaptive filtering using LMS
% Aaptive filtering of the input vector x using the desired vector d
% The algorithm performs an adaptive FIR filtering on the input x
% The LMS algorithm updates the filter weights/coefficients 
% according to:
%   y(n) = w(n)*x(n) = sum{w(l)x(n-l)}  (FIR filter for l=1:N)
%   e(n) = d(n)-y(n)                    (Estimation error)
%   w(k;n) = w(k;n-1)+f(k;x(n),e(n),u)  (LMS update of weights)
% where
%   f(k;x(n),e(n),x) = ue(n)x*(n-k) 
%
% Complex conjugate of the input vector, assuming only real value of x
%
% Parameters:
%
% x - input vector (Must be normalized with peak(x) < 1)
% w - weights (FIR filter coefficients)
% u - adaptation step size 
% N - vector size of filter weights
%
% y - output vector
% e - estimation error

% Initialize vectors
w = zeros(1,N);         % Weights w = 0
y = zeros(1,length(x)); % Output vector
e = zeros(1,length(x)); % Estimation error

for n=1:length(x)
    
    % FIR filter input vector
    for l=1:N
        if (n > l) 
            y(n) = y(n) + w(l)*x(n-l+1);
        end
    end
    
    % Estimate error
    e(n) = d(n) - y(n);
    
    % Adjust weights
    for k=1:N
        if (n > k)
            w(k) = w(k) + u*e(n)*x(n-k); 
        end
    end
    
end

%% For debug only - final weights filter plot
xn = [0:0.03:pi];
HH = freqz(w, 1, xn);
xn = xn.*(500/(2*pi));
    
figure(3);
subplot(2,1,1);
plot(xn, abs(HH));
title('Amplitude response of LMS filter');
xlabel('frequence');
ylabel('amplitude');
subplot(2,1,2);
plot(xn, angle(HH));
title('Phase response of LMS filter');
xlabel('frequence');
ylabel('phase');

end