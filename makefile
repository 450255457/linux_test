objects = tuobao_tcpclient.o httppost.o
httppost: $(objects)
    cc -o httppost $(objects)
tuobao_tcpclient.o: tuobao_tcpclient.h
httppost.o:
.PHONY : clean
clean :
    @echo ÕýÔÚÒÆ³ý
    -rm httppost $(objects)
	
#EXE = Server
#
#all : $(EXE)
#
#$(EXE) : main.cpp tuobao_tcpclient.h
#    g++ -g -o $(EXE) main.cpp tuobao_tcpclient.cpp
#
#.PHONY??clean???????
#.PHONY : clean
#clean : 
#    -rm -f $(EXE)
