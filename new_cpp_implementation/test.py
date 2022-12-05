from cmath import log
import ctypes

shared_file_path = "./shared_python.so"
cfunc = ctypes.CDLL(shared_file_path)

class Sbiomes(ctypes.Structure):
  _fields_= [
    ("biomeInfoArr", (ctypes.c_int * 3) * 100),
    ("totalBiomes", ctypes.c_int)
  ]

cfunc.getBiomeInfo.restype = Sbiomes
a = cfunc.getBiomeInfo(0, 18, 100, 1000)
print(a.__dir__())