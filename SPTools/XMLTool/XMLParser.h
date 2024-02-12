#pragma once
#include <ToolsGlobal.h>

namespace ShadowPlay
{
    struct SPXMLNode
    {
        SPXMLNode* sonNode;
        SPXMLNode* broNode;

        std::string nodeRoute;
        std::string nodeType;
        std::string nodeData;
    };

    struct SPXMLReadingInstruction
    {
        std::string sourceModel;
        std::string readingDir;
        int instructionErrCode;
    };

    class SHADOWPLAY_API XMLParser
    {
    public:
        XMLParser();
        ~XMLParser();

        int fileParse(const std::string& fileDir);

        static void Testing();
    };
}