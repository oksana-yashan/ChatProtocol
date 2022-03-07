#ifndef PROTOCOLTYPE_HPP
#define PROTOCOLTYPE_HPP

#include <string>
#include <sstream>
#include <map>
//#include <QDebug>

namespace ProtocolConst
{
    static const std::string USERNAME{"username"};
    static const std::string MESSAGE{"message"};
    static const std::string INFO{"info"};
    static const std::string TYPE{"type"};
}

enum class ProtocolType
{
        HANDSHAKE,
        MESSAGE,
        INFO
};

struct DataPacket
{
    inline DataPacket(const std::string& name, const std::string& message = "", const std::string& info = "")
        :
          user_name(name),
          message(message),
          info(info)
    {

    }

    std::string user_name;
    std::string message;
    std::string info;
};



namespace HandleProtocol
{
    std::string encode(ProtocolType type, const DataPacket& data, bool is_request);
    std::map<std::string, std::string> decode(const std::string& data);
}

#endif // PROTOCOLTYPE_HPP
