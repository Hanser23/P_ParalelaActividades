import random
import string

def generar_palabra(longitud=5):
    return ''.join(random.choices(string.ascii_lowercase, k=longitud))

def generar_linea(palabras_por_linea=100):
    return ' '.join(generar_palabra() for _ in range(palabras_por_linea))

# Generar archivo de ~100MB
with open("texto_100mb.txt", "w", encoding="utf-8") as f:
    size = 0
    while size < 100 * 1024 * 1024:  # 100MB
        linea = generar_linea() + "\n"
        f.write(linea)
        size += len(linea.encode("utf-8"))

print("Archivo generado: texto_100mb.txt (~100MB)")
