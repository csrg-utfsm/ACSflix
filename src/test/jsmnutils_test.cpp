#include <jsmnutils.h>
#include <iostream>
#include <sstream>

int main(int argc, const char *argv[])
{
    JSONParser parser;
    std::string filename = "input_test.json";
    
    if (argc == 2) {
        filename = std::string(argv[1]);
    }

    parser.load_file(filename);
    JSONObject object = parser.parse();

    std::string default_bind = object["bind"];

    JSONArray flows = object["flows"];
    for (int i = 0; i < flows.size(); i++) {
        JSONObject flow = flows[i];
        
        std::string local_bind = default_bind;
        try {
            local_bind = (std::string)flow["bind"];
        
        } catch (JSMNUtilsEx &ex) {
            std::cout << "not found" << std::endl;
        }
        int port = flow["port"];
        std::stringstream ss;
        ss << local_bind << ":" << port;
        std::string addr = ss.str();

        std::cout << "Flow " << (i + 1) << std::endl;
        std::cout << "======" << std::endl;
        std::cout << "name: " << (std::string)flow["name"] << std::endl;
        std::cout << "bind: " << addr << std::endl;
        std::cout << "file: " << (std::string)flow["file"] << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
