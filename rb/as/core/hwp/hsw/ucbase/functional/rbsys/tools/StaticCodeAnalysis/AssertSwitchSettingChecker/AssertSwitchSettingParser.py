import os
import re
import sys



class File():
  def __init__(self, abspath, filename):
    self.abspath = os.path.normpath(abspath)
    self.filename = filename
    
  def __str__(self):
    return str(self.abspath)


all_files = []


for root, dirs, files in os.walk("."):
  for file in files:
    path_abs = os.path.join(root, file)
    filename = file
    
    all_files.append(File(path_abs, filename))
    

# filter: only .c and .h files
all_files = [file for file in all_files if (".c" in file.filename or ".h" in file.filename)]

# filter: only produtive code
all_files = [file for file in all_files if not "tst" in file.abspath]

# filter: remove files to which AssertSwitchSetting Checker is not applied
all_files = [file for file in all_files if not file.filename in ["RBSYS_GuardMemoryMap.h", "RBSYS_DefaultElementsPure.h", "RBSYS_RteOsServices.h"]]



def get_used_RBFS(file):
  switches = []
  
  with open(file, "r") as f:
    f_content = f.read()
    
    matches = re.finditer("(RBFS_[\w0-9]*)\s*[!=]*\s*RBFS_[\w0-9_]*", f_content)
    for match in matches:
      m = match.group(1)
      switches.append(m)
  
  return list( dict.fromkeys(switches)) # remove duplicates

def get_covered_RBFS(file):
  switches = []
  
  with open(file, "r") as f:
    f_content = f.read()
    
    # Function Switches that are correctly asserted via RB_ASSERT_SWITCH_SETTINGS
    matches = re.finditer("RB_ASSERT_SWITCH_SETTINGS\(\s*(RBFS_[a-zA-Z0-9]*)", f_content)
    for match in matches:
      m = match.group(1)
      switches.append(m)
      
    # Function Switches that are correctly defined in this file
    matches = re.finditer("#define\s*(RBFS_[a-zA-Z0-9]*)\s", f_content)
    for match in matches:
      m = match.group(1)
      switches.append(m)
  
  
  
  return list( dict.fromkeys(switches)) # remove duplicates


def prettyprint_list(l):
  for item in l:
    print("    "+item)

num_of_deviations = 0

for f in all_files:
  all_used_RBFS = get_used_RBFS(f.abspath)
  all_covered_RBFS = get_covered_RBFS(f.abspath)
  
  uncovered_but_used_RBFS = [fs for fs in all_used_RBFS if fs not in all_covered_RBFS]
  covered_but_unused_RBFS = [fs for fs in all_covered_RBFS if fs not in all_used_RBFS]
  
  if( len(uncovered_but_used_RBFS) > 0 or len(covered_but_unused_RBFS) > 0 ):
    print("File: "+f.abspath)
    if( len(uncovered_but_used_RBFS) > 0 ):
      print("  Assertion Missing: ")
      prettyprint_list(uncovered_but_used_RBFS)
      print("")
      num_of_deviations += len(uncovered_but_used_RBFS)
    if( len(covered_but_unused_RBFS) > 0 ):
      print("  Unused: ")
      prettyprint_list(covered_but_unused_RBFS)
      print("")
      num_of_deviations += len(covered_but_unused_RBFS)

sys.exit(num_of_deviations)



