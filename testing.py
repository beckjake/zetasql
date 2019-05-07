import ctypes
dll = ctypes.CDLL('./bazel-bin/zetasql/python/libffi.so')

def main():
    dll.get_statement_parts.argtypes = [ctypes.c_char_p]
    rc = dll.get_statement_parts('hello!'.encode('utf-8'))
    print('rc={}'.format(rc))
    rc = dll.get_statement_parts('select * from whatever'.encode('utf-8'))
    print('rc={}'.format(rc))


if __name__ == '__main__':
    main()
