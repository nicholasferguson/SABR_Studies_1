% Example from page 270 of Espen Haug's (aka The Collector) excellent book
% By Fabrice Douglas Rouah

clc; clear;

% Required inputs
F = 100;            % Futures price
T = 0.5;            % Maturity in years   
b = 0.9999;         % beta SABR parameter
v = 0.5;            % vol-of-vol SABR parameter
ATMvol = 0.30;      % Market ATM volatility

% Define the strikes and correlation levels
K   = [70 80 90 100 110 120 130];
rho = [-0.75 -0.50 -0.25 0.00 0.25 0.50 0.75];

% Find the length of each vector
I = length(rho);
J = length(K);

% Find the SABR volatilities for each strike/correlation combination
for i=1:I
    for j=1:J
        alpha(i,j) = findAlpha(F, K(j), T, ATMvol, b, rho(i), v);
        Vol(i,j) = SABRvol(alpha(i,j), b, rho(i), v, F, K(j), T);
    end
end

% Multiply by 100 to have the same format as Haug's example
Vol = Vol.*100

% Output the results
Res = dataset({rho', 'Rho'}, {Vol(:,1), 'Strike70'},  {Vol(:,2), 'Strike80'},  {Vol(:,3), 'Strike90'},...
    {Vol(:,4), 'Strike100'}, {Vol(:,5), 'Strike110'}, {Vol(:,6), 'Strike120'}, {Vol(:,7), 'Strike130'})

% Look at alpha also
alpha
