% ensure the output gain is 1
if not(G(end)==1)
    error("the Output gain is not 1")
end

%transform the gains into the coefficient
SOS(:,1:3)=SOS(:,1:3).*G(1:end-1);

% fill not used sections with empty sections
while size(SOS,1)<3
    SOS(end+1,:)=[1 0 0 1 0 0];
end

%ensure the column 4 (coefficient a0) is completely 1
if not(isequal(SOS(:,4),ones(size(SOS(:,4)))))
    error("the column 4 (coefficient a0) is not everything 1")
end

%check if the SOS has correct dimmenstions
%3x6: 3 is the ammount of second order sections supported by the SW
%     6 is the ammount of coefficient per second order section
if not(isequal(size(SOS), [3 6]))
    error("SOS has wrong dimensions");
end

%order the coefitients in order a1 a2 b0 b1 b2
SosForNvm(1:3,1)=SOS(:,5);
SosForNvm(1:3,2)=SOS(:,6);
SosForNvm(1:3,3)=SOS(:,1);
SosForNvm(1:3,4)=SOS(:,2);
SosForNvm(1:3,5)=SOS(:,3);

%convert Matrix elements to a string for nvm
Nvm='rbl_ImuSigFil_NvmFilCfg:[';
for section=1:size(SosForNvm,1)
    for column=1:size(SosForNvm,2)
        %convert the float values to hex strings
        coeffasstring=char(sprintf("%08X",Float32ToUint32(SosForNvm(section,column))));
        %change byte order
        Nvm=[Nvm '0x' coeffasstring(7:8) ',0x' coeffasstring(5:6) ',0x' coeffasstring(3:4) ',0x' coeffasstring(1:2) ','];
    end
end
Nvm=[Nvm(1:end-1) ']']