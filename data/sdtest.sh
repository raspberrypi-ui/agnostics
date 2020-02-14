#!/bin/bash
#NAME=SD Card Speed Test
#DESC=This test determines whether an SD card can read and write data fast enough to provide adequate performance in a Raspberry Pi.
#CAT=SD Card
RES=$(fio --output-format=terse ./sd_bench.fio | cut -f 3,45,86 -d";" -)
echo "$RES"
prep=$(echo "$RES" | head -n 1 | cut -d ";" -f 3 | cut -d "." -f 1)
swri=$(echo "$RES" | head -n 2 | tail -n 1 | cut -d ";" -f 3 | cut -d "." -f 1)
rwri=$(echo "$RES" | head -n 3 | tail -n 1 | cut -d ";" -f 3 | cut -d "." -f 1)
rrea=$(echo "$RES" | head -n 4 | tail -n 1 | cut -d ";" -f 2 | cut -d "." -f 1)
# some arbitrary pass/fail criteria here for now...
pass=0
if [ "$prep" -lt 9000 ] ; then
    echo "Prepare speed - FAIL"
    pass=1
fi
if [ "$swri" -lt 7500 ] ; then
    echo "Sequential write speed - FAIL"
    pass=1
fi
if [ "$rwri" -lt 2500 ] ; then
    echo "Random write speed - FAIL"
    pass=1
fi
if [ "$rrea" -lt 9000 ] ; then
    echo "Random read speed - FAIL"
    pass=1
fi
if [ "$pass" -eq 0 ] ; then
    echo "All tests passed"
fi
return $pass
