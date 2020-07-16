import time
import sys

from signals import PilotSignal

def karetka(sender):
    while True:
        sender.send(PilotSignal.Red)
        time.sleep(0.3)
        yield
        sender.send(PilotSignal.Blue)
        time.sleep(0.3)
        yield

def doNothing(sender):
    while True:
        yield

def killThread(sender):
    #sender.lock.release()
    sys.exit()
    yield

options = {
    "Karetka" : karetka,
    "Nic" : doNothing
    }
