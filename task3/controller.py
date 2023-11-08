import os
import sys
import signal

produced = 0

def sigusr1_handler(signum, frame):
    print(f'Produced: {produced}', file=sys.stderr)
    
def main():
    global produced

    signal.signal(signal.SIGUSR1, sigusr1_handler)

    pipe_1_0_read, pipe_1_0_write = os.pipe()
    pipe_0_2_read, pipe_0_2_write = os.pipe()
    pipe_2_0_read, pipe_2_0_write = os.pipe()

    print(os.getpid())

    pid1 = os.fork()
    
    if pid1 == 0:
        # P1
        os.close(pipe_1_0_read)  
        os.dup2(pipe_1_0_write, 1)
        os.execve("/bin/python3", ["/bin/python3", "producer.py"], os.environ)

    pid2 = os.fork()

    if pid2 == 0:
        # P2
        os.close(pipe_0_2_write) 
        os.close(pipe_2_0_read)
        os.dup2(pipe_0_2_read, 0)
        os.dup2(pipe_2_0_write, 1)
        os.execve("/usr/bin/bc", ["/usr/bin/bc"], os.environ)

    # P0
    os.close(pipe_1_0_write)
    os.close(pipe_0_2_read)
    os.close(pipe_2_0_write)

    while True:
        expression = os.read(pipe_1_0_read, 100).decode()
        if not expression:
            break
        
        os.write(pipe_0_2_write, expression.encode())
        result = os.read(pipe_2_0_read, 100).decode()
        print(f"{expression.strip()} = {result.strip()}")
        produced += 1

if __name__ == "__main__":
    main()