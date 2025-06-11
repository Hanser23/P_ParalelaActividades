from xmlrpc.server import SimpleXMLRPCServer

def cuadrado(numero):
    return numero * numero

server = SimpleXMLRPCServer(("localhost", 8000))
print("Servidor RPC activo en puerto 8000...")

server.register_function(cuadrado, "cuadrado")

server.serve_forever()
