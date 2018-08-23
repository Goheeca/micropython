import gc
gc.threshold((gc.mem_free() + gc.mem_alloc()) // 4)
import uos
from flashstorage import flashStorage
#from ramstorage import RAMStorage

try:
    if flashStorage:
        uos.mount(flashStorage, '/')
except OSError:
    print("Performing initial setup")
    uos.VfsFat.mkfs(flashStorage)
    vfs = uos.VfsFat(flashStorage)
    uos.mount(vfs, '/')
    with open("boot.py", "w") as f:
        f.write("""\
#This file is executed on every boot
""")
    with open("main.py", "w") as f:
        f.write("""\
#This file is executed on every boot in friendly repl mode
""")

gc.collect()
