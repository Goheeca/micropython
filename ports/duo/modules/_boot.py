import gc
gc.threshold((gc.mem_free() + gc.mem_alloc()) // 4)
import uos
from flashstorage import flashStorage

try:
    if flashStorage:
        uos.mount(flashStorage, '/')
except OSError:
    import inisetup
    inisetup.setup()

gc.collect()
