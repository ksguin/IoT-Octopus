import socket
import sys
import select
import queue

host = ''
port = int(sys.argv[1])

bufferSize = 1024

msg = 'Received By Pi'

def setupServer():
    server= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setblocking(0)
    print("Socket created.")
    try:
        server.bind((host, port))
    except socket.error as err:
        print(err)
    print("Socket bind comlete.")
    return server


def Connections(server):
    server.listen(5) # Allows five connections at a time.
    incoming = [ server ]
    outgoing = [ ]
    reading_writing(server,incoming,outgoing)


def reading_writing(server,incoming,outgoing):
    timeout = 100
    while incoming:

        #print('Waiting for New Event\n')
        reading_conn, writing_conn, error_conn = select.select(incoming, outgoing, incoming, timeout)

        if not (reading_conn or writing_conn or error_conn):
            print('\nTimout',file=sys.stderr)
            continue

        for s in reading_conn:   
            reading(s,server,incoming,outgoing)

        for s in writing_conn:
            writing(s,incoming,outgoing)
        for s in error_conn:
            exception(s,incoming,outgoing)    


def reading(s,server,incoming,outgoing):
    if s is server:
        accept_connection(s,incoming,outgoing) 
    else:
        receive(s,incoming,outgoing) 

def accept_connection(s,incoming,outgoing):
    conn, address = s.accept()
    print("Connected to: " + address[0] + ":" + str(address[1]))
    conn.setblocking(0)
    incoming.append(conn)


def receive(s,incoming,outgoing):
    data = s.recv(bufferSize)
    data = data.decode('utf-8')
    if data:
        print('%s : %s' % (s.getpeername(),data))
        if s not in outgoing:
            outgoing.append(s)
    else:
        print('closing', s.getpeername() , 'after reading no data', file=sys.stderr)
        if s in outgoing:
            outgoing.remove(s)
        incoming.remove(s)
        s.close()

def writing(s,incoming,outgoing):
    print('Msg sent to' , s.getpeername())
    s.send(str.encode(msg)) 
    outgoing.remove(s)        


def exception(s,incoming,outgoing):
    print('handling exceptional condition for', s.getpeername(), file=sys.stderr)
    incoming.remove(s)
    if s in outgoing:
        outgoing.remove(s)
    s.close()    


def main():
    s = setupServer()
    Connections(s)

if __name__ == '__main__':
    main()    

