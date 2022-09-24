from socket import SO_J1939_ERRQUEUE
import sys
import os

def cmd(s):
  print(s)
  os.system(s)


cmd("make")

