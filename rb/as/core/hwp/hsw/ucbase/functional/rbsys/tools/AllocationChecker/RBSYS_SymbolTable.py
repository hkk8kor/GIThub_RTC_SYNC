import RBSYS_call_proc
import os.path

class Symbol:
  def __init__(self, name, address, size, l_type, section, binding, objFile):
    self.name = name
    self.address = address
    self.size = size
    self.type = l_type
    self.section = section
    self.binding = binding
    self.objFile = objFile

  def __str__(self):
    return "Symbol(%s, %s, %s, %s, %s, %s, %s)" % (self.name, hex(self.address), hex(self.size), self.type, self.section, self.binding, self.objFile)

  def __repr__(self):
    return "Symbol(%s, %s, %s, %s, %s, %s, %s)" % (self.name, hex(self.address), hex(self.size), self.type, self.section, self.binding, self.objFile)

def getSymbols(elfFilePath, ghsFilePath):
  ignoreLine = True
  symbols = {}
  proc, output = RBSYS_call_proc.call_proc([os.path.join(ghsFilePath, "gnm.exe"), "-no_dotdot", elfFilePath], return_output = True)
  #f = open("debug.txt", "w+")
  for line in output.splitlines():
    if(line.startswith("[1]")):
      ignoreLine = False
    if(ignoreLine):
      continue

    _, address, size, typ, binding, _, section, name = [s.strip() for s in line.split("|")]
    
    objFile = ""
    loc = name.find("..")
    if(loc != -1):
      name, objFile = (name[:loc], name[loc:])
      objFile = objFile.replace("..C", "")
      objFile = objFile.replace(".3A", ":")
      objFile = objFile.replace(".5C", "/")
    if(name not in symbols):
      symbols[name] = [Symbol(name, int(address), int(size), typ, section, binding, objFile)]
    else:
      symbols[name].append(Symbol(name, int(address), int(size), typ, section, binding, objFile))

  #f.close()
  return symbols

