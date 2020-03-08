# Raspberry Pi agnostics utility - template file for test definition
# Shebang lines are ignored - invoke using e.g. 'sh mytest.sh'.

# *** N.B. - shell compatibility ***
# Agnostics calls /bin/sh, which is the dash shell on Debian Buster -
# beware of bashisms if you use bash to develop your test script.
# See https://wiki.archlinux.org/index.php/Dash for background info on dash.

# NAME - name of test as it should appear in the GUI
#NAME=SD Card Speed Test

# DESC - Brief description of what the test does
#DESC=Determines whether an SD card can read and write data fast enough to provide adequate performance.\n\nShould be run on a new or newly-formatted SD card.

# Put code that performs the test here.

# agnostics captures all output the test script sends to stdout and stderr and add this to its log file

# Script must return 0 if test passed, 1 if test failed.
# return $pass
