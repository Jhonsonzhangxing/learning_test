#!/bin/bash

pid=$(ps -ef | grep sr_service | grep -v grep | awk '{print $2}')
echo $pid

while [ true  ]
do
	sudo pmap -x $pid >> /tmp/pmap.txt
	sudo vmstat 2 1 >> /tmp/vmstate.txt
	echo "sleeping ....."
	sleep 3m
done




