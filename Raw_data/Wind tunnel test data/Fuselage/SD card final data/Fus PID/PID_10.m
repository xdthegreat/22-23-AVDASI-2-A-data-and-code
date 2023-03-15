i = 10;
csv_name = "Fus_PID_" + string(i) + ".csv";
no_control_data = readmatrix(csv_name);
no_control_time = (no_control_data(:, 1) - no_control_data(1, 1))/1000.0;
no_control_target_angle = zeros(length(no_control_time), 1);
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

%% chop up PID 10 peak 5
Peak_5_data = no_control_data(5500:6000, :);
peak_5_time = (Peak_5_data(:, 1) - Peak_5_data(1, 1))/1000.0;
peak_5_target_angle = Peak_5_data(:, 3);
peak_5_AoA = Peak_5_data(:, 4);

peak_5_stable_AoA = mean(peak_5_AoA(length(peak_5_AoA)-100:end));
peak_5_start_time = 2.1;

%end time req: +-0.5
for i = 100:length(peak_5_AoA)-50
    peak_5_end_check = peak_5_AoA(i:i+50);
    if max(abs(peak_5_AoA(i) - peak_5_end_check)) > 0.5
        continue
    else
        peak_5_end_time = peak_5_time(i);
        break
    end
end

peak_5_settling_time = peak_5_end_time - peak_5_start_time;
peak_5_kP = mean(Peak_5_data(:, 5));
peak_5_kI = mean(Peak_5_data(1:100, 6));
peak_5_kD = mean(Peak_5_data(:, 7));

figure()
plot(peak_5_time, peak_5_target_angle, "--b")
hold on
plot(peak_5_time, peak_5_AoA, "-r")
yline(peak_5_stable_AoA, "--k")
xline(peak_5_start_time, "--m")
xline(peak_5_end_time, "--m")
xlabel("Time (s)")
ylabel("Angles (deg)")
legend("Target AoA", "Actual AoA", "AoA after stabilization", "Start time", "End time")
title_name = {'Angle-of-attack of fuselage in PID mode with', 'kP = ' + ...
    string(peak_5_kP) + ", kI = " + string(peak_5_kI) + " and kD = " + string(peak_5_kD)};
title(title_name)
hold off
fprintf("Settling time of PID 10 peak 5 is %f s. \n", peak_5_settling_time)
fprintf("PID 10 peak 5 kP is %f , kI is %f and kD is %f. \n", peak_5_kP, peak_5_kI, peak_5_kD)
jpg_name = "Fus_PID_10_peak_5.jpg";
saveas(gcf,jpg_name)

%kP, kI, kD check
figure()
hold on
plot(peak_5_time, peak_5_AoA, "-r")
plot(peak_5_time, Peak_5_data(:, 5))
plot(peak_5_time, Peak_5_data(:, 6))
plot(peak_5_time, Peak_5_data(:, 7))
title(title_name)
legend("Actual AoA", "kP", "kI", "kD")
xlabel("Time (s)")
hold off

T = array2table(Peak_5_data);
T.Properties.VariableNames(1:7) = {'Time (ms)','mode','Target angle (deg)', 'Actual angle(deg)',...
    'k_P', 'k_I', 'k_D'};
writetable(T,'Fus_PID_10_peak_5.csv') 


%% chop up PID 10 peak 6
Peak_5_data = no_control_data(6530:7200, :);
peak_5_time = (Peak_5_data(:, 1) - Peak_5_data(1, 1))/1000.0;
peak_5_target_angle = Peak_5_data(:, 3);
peak_5_AoA = Peak_5_data(:, 4);

peak_5_stable_AoA = mean(peak_5_AoA(length(peak_5_AoA)-100:end));
peak_5_start_time = 2.35;

%end time req: +-0.5
for i = 100:length(peak_5_AoA)-50
    peak_5_end_check = peak_5_AoA(i:i+50);
    if max(abs(peak_5_AoA(i) - peak_5_end_check)) > 0.5
        continue
    else
        peak_5_end_time = peak_5_time(i);
        break
    end
end

peak_5_settling_time = peak_5_end_time - peak_5_start_time;
peak_5_kP = mean(Peak_5_data(:, 5));
peak_5_kI = mean(Peak_5_data(1:100, 6));
peak_5_kD = mean(Peak_5_data(:, 7));

figure()
plot(peak_5_time, peak_5_target_angle, "--b")
hold on
plot(peak_5_time, peak_5_AoA, "-r")
yline(peak_5_stable_AoA, "--k")
xline(peak_5_start_time, "--m")
xline(peak_5_end_time, "--m")
xlabel("Time (s)")
ylabel("Angles (deg)")
legend("Target AoA", "Actual AoA", "AoA after stabilization", "Start time", "End time")
title_name = {'Angle-of-attack of fuselage in PID mode with', 'kP = ' + ...
    string(peak_5_kP) + ", kI = " + string(peak_5_kI) + " and kD = " + string(peak_5_kD)};
title(title_name)
hold off
fprintf("Settling time of PID 10 peak 6 is %f s. \n", peak_5_settling_time)
fprintf("PID 10 peak 6 kP is %f , kI is %f and kD is %f. \n", peak_5_kP, peak_5_kI, peak_5_kD)
jpg_name = "Fus_PID_10_peak_6.jpg";
saveas(gcf,jpg_name)

%kP, kI, kD check
figure()
hold on
plot(peak_5_time, peak_5_AoA, "-r")
plot(peak_5_time, Peak_5_data(:, 5))
plot(peak_5_time, Peak_5_data(:, 6))
plot(peak_5_time, Peak_5_data(:, 7))
title(title_name)
legend("Actual AoA", "kP", "kI", "kD")
xlabel("Time (s)")
hold off

