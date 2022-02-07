#!/bin/sh


for i in $(seq 1 1 100)
do
	echo "SET $i"
	echo "SET key_$i 0" | redis-cli -h myredis
done


while true
do
	for i in $(seq 1 1 100)
	do
		echo "INCR $i"
		echo "INCR key_$i" | redis-cli -h myredis
	done
done
