#include "ToolsPreCompileHeader.h"
#include "XMLParser.h"

namespace ShadowPlay
{
    XMLParser::XMLParser()
    {
    }

    XMLParser::~XMLParser()
    {
    }

    int XMLParser::fileParse(const std::string &fileDir)
    {
        tinyxml2::XMLDocument doc;
        int errcode = doc.LoadFile("Config\\GlobalSettings.xml");
        if (!errcode)
        {
            doc;
        }
        
        return errcode;
    }

    void XMLParser::Testing()
    {
        tinyxml2::XMLDocument doc;
        //WCHAR settingFile;
        wchar_t buff[1000];
        _wgetcwd(buff, 1000);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> wcConvert;
        std::string xmlFile = wcConvert.to_bytes(buff) + "\\Config\\GlobalSettings.xml";
        int errcode = doc.LoadFile("Config\\GlobalSettings.xml");
        if(errcode == tinyxml2::XML_SUCCESS) 
        {
            std::cout << "Load success.\n";
        }
    }
}
