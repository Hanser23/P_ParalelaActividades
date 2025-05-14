import multiprocessing
import time

# Información de Hanser
nombre = "Hanser López"
edad = 22
hobies = ["jugar voleibol", "descansar escuchando música"]

# Funciones que simulan las actividades
def jugar_voleibol():
    for i in range(3):
        print(f"{nombre} está jugando voleibol... (partida {i+1})")
        time.sleep(2)

def descansar():
    for i in range(3):
        print(f"{nombre} está descansando y escuchando música... (minuto {i+1})")
        time.sleep(1.5)

if __name__ == "__main__":
    print(f"Hola, soy {nombre}, tengo {edad} años y me encanta {hobies[0]} y {hobies[1]}.")
    print("Hoy haré mis actividades favoritas usando multiprocessing")

    # Crear los procesos
    proceso_voleibol = multiprocessing.Process(target=jugar_voleibol)
    proceso_descanso = multiprocessing.Process(target=descansar)

    # Iniciar ambos procesos
    proceso_voleibol.start()
    proceso_descanso.start()

    # Esperar que terminen
    proceso_voleibol.join()
    proceso_descanso.join()

    print("Hanser ha terminado sus actividades del día ¡Buen trabajo!")
