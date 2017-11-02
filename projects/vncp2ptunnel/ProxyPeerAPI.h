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

	// 初始化，指定服务器IP和端口，以及当前proxy需要监听的端口(0就是自动分配)
	// 一个对象只能初始化一次
	// 初始化成功返回true，否则返回false
	bool init(const std::string& serverip,unsigned short serverport,unsigned short bindport);

	// 获取自己的ID只有初始化成功才会有ID。
	// 每个对象的ID不一样
	std::string getMyID();

	// 获取自己监听的端口，0就是没有监听
	unsigned short getBindPort();

	// 释放自己
	void destory();

	// 创建p2p通道，成功返回true，否非返回false
	// 如果创建失败可以通过getError获取错误原因
	bool makeP2pTunnel(const std::string& fwd_peer_id);

	// 关闭与指定peer的通道
	void closeP2pTunnel(const std::string& fwd_peer_id);

	// 判断是否有客户端连到了当前proxy绑定的端口
	bool isClientConnected();

	// 判断当前是否与指定的peerid相连
	bool isConnectedToPeer(const std::string& peerid);

	// 返回最近一次错误信息
	std::string getError();

	// 获取版本描述
	std::string getVersion();
private:
	bool m_inited;

	std::string m_myid;

	std::string m_lasterror;

    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

