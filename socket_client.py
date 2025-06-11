import socket

HOST = '192.168.100.28'
PORT = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
    client_socket.connect((HOST, PORT))
    mensaje = input("Ingrese el mensaje para el servidor: ")
    client_socket.sendall(mensaje.encode())
    data = client_socket.recv(1024).decode()
    print(f"[Cliente] Respuesta del servidor: {data}")
