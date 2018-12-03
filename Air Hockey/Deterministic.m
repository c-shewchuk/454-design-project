height = 100;
width = 100;

R = 5;

theta_min = -atan(height/2/width);
theta_max = atan(height/2/width);

Vmax = 10;

limit = 20;
size = 10^4;

data = zeros(size,3);

for j = 1:size
    x_puck_0 = width/4;
    y_puck_0 = height/2;
    x_striker_0 = 3*width/4;
    y_striker_0 = height/2;
    hit = 0;
    t = 0;
    theta = theta_max*(2*rand-1);
    Vx_puck_0 = abs(Vmax*rand);
    Vy_puck_0 = tan(theta)*Vx_puck;
    gamma = (x_striker_0 - x_puck_0)/Vx_puck;
    beta = y_puck_0 + Vy_puck*gamma;
    if mod(floor(beta/height),2)==0
        y_puck_final = rem;
    else
            y_puck_final = height - rem;
    end
    Vy_striker = Vy_puck_0
        
        while t < limit
        x_puck = x_puck + Vx_puck*t
        y_puck = y_puck + Vy_puck;
        y_striker = y_striker + v_striker;
        %y_striker = y_striker + Vy_striker; %using random striker velocity
            if abs(x_puck - x_striker) < R && abs(y_puck - y_striker) < R
                hit = 1;
                break;
            end
        t=t+1;
        end
    %data(j,1) = theta;
    %data(j,2) = Vy_striker;
    %data(j,3) = hit;
end

%mean(data(:,3))
%max(data(:,3))
plotData(data(:,1:2),data(:,3))

