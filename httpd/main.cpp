#include<stdio.h>
#include<string.h>
#include<errno.h>

//#include<unistd.h>
#include<event.h>
#include <winsock.h>




void accept_cb(int fd, short events, void* arg);
void socket_read_cb(int fd, short events, void *arg);

int tcp_server_init(int port, int listen_num);

int main(int argc, char** argv)
{

  int listener = tcp_server_init(9999, 10);
  if( listener == -1 )
  {
    perror(" tcp_server_init error ");
    return -1;
  }

  struct event_base* base = event_base_new();

  //��Ӽ����ͻ������������¼�
  struct event* ev_listen = event_new(base, listener, EV_READ | EV_PERSIST,accept_cb, base);
  event_add(ev_listen, NULL);
  event_base_dispatch(base);

  printf("����������.....\n");

  return 0;
}



void accept_cb(int fd, short events, void* arg)
{
  evutil_socket_t sockfd;

  struct sockaddr_in client;
  int len;

  sockfd = ::accept(fd, (struct sockaddr*)&client, &len );
  evutil_make_socket_nonblocking(sockfd);

  

  printf("accept a client %s\t%d\n", inet_ntoa(client.sin_addr),client.sin_port);

  struct event_base* base = (event_base*)arg;

  //������Ϊ�˶�̬����һ��event�ṹ��
  struct event *ev = event_new(NULL, -1, 0, NULL, NULL);
  //����̬�����Ľṹ����Ϊevent�Ļص�����
  event_assign(ev, base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, (void*)ev);

  event_add(ev, NULL);
}


void socket_read_cb(int fd, short events, void *arg)
{
  char msg[4096];
  struct event *ev = (struct event*)arg;
  int len = read(fd, msg, sizeof(msg) - 1);



  if( len <= 0 )
  {
    printf("some error happen when read\n");
    close(event_get_fd(ev));
    event_free(ev);
    return ;
  }

  msg[len] = '\0';
  printf("recv the client msg: %s", msg);

  char reply_msg[4096] = "I have recvieced the msg: ";
  strcat(reply_msg + strlen(reply_msg), msg);

  write(fd, reply_msg, strlen(reply_msg) );
}



typedef struct sockaddr SA;
int tcp_server_init(int port, int listen_num)
{
  int errno_save;
  evutil_socket_t listener;

  listener = ::socket(AF_INET, SOCK_STREAM, 0);
  if( listener == -1 )
    return -1;

  //�����ΰ�ͬһ����ַ��Ҫ����socket��bind֮��
  evutil_make_listen_socket_reuseable(listener);

  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = 0;
  sin.sin_port = htons(port);

  if( ::bind(listener, (SA*)&sin, sizeof(sin)) < 0 )
    goto error;

  if( ::listen(listener, listen_num) < 0)
    goto error;


  //��ƽ̨ͳһ�ӿڣ����׽�������Ϊ������״̬
  evutil_make_socket_nonblocking(listener);

  return listener;

  error:
    errno_save = errno;
    evutil_closesocket(listener);
    errno = errno_save;

    return -1;
}