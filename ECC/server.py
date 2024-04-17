import socket
import threading


HEADER = 64 # How much length of msg we are reciveing ("hello" , so 5____ (64))
PORT = 5050
# SERVER =  socket.gethostbyname(socket.gethostname())

SERVER = '0.0.0.0'
ADDR = (SERVER,PORT) # must be in tuple
FORMAT = 'utf-8'
DICONNECT_MSG = "!Disconnect"

server = socket.socket(socket.AF_INET,socket.SOCK_STREAM) # Family, Type

server.bind(ADDR)

def generate_points(a,b,p):
    #y^2 mod p = (x^3 + a*x + b) mod p
    
    # Generate points
    points = []
    for x in range(p):
        for y in range(p):
            if (y*y - ((x*x*x) + a*x + b)) % p == 0:
                points.append((x, y))
    
    return points


def calculate_point(x1, y1, x2, lambda_value,p):
    x3 = (lambda_value * lambda_value - x1 - x2) % p
    y3 = (lambda_value * (x1 - x3) - y1) % p
    
    return (x3, y3)


def add_different_points(point1, point2,p):
    x1, y1 = point1
    x2, y2 = point2
    
    # lambda_value = (y2 - y1) / (x2 - x1)
    lambda_value = ((y2 - y1) * pow(x2 - x1, p - 2, p)) % p # For more accuracy we use this formula
    
    return calculate_point(x1, y1, x2, lambda_value,p)


def add_same_points(point,a,p):
    x1, y1 = point
    
    # lambda_value = ((3 * x1 * x1) + a) / (2 * y1)
    lambda_value = ((3 * x1 * x1 + a) * pow(2 * y1, p - 2, p)) % p # For more accuracy we use this formula
    
    return calculate_point(x1, y1, x1, lambda_value,p)


def add_points(point1,point2,p,a):
    
    if point1 == point2: # Same points (p1 = p2)
        return add_same_points(point1,a,p)
    elif point1[0] == point2[0] and (point1[1] != point2[1] or point1[1] == 0): # Two points are "additive inverses" of each other
        return None #the point at infinity or zero point
    else: # Different Points (p1 != p2)
        return add_different_points(point1,point2,p)
    

def inverse_point(point,p):
    return (point[0], -point[1] % p)


def point_multiplied_by_k(point,p,a,k):
    result = None  # Point at infinity
    
    for _ in range(k):
        if result is None:
            result = point
        else:
            result = add_points(point, result, p, a)
    return result


#Handle Individual Connection b/w server and client
def handle_client(conn,addr):
    print(f"New connection {addr} connected")
    
    connected = True
    
    recived_values = [] #0 - a , 1- b , 2- p , 3 - p1(x,y) , 4 - p2(x,y) , 5 - point to find inverse , 6 - k , 7 - point for k*p
    
    try:
        while connected:
            try:
                msg_length = conn.recv(HEADER).decode(FORMAT)
            except ConnectionResetError:
                print(f"Connection lost with {addr}.")
                break
            
            
            if msg_length:
                msg_length = int(msg_length)
                msg = conn.recv(msg_length).decode(FORMAT)
                
                if msg == DICONNECT_MSG:
                    connected = False
                    conn.send("Successfully disconnected".encode(FORMAT))
                    break
                
                recived_values.append(msg)
                conn.send("Server: Message Recived!".encode(FORMAT))
        
        
        a = int(recived_values[0])
        b = int(recived_values[1])
        p = int(recived_values[2])
        
        k = int(recived_values[6])
        
        # Points Generation
        print(f"\nGenerated Points over Curve:\n{generate_points(a,b,p)}")
        
        # Input points refactoring
        point1 = recived_values[3].split(",")
        
        point2 = recived_values[4].split(",")
        
        point1 = [int(point1[0].strip()),int(point1[1].strip())]
        point2 = [int(point2[0].strip()),int(point2[1].strip())]
        
        
        # Add Two Points
        print(f"\nAddition Of Two Points {point1} and {point2} : {add_points(point1,point2,p,a)}")

        
        # Inverse of point
        point = recived_values[5].split(",")
        point = [int(point[0].strip()),int(point[1].strip())]
        
        print(f"\nThe value of -{point} is : {inverse_point(point1,p)}")
        
        # k * point (x,y)
        point = recived_values[7].split(",")
        point = [int(point[0].strip()),int(point[1].strip())]
        
        print(f"\nThe value of {k} * {point} : {point_multiplied_by_k(point1,p,a,k)}")
        
    except:
        print(f"Something Went Wrong.")
    finally:
        conn.close()
        


# Handle New Connections
def start():
    server.listen()
    print(f"Server is listening on {SERVER}")
    
    while True:
        conn, addr = server.accept();
        # conn (socket) -> to comunicate back to the client this object is used
        # addr -> client address, what port and ip address
        
        thread = threading.Thread(target=handle_client,args=(conn,addr))
        thread.start()
        
        print(f"\nActive connections are: {threading.active_count()-1}") # Amount of thread means how many clients connected to server
        # 1 thread will always run ie start thread to listen for new connections, so -1

print("Server is Starting....")

start()


# --------------------------------------------------------------

# Test Case 1:

# Input (Client-Side):
'''
Enter a value: 1
Server: Message Recived!
Enter b value: 1
Server: Message Recived!
Enter p value: 23
Server: Message Recived!
Enter any point value (x,y) p1: 3,10
Server: Message Recived!
Enter any point value (x,y) p2: 9,7
Server: Message Recived!
Enter point value to find inverse of that (x,y): 3,10
Server: Message Recived!
Enter k value: 2
Server: Message Recived!
Enter k*p enter point p value(x,y): 3,10
Server: Message Recived!
Successfully disconnected

'''

# Output (Server-Side):

'''
Server is Starting....
Server is listening on 0.0.0.0
New connection ('127.0.0.1', 63138) connected
Active connections are: 1

Generated Points over Curve:
[(0, 1), (0, 22), (1, 7), (1, 16), (3, 10), (3, 13), (4, 0), (5, 4), (5, 19), (6, 4), (6, 19), (7, 11), (7, 12), (9, 7), (9, 16), (11, 3), (11, 20), (12, 4), (12, 19), (13, 7), (13, 16), (17, 3), (17, 20), (18, 3), (18, 20), (19, 5), (19, 18)]

Addition Of Two Points [3, 10] and [9, 7] : (17, 20)

The value of -[3, 10] is : (3, 13)

The value of 2 * [3, 10] : (7, 12)

'''

# --------------------------------------------------------------