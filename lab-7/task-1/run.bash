#!/usr/bin/bash

# compilation
echo "compiling server program"
gcc -g Server.c -o srvr

echo "compiling client program"
gcc -g Client.c -o clnt

echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo "Starting server..."

if [ -n $1 ]; then
	./srvr $1 &
else
	./srvr 5000 &
fi

sleep 5

echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo "Starting client..."

if [ -n $1 ]; then
	./clnt $1
else
	./clnt 5000
fi

rm -rf srvr clnt
