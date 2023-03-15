clear variables
close all

[FileName, PathName] = uigetfile('*.txt','Select the data file','MultiSelect','on');
addpath(genpath(PathName))

AoA = [-10 -5 0 5 10 15 20 25 30]; %For group 9
%AoA = [-10 -5 0 5 10 15 20 25];


LoadCellData= cell(18,1);

LoadCellData{1} = importLoadCellDataFile(cell2mat(FileName(1)));
LoadCellData{2} = importLoadCellDataFile(cell2mat(FileName(2)));
LoadCellData{3} = importLoadCellDataFile(cell2mat(FileName(3)));
LoadCellData{4} = importLoadCellDataFile(cell2mat(FileName(4)));
LoadCellData{5} = importLoadCellDataFile(cell2mat(FileName(5)));
LoadCellData{6} = importLoadCellDataFile(cell2mat(FileName(6)));
LoadCellData{7} = importLoadCellDataFile(cell2mat(FileName(7)));
LoadCellData{8} = importLoadCellDataFile(cell2mat(FileName(8)));
LoadCellData{9} = importLoadCellDataFile(cell2mat(FileName(9)));

[FileName, PathName] = uigetfile('*.txt',['Select the 0 sweep data file'],'MultiSelect','on');
addpath(genpath(PathName))

LoadCellData{10} = importLoadCellDataFile(cell2mat(FileName(1)));
LoadCellData{11} = importLoadCellDataFile(cell2mat(FileName(2)));
LoadCellData{12} = importLoadCellDataFile(cell2mat(FileName(3)));
LoadCellData{13} = importLoadCellDataFile(cell2mat(FileName(4)));
LoadCellData{14} = importLoadCellDataFile(cell2mat(FileName(5)));
LoadCellData{15} = importLoadCellDataFile(cell2mat(FileName(6)));
LoadCellData{16} = importLoadCellDataFile(cell2mat(FileName(7)));
LoadCellData{17} = importLoadCellDataFile(cell2mat(FileName(8)));
LoadCellData{18} = importLoadCellDataFile(cell2mat(FileName(9)));

MeanLoads = zeros(9,12); %For group 9
MeanLoadsZero = zeros(9,12);

for ii=10:18 %For Group 9
% for i=1:9 %For Groups 7 and 11
    %LC250
	FX1_mean = mean(LoadCellData{ii,1}.FX1);
    FY1_mean = mean(LoadCellData{ii,1}.FY1);
    FZ1_mean = mean(LoadCellData{ii,1}.FZ1);
    MX1_mean = mean(LoadCellData{ii,1}.MX1);
    MY1_mean = mean(LoadCellData{ii,1}.MY1);
    MZ1_mean = mean(LoadCellData{ii,1}.MZ1);
    %LC1000
    FX2_mean = mean(LoadCellData{ii,1}.FX2);
    FY2_mean = mean(LoadCellData{ii,1}.FY2);
    FZ2_mean = mean(LoadCellData{ii,1}.FZ2);
    MX2_mean = mean(LoadCellData{ii,1}.MX2);
    MY2_mean = mean(LoadCellData{ii,1}.MY2);
    MZ2_mean = mean(LoadCellData{ii,1}.MZ2);
    
    MeanLoadsZero(ii-9,1)  = FX1_mean;
    MeanLoadsZero(ii-9,2)  = FY1_mean;
    MeanLoadsZero(ii-9,3)  = FZ1_mean;
    MeanLoadsZero(ii-9,4)  = MX1_mean;
    MeanLoadsZero(ii-9,5)  = MY1_mean;
    MeanLoadsZero(ii-9,6)  = MZ1_mean;
    MeanLoadsZero(ii-9,7)  = FX2_mean;
    MeanLoadsZero(ii-9,8)  = FY2_mean;
    MeanLoadsZero(ii-9,9)  = FZ2_mean;
    MeanLoadsZero(ii-9,10) = MX2_mean;
    MeanLoadsZero(ii-9,11) = MY2_mean;
    MeanLoadsZero(ii-9,12) = MZ2_mean;

end

for i=1:9 %For Group 9
% for i=1:9 %For Groups 7 and 11
    %LC250
	FX1_mean = mean(LoadCellData{i,1}.FX1);
    FY1_mean = mean(LoadCellData{i,1}.FY1);
    FZ1_mean = mean(LoadCellData{i,1}.FZ1);
    MX1_mean = mean(LoadCellData{i,1}.MX1);
    MY1_mean = mean(LoadCellData{i,1}.MY1);
    MZ1_mean = mean(LoadCellData{i,1}.MZ1);
    %LC1000
    FX2_mean = mean(LoadCellData{i,1}.FX2);
    FY2_mean = mean(LoadCellData{i,1}.FY2);
    FZ2_mean = mean(LoadCellData{i,1}.FZ2);
    MX2_mean = mean(LoadCellData{i,1}.MX2);
    MY2_mean = mean(LoadCellData{i,1}.MY2);
    MZ2_mean = mean(LoadCellData{i,1}.MZ2);
    
    MeanLoads(i,1)  = FX1_mean-MeanLoadsZero(i,1);
    MeanLoads(i,2)  = FY1_mean-MeanLoadsZero(i,2);
    MeanLoads(i,3)  = FZ1_mean-MeanLoadsZero(i,3);
    MeanLoads(i,4)  = MX1_mean-MeanLoadsZero(i,4);
    MeanLoads(i,5)  = MY1_mean-MeanLoadsZero(i,5);
    MeanLoads(i,6)  = MZ1_mean-MeanLoadsZero(i,6);
    MeanLoads(i,7)  = FX2_mean-MeanLoadsZero(i,7);
    MeanLoads(i,8)  = FY2_mean-MeanLoadsZero(i,8);
    MeanLoads(i,9)  = FZ2_mean-MeanLoadsZero(i,9);
    MeanLoads(i,10) = MX2_mean-MeanLoadsZero(i,10);
    MeanLoads(i,11) = MY2_mean-MeanLoadsZero(i,11);
    MeanLoads(i,12) = MZ2_mean-MeanLoadsZero(i,12);

end

U = 20; %m/s
rho = 1.225; %kg/m^3

% Wing parameters 

b = 1.2; %m
c = 0.3; %m
S = b*c; %m^2

for ii=1:9
    VerticalForce(ii) = -(MeanLoads(ii,8)*sind(AoA(1,ii))-MeanLoads(ii,7)*cosd(AoA(1,ii))+MeanLoads(ii,3));
    HorizontalForce(ii)= (MeanLoads(ii,8)*cosd(AoA(1,ii))+MeanLoads(ii,7)*sind(AoA(1,ii))+MeanLoads(ii,2));
    Pitching_M(ii) = MeanLoads(ii,12);
    CL(ii,1) = 2*VerticalForce(ii)/(rho*U^2*S);
    CD(ii,1) = 2*HorizontalForce(ii)/(rho*U^2*S);
    CM(ii,1) = 2*Pitching_M(ii)/(rho*U^2*S*c);
end

figure;
subplot(131)
plot(AoA,CL,'-*', 'LineWidth',2)
xlabel('Angle of attack [deg]')
ylabel('Lift Coefficient []')
subplot(132)
plot(AoA,CD,'*')
xlabel('Angle of attack [deg]')
ylabel('Drag Coefficient []')
subplot(133)
plot(AoA,CM,'*')
xlabel('Angle of attack [deg]')
ylabel('Pitching M Coefficient []')