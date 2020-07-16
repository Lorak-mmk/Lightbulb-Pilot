#!/bin/python
import tkinter as tk
import time

from modes import options
from signals import PilotSignal
from sender import Sender


class Application(tk.Frame):
    def __init__(self, master=None, sender=None):
        super().__init__(master)
        self.master = master
        self.pack()

        self.sender = sender
        self.pbuttons = []
        self.frames = []


        self.create_widgets()

    def create_frame(self, side='top', master=None):
        if master == None:
            master = self.master
        frame = tk.Frame(master)
        frame.pack(side=side)
        self.frames.append(frame)
        return frame

    def add_buttons(self, sigs):
        frame = self.create_frame()
        for sig in sigs:
            button = tk.Button(master=frame, text=sig.name, command= lambda sig=sig: self.sender.send(sig))
            button.pack(side='left')
            self.pbuttons.append(button)

    def create_widgets(self):
        self.add_buttons(list(PilotSignal)[0:1])
        self.add_buttons(list(PilotSignal)[1:4])

        self.add_buttons(list(PilotSignal)[4:8])
        self.add_buttons(list(PilotSignal)[8:12])
        self.add_buttons(list(PilotSignal)[12:16])
        self.add_buttons(list(PilotSignal)[16:19])
        self.add_buttons(list(PilotSignal)[19:22])

        self.select_var = tk.StringVar()
        self.select_var.set("Nic")

        frame = self.create_frame()
        for k, v in options.items():
            b = tk.Radiobutton(frame, text=k, variable=self.select_var, value=k, command=lambda: self.update_mode(), indicatoron=False)
            b.pack(side='left')
            self.pbuttons.append(b)

        self.quit = tk.Button(self, text='QUIT', fg='red', command=lambda: self.close())
        self.quit.pack(side='top')

    def update_mode(self):
        print('Entered Application.update_mode ' + self.select_var.get())
        #self.sender.lock.acquire()
        self.sender.proc = options[self.select_var.get()](self.sender)
        #self.sender.lock.release()

    def close(self):
        print('Entered Application.close')
        self.sender.close()
        self.master.destroy()


if __name__ == '__main__':
    filename = '/dev/ttyUSB0'
    sender = Sender(filename)

    root = tk.Tk()
    app = Application(master=root, sender=sender)
    app.mainloop()
