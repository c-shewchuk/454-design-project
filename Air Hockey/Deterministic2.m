clear all
close all
%% Boundary Conditions
sz = 10000;
data = zeros(sz,3);
limit = 150;
height = 100;
width = 100;
R = 5;
theta_max = atan(height/2/width);
Vmax_puck = 10;
Vmax_striker = 2;
%% Initial Conditions
% Default IC
x_puck_0 = width/4;
y_puck_0 = height/2;
x_striker_0 = 3*width/4;
y_striker_0 = height/2;

for j = 1:sz
   hit = 0;
   t = 0;
   % Calculate POI
   theta = theta_max*(2*rand-1);
   Vx_puck_0 = abs(Vmax_puck*rand);
   Vy_puck_0 = tan(theta)*Vx_puck_0;
   gamma = (x_striker_0-x_puck_0)/Vx_puck_0;
   Vy_striker = Vy_puck_0 + (y_puck_0-y_striker_0)/gamma;
   if abs(Vy_striker) > Vmax_striker
       Vy_striker = sign(Vy_striker)*Vmax_striker;
   end
   Vx_striker = 0;
   %
   x_puck = x_puck_0;
   y_puck = y_puck_0;
   x_striker = x_striker_0;
   y_striker = y_striker_0;
   
   while t<limit
       dt=t/width;
       x_puck = x_puck + Vx_puck_0*dt;
       y_puck = y_puck + Vy_puck_0*dt;
       y_striker = y_striker + Vy_striker*dt;
       x_striker = x_striker + Vx_striker*dt;
       if abs(x_puck - x_striker) < R && abs(y_puck - y_striker) < R
            hit = 1;
            break;
       end
       t=t+1;
   end
   
   data(j,1) = theta;
   data(j,2) = Vy_puck_0;
   data(j,3) = hit;
end
X = data(:, [1, 2]); y = data(:, 3);
mean(data(:,3))
max(data(:,3))
plotData(X, y);
hold on;
xlabel('Theta')
ylabel('V_{y,Striker}')
