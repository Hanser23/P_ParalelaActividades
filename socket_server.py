import socket

HOST = '192.168.100.28'
PORT = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.bind((HOST, PORT))
    server_socket.listen()
    print(f"[Servidor] Esperando conexión en {HOST}:{PORT}...")
    conn, addr = server_socket.accept()
    with conn:
        print(f"[Servidor] Conectado por {addr}")
        data = conn.recv(1024).decode()
        print(f"[Servidor] Mensaje recibido: {data}")
        conn.sendall("Mensaje recibido correctamente.".encode())