import socket
import sys

host = sys.argv[1]
port = int(sys.argv[2])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))

while True:
    command = input("Enter msg for Server: ")   
    if(command == "Exit"):
        break
    s.send(str.encode(command))    
    reply = s.recv(1024)
    print("Pi Server: " + reply.decode('utf-8'))

print("Connection closed")  
s.close()           
