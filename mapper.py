#!/usr/bin/env python3
import sys

# Lectura línea por línea
for line in sys.stdin:
    # Eliminar espacios y saltos
    line = line.strip()
    # Dividir en palabras
    words = line.split()
    # Emitir cada palabra con valor 1
    for word in words:
        print(f"{word}\t1")