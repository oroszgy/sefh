#/ /bin/bash

# Creates class file
gcj -C ./com/weblib/linguist/Humor.java
# Generates CNI header
rm ./com/weblib/linguist/Humor.h
gcjh ./com/weblib/linguist/Humor.class
# Creates object file
gcj -fjni -g -c ./com/weblib/linguist/Humor.java
