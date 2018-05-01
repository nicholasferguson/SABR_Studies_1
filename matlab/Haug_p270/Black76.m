% Finds the Black (1976) price
% By Fabrice Douglas Rouah

function y = Black76(F,K,T,v,rf,PutCall);

% F = futures price
% K = strike price
% T = maturity in years
% v = volatility
% rf = risk free rate
% PutCall = 'Call' or 'Put'

d1 = (log(F/K) + (v^2/2)*T)/v/sqrt(T);
d2 = d1 - v*sqrt(T);

if strcmp(PutCall, 'Call')
    Nd1 = cdf('normal',d1,0,1);
    Nd2 = cdf('normal',d2,0,1);
    y = exp(-rf*T)*(F*Nd1 - K*Nd2);
elseif strcmp(PutCall, 'Put');
    Nd1 = cdf('normal',-d1,0,1);
    Nd2 = cdf('normal',-d2,0,1);
    y = exp(-rf*T)*(K*Nd2 - F*Nd1);
else
    y = 'Error: specify Call or Put';
end
