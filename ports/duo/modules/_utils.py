import uos
import ucollections
import ubinascii
import ujson
import sys

class AnsiEscaper(object):
    class Color(object):
        BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE = range(30, 38)
        BLACK_BRIGHT, RED_BRIGHT, GREEN_BRIGHT, YELLOW_BRIGHT, BLUE_BRIGHT, MAGENTA_BRIGHT, CYAN_BRIGHT, WHITE_BRIGHT = range(90, 98)
        BG_BLACK, BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE, BG_MAGENTA, BG_CYAN, BG_WHITE = range(40, 48)
        BG_BLACK_BRIGHT, BG_RED_BRIGHT, BG_GREEN_BRIGHT, BG_YELLOW_BRIGHT, BG_BLUE_BRIGHT, BG_MAGENTA_BRIGHT, BG_CYAN_BRIGHT, BG_WHITE_BRIGHT = range(100, 108)

    def __init__(self):
        self.state = set()
        self.enabled = True

    def enable(self, enabled):
        self.enabled = enabled

    def _esc(self):
        if self.enabled:
            print('\x1b[' + ';'.join(map(str, self.state)) + 'm', end='')

    def reset(self):
        self.state.clear()
        self._esc()

    def set(self, *args):
        def update(values, value):
            self.state.difference_update(values)
            self.state.add(value)

        for arg in args:
            fg = list(range(30, 38)) + list(range(90, 98))
            bg = list(range(40, 48)) + list(range(100, 108))
            update(fg, arg)
            update(bg, arg)
        self._esc()

ansiEscaper = AnsiEscaper()

FILE = 0x8000
DIR = 0x4000
BASE64_BLOCK = 3*128
CRC_BLOCK = 1024

def is_type(path, type):
    if path.endswith('/'):
        path = path[:-1]
    return uos.stat(path)[0] == type

def is_dir(path):
    return is_type(path, DIR)

def is_file(path):
    return is_type(path, FILE)

def ilistdir(dirpath, filter_=lambda _: True):
    if dirpath.endswith('/'):
        dirpath = dirpath[:-1]
    return filter(filter_, map(lambda item: (item[0]+('/' if item[1] == DIR else ''),) + tuple(item[1:]), uos.ilistdir(dirpath)))

def listdir(dirpath, filter_=lambda _: True):
    return list(map(lambda item: item[0], ilistdir(dirpath, filter_)))

def subdirs(dir):
    return listdir(dir, filter_=lambda item: item[0].endswith('/'))

def files(dir):
    return listdir(dir, filter_=lambda item: not item[0].endswith('/'))

def touch(filepath):
    if filepath.endswith('/'):
        filepath = filepath[:-1]
        try:
            uos.mkdir(filepath)
        except OSError:
            pass
    else:
        try:
            with open(filepath, 'w'):
                pass
        except OSError:
            pass

def remove(filepath):
    if filepath.endswith('/'):
        filepath = filepath[:-1]
    if is_dir(filepath):
        uos.rmdir(filepath)
    else:
        uos.remove(filepath)

def file_size(file):
    return uos.stat(file)[6]

def file_checksum(file):
    with open(file, 'r') as f:
        size = file_size(file)
        crc32 = 0
        while f.tell() != size:
            crc32 = ubinascii.crc32(f.read(CRC_BLOCK), crc32)
        return crc32

class Walker(object):
    def __init__(self, indent=4):
        self.indent = indent

    def print_padding(self, levels):
        padding = ''
        for i, level in enumerate(levels):
            if level:
                if i+1 == len(levels):
                    padding += '\\' + (self.indent-1) * '-'
                else:
                    padding += self.indent * ' '
            else:
                if i+1 == len(levels):
                    padding += '+' + (self.indent-1) * '-'
                else:
                    padding += '|' + (self.indent-1) * ' '
        print(padding, end='')

    def __call__(self, path='/'):
        levels = []
        stack = []
        stack.append(([], path))
        while len(stack) != 0:
            levels, path = stack.pop()
            ansiEscaper.set(ansiEscaper.Color.YELLOW)
            self.print_padding(levels)
            dir = is_dir(path)
            if dir:
                ansiEscaper.set(ansiEscaper.Color.BLUE_BRIGHT)
            else:
                ansiEscaper.set(ansiEscaper.Color.GREEN)
            name = path[path.rfind('/', None, -1)+1:]
            print(name, end='')
            if not dir:
                ansiEscaper.set(ansiEscaper.Color.WHITE)
                print(' ['+str(file_size(path))+']', end='')
            print()
            if dir:
                files = listdir(path)
                last = True
                for file in reversed(files):
                    stack.append((levels + [last], path + file))
                    last = False
        ansiEscaper.reset()

def tree(path='/', ordered=True, stat=file_size, checksum=file_checksum):
    stack = []
    tree_ = {}
    stack.append((tree_, path, ''))
    while len(stack) != 0:
        subtree, path_, item = stack.pop()
        itempath = path_+item
        if is_dir(itempath):
            subtree[item] = ucollections.OrderedDict() if ordered else {}
            for file in reversed(listdir(itempath)):
                stack.append((subtree[item], itempath, file))
        else:
            subtree[item] = (stat(itempath) if stat else None, checksum(itempath) if checksum else None)
    return tree_['']

walk = Walker(indent=4)

def fsstat():
    stat = uos.statvfs('/')
    return {
        'block_size': stat[0],
        'blocks': stat[2],
        'free_blocks': stat[3],
        'max_file_length': stat[9]
    }

def print_file(filepath):
    with open(filepath, 'r') as f:
        for line in f:
            print(line, end='')
        print('\x00', end='')

def input_file(filepath):
    with open(filepath, 'w') as f:
        try:
            while True:
                line = input()
                f.write(line + '\n')
        except EOFError:
            pass

def print_base64_file(filepath):
    with open(filepath, 'r') as f:
        size = file_size(filepath)
        while f.tell() != size:
            block = f.read(BASE64_BLOCK)
            print(str(ubinascii.b2a_base64(block))[2:-3], end='')
        print()

def input_base64_file(filepath):
    with open(filepath, 'w') as f:
        i = 0
        buf = '\x00\x00\x00\x00'
        while True:
            c = sys.stdin.read(1)
            sys.stdout.write(c)
            buf[i] = c
            i = (i + 1) % 4
            if not ('A' <= c <= 'Z' or 'a' <= c <= 'z' or '0' <= c <= '9' or c == '+' or c == '/' or c == '='):
                break
            f.write(ubinascii.a2b_base64(buf))
            if buf[3] == '=':
                break

def sync():
    actions = {
        'STAT': lambda _: ujson.dumps(fsstat()),
        'INFO': lambda path: ujson.dumps(tree(path, ordered=False)),
        'CREATE': touch,
        'REMOVE': remove,
        'EDIT': input_file,
        'SHOW': print_file,
        'BINEDIT': input_base64_file,
        'BINSHOW': print_base64_file
    }
    try:
        while True:
            try:
                action = input('ACTION ')
                if action in {'STAT'}:
                    action += ' '
                cut = action.find(' ')
                if cut == -1:
                    raise ValueError
                type_, arg_str = action[:cut], action[cut+1:]
                result = actions[type_](arg_str)
                if result:
                    print(result)
                print('\x00OK')
            except Exception as e:
                if isinstance(e, EOFError):
                    raise EOFError
                print('\x00KO')
    except EOFError:
        print('\x00OK')
