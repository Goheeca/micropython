import spark

class FlashStorage:

    SEC_SIZE = spark.sFlash.sector_size()
    START_SEC = spark.sFlash.start() // SEC_SIZE
    NUM_BLK = spark.sFlash.size() // SEC_SIZE #+ 1

    def __init__(self, blocks=NUM_BLK):
        self.blocks = blocks

    def readblocks(self, n, buf):
        spark.sFlash.read((n + self.START_SEC) * self.SEC_SIZE, buf)

    def writeblocks(self, n, buf):
        spark.sFlash.erase((n + self.START_SEC) * self.SEC_SIZE)
        spark.sFlash.write((n + self.START_SEC) * self.SEC_SIZE, buf)

    def ioctl(self, op, arg):
        if op == 4:  # BP_IOCTL_SEC_COUNT
            return self.blocks
        if op == 5:  # BP_IOCTL_SEC_SIZE
            return self.SEC_SIZE

    def mk_partition_info(self, buf, pos, boot, fat_type, start_block, num_blocks):
        buf[0+pos] = boot
        buf[1+pos] = 0xff
        buf[2+pos] = 0xff
        buf[3+pos] = 0xff
        buf[4+pos] = fat_type
        buf[5+pos] = 0xff
        buf[6+pos] = 0xff
        buf[7+pos] = 0xff

        buf[8+pos] = start_block & 0xff
        buf[9+pos] = start_block >> 8
        buf[10+pos] = start_block >> 16
        buf[11+pos] = start_block >> 24

        buf[12+pos] = num_blocks & 0xff
        buf[13+pos] = num_blocks >> 8
        buf[14+pos] = num_blocks >> 16
        buf[15+pos] = num_blocks >> 24

    def mk_fake_mbr(self, buf):
        self.mk_partition_info(buf, 446, 0, 0x01, self.START_SEC + 1, self.NUM_BLK - 1)
        self.mk_partition_info(buf, 462, 0, 0, 0, 0)
        self.mk_partition_info(buf, 478, 0, 0, 0, 0)
        self.mk_partition_info(buf, 494, 0, 0, 0, 0)
        buf[510] = 0x55
        buf[511] = 0xaa

flashStorage = FlashStorage()
