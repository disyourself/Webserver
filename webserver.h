#ifndef WEBSERVER_H
#define WEBSERVER_H

#include"mysql_conn/sql_connection_pool.h"
#include"http_conn/http_conn.h"
#include"timer/list_timer.h"
#include"thread_pool/thread_pool.hpp"
#include"assert.h"

const int MAX_FD = 65536;
const int MAX_EVENT_NUMBER = 10000;
const int TIMESLOT = 5;     // min timeout units


class Webserver
{
private:
    // Fundations
    int m_port;
    char* m_root;
    int m_log_write;
    int m_close_log;
    int m_actormodel;

    int m_pipefd[2];
    int m_epollfd;
    http_conn* users;

    // thread_pools
    threadpool<http_conn>* m_pool;
    int m_thread_num;

    // DBs
    sql_conn_pool* m_connPool;
    std::string m_user;
    std::string m_password;
    std::string m_databaseName;
    int m_sql_num;

    // Timers
    client_data* users_timer;
    Utils utils;

    // epoll_events
    epoll_event event[MAX_EVENT_NUMBER];

    int m_listenfd;
    int m_OPT_LINGER;
    int m_TRIGMode;
    int m_LISTENTRgimode;
    int m_CONNTRigmode;

public:
    Webserver();
    ~Webserver();

    void init(int port , std::string user , std::string passwd , std::string databaseName , int log_write , int opt_linger , int trigmode , int sql_num ,
        int thread_num , int close_log , int actor_model);

    void thread_pool();
    void sql_pool();
    void log_write();
    void trig_mode();
    void eventListen();
};

#endif
