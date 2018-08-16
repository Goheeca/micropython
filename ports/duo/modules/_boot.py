import gc
gc.threshold((gc.mem_free() + gc.mem_alloc()) // 4)
import uos
from flashstorage import flashStorage
#from pyb import RGB

#RGB.control(True)
#RGB.color([0,255,0])
try:
    if flashStorage:
	#RGB.color([255,0,0])
        uos.mount(flashStorage, '/')
	#RGB.color([0,0,255])
except OSError:
    import inisetup
    #RGB.color([255,255,0])
    inisetup.setup()
    #RGB.color([0,255,255])

gc.collect()
