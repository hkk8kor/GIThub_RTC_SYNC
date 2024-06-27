function [Val_u32] = Float32ToUint32(Val_float32)

e = floor(log2(abs(Val_float32)))+127;
m = ((abs(Val_float32)/(2^(e-127)))-1)*2^23;
if(Val_float32<0)
    v = 1;
else
    v = 0;
end

v = v*2^31;
e = e*2^23;

value = v+e+m;

Val_u32 = uint32(value);

end