client_=client
server_=server

cc=gcc

clientSrc=client.c common.c
serverSrc=server.c common.c

.PHONY:all
all:$(client_) $(server_)

$(client_):$(clientSrc)
	$(cc) -o  $(client_)  $^  
$(server_):$(serverSrc)
	$(cc) -o  $@  $^ # $@目标文件 $^所有依赖的文件   


.PHONY:clean
clean:
	rm -f $(client_) $(server_) 