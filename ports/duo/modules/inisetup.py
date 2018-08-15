import uos
import pyb
from flashstorage import flashStorage

def fs_corrupted():
    while 1:
        print("""\
The FAT filesystem starting at sector %d with size %d sectors appears to
be corrupted. If you had important data there, you may want to make a flash
snapshot to try to recover it. Otherwise, perform factory reprogramming
of MicroPython firmware (completely erase flash, followed by firmware
programming).
""" % (flashStorage.START_SEC, flashStorage.blocks))
        pyb.delay(3000)

def setup():
    print("Performing initial setup")
    uos.VfsFat.mkfs(flashStorage)
    vfs = uos.VfsFat(flashStorage)
    uos.mount(vfs, '/')
    with open("boot.py", "w") as f:
        f.write("""\
# This file is executed on every boot (including wake-boot from deepsleep)
""")
    return vfs
