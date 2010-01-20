function HdfTestScript
% Example code for HdfImport/HdfExport scripts

% text string
obj.name = 'Test object';
% scalar value
obj.val  = 3.14;
% vector
obj.vec = [1 2];
% matrix
obj.mat = [1 2 3;
           4 5 6];
% sub-structure
obj.sub.a = 3;
obj.sub.b = 4;

% export matlab structure to HDF5
HdfExport('testfile.h5', obj);
clear obj;

% import HDF5 back to matlab
obj = HdfImport('testfile.h5')
