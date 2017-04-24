#ifndef JSMNUTILS_H
#define JSMNUTILS_H

#include <string>
#include <jsmn.h>
#include <vector>
#include <stdexcept>

class JSMNUtilsEx : public std::runtime_error
{
public:
    JSMNUtilsEx(std::string errmsg) :
        std::runtime_error("jsmnutils error: " + errmsg) {}
};

class JSONElement;

class JSONObject
{
    jsmntok_t *m_tokens;
    size_t m_toksize;

    const char *m_buffer;

public:
    JSONObject(jsmntok_t *tokens, size_t toksize, const char *buffer);
    JSONElement operator[](const std::string &key) const;

};

class JSONArray
{
    jsmntok_t *m_tokens;
    size_t m_toksize;

    const char *m_buffer;

public:
    JSONArray(jsmntok_t *tokens, size_t toksize, const char *m_buffer);
    JSONElement operator[](size_t i) const;

    size_t size() const;
};

class JSONElement
{
    jsmntok_t *m_tokens;
    size_t m_toksize;

    const char *m_buffer;

public:
    JSONElement(jsmntok_t *tokens, size_t toksize, const char *buffer);

    bool is_valid() const;

    operator JSONObject();
    operator std::string();
    operator JSONArray();
    operator int();
};

class JSONParser
{
    jsmn_parser m_parser;
    jsmntok_t *m_tokens;
    int m_toksize;
    std::vector<char> m_buffer;

    bool m_buffer_loaded;

public:
    JSONParser();
    ~JSONParser();

    void load_file(std::string filename);
    JSONElement parse();

    std::vector<char> &buffer();
};

#endif /* end of include guard: JSMNUTILS_H */
