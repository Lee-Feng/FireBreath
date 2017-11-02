/**********************************************************\

  Auto-generated vncp2ptunnelAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "vncp2ptunnel.h"

#ifndef H_vncp2ptunnelAPI
#define H_vncp2ptunnelAPI


FB_FORWARD_PTR(ForwardPeerAPI);
FB_FORWARD_PTR(ProxyPeerAPI);

class vncp2ptunnelAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn vncp2ptunnelAPI::vncp2ptunnelAPI(const vncp2ptunnelPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    vncp2ptunnelAPI(const vncp2ptunnelPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
        registerMethod("echo",      make_method(this, &vncp2ptunnelAPI::echo));
        registerMethod("testEvent", make_method(this, &vncp2ptunnelAPI::testEvent));
		registerMethod("hello", make_method(this, &vncp2ptunnelAPI::hello));
		registerMethod("createForwardAPI", make_method(this, &vncp2ptunnelAPI::createForwardAPI));
		registerMethod("createProxyAPI", make_method(this, &vncp2ptunnelAPI::createProxyAPI));
        
        // Read-write property
        registerProperty("testString",
                         make_property(this,
                                       &vncp2ptunnelAPI::get_testString,
                                       &vncp2ptunnelAPI::set_testString));
        
        // Read-only property
        registerProperty("version",
                         make_property(this,
                                       &vncp2ptunnelAPI::get_version));
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn vncp2ptunnelAPI::~vncp2ptunnelAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~vncp2ptunnelAPI() {};

    vncp2ptunnelPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Event helpers
    FB_JSAPI_EVENT(test, 0, ());
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));

    // Method test-event
    void testEvent();

	// test
	std::string hello(const std::string& hi);

	// 创建一个forwardapi对象，用于实现forward相关控制
	ForwardPeerAPIPtr createForwardAPI();
	// 创建一个proxyapi对象，用于实现forward相关控制
	ProxyPeerAPIPtr createProxyAPI();

private:
    vncp2ptunnelWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_vncp2ptunnelAPI

