/**********************************************************\ 
Original Author: Richard Bateman and Georg Fritzsche 

Created:    December 3, 2009
License:    Dual license model; choose one of two:
            Eclipse Public License - Version 1.0
            http://www.eclipse.org/legal/epl-v10.html
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 PacketPass Inc, Georg Fritzsche,
               Firebreath development team
\**********************************************************/

#include <string>
#include <sstream>
#include "JSAPIAuto.h"
#include "BrowserHostWrapper.h"

class FBTestPluginAPI : public FB::JSAPIAuto
{
public:
    FBTestPluginAPI(FB::BrowserHostWrapper *host);
    virtual ~FBTestPluginAPI();

    // Read/Write property testString
    std::string get_testString();
    void set_testString(std::string val);

    // Read-only property someInt
    long get_someInt();

    FB::AutoPtr<JSAPI> get_simpleMath();

    // Method add
    long add(long a, long b);

private:
    FB::AutoPtr<FB::BrowserHostWrapper> m_host;
    FB::AutoPtr<JSAPI> m_simpleMath;

    std::string m_testString;
};
