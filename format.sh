# required: astyle

astyle --style=java include/*.h
astyle --style=java kernel/*.c
astyle --style=java drivers/display/textmode/*.c
astyle --style=java drivers/display/vesa/*.c
astyle --style=java drivers/keyboard/*.c

find . -name *.orig | xargs rm -f
