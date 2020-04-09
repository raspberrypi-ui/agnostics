#!/bin/bash
#NAME=SD Card Speed Test
#DESC=Determines whether an SD card can read and write data fast enough to provide adequate performance.\n\nShould be run on a new or newly-formatted SD card.
for i in 1 2 3
do
    echo "Run" $i
    RES=$(fio --output-format=terse --max-jobs=4 /usr/share/agnostics/sd_bench.fio | cut -f 3,7,8,48,49 -d";" -)
    echo "$RES"
    swri=$(echo "$RES" | head -n 2 | tail -n 1 | cut -d ";" -f 4)
    rwri=$(echo "$RES" | head -n 3 | tail -n 1 | cut -d ";" -f 5)
    rrea=$(echo "$RES" | head -n 4 | tail -n 1 | cut -d ";" -f 3)
    pass=0
    if [ "$swri" -lt 10000 ] ; then
        echo "Sequential write speed $swri KB/sec (target 10000) - FAIL"
        echo "Note that sequential write speed declines over time as a card is used - your card may require reformatting"
        pass=1
    else
        echo "Sequential write speed $swri KB/sec (target 10000) - PASS"
    fi
    if [ "$rwri" -lt 500 ] ; then
        echo "Random write speed $rwri IOPS (target 500) - FAIL"
        pass=1
    else
        echo "Random write speed $rwri IOPS (target 500) - PASS"
    fi
    if [ "$rrea" -lt 1500 ] ; then
        echo "Random read speed $rrea IOPS (target 1500) - FAIL"
        pass=1
    else
        echo "Random read speed $rrea IOPS (target 1500) - PASS"
    fi
    rm -f /var/tmp/sd.test.file
    if [ "$pass" -eq 0 ] ; then
        return $pass
    fi
done
return $pass
