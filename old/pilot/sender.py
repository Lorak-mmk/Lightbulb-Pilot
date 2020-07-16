import serial
from threading import Thread

from modes import doNothing, killThread

class Sender():
    def __init__(self, filename):
        self.ser = serial.Serial(filename)

        self.proc = doNothing(self)

        self.th = Thread(target=self.thread_func)
        self.th.start()

    def send(self, sig):
        self.ser.write(hex(sig.value)[2:].upper().encode() + b'\n')
        #print(f'Send {sig.name} : {hex(sig.value)}')

    def __del__(self):
        self.ser.close()

    def close(self):
        print('Entered Sender.close()')
        self.proc = killThread(self)
        self.th.join()

    def thread_func(self):
        print('Entered Sender.thread_func')
        while True:
            next(self.proc)
