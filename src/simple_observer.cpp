
/**************************************/
/** FeedOS sample client code        **/
/**                                  **/
/** simple observer class to monitor **/
/** Connection objects               **/
/**                                  **/
/** QuantHouse 2005                  **/
/**************************************/

#include <feedos/zmqpp/simple_observer.h>
#include <iostream>
using namespace std;

SimpleObserver::SimpleObserver()
{
}

void SimpleObserver::proxy_disconnected_hook		(FeedOS::ProxyServer & p)
{
	string proxy_name = p.get_proxy_name();
	cerr << "\nproxy_disconnected "<<endl; 
}

void SimpleObserver::proxy_connected_hook			(FeedOS::ProxyServer & p)
{
	string proxy_name = p.get_proxy_name();
	cerr << "\nproxy_connected "<<endl; 
}

void SimpleObserver::proxy_heartbeat_hook			(FeedOS::ProxyServer & p)
{
	string proxy_name = p.get_proxy_name();
	FeedOS::Timestamp server_utc_time = p.get_heartbeat_server_timestamp();
	cerr << "\nproxy_heartbeat server_utc_time="<<server_utc_time<<endl;
}

void SimpleObserver::proxy_normal_disconnect_hook	(FeedOS::ProxyServer & p)
{
	string proxy_name = p.get_proxy_name();
	cerr << "\nproxy_normal_disconnect "<<endl; 
}


void SimpleObserver::proxy_admin_message_hook		(FeedOS::ProxyServer & p)
{
	FeedOS::ProxyServer::AdminMessage msg;
	p.pop_admin_message (msg);
	cerr << "\nproxy_admin_message urgent="<<boolalpha<<msg.urgent<<" origin="<<msg.origin<<" headline="<<msg.headline <<endl; 
	if (!msg.content.empty()) {
		cerr << "  content="<<msg.content<<endl; 
	}
}

