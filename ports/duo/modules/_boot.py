import gc
gc.threshold((gc.mem_free() + gc.mem_alloc()) // 4)
import uos
from _flashstorage import flashStorage

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
# boot.py -- runs after the device boots up
""")
    with open("main.py", "w") as f:
        f.write("""\
# main.py -- put your code here!
""")

gc.collect()

del flashStorage, uos, gc
