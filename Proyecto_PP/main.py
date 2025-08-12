import numpy as np, ctypes, os, json
from fastapi import FastAPI
app = FastAPI()

lib = ctypes.CDLL("/app/libnormalize.so")  # expone normalize_cuda & normalize_omp
lib.normalize_cuda.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_int]
lib.normalize_omp.argtypes  = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_int]

def has_cuda():
    return os.path.exists("/dev/nvidia0")  # simple check en ACA GPU

@app.post("/run")
def run(payload: dict):
    arr = np.array(payload["data"], dtype=np.float32, copy=True)
    minv, maxv = float(arr.min()), float(arr.max())
    if has_cuda():
        # copiar a device (usando cuda Python bindings mínimos vía ctypes + cudaMemcpy en lib si prefieres)
        # para simplificar, aquí usaríamos CuPy si lo incluyes en la imagen
        import cupy as cp
        d = cp.asarray(arr)
        lib.normalize_cuda(int(d.data.ptr), minv, maxv, arr.size)
        arr = cp.asnumpy(d)
    else:
        ptr = arr.ctypes.data_as(ctypes.c_void_p)
        lib.normalize_omp(ptr, minv, maxv, arr.size)
    return {"min":minv, "max":maxv, "data":arr.tolist()}
