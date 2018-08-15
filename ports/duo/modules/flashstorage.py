import spark

class FlashStorage:

    SEC_SIZE = spark.sFlash.sector_size()
    START_SEC = spark.sFlash.start() // SEC_SIZE
    NUM_BLK = spark.sFlash.size() // SEC_SIZE

    def __init__(self, blocks=NUM_BLK):
        self.blocks = blocks

    def readblocks(self, n, buf):
        #print("readblocks(%s, %x(%d))" % (n, id(buf), len(buf)))
        spark.sFlash.read((n + self.START_SEC) * self.SEC_SIZE, buf)

    def writeblocks(self, n, buf):
        #print("writeblocks(%s, %x(%d))" % (n, id(buf), len(buf)))
        #assert len(buf) <= self.SEC_SIZE, len(buf)
        spark.sFlash.erase(n + self.START_SEC)
        spark.sFlash.write((n + self.START_SEC) * self.SEC_SIZE, buf)

    def ioctl(self, op, arg):
        #print("ioctl(%d, %r)" % (op, arg))
        if op == 4:  # BP_IOCTL_SEC_COUNT
            return self.blocks
        if op == 5:  # BP_IOCTL_SEC_SIZE
            return self.SEC_SIZE

flashStorage = FlashStorage()
