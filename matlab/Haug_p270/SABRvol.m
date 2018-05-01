function y = SABRvol(a,b,r,v,F,K,T);
% ---------------------------------------------
% Returns the SABR volatility.
% Required inputs:
% a = alpha parameter
% b = beta parameter
% r = rho parameter
% v = vol of vol parameter
% F = spot price
% K = strike price
% T = maturity
% ---------------------------------------------
% By Fabrice Douglas Rouah

% Separate into ATM case (simplest case) and
% Non-ATM case (most general case)

if abs(F-K) <= 0.001  % ATM vol

	Term1 = a/F^(1-b);
	Term2 = ((1-b)^2/24*a^2/F^(2-2*b) + r*b*a*v/4/F^(1-b) + (2-3*r^2)*v^2/24);
	y = Term1*(1 + Term2*T);

else    % Non-ATM vol

	FK = F*K;
	z = v/a*(FK)^((1-b)/2)*log(F/K);
	x = log((sqrt(1 - 2*r*z + z^2) + z - r)/(1-r));
	Term1 = a / FK^((1-b)/2) / (1 + (1-b)^2/24*log(F/K)^2 + (1-b)^4/1920*log(F/K)^4);
	if abs(x-z) < 1e-10
		Term2 = 1;
	else
		Term2 = z / x;
	end
	Term3 = 1 + ((1-b)^2/24*a^2/FK^(1-b) + r*b*v*a/4/FK^((1-b)/2) + (2-3*r^2)/24*v^2)*T;
	y = Term1*Term2*Term3;

end
