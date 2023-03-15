function LoadCellData = importLoadCellDataFile(filename, startRow, endRow)
%IMPORTFILE Import numeric data from a text file as a matrix.
%   LoadCellData = importLoadCellDataFile(FILENAME) Reads data from text file
%   FILENAME for the default selection.
%
%   LoadCellData = importLoadCellDataFile(FILENAME, STARTROW, ENDROW) Reads data from
%   rows STARTROW through ENDROW of text file FILENAME.
%
% Example:
%   LoadCellData = importLoadCellDataFile('calibration 0g Z.txt', 1, 20000);
%
%    See also TEXTSCAN.

% Auto-generated by MATLAB on 2018/02/26 11:36:27

%% Initialize variables.
delimiter = ',';
if nargin<=2
    startRow = 1;
    endRow = inf;
end

%% Format for each line of text:
%   column1: double (%f)
%	column2: double (%f)
%   column3: double (%f)
%	column4: double (%f)
%   column5: double (%f)
%	column6: double (%f)
%   column7: double (%f)
%	column8: double (%f)
%   column9: double (%f)
%	column10: double (%f)
%   column11: double (%f)
%	column12: double (%f)
%   column13: double (%f)
%	column14: double (%f)
%   column15: double (%f)
%	column16: double (%f)
% For more information, see the TEXTSCAN documentation.
formatSpec = '%f%f%f%f%f%f%f%f%f%f%f%f%[^\n\r]';

%% Open the text file.
fileID = fopen(filename,'r');

%% Read columns of data according to the format.
% This call is based on the structure of the file used to generate this
% code. If an error occurs for a different file, try regenerating the code
% from the Import Tool.
dataArray = textscan(fileID, formatSpec, endRow(1)-startRow(1)+1, 'Delimiter', delimiter, 'TextType', 'string', 'EmptyValue', NaN, 'HeaderLines', startRow(1)-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');
for block=2:length(startRow)
    frewind(fileID);
    dataArrayBlock = textscan(fileID, formatSpec, endRow(block)-startRow(block)+1, 'Delimiter', delimiter, 'TextType', 'string', 'EmptyValue', NaN, 'HeaderLines', startRow(block)-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');
    for col=1:length(dataArray)
        dataArray{col} = [dataArray{col};dataArrayBlock{col}];
    end
end

%% Close the text file.
fclose(fileID);

%% Post processing for unimportable data.
% No unimportable data rules were applied during the import, so no post
% processing code is included. To generate code which works for
% unimportable data, select unimportable cells in a file and regenerate the
% script.

%% Create output variable
LoadCellData = table;
LoadCellData.FX1 = dataArray{:, 1};
LoadCellData.FY1 = dataArray{:, 2};
LoadCellData.FZ1 = dataArray{:, 3};
LoadCellData.MX1 = dataArray{:, 4};
LoadCellData.MY1 = dataArray{:, 5};
LoadCellData.MZ1 = dataArray{:, 6};

LoadCellData.FX2 = dataArray{:, 7};
LoadCellData.FY2 = dataArray{:, 8};
LoadCellData.FZ2 = dataArray{:, 9};
LoadCellData.MX2 = dataArray{:, 10};
LoadCellData.MY2 = dataArray{:, 11};
LoadCellData.MZ2 = dataArray{:, 12};
