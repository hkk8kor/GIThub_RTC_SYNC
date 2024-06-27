import os
import os.path
import subprocess
import datetime
import shutil
import openpyxl
import zipfile


script_template = """
load "path1" "path2"
expand all
expand out.zip
filter "-*.zip;-*.a;-*.dba;-*.sig;-*.css;-*.html;-*.lst"
select all.files
file-report layout:statistics options:display-all output-to:outfile.txt
compare rules-based"""


BCOMP_PATH = "C:\\Program Files\\Beyond Compare 4\\BCompare.exe"


configurations = [
  #  ---------------------------------------- OLD ----------------------------------------    ---------------------------------------- NEW ----------------------------------------
  ("2021 vs 2024", r"D:\Sandbox_RB_MS_HSW_Dev\HWRef\rb\as\core\hwp\hsw\ucbase\functional\rbsys\rtaos\RH850G4M\MultiCore_SC4\202115", r"D:\Sandbox_RB_MS_HSW_Dev\HWRef\rb\as\core\hwp\hsw\ucbase\functional\rbsys\rtaos\RH850G4M\MultiCore_SC4\201815")
  #("Title of Comparison 1", r"path to old folder1", r"path to new folder1"),
  #("Title of Comparison 2", r"path to old folder2", r"path to new folder2")
]

review_report_template = "ReviewOS_Template.xlsx"
review_report = "ReviewOS_" + str(datetime.datetime.now()).replace("-", "").replace(":", "").replace(" ", "") + ".xlsx"


# Copy template file
shutil.copyfile(review_report_template, review_report)

def expand_all_zip_files(path):
  for root, _, files in os.walk(path):
    for f in files:
      if ".zip" in f:
        zip_path = os.path.join(root, f)
        with zipfile.ZipFile(zip_path, "r") as z:
          z.extractall(zip_path.replace(".zip", ""))
  
  
  
for conf in configurations:
  (desc, path_old, path_new) = conf
  
  # apparently, Beyond Compare script cannot handle zip files as folders. Therefore unzip anything...
  expand_all_zip_files(path_old)
  expand_all_zip_files(path_new)
  
  script_content = script_template.replace("path1", path_old).replace("path2", path_new)
  with open("bcomp_script.txt", "w+") as f:
    f.write(script_content)
  
  # call Beyond Compare
  p = subprocess.Popen(BCOMP_PATH + " @bcomp_script.txt")
  p.wait()
  
  
  wb = openpyxl.load_workbook(filename = review_report)
  t = wb["template"]
  s = wb.copy_worksheet(t)
  s.title = desc

  text = ""
  with open("outfile.txt", "r") as f:
    text = f.readlines()
  data = []
  for l in text:
    row = []
    for content in l.split(","):
      row.append(content)
    data.append(row)

  for r in range(len(data)):
    for c in range(len(data[r])):
      cell = s.cell(row=3+r, column=1+c)
      # value can be number or text
      try:
        cell.value = int(data[r][c])
      except:
        cell.value = data[r][c]

  wb.save(review_report)
  

os.remove("bcomp_script.txt")
os.remove("outfile.txt")



