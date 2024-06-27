import os
import re
import sys


"""
################## Motivation ##################
Lots of Stub files are just copy-paste products
1. Find files with same content
2. Analyze similarity in content (e.g. "30% same content in file xy")
"""

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

# filter: only tst files
all_files = [file for file in all_files if "tst\\unit" in file.abspath]

# filter: remove files to which Checker is not applied
#all_files = [file for file in all_files if not file.filename in ["RBSYS_GuardMemoryMap.h", "RBSYS_DefaultElementsPure.h", "RBSYS_Config.h", "RBSYS_DefaultElements.h", "RBSYS_RteOsServices.h"]]


def analyze_similarity(lst_files):
  #create cross product 2s-tuples of all files
  import itertools

  combinations = list(itertools.combinations(lst_files, 2)) # compare every file with every other file (no double comparisons, no self comparison)
  
  print("Number of file combinations: " +str(len(combinations)))
  
  combs_w_similarity = []
  
  #analyze file similarity
  from difflib import SequenceMatcher
  for comb in combinations:
    # if file name similarity > 70%
    if( SequenceMatcher(None, comb[0].filename, comb[1].filename).ratio() > 0.7 ):
      similarity = 0
      with open(comb[0].abspath) as f1:
        with open(comb[1].abspath) as f2:
          similarity = SequenceMatcher(None, f1.read(), f2.read()).ratio()
      combs_w_similarity.append( (comb, similarity) )

  #sort by decending similarity
  combs_w_similarity.sort(key=lambda x:x[1], reverse=True)

  for c in combs_w_similarity:
    # for files with at least 20% similar content
    if( c[1] > 0.2 ):
      print("File 1: "+c[0][0].abspath)
      print("File 2: "+c[0][1].abspath)
      print("Similarity: "+str(c[1]))
      print("\n")


analyze_similarity(all_files)
