cc=gcc
tem=temperature_server

targets:
	${cc}  ${tem}.c -o tem_server -lsqlite3

static:
	${cc} -c ${tem}.c
	ar -rcs libtem.a ${tem}.o
	rm *.o

dynamic:
	${cc} -shared -fPIC -o libtem.so ${tem}.c

clear:
	rm -rf tem_server
