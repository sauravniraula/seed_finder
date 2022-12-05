import math
import ctypes


class Sbiomes(ctypes.Structure):
  _fields_= [
    ("biomeInfoArr", (ctypes.c_int * 3) * 100),
    ("spawn", (ctypes.c_int * 2)),
    ("spawnOn", ctypes.c_int),
    ("totalBiomes", ctypes.c_int)
  ]

def get_distance(cood1, cood2):
  return math.sqrt(math.pow(cood1[0] - cood2[0], 2) + math.pow(cood1[1] - cood2[1], 2))