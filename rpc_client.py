import xmlrpc.client

proxy = xmlrpc.client.ServerProxy("http://localhost:8000/")

try:
    numero = int(input("Ingresa un número para obtener su cuadrado: "))
    resultado = proxy.cuadrado(numero)
    print(f"El cuadrado de {numero} es: {resultado}")
except Exception as e:
    print("Error en la llamada RPC:", e)
5