clear all
close all
%% Boundary Conditions
sz = 10000;
data = zeros(sz,3);
limit = 5;
resolution = 1000; % "Frames per second"
height = 368.75;
width = 825;
R = 5*(1+1.26);
theta_max = pi/2;%atan(height/2/width);
Vmax_puck = 10;
Vmax_striker = 1;
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
   theta = abs(theta_max*(2*rand-1)); %abs for only upper right half since its symmetric
   Vx_puck_0 = abs(Vmax_puck*rand);
   Vy_puck_0 = tan(theta)*Vx_puck_0;
   gamma = (x_striker_0-x_puck_0)/Vx_puck_0;
   beta = gamma*Vy_puck_0 + y_puck_0;
   ri = rem(beta,height);
   if mod(floor(beta/height),2)==0
       Vy_striker = (ri - y_striker_0)/gamma;
   else
       Vy_striker = (height-ri-y_striker_0)/gamma;
   end
   data(j,2) = Vy_striker;
   %data(j,2) = sqrt(Vx_puck_0^2+Vx_puck_0^2);
    if abs(Vy_striker) > Vmax_striker
        Vy_striker = sign(Vy_striker)*Vmax_striker;
    end
   
   Vx_striker = 0;
   %
   x_puck = x_puck_0;
   y_puck = y_puck_0;
   x_striker = x_striker_0;
   y_striker = y_striker_0;
   
   while t<limit*resolution
       dt=t/resolution;
       x_puck = x_puck + Vx_puck_0*dt;
       y_puck = y_puck + Vy_puck_0*dt;
       if y_puck > height ||  y_puck < 0
           Vy_puck_0 = -Vy_puck_0;
       end
       y_striker = y_striker + Vy_striker*dt;
       x_striker = x_striker + Vx_striker*dt;
       if abs(x_puck - x_striker) < R && abs(y_puck - y_striker) < R
            hit = 1;
            break;
       end
       t=t+1;
   end
   
   data(j,1) = theta;
   data(j,3) = hit;
end
X = data(:, [1, 2]); y = data(:, 3);
mean(data(:,3))
max(data(:,3))%
plotData(X, y);
hold on;
xlabel('Theta')
ylabel('V_{y,striker}')
