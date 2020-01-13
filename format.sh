# required: astyle

astyle --style=java include/*.h
astyle --style=java kernel/*.c
astyle --style=java drivers/display/*.c
astyle --style=java drivers/keyboard/*.c

find . -name *.orig | xargs rm -f
