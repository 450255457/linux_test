#include "tuobao_tcpclient.h"

int http_post(tuobao_tcpclient *pclient,char *page,char *request,char **response){

    char post[300],host[100],content_len[100];
    char *lpbuf,*ptmp;
    int len=0;

    lpbuf = NULL;
    const char *header2="User-Agent: Tuobao Http 0.1\r\nCache-Control: no-cache\r\nContent-Type: application/x-www-form-urlencoded\r\nAccept: */*\r\n";

    sprintf(post,"POST %s HTTP/1.0\r\n",page);
    sprintf(host,"HOST: %s:%d\r\n",pclient->remote_ip,pclient->remote_port);
    sprintf(content_len,"Content-Length: %d\r\n\r\n",strlen(request));

    len = strlen(post)+strlen(host)+strlen(header2)+strlen(content_len)+strlen(request)+1;
    lpbuf = (char*)malloc(len);
    if(lpbuf==NULL){
        return -1;
    }

    strcpy(lpbuf,post);
    strcat(lpbuf,host);
    strcat(lpbuf,header2);
    strcat(lpbuf,content_len);
    strcat(lpbuf,request);

    if(!pclient->connected){
        tuobao_tcpclient_conn(pclient);
    }

    if(tuobao_tcpclient_send(pclient,lpbuf,len)<0){
        return -1;
    }
printf("·¢ËÇÇ:\n%s\n",lpbuf);

    /*Ê·Åڴæ
    if(lpbuf != NULL) free(lpbuf);
    lpbuf = NULL;

    /*it's time to recv from server*/
    if(tuobao_tcpclient_recv(pclient,&lpbuf,0) <= 0){
        if(lpbuf) free(lpbuf);
        return -2;
    }
printf("½ÓÕì:\n%s\n",lpbuf);

    /*ÏӦ´úHTTP/1.0 200 OK|
     *´ӵÚ0¸öû,µÚλ
     * */
    memset(post,0,sizeof(post));
    strncpy(post,lpbuf+9,3);
    if(atoi(post)!=200){
        if(lpbuf) free(lpbuf);
        return atoi(post);
    }


    ptmp = (char*)strstr(lpbuf,"\r\n\r\n");
    if(ptmp == NULL){
        free(lpbuf);
        return -3;
    }
    ptmp += 4;/*Ì¹ý/

    len = strlen(ptmp)+1;
    *response=(char*)malloc(len);
    if(*response == NULL){
        if(lpbuf) free(lpbuf);
        return -1;
    }
    memset(*response,0,len);
    memcpy(*response,ptmp,len-1);

    /*´Ó·ÓÕµ½ÄÈ³¤¶ÈÈ¹ûÕµ½Ô²»´¦À*/
    ptmp = (char*)strstr(lpbuf,"Content-Length:");
    if(ptmp != NULL){
        char *ptmp2;
        ptmp += 15;
        ptmp2 = (char*)strstr(ptmp,"\r\n");
        if(ptmp2 != NULL){
            memset(post,0,sizeof(post));
            strncpy(post,ptmp,ptmp2-ptmp);
            if(atoi(post)<len)
                (*response)[atoi(post)] = '\0';
        }
    }

    if(lpbuf) free(lpbuf);

    return 0;
}

int main(){

    tuobao_tcpclient client;

    char *response = NULL;
    printf("¿ªʼ×°ü
    tuobao_tcpclient_create(&client,"127.0.0.1",80);

    if(http_post(&client,"/i.php","f1=hello",&response)){
        printf("ʧ°Ü\n");
        exit(2);
    }
    printf("ÏӦ:\n%d:%s\n",strlen(response),response);

    free(response);
    return 0;
}
