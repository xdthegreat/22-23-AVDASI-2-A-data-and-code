clear variables
close all

[FileName, PathName] = uigetfile('*.csv','Select the data file','MultiSelect','off');
addpath(genpath(PathName))

DataFile = readmatrix(FileName);

DataFile(:,1)=[];

WindSpeed=20;
density=1.225;

DataFile=DataFile./((density*(WindSpeed^2))/2);

PS1(1)=min(DataFile(1,:));
PS2(1)=min(DataFile(2,:));
PS3(1)=min(DataFile(3,:));
PS4(1)=min(DataFile(4,:));
PS5(1)=min(DataFile(5,:));
PS6(1)=min(DataFile(6,:));
PS7(1)=min(DataFile(7,:));
PS8(1)=min(DataFile(8,:));
PS9(1)=min(DataFile(9,:));
PS10(1)=min(DataFile(10,:));
PS11(1)=min(DataFile(11,:));
PS12(1)=min(DataFile(12,:));
PS13(1)=min(DataFile(13,:));
PS14(1)=min(DataFile(14,:));
PS15(1)=min(DataFile(15,:));
PS16(1)=min(DataFile(16,:));

PS1(2)=max(DataFile(1,:));
PS2(2)=max(DataFile(2,:));
PS3(2)=max(DataFile(3,:));
PS4(2)=max(DataFile(4,:));
PS5(2)=max(DataFile(5,:));
PS6(2)=max(DataFile(6,:));
PS7(2)=max(DataFile(7,:));
PS8(2)=max(DataFile(8,:));
PS9(2)=max(DataFile(9,:));
PS10(2)=max(DataFile(10,:));
PS11(2)=max(DataFile(11,:));
PS12(2)=max(DataFile(12,:));
PS13(2)=max(DataFile(13,:));
PS14(2)=max(DataFile(14,:));
PS15(2)=max(DataFile(15,:));
PS16(2)=max(DataFile(16,:));

PS1(3)=mean(DataFile(1,:));
PS2(3)=mean(DataFile(2,:));
PS3(3)=mean(DataFile(3,:));
PS4(3)=mean(DataFile(4,:));
PS5(3)=mean(DataFile(5,:));
PS6(3)=mean(DataFile(6,:));
PS7(3)=mean(DataFile(7,:));
PS8(3)=mean(DataFile(8,:));
PS9(3)=mean(DataFile(9,:));
PS10(3)=mean(DataFile(10,:));
PS11(3)=mean(DataFile(11,:));
PS12(3)=mean(DataFile(12,:));
PS13(3)=mean(DataFile(13,:));
PS14(3)=mean(DataFile(14,:));
PS15(3)=mean(DataFile(15,:));
PS16(3)=mean(DataFile(16,:));


Output=[PS1;PS2;PS3;PS4;PS5;PS6;PS7;PS8;PS9;PS10;PS11;PS12;PS13;PS14;PS15;PS16]