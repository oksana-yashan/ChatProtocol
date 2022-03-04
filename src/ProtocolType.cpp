#include "ProtocolType.hpp"

std::string encode_messages(const std::string& user_name, const std::string& message);
std::string encode_handshake_request(const std::string& handshake);
std::string encode_handshake_response(const std::string& handshake, const std::string& status);
std::string encode_info(const std::string& data);


namespace HandleProtocol
{

    std::string encode(ProtocolType type, const DataPacket& data, bool is_request)
    {
        switch(type)
        {
            case ProtocolType::HANDSHAKE:
                return (is_request) ? encode_handshake_request(data.user_name) : encode_handshake_response(data.user_name, data.info);

            case ProtocolType::MESSAGE:
                return encode_messages(data.user_name, data.message);

            case ProtocolType::INFO:
                return encode_info(data.info);
        }

        return {};
    }

    std::map<std::string, std::string> decode(const std::string& data)
    {
        char delimeter_key_value = '=';
        char delimeter_new = '&';
        std::stringstream stream_str(data);
        std::map<std::string, std::string> client_info;
        std::string parse_line;

        // get ProtocolType from first line by delimeter_new
        std::getline(stream_str, parse_line, delimeter_new);
        client_info[ProtocolConst::TYPE] = parse_line;

        // get other key and values of protocol
        while (std::getline(stream_str, parse_line, delimeter_new))
        {
            size_t iter = parse_line.find(delimeter_key_value);
            //TODO check iter == npos;
            std::string key(parse_line.begin(), parse_line.begin() + iter);
            std::string value(parse_line.begin() + (iter + 1), parse_line.end());

            client_info[key] = value;
        }
        return client_info;
    }
}



std::string encode_messages(const std::string &user_name, const std::string &message)
{
    // TODO check for unique name
    // TODO delimeter in config file

    std::string delimeter_key_value = "=";
    std::string delimeter_new = "&";

//    username=oksana&
//    message=Hello my friend\nMy name is Oksana

    return std::to_string(
            static_cast<int>(ProtocolType::MESSAGE)) + delimeter_new
            + ProtocolConst::USERNAME + delimeter_key_value + user_name + delimeter_new
            + ProtocolConst::MESSAGE + delimeter_key_value + message;
}

std::string encode_handshake_request(const std::string& handshake)
{
    // TODO check for unique name
    // TODO delimeter in config file

    std::string delimeter_key_value = "=";
    std::string delimeter_new = "&";

    std::string encoded = std::to_string(
            static_cast<int>(ProtocolType::HANDSHAKE)) + delimeter_new
            + ProtocolConst::USERNAME + delimeter_key_value + handshake;
    return encoded;
}

std::string encode_handshake_response(const std::string& handshake, const std::string& status)
{
    // TODO check for unique name
    // TODO delimeter in config file

    std::string delimeter_key_value = "=";
    std::string delimeter_new = "&";

    std::string encoded = std::to_string(
            static_cast<int>(ProtocolType::HANDSHAKE)) + delimeter_new
            + ProtocolConst::USERNAME + delimeter_key_value + handshake + delimeter_new
            + ProtocolConst::INFO + delimeter_key_value + status;
    return encoded;
}

std::string encode_info(const std::string& data)
{
    // TODO check for unique name
    // TODO delimeter in config file

    std::string delimeter_key_value = "=";
    std::string delimeter_new = "&";

    std::string encoded = std::to_string(
            static_cast<int>(ProtocolType::INFO)) + delimeter_new
            + ProtocolConst::INFO + delimeter_key_value + data;
//            + INFO + delimeter_key_value + "<font color=\"Purple\">" + data + "</font>";
    return encoded;
}
