close all
clear all
clc

%no control graphing
for i = 1:100
    csv_name = "Fus_no_control_" + string(i) + ".csv";
    %trying to open .csv
    try
        no_control_data = readmatrix(csv_name);
    catch
        fprintf("CSV no control requested number %i does not exist. \n", i)
        continue
    end

    no_control_time = (no_control_data(:, 1) - no_control_data(1, 1))/1000.0;
    if length(no_control_time) <5
        continue
    end
    no_control_target_angle = zeros(length(no_control_time), 1);
    no_control_AoA = no_control_data(:, 4);

    figure()
    plot(no_control_time, no_control_target_angle, "--b")
    hold on
    plot(no_control_time, no_control_AoA, "-r")
    xlabel("Time (s)")
    ylabel("Angles (deg)")
    legend("Target AoA", "Actual AoA")
    title_name = "Angle-of-attack of fuselage with no inputs to elevator " + string(i);
    title(title_name)
    hold off
    jpg_name = "Fus_no_control_" + string(i) + ".jpg";
    saveas(gcf,jpg_name)

end

%direct elevator mode graphing
for i = 1:100
    csv_name = "Fus_direct_" + string(i) + ".csv";
    try
        no_control_data = readmatrix(csv_name);
    catch
        fprintf("CSV direct requested number %i does not exist. \n", i)
        continue
    end
    no_control_time = (no_control_data(:, 1) - no_control_data(1, 1))/1000.0;
    if length(no_control_time) <5
        continue
    end
    no_control_target_angle = no_control_data(:, 2);
    no_control_AoA = no_control_data(:, 4);

    figure()
    plot(no_control_time, no_control_target_angle, "--b")
    hold on
    plot(no_control_time, no_control_AoA, "-r")
    xlabel("Time (s)")
    ylabel("Angles (deg)")
    legend("Target AoA", "Actual AoA")
    title_name = "Angle-of-attack of fuselage in direct elevator mode " + string(i);
    title(title_name)
    hold off
    jpg_name = "Fus_direct_" + string(i) + ".jpg";
    saveas(gcf,jpg_name)

end

%PID mode graphing
for i = 1:100
    csv_name = "Fus_PID_" + string(i) + ".csv";
    try
        no_control_data = readmatrix(csv_name);
    catch
        fprintf("CSV PID requested number %i does not exist.\n", i)
        continue
    end
    no_control_time = (no_control_data(:, 1) - no_control_data(1, 1))/1000.0;
    if length(no_control_time) < 5
        continue
    end
    no_control_target_angle = no_control_data(:, 3);
    no_control_AoA = no_control_data(:, 4);

    figure()
    plot(no_control_time, no_control_target_angle, "--b")
    hold on
    plot(no_control_time, no_control_AoA, "-r")
    xlabel("Time (s)")
    ylabel("Angles (deg)")
    legend("Target AoA", "Actual AoA")
    title_name = "Angle-of-attack of fuselage in PID mode " + string(i);
    title(title_name)
    hold off
    jpg_name = "Fus_PID_" + string(i) + ".jpg";
    saveas(gcf,jpg_name)

end