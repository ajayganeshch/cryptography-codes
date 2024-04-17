import socket

HEADER = 64 #how much length of msg we are reciveing ("hello" , so 5____ (64))
PORT = 5050
SERVER = '127.0.0.1' # Use localhost if server is on the same machine
FORMAT = 'utf-8'
DICONNECT = "!Disconnect"

ADDR = (SERVER,PORT)

client = socket.socket(socket.AF_INET,socket.SOCK_STREAM) # Family, Type
client.connect(ADDR)

def send(msg):
    message = msg.encode(FORMAT)
    msg_length = len(message)
    
    encode_msg_length = str(msg_length).encode(FORMAT)
    padded_encode_msg_length = encode_msg_length + b' ' * (HEADER - len(encode_msg_length))
    
    client.send(padded_encode_msg_length)
    client.send(message)
    print(client.recv(2048).decode(FORMAT))



values = ["a value: ", "b value: ","p value: ","any point value (x,y) p1: ", "any point value (x,y) p2: ","point value to find inverse of that (x,y): ","k value: ","k*p enter point p value(x,y): "]

for value in values:
    send(input(f"Enter {value}"))


send(DICONNECT)