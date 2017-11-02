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

	// 初始化，指定服务器IP和端口，以及数据需要转发到的服务器和端口
	// 一个对象只能初始化一次
	// 初始化成功返回true，否则返回false
	bool init(const std::string& serverip,unsigned short serverport,const std::string& fwdip,unsigned short fwdport);

	// 获取自己的ID只有初始化成功才会有ID。
	// 每个对象的ID不一样
	std::string getMyID();

	// 释放自己
	void destory();

	// 判断自己是否连上了fwd主机的指定端口
	bool isConnectedToHost();

	// 判断当前是否与指定的peerid相连
	bool isConnectedToPeer(const std::string& peerid);

	// 获取最近一次错误信息
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

