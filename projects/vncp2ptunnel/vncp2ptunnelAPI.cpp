/**********************************************************\

  Auto-generated vncp2ptunnelAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "vncp2ptunnelAPI.h"
#include "ForwardPeerAPI.h"
#include "ProxyPeerAPI.h"
#include "ProxyManagerWinMigrate/ProxyManagerWinMigrate.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant vncp2ptunnelAPI::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript.
///         Go ahead and change it. See what happens!
///////////////////////////////////////////////////////////////////////////////
FB::variant vncp2ptunnelAPI::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo("So far, you clicked this many times: ", n++);

    // return "foobar";
    return msg;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn vncp2ptunnelPtr vncp2ptunnelAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
vncp2ptunnelPtr vncp2ptunnelAPI::getPlugin()
{
    vncp2ptunnelPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read/Write property testString
std::string vncp2ptunnelAPI::get_testString()
{
    return m_testString;
}

void vncp2ptunnelAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string vncp2ptunnelAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void vncp2ptunnelAPI::testEvent()
{
    fire_test();
}
std::string vncp2ptunnelAPI::hello(const std::string& hi)
{
	return hi + ":from C++";
}



ForwardPeerAPIPtr vncp2ptunnelAPI::createForwardAPI()
{
	return boost::make_shared<ForwardPeerAPI>(m_host);
}
ProxyPeerAPIPtr vncp2ptunnelAPI::createProxyAPI()
{
	return boost::make_shared<ProxyPeerAPI>(m_host);
}