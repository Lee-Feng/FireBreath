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
// ��ʼ����ָ��������IP�Ͷ˿ڣ��Լ���ǰproxy��Ҫ�����Ķ˿�(0�����Զ�����)
// һ������ֻ�ܳ�ʼ��һ��
// ��ʼ���ɹ�����true�����򷵻�false
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

// ��ȡ�Լ���IDֻ�г�ʼ���ɹ��Ż���ID��
// ÿ�������ID��һ��
std::string ProxyPeerAPI::getMyID()
{
	return m_myid;
}

// ��ȡ�Լ������Ķ˿ڣ�0����û�м���
unsigned short ProxyPeerAPI::getBindPort()
{
	if(!m_inited || m_myid.empty())
	{
		m_lasterror = "not inited yet";
		return 0;
	}
	return proxy_get_proxypeer_bindport(m_myid.c_str());
}

// �ͷ��Լ�
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

// ����p2pͨ�����ɹ�����true����Ƿ���false
// �������ʧ�ܿ���ͨ��getError��ȡ����ԭ��
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

// �ر���ָ��peer��ͨ��
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

// �������һ�δ�����Ϣ
std::string ProxyPeerAPI::getError()
{
	return m_lasterror;
}

// �ж��Ƿ��пͻ��������˵�ǰproxy�󶨵Ķ˿�
bool ProxyPeerAPI::isClientConnected()
{
	if(!m_inited || m_myid.empty())
	{
		return false;
	}
	return proxy_is_clients_connected_proxypeer(m_myid.c_str()) ? true : false;
}

// �жϵ�ǰ�Ƿ���ָ����peerid����
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