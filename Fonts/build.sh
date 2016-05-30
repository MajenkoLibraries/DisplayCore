#!/bin/bash

mkdir -p Preview

echo > MakeFonts.cpp

for A in */*.h; do 
    echo "#include \"$A\"" >> MakeFonts.cpp
    B=`basename $A .h`;
done

echo >> MakeFonts.cpp
echo "extern void makeFont(const char *family, const char *name, const uint8_t *data);" >> MakeFonts.cpp
echo >> MakeFonts.cpp

echo "void makeFonts() {" >> MakeFonts.cpp
for F in */*.h; do 
    B=`basename $F .h`;
    FLIST=`grep 'extern const uint8_t .*\[\];' $F | awk '{print $4}' | cut -f1 -d'['`
    for A in $FLIST; do
        echo "    makeFont(\"$B\", \"$A\", Fonts::$A);" >> MakeFonts.cpp
    done
done
echo "}" >> MakeFonts.cpp

echo -n "SRCS=" > Makefile
for A in */*.cpp; do echo -n "$A " >> Makefile; done
echo >> Makefile
echo 'OBJS=$(SRCS:%.cpp=%.o)' >> Makefile
echo 'BIN=MakeFonts' >> Makefile

echo 'CFLAGS=-D__PIC32MX__ -I.' >> Makefile
for A in */*.h; do 
    D=`dirname $A`
    echo "  CFLAGS+=-I./$D" >> Makefile
done

echo 'CXXFLAGS=$(CFLAGS)' >> Makefile
echo 'LDFLAGS=-lgd' >> Makefile
echo >> Makefile
echo 'MakeFonts: main.o MakeFonts.o $(OBJS)' >> Makefile

echo >> Makefile
echo "clean:" >> Makefile
echo '	rm -f $(OBJS) main.o MakeFonts.o $(BIN)' >> Makefile

make

