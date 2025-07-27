import time

class Nodo:
    def __init__(self, id):
        self.id = id
        self.estado = "Follower"
        self.term = 0
        self.votos = 0
        self.lider = None
        self.valor = None
        self.vivo = True

    def iniciar_eleccion(self, nodos):
        if not self.vivo:
            return
        self.estado = "Candidate"
        self.term += 1
        self.votos = 1  
        print(f"Nodo {self.id} se postula en el término {self.term}")

        for nodo in nodos:
            if nodo.id != self.id and nodo.vivo:
                if nodo.dar_voto(self.term):
                    self.votos += 1

        if self.votos > len(nodos) // 2:
            self.estado = "Leader"
            self.lider = self.id
            print(f"Nodo {self.id} ha sido elegido líder\n")
            return True
        else:
            print(f"Nodo {self.id} no logró mayoría\n")
            self.estado = "Follower"
            return False

    def dar_voto(self, term):
        if not self.vivo:
            return False
        if term >= self.term:
            self.term = term
            return True
        return False

    def replicar_valor(self, nodos, valor):
        if self.estado != "Leader" or not self.vivo:
            return
        print(f"Nodo líder {self.id} replicando valor: {valor}")
        for nodo in nodos:
            if nodo.vivo:
                nodo.valor = valor
        print("Valor replicado en nodos activos\n")

    def simular_fallo(self):
        self.vivo = False
        print(f"Nodo {self.id} ha fallado")

    def recuperar(self):
        self.vivo = True
        self.estado = "Follower"
        print(f"Nodo {self.id} ha vuelto a estar activo")


nodos = [Nodo(i) for i in range(3)]

nodos[0].iniciar_eleccion(nodos)

nodos[0].replicar_valor(nodos, "A=1")

nodos[0].simular_fallo()

time.sleep(1)
print("\nDetectando fallo... nueva elección en curso...")
nodos[1].iniciar_eleccion(nodos)

nodos[1].replicar_valor(nodos, "A=2")
