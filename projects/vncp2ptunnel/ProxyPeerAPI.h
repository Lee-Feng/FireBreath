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

#pragma  once

#include <string>
#include <sstream>
#include "JSAPIAuto.h"
#include "BrowserHost.h"

class ProxyPeerAPI : public FB::JSAPIAuto
{
public:
    ProxyPeerAPI(const FB::BrowserHostPtr& host);
    virtual ~ProxyPeerAPI();

	// ��ʼ����ָ��������IP�Ͷ˿ڣ��Լ���ǰproxy��Ҫ�����Ķ˿�(0�����Զ�����)
	// һ������ֻ�ܳ�ʼ��һ��
	// ��ʼ���ɹ�����true�����򷵻�false
	bool init(const std::string& serverip,unsigned short serverport,unsigned short bindport);

	// ��ȡ�Լ���IDֻ�г�ʼ���ɹ��Ż���ID��
	// ÿ�������ID��һ��
	std::string getMyID();

	// ��ȡ�Լ������Ķ˿ڣ�0����û�м���
	unsigned short getBindPort();

	// �ͷ��Լ�
	void destory();

	// ����p2pͨ�����ɹ�����true����Ƿ���false
	// �������ʧ�ܿ���ͨ��getError��ȡ����ԭ��
	bool makeP2pTunnel(const std::string& fwd_peer_id);

	// �ر���ָ��peer��ͨ��
	void closeP2pTunnel(const std::string& fwd_peer_id);

	// �ж��Ƿ��пͻ��������˵�ǰproxy�󶨵Ķ˿�
	bool isClientConnected();

	// �жϵ�ǰ�Ƿ���ָ����peerid����
	bool isConnectedToPeer(const std::string& peerid);

	// �������һ�δ�����Ϣ
	std::string getError();

	// ��ȡ�汾����
	std::string getVersion();
private:
	bool m_inited;

	std::string m_myid;

	std::string m_lasterror;

    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

