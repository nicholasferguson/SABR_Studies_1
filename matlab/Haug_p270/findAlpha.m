function y = findAlpha(F,K,T,ATMvol,b,r,v)
% By Fabrice Douglas Rouah

% -------------------------------------------------------------------------
% Finds the SABR "alpha" parameter by solving the cubic equation described
% in West (2005) "Calibration of the SABR Model in Illiquid Markets"
% The function can return multiple roots.  In that case, the program 
% eliminates negative roots, and select the smallest root among the 
% positive roots that remain.
% Required inputs:
% F = spot price
% K = strike price
% T = maturity
% ATMvol = ATM market volatility
% b = beta parameter
% r = rho parameter
% v = vol of vol parameter
% -------------------------------------------------------------------------

% Find the coefficients of the cubic equation for alpha
C0 = -ATMvol*F^(1-b);
C1 = (1 + (2-3*r^2)*v^2*T/24);
C2 = r*b*v*T/4/F^(1-b);
C3 = (1-b)^2*T/24/F^(2-2*b);

% Return the roots of the cubic equation (multiple roots)
AlphaVector = roots([C3 C2 C1 C0]);

% Find and return the smallest positive root
index = find(AlphaVector>0);
Alpha = AlphaVector(index);
y = min(Alpha);

