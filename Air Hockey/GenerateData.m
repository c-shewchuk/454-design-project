height = 100;
width = 100;

R = 5;

theta_min = -atan(height/2/width);
theta_max = atan(height/2/width);

Vmax = 10;

limit = 5;
size = 10^4;


data = zeros(size,3);

for j = 1:size
    x_puck = width/4;
    y_puck = height/2;
    x_striker = 3*width/4;
    y_striker = height/2;
    hit = 0;
    t = 0;
    theta = theta_max*(2*rand-1);
    Vx_puck = abs(Vmax*rand);
    Vy_puck = tan(theta)*Vx_puck;
    Vy_striker = Vmax/4*(2*rand-1);
        while t < limit
        x_puck = x_puck + Vx_puck;
        y_puck = y_puck + Vy_puck;
        y_striker = y_striker + Vy_striker;
            if abs(x_puck - x_striker) < R && abs(y_puck - y_striker) < R
                hit = 1;
                break;
            end
        t=t+1;
        end
    data(j,1) = theta;
    data(j,2) = Vy_striker;
    data(j,3) = hit;
end

mean(data(:,3))
max(data(:,3))
plotData(data(:,1:2),data(:,3))
