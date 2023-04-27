#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sol/sol.hpp>
#include "lua/plugins/luasocket/luasocket.h"
#include "lua/plugins/luasocket/mime.h"

class A
{
public:
    A() = default;
    A(int a)  { mA = a; };
    virtual ~A() = default;
    void foo()
    {
        std::cout << "I'm in class A" << std::endl;
    }

private:
    int mA;
};


int main()
{
    // sol::state lua;
    // lua.open_libraries();
    // lua.new_usertype<A>
    // (
    //     "A", // lua中识别的类
    //     sol::constructors<sol::types<void>>(),
    //     "foo", &A::foo // 绑定成员函数
    // );
    // lua.script("local a = A.new() a:foo() ");
    sol::state lua;
    lua.open_libraries(
        sol::lib::base,
        sol::lib::package,
        sol::lib::coroutine,
        sol::lib::string,
        sol::lib::os,
        sol::lib::math,
        sol::lib::table,
        sol::lib::debug,
        sol::lib::bit32,
        sol::lib::io,
        sol::lib::utf8
    );
    //启用luasocket
    lua.require("socket.core", luaopen_socket_core, true);
    lua.require("mime.core", luaopen_mime_core, true);
    sol::table searchers = lua["package"]["searchers"];
    searchers.add(sol::as_function([&](const std::string& module)
    {
        std::string filePath;
        const static std::string baseFolder = "data/";
        if (module.length() >= baseFolder.length() &&
            module.compare(0, baseFolder.length(), baseFolder) == 0)
        {
            filePath = module;
        }
        else
        {
            filePath = "data/luascripts/" + module;
        }
        // 替换.为/
        std::replace(filePath.begin(), filePath.end(), '.', '/');
        filePath = filePath + ".lua";
        std::ifstream t(filePath);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        t.close();
        return sol::make_object(lua, lua.load(str.c_str(), filePath.c_str()).get<sol::object>());
    }));
    lua.script_file("data/luascripts/test.lua");
}