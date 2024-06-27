import sys
import re

compilerPath = sys.argv[1]
compilerOptions = "-cpu=cortexr52 -thumb -thumb_lib --c++11 -Ogeneral -DMTC_GHS_OGENERAL -map -MD -Mn -Mx -Mu -DNDEBUG -mapfile_type=2 -Ml -no_map_eofn_symbols -Man -keepmap -align8 -g -dual_debug -passsource -preprocess_assembly_files -asm3g --no_commons --short_enum -list -delete --no_rtti -frigor=accurate -fhard -preprocess_special_assembly_files --new_outside_of_constructor -ignore_debug_references -nofarcalls -farcallpatch -nostartfiles -Wundef --diag_remark=set_but_not_used --diag_error=undefined_preproc_id --diag_error=ghs_pointer_to_larger_alignment --misra_2004=8.1 --diag_warning=nonprototype_function_defined --diag_suppress=ghs_static_nonprototype_function_defined --diag_warning=ghs_not_enough_initializers --diag_error=pragma_information_conflict --brief_diagnostics --no_wrap_diagnostics --prototype_errors -Wshadow --diag_suppress=unsigned_compare_with_zero --diag_error=returning_ptr_to_local_variable --diag_error=used_before_set --diag_warning=integer_sign_change --diag_warning=missing_type_specifier --diag_warning=ghs_identical_param_and_return_types_required --diag_error=subscript_out_of_range --diag_error=implicit_return_from_non_void_function --diag_error=incompatible_assignment_operands -elxr_diag_error=283 --diag_suppress=declared_but_not_referenced -strict_overlap_check -globalcheck=normal -globalcheck_qualifiers -argcheck=normal --diag_suppress=1795"
# -ansi removed from compiler options
additionalCompilerOptions = "-UNDEBUG --diag_error=missing_type_specifier --diag_error=implicit_return_from_non_void_function -elxr_diag_error=283"
# --diag_error=1800 removed from additional compiler options

f = open("./out/rtaos_ccas_stellar_mcore_sc1_build_info.bat")
lines = f.readlines()
f.close()
out = []
for line in lines:
  if line.startswith("ccarm.exe -c"):
    matches = re.findall(r"\".*?\"", line)
    quotedParameters = " ".join(matches)
    line = "%s\cxarm.exe %s %s -c %s\n" % (compilerPath, compilerOptions, additionalCompilerOptions, quotedParameters)
    line = re.sub(r'"-I\S*Samples\\Includes"', r'"-ISamples\\Includes"', line)
    line = re.sub(r' "-I\S*out"', r'', line)
    out.append(line)
  elif line.startswith("ccarm.exe -archive"):
    line = line.replace("ccarm.exe", "cxarm.exe")
    line = re.sub(r"(\S*\.exe)",r"%s\\\1"%compilerPath.replace("\\","\\\\"),line)
    line = re.sub(r" -r \".*?RTAOS.a\"", r" -r \"RTAOS.a\"", line)
    out.append(line)
  else:
    out.append(line)

f = open("./out/rtaos_ccas_stellar_mcore_sc1_build_info.bat","w")
f.writelines(out)
f.close()