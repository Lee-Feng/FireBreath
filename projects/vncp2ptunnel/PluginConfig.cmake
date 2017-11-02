#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for vncp2ptunnel
#
#\**********************************************************/

set(PLUGIN_NAME "vncp2ptunnel")
set(PLUGIN_PREFIX "VNC")
set(COMPANY_NAME "LFP")

# ActiveX constants:
set(FBTYPELIB_NAME vncp2ptunnelLib)
set(FBTYPELIB_DESC "vncp2ptunnel 1.0 Type Library")
set(IFBControl_DESC "vncp2ptunnel Control Interface")
set(FBControl_DESC "vncp2ptunnel Control Class")
set(IFBComJavascriptObject_DESC "vncp2ptunnel IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "vncp2ptunnel ComJavascriptObject Class")
set(IFBComEventSource_DESC "vncp2ptunnel IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 93edae32-c295-5427-b40e-eeff2ab915f9)
set(IFBControl_GUID e2d42144-52b7-58ea-b870-fedf1339bd32)
set(FBControl_GUID cbfa09ae-5f23-5395-af96-c0a5f4ff7a1b)
set(IFBComJavascriptObject_GUID ce6a49b2-fa9a-51f8-90e4-b5d0e33df2bd)
set(FBComJavascriptObject_GUID d0fc55b8-2265-5736-981c-5414e2115084)
set(IFBComEventSource_GUID 2887516c-2bc0-582e-b60a-c55884c8c7f9)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID a3e50c88-c155-542f-b5da-0d165fbebfbd)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 7b719ffb-d22b-530f-b6ab-dcc97d13ab1a)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "LFP.vncp2ptunnel")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "lfp.com/vncp2ptunnel")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "lfp.com/vncp2ptunnel_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "LF-Personal")
set(FBSTRING_PluginDescription "a p2p tunnel for vnc access")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2017 LF-Personal")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
set(FBSTRING_ProductName "vncp2ptunnel")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "vncp2ptunnel")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "vncp2ptunnel_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-vncp2ptunnel")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

#set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)

# 开启日志模块
add_firebreath_library(log4cplus)