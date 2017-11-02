/**********************************************************\
Original Author: Richard Bateman and Georg Fritzsche

Created:    December 3, 2009
License:    Dual license model; choose one of two:
            New BSD License
            http://www.opensource.org/licenses/bsd-license.php
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 PacketPass Inc, Georg Fritzsche,
               Firebreath development team
\**********************************************************/

#include "JSObject.h"
#include <boost/assign.hpp>
#include "DOM/Document.h"
#include "variant_list.h"
using boost::assign::list_of;

#include "ProxyPeerAPI.h"
#include "ProxyManagerWinMigrate/ProxyManagerWinMigrate.hpp"

ProxyPeerAPI::ProxyPeerAPI(const FB::BrowserHostPtr& host) : m_host(host),m_inited(false)
{
	std::ostringstream os;
	os << "construction : proxy obj" << this;
	FBLOG_INFO(__FUNCTION__,os.str().c_str());

    registerMethod("init",  make_method(this, &ProxyPeerAPI::init));
    registerMethod("getMyID",  make_method(this, &ProxyPeerAPI::getMyID));
    registerMethod("getBindPort",  make_method(this, &ProxyPeerAPI::getBindPort));
    registerMethod("destory",  make_method(this, &ProxyPeerAPI::destory));
    registerMethod("makeP2pTunnel",  make_method(this, &ProxyPeerAPI::makeP2pTunnel));
	registerMethod("closeP2pTunnel",  make_method(this, &ProxyPeerAPI::closeP2pTunnel));
	registerMethod("isClientConnected",  make_method(this, &ProxyPeerAPI::isClientConnected));
	registerMethod("isConnectedToPeer",  make_method(this, &ProxyPeerAPI::isConnectedToPeer));
	registerMethod("getError",  make_method(this, &ProxyPeerAPI::getError));
	registerMethod("getVersion",  make_method(this, &ProxyPeerAPI::getVersion));
}

ProxyPeerAPI::~ProxyPeerAPI()
{
	std::ostringstream os;
	os << "destruction : proxy obj" << this;
	FBLOG_INFO(__FUNCTION__,os.str().c_str());

	destory();
}
// 初始化，指定服务器IP和端口，以及当前proxy需要监听的端口(0就是自动分配)
// 一个对象只能初始化一次
// 初始化成功返回true，否则返回false
bool ProxyPeerAPI::init(const std::string& serverip,unsigned short serverport,unsigned short bindport)
{
	if(m_inited)
	{
		m_lasterror = "already inited, can not call one more";
		FBLOG_ERROR(__FUNCTION__,m_lasterror.c_str());
		return false;
	}

	netaddr pub;
	if(serverip.size() >= sizeof(pub.ip))
	{
		std::ostringstream os;
		os << "ip address is too long,limit" << sizeof(pub.ip) << "bytes";
		m_lasterror = os.str();
		FBLOG_ERROR(__FUNCTION__, m_lasterror.c_str());
		return false;

	}
	strcpy(pub.ip,serverip.c_str());
	pub.port = serverport;
	string_result rst;
	if(!proxy_create_proxypeer(pub,bindport,&rst))
	{
		std::ostringstream os;
		os << "can not create proxypeer,port = " << bindport << ","<< rst.result;
		m_lasterror = os.str();
		FBLOG_ERROR(__FUNCTION__, m_lasterror.c_str());
		return false;
	}
	m_inited = true;
	m_myid = rst.result;
	std::ostringstream os;
	os << "create proxypeer sucessful, id = " << m_myid << ", listen at " << proxy_get_proxypeer_bindport(m_myid.c_str());
	FBLOG_INFO(__FUNCTION__, os.str().c_str());
	return true;
}

// 获取自己的ID只有初始化成功才会有ID。
// 每个对象的ID不一样
std::string ProxyPeerAPI::getMyID()
{
	return m_myid;
}

// 获取自己监听的端口，0就是没有监听
unsigned short ProxyPeerAPI::getBindPort()
{
	if(!m_inited || m_myid.empty())
	{
		m_lasterror = "not inited yet";
		return 0;
	}
	return proxy_get_proxypeer_bindport(m_myid.c_str());
}

// 释放自己
void ProxyPeerAPI::destory()
{
	if(m_inited && !m_myid.empty())
	{
		proxy_distory_peer(m_myid.c_str());
		std::ostringstream os;
		os << "distory peer " << m_myid;
		FBLOG_INFO(__FUNCTION__, os.str().c_str());
		m_myid = "";
		m_inited = false;
	}
}

// 创建p2p通道，成功返回true，否非返回false
// 如果创建失败可以通过getError获取错误原因
bool ProxyPeerAPI::makeP2pTunnel(const std::string& fwd_peer_id)
{
	if(!m_inited || m_myid.empty())
	{
		m_lasterror = "not inited yet";
		FBLOG_ERROR(__FUNCTION__, m_lasterror.c_str());
		return false;
	}

	string_result rlt;
	if(!proxy_make_p2p_tunnel(m_myid.c_str(),fwd_peer_id.c_str(),&rlt))
	{
		m_lasterror = rlt.result;
		FBLOG_ERROR(__FUNCTION__, m_lasterror.c_str());
		return false;
	}
	return true;
}

// 关闭与指定peer的通道
void ProxyPeerAPI::closeP2pTunnel(const std::string& fwd_peer_id)
{
	if(!m_inited || m_myid.empty())
	{
		m_lasterror = "not inited yet";
		FBLOG_ERROR(__FUNCTION__, "not inited ,can not close tunnel..");
		return;
	}
	proxy_close_p2p_tunnel(m_myid.c_str(),fwd_peer_id.c_str());
	std::ostringstream os;
	os << "close tunnel " << m_myid << " --> " << fwd_peer_id;
	FBLOG_INFO(__FUNCTION__, os.str().c_str());
}

// 返回最近一次错误信息
std::string ProxyPeerAPI::getError()
{
	return m_lasterror;
}

// 判断是否有客户端连到了当前proxy绑定的端口
bool ProxyPeerAPI::isClientConnected()
{
	if(!m_inited || m_myid.empty())
	{
		return false;
	}
	return proxy_is_clients_connected_proxypeer(m_myid.c_str()) ? true : false;
}

// 判断当前是否与指定的peerid相连
bool ProxyPeerAPI::isConnectedToPeer(const std::string& peerid)
{
	if(!m_inited || m_myid.empty())
	{
		return false;
	}
	return proxy_is_peer_connected(m_myid.c_str(),peerid.c_str()) ? true : false;
}

std::string ProxyPeerAPI::getVersion()
{
	return "ProxyPeerAPI_1.0.0";
}