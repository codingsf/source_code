#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <curl/curl.h>

typedef struct _mult_info
{
    int _epfd;
    CURLM *_multi;
} Mult_info;

typedef struct _easy_curl_data
{
    CURL *curl;
    char data[1024] = {0};
} easy_curl_data;

typedef struct _multi_curl_sockinfo
{
    curl_socket_t fd;
    CURL *cp;
} multi_curl_sockinfo;

char curl_cb_data[1024] = {0};

static int sock_cb (CURL *e, curl_socket_t s, int what, void *cbp, void *sockp)
{
    struct epoll_event ev = {0};

    global_info *g = (global_info *) cbp;
    multi_curl_sockinfo  *fdp = (multi_curl_sockinfo *) sockp;

    if (what == CURL_POLL_REMOVE)
    {
        if (fdp)
        {
            free(fdp);
        }
        epoll_ctl(g->epfd, EPOLL_CTL_DEL, s, &ev);
    }
    else
    {
        if (what == CURL_POLL_IN)
        {
            ev.events |= EPOLLIN;
        }
        else if (what == CURL_POLL_OUT)
        {
            ev.events |= EPOLLOUT;
        }
        else if (what == CURL_POLL_INOUT)
        {
            ev.events |= EPOLLIN | EPOLLOUT;
        }

        if (!fpd)
        {
            fpd = (multi_curl_sockinfo *)malloc(sizeof(multi_curl_sockinfo));
            fpd->fd = s;
            fpd->cp = e;

            epoll_ctl(g->epfd, EPOLL_CTL_ADD, s, &ev);
            curl_multi_assign(g->multi, s, &ev);
        }

    }
    return 0;
}

static int multi_timer_cb(CURLM *multi, long timeout_ms, GlobalInfo *g)
{
  struct timeval timeout;
  (void)multi; /* unused */

  timeout.tv_sec = timeout_ms/1000;
  timeout.tv_usec = (timeout_ms%1000)*1000;
  fprintf(MSG_OUT, "multi_timer_cb: Setting timeout to %ld ms\n", timeout_ms);
  evtimer_add(g->timer_event, &timeout);
  return 0;
}
static void set_curl_opt(CURL *curl)
{
    //set curl options..
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, curl_cb_data);
    //other options..
}
static void Add_Curl(Mult_info &pMult_handle)
{
    CURL *curl = curl_easy_init();
    set_curl_opt(curl);
    curl_multi_add_handle(pMult_handle.multi, curl);
}
static void InitMultCurl(Mult_info &pMult_handle)
{
    curl_global_init(CURL_GLOBAL_ALL);
    memset(&mult_handle, 0, sizeof(Mult_info));
    mult_handle._multi = curl_multi_init();
    curl_multi_setopt(mult_handle._multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
    curl_multi_setopt(mult_handle._multi, CURLMOPT_SOCKETDATA, &pMult_handle);
    curl_multi_setopt(mult_handle._multi, CURLMOPT_TIMERFUNCTION, multi_timer_cb);
    curl_multi_setopt(mult_handle._multi, CURLMOPT_TIMERDATA, &pMult_handle);
    mult_handle._epfd = epoll_create(100);
}

void RunMultCurl(Mult_info &pMult_handle)
{
    int running_count;
    struct epoll_event events[100];
    while (CURLM_CALL_MULTI_PERFORM == curl_multi_socket_action(pMult_handle.multi, CURL_SOCKET_TIMEOUT,
            0, &running_count));
    while(running_count)
    {
        nfds = epoll_wait(pMult_handle.epfd, events, 10, 500);
        if(nfds > 0)
        {
            int z = 0;
            for (; z < nfds; z++)
            {
                if (events[i].events & EPOLLIN)
                {
                    curl_multi_socket_action(pMult_handle.multi, CURL_CSELECT_IN, events[i].data.fd, &running_count);
                }
                else if (events[i].events & EPOLLOUT)
                {
                    curl_multi_socket_action(pMult_handle.multi, CURL_CSELECT_OUT, events[i].data.fd, &running_count);
                }
            }
        }

    }
    int main(int argc, char *argv[])
    {
        //char *urls[3] = {"https://google.com", "http://qq.com", "http://xxx.com"};

        curl_global_init(CURL_GLOBAL_ALL);
        global_info g;
        memset(&g, 0, sizeof(global_info));
        g.epfd = epoll_create(10);
        g.multi = curl_multi_init();

        int i = 0;
        for(; i < 3; i++)
        {
            CURL *curl;
            curl = curl_easy_init();
            set_curl_opt(curl);
            curl_multi_add_handle(g.multi, curl);
        }

        curl_multi_setopt(multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
        curl_multi_setopt(multi->cm, CURLMOPT_SOCKETDATA, &g);

        int running_count;
        struct epoll_event events[10]
        while (CURLM_CALL_MULTI_PERFORM == curl_multi_socket_action(g.multi, CURL_SOCKET_TIMEOUT, 0, &running_count));

        if (running_count)
        {
            do
            {
                nfds = epoll_wait(g.epfd, events, 10, 500);
                if(nfds > 0)
                {
                    int z = 0;
                    for (; z < nfds; z++)
                    {
                        if (events[i].events & EPOLLIN)
                        {
                            curl_multi_socket_action(g.multi, CURL_CSELECT_IN, events[i].data.fd, &running_count);
                        }
                        else if (events[i].events & EPOLLOUT)
                        {
                            curl_multi_socket_action(g.multi, CURL_CSELECT_OUT, events[i].data.fd, &running_count);
                        }
                    }
                }
            }
            while (running_count);
        }

        curl_global_cleanup();
        return 0;
    }