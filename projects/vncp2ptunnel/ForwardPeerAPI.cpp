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
#include <sstream>

using boost::assign::list_of;

#include "ForwardPeerAPI.h"
#include "ProxyManagerWinMigrate/ProxyManagerWinMigrate.hpp"

ForwardPeerAPI::ForwardPeerAPI(const FB::BrowserHostPtr& host) : m_host(host),m_inited(false)
{
	std::ostringstream os;
	os << "construction : forward obj" << this;
	FBLOG_INFO(__FUNCTION__,os.str().c_str());

    registerMethod("init",  make_method(this, &ForwardPeerAPI::init));
    registerMethod("getMyID",  make_method(this, &ForwardPeerAPI::getMyID));
    registerMethod("destory",  make_method(this, &ForwardPeerAPI::destory));
    registerMethod("isConnectedToHost",  make_method(this, &ForwardPeerAPI::isConnectedToHost));
    registerMethod("isConnectedToPeer",  make_method(this, &ForwardPeerAPI::isConnectedToPeer));
	registerMethod("getError",  make_method(this, &ForwardPeerAPI::getError));
}

ForwardPeerAPI::~ForwardPeerAPI()
{
	std::ostringstream os;
	os << "destruction : forward obj" << this;
	FBLOG_INFO(__FUNCTION__,os.str().c_str());
	destory();
}


// ��ʼ����ָ��������IP�Ͷ˿ڣ��Լ�������Ҫת�����ķ������Ͷ˿�
// һ������ֻ�ܳ�ʼ��һ��
// ��ʼ���ɹ�����true�����򷵻�false
bool ForwardPeerAPI::init(const std::string& serverip,unsigned short serverport,const std::string& fwdip,unsigned short fwdport)
{
	if(m_inited)
	{
		m_lasterror = "already inited, can not call one more";
		FBLOG_ERROR(__FUNCTION__,m_lasterror.c_str());
		return false;
	}

	netaddr pub;
	netaddr fwd;
	if(serverip.size() >= sizeof(pub.ip) || fwdip.size() >= sizeof(pub.ip))
	{
		std::ostringstream os;
		os << "ip address is too long,limit" << sizeof(pub.ip) << "bytes";
		m_lasterror = os.str();
		FBLOG_ERROR(__FUNCTION__, m_lasterror.c_str());
		return false;

	}
	strcpy(pub.ip,serverip.c_str());
	pub.port = serverport;
	strcpy(fwd.ip,fwdip.c_str());
	fwd.port = fwdport;
	string_result rst;
	if(!proxy_create_forwardpeer(pub,fwd,&rst))
	{
		std::ostringstream os;
		os << "can not create forwardpeer," << rst.result;
		m_lasterror = os.str();
		FBLOG_ERROR(__FUNCTION__, m_lasterror.c_str());
		return false;
	}
	m_inited = true;
	m_myid = rst.result;
	std::ostringstream os;
	os << "create forwardpeer sucessful, id = " << m_myid;
	FBLOG_INFO(__FUNCTION__, os.str().c_str());
	return true;
}

// ��ȡ�Լ���IDֻ�г�ʼ���ɹ��Ż���ID��
// ÿ�������ID��һ��
std::string ForwardPeerAPI::getMyID()
{
	return m_myid;

}

// �ͷ��Լ�
void ForwardPeerAPI::destory()
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

// �ж��Լ��Ƿ�������fwd������ָ���˿�
bool ForwardPeerAPI::isConnectedToHost()
{
	if(!m_inited && m_myid.empty())
	{
		return false;
	}
	return proxy_is_forwardpeer_connected_to_dst(m_myid.c_str()) ? true : false;
}

// �жϵ�ǰ�Ƿ���ָ����peerid����
bool ForwardPeerAPI::isConnectedToPeer(const std::string& peerid)
{
	if(!m_inited && m_myid.empty())
	{
		return false;
	}
	return proxy_is_peer_connected(peerid.c_str(),m_myid.c_str()) ? true : false;
}


// ��ȡ���һ�δ�����Ϣ
std::string ForwardPeerAPI::getError()
{
	return m_lasterror;
}