class RAMStorage:
    def __init__(self, blocks, block_size=512):
        self.blocks = blocks
	self.block_size = block_size
	self.data = bytearray(blocks * block_size)

    def readblocks(self, n, buf):
        #print("readblocks(%s, %x(%d))" % (n, id(buf), len(buf)))
        for i in range(len(buf)):
            buf[i] = self.data[n * self.block_size + i]

    def writeblocks(self, n, buf):
        #print("writeblocks(%s, %x)" % (n, id(buf)))
        for i in range(len(buf)):
            self.data[n * self.block_size + i] = buf[i]

    def ioctl(self, op, arg):
        #print("ioctl(%d, %r)" % (op, arg))
        if op == 4:  # BP_IOCTL_SEC_COUNT
            return len(self.data) // self.block_size
        if op == 5:  # BP_IOCTL_SEC_SIZE
            return self.block_size
