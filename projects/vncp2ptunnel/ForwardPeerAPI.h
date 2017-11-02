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

class ForwardPeerAPI : public FB::JSAPIAuto
{
public:
    ForwardPeerAPI(const FB::BrowserHostPtr& host);
    virtual ~ForwardPeerAPI();

	// ��ʼ����ָ��������IP�Ͷ˿ڣ��Լ�������Ҫת�����ķ������Ͷ˿�
	// һ������ֻ�ܳ�ʼ��һ��
	// ��ʼ���ɹ�����true�����򷵻�false
	bool init(const std::string& serverip,unsigned short serverport,const std::string& fwdip,unsigned short fwdport);

	// ��ȡ�Լ���IDֻ�г�ʼ���ɹ��Ż���ID��
	// ÿ�������ID��һ��
	std::string getMyID();

	// �ͷ��Լ�
	void destory();

	// �ж��Լ��Ƿ�������fwd������ָ���˿�
	bool isConnectedToHost();

	// �жϵ�ǰ�Ƿ���ָ����peerid����
	bool isConnectedToPeer(const std::string& peerid);

	// ��ȡ���һ�δ�����Ϣ
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

