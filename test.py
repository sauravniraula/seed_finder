import ctypes
cfunc = ctypes.CDLL("./shr.so")

cfunc.retChar.restype = ctypes.pointer

# i = cfunc.retChar()