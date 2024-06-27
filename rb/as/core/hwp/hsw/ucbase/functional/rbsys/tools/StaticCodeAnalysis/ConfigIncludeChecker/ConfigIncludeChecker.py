import os
import re
import sys


"""
################## Motivation ##################
- Variance Test: Component config will be stubbed. Therefore files should never directly include the stub config.
=> Design Reqm: Never include TRBSYS_Config.h
- UnitTest / CompTest: Files using RBFS shall always include RBSYS_Config.h directly. Why? Otherwise, it will not be testable and / or
  the effort for a redesign is higher.
"""

class File():
  def __init__(self, abspath, filename):
    self.abspath = os.path.normpath(abspath)
    self.filename = filename
    
  def __str__(self):
    return str(self.abspath)


all_files = []
exit_code = 0


for root, dirs, files in os.walk("."):
  for file in files:
    path_abs = os.path.join(root, file)
    filename = file
    
    all_files.append(File(path_abs, filename))
    

# filter: only .c and .h files
all_files = [file for file in all_files if (".c" in file.filename or ".h" in file.filename)]

# filter: no HSWSim stub
all_files = [file for file in all_files if not "HSWSim" in file.abspath]

# filter: remove files to which AssertSwitchSetting Checker is not applied
all_files = [file for file in all_files if not file.filename in ["RBSYS_GuardMemoryMap.h", "RBSYS_DefaultElementsPure.h", "RBSYS_Config.h", "RBSYS_DefaultElements.h", "RBSYS_RteOsServices.h", "TRBSYS_Config.h"]]

def get_files_using_TRBSYSConfig():
  files_found = []

  for file in all_files:
    with open(file.abspath, "r") as f:
      if re.search("TRBSYS_Config\.h", f.read()):
        # this file is including TRBSYS_Config
        files_found.append(file)
  
  return files_found
  
print("------------- TRBSYS_Config shall not be included in these files ----------------")
files_found = get_files_using_TRBSYSConfig()
exit_code += len(files_found)
for file in files_found:
  print( file.filename )


def get_files_using_RBFS_but_not_including_RBSYS_Config():
  files_found = []
  
  for file in all_files:
    with open(file.abspath, "r") as f:
      code_str = f.read()
      if( re.search("#if[\s\(]*RBFS_", code_str) != None 
      and re.search("#include\s*\"RBSYS_Config\.h", code_str) == None ):
        files_found.append(file)
  
  return  files_found

print("------------- RBSYS_Config shall be directly included in these files ----------------")
files_found = get_files_using_RBFS_but_not_including_RBSYS_Config()
exit_code += len(files_found)
for file in files_found:
  print( file.abspath )

sys.exit(exit_code)

