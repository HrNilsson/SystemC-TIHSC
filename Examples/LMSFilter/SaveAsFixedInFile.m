function [] = SaveAsFixedInFile(h, name)
%% Converts vector h to 1.15 and save in file given by name
% Convert input vector to 1.15 fixed point format 
h16 = h*2^15;

% Modified for Matlab 7
fid = fopen(name, 'w');
for i=1:length(h16)
    xtext = num2str(round(h16(i)));
    fprintf(fid, '%s,\n', xtext);
end
fclose(fid);

end