T = array2table(Peak_5_data);
T.Properties.VariableNames(1:7) = {'Time (ms)','mode','Target angle (deg)', 'Actual angle(deg)',...
    'k_P', 'k_I', 'k_D'};
writetable(T,'Fus_PID_10_peak_6.csv') 

%% chop up PID 10 peak 7
Peak_5_data = no_control_data(7670:8200, :);
peak_5_time = (Peak_5_data(:, 1) - Peak_5_data(1, 1))/1000.0;
peak_5_target_angle = Peak_5_data(:, 3);
peak_5_AoA = Peak_5_data(:, 4);

peak_5_stable_AoA = mean(peak_5_AoA(length(peak_5_AoA)-100:end));
peak_5_start_time = 2.55;

%end time req: +-0.5
for i = 100:length(peak_5_AoA)-50
    peak_5_end_check = peak_5_AoA(i:i+50);
    if max(abs(peak_5_AoA(i) - peak_5_end_check)) > 0.5
        continue
    else
        peak_5_end_time = peak_5_time(i);
        break
    end
end

peak_5_settling_time = peak_5_end_time - peak_5_start_time;
peak_5_kP = mean(Peak_5_data(:, 5));
peak_5_kI = mean(Peak_5_data(1:100, 6));
peak_5_kD = mean(Peak_5_data(:, 7));

figure()
plot(peak_5_time, peak_5_target_angle, "--b")
hold on
plot(peak_5_time, peak_5_AoA, "-r")
yline(peak_5_stable_AoA, "--k")
xline(peak_5_start_time, "--m")
xline(peak_5_end_time, "--m")
xlabel("Time (s)")
ylabel("Angles (deg)")
legend("Target AoA", "Actual AoA", "AoA after stabilization", "Start time", "End time")
title_name = {'Angle-of-attack of fuselage in PID mode with', 'kP = ' + ...
    string(peak_5_kP) + ", kI = " + string(peak_5_kI) + " and kD = " + string(peak_5_kD)};
title(title_name)
hold off
fprintf("Settling time of PID 10 peak 7 is %f s. \n", peak_5_settling_time)
fprintf("PID 10 peak 7 kP is %f , kI is %f and kD is %f. \n", peak_5_kP, peak_5_kI, peak_5_kD)
jpg_name = "Fus_PID_10_peak_7.jpg";
saveas(gcf,jpg_name)

%kP, kI, kD check
figure()
hold on
plot(peak_5_time, peak_5_AoA, "-r")
plot(peak_5_time, Peak_5_data(:, 5))
plot(peak_5_time, Peak_5_data(:, 6))
plot(peak_5_time, Peak_5_data(:, 7))
title(title_name)
legend("Actual AoA", "kP", "kI", "kD")
xlabel("Time (s)")
hold off

T = array2table(Peak_5_data);
T.Properties.VariableNames(1:7) = {'Time (ms)','mode','Target angle (deg)', 'Actual angle(deg)',...
    'k_P', 'k_I', 'k_D'};
writetable(T,'Fus_PID_10_peak_7.csv') 

%% chop up PID 10 peak 8
Peak_5_data = no_control_data(8650:end, :);
peak_5_time = (Peak_5_data(:, 1) - Peak_5_data(1, 1))/1000.0;
peak_5_target_angle = Peak_5_data(:, 3);
peak_5_AoA = Peak_5_data(:, 4);

peak_5_stable_AoA = mean(peak_5_AoA(length(peak_5_AoA)-100:end));
peak_5_start_time = 1.75;
%end time req: +-0.5
for i = 100:length(peak_5_AoA)-50
    peak_5_end_check = peak_5_AoA(i:i+50);
    if max(abs(peak_5_AoA(i) - peak_5_end_check)) > 0.5
        continue
    else
        peak_5_end_time = peak_5_time(i);
        break
    end
end

peak_5_settling_time = peak_5_end_time - peak_5_start_time;
peak_5_kP = mean(Peak_5_data(:, 5));
peak_5_kI = mean(Peak_5_data(1:100, 6));
peak_5_kD = mean(Peak_5_data(:, 7));

figure()
plot(peak_5_time, peak_5_target_angle, "--b")
hold on
plot(peak_5_time, peak_5_AoA, "-r")
yline(peak_5_stable_AoA, "--k")
xline(peak_5_start_time, "--m")
xline(peak_5_end_time, "--m")
xlabel("Time (s)")
ylabel("Angles (deg)")
legend("Target AoA", "Actual AoA", "AoA after stabilization", "Start time", "End time")
title_name = {'Angle-of-attack of fuselage in PID mode with', 'kP = ' + ...
    string(peak_5_kP) + ", kI = " + string(peak_5_kI) + " and kD = " + string(peak_5_kD)};
title(title_name)
hold off
fprintf("Settling time of PID 10 peak 8 is %f s. \n", peak_5_settling_time)
fprintf("PID 10 peak 8 kP is %f , kI is %f and kD is %f. \n", peak_5_kP, peak_5_kI, peak_5_kD)
jpg_name = "Fus_PID_10_peak_8.jpg";
saveas(gcf,jpg_name)

%kP, kI, kD check
figure()
hold on
plot(peak_5_time, peak_5_AoA, "-r")
plot(peak_5_time, Peak_5_data(:, 5))
plot(peak_5_time, Peak_5_data(:, 6))
plot(peak_5_time, Peak_5_data(:, 7))
title(title_name)
legend("Actual AoA", "kP", "kI", "kD")
xlabel("Time (s)")
hold off

T = array2table(Peak_5_data);
T.Properties.VariableNames(1:7) = {'Time (ms)','mode','Target angle (deg)', 'Actual angle(deg)',...
    'k_P', 'k_I', 'k_D'};
writetable(T,'Fus_PID_10_peak_8.csv') 
