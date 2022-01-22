#include <iostream>
#include <event2/event.h>
#include <csignal>
#include <event2/listener.h>

#define SPORT 5001

void listen_cb(evconnlistener *base,
               int cb, sockaddr *ptr, int flags, void *backlog
){
    std::cout<<"listen_cb"<<std::endl;
}
int main() {
#ifdef _WIN32
    std::cout << "Hello, windows World!" << std::endl;
#elif __APPLE__
    std::cout << "Hello, mac World!" << std::endl;
#elif __linux__
    std::cout << "Hello, linux World!" << std::endl;
    if(signal(SIGPIPE,SIG_IGN)==SIG_ERR)
#endif
    //初始化配置libevent上下文
    //event_base * base = event_base_new();

    //根据配置项配置libevnet上下文
    event_config *conf = event_config_new();
    //显示支持的模式
    auto methods =  event_get_supported_methods();
    std::cout<<"supported_methods:"<<std::endl;
    for(int i =0;methods[i]!= nullptr;i++)
    {
        std::cout<<methods[i]<<std::endl;
    }
    event_base * base = event_base_new_with_config(conf);
    event_config_free(conf);
    if(base!= nullptr)
    {
        std::cout<<"event_base_new success!"<<std::endl;
    } else{
        std::cerr<<"event_base创建失败!"<<std::endl;
    }
    //监听端口
    //socket,bind,listen绑定时间
    sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SPORT);
    evconnlistener* ev= evconnlistener_new_bind(base,   //libevent的上下文
                            listen_cb,//接收到连接的回调函数
                            base,   //回调函数获取的参数arg
                            LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE,//地址重用，evconnlistener关闭同时关闭socket
                            10, //链接队列大小，对应listen函数
                            (sockaddr*)&sin,    //绑定的地址和端口
                            sizeof(sin)
            );
    //事件分发处理
    if(base)
        event_base_dispatch(base);
    if(ev)
        evconnlistener_free(ev);
    if(base)
        event_base_free(base);
    return 0;
}
