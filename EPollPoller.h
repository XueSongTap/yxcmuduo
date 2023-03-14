#pragma once
#include "Poller.h"
#include "Timestamp.h"
#include <vector>
#include <sys/epoll.h>

class Channel;

class EPollPoller : public Poller{
public:
    EPollPoller(EventLoop *loop);
    ~EPollPoller() override;

    
    Timestamp poll(int timeoutMs, ChannelList * activateChannels) override;

    void updateChannel(Channel *channel) override;
    void removeChannel(Channel* channel) override;

private:

    static const int kInitEventListSize = 16;
    
    // 
    void fillActiveChannels(int numEvents, ChannelList *activateChannels) const;
    
    //update channels
    void update(int operation, Channel * channel);

    using EventList = std::vector<epoll_event>;

    int epollfd_;

    EventList events_;
    
};