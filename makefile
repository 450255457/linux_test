EXE	=	Server

all	:	$(EXE)

$(EXE)	:	main.cpp tuobao_tcpclient.h
    g++ -g -o $(EXE) main.cpp tuobao_tcpclient.cpp

#.PHONY表示clean是个伪目标文件
.PHONY	:	clean
clean	: 
    -rm -f $(EXE)
