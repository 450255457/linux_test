EXE = Server

all : $(EXE)

$(EXE) : main.cpp tuobao_tcpclient.h
    g++ -g -o $(EXE) main.cpp tuobao_tcpclient.cpp

#.PHONY??clean???????
.PHONY : clean
clean : 
    -rm -f $(EXE)
