close all
clear all
clc

csv_name = "raw.csv";
no_control_data = readmatrix(csv_name);
no_control_time = (no_control_data(:, 1) - no_control_data(1, 1))/1000.0;
no_control_mode_angle = no_control_data(:, 2);
no_control_target_angle = no_control_data(:, 3);
no_control_AoA = no_control_data(:, 4);

figure()
plot(no_control_time, no_control_target_angle, "--b")
hold on
plot(no_control_time, no_control_mode_angle, "--black")
plot(no_control_time, no_control_AoA, "-r")
xlabel("Time (s)")
ylabel("Angles (deg)")
legend("Target AoA", "Actual AoA")
title_name = "Angle-of-attack of fuselage raw";
title(title_name)
hold off
jpg_name = "raw.jpg";
saveas(gcf,jpg_name)