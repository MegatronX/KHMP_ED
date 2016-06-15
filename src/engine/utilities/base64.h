#pragma once
#ifndef _BASE64_H_
#define _BASE64_H_

#include <string>
#include <vector>

extern std::string base64_encode(unsigned char const*, int len);
extern void base64_decode(std::vector<int>& data, const std::string& s);
extern void base64_inFours(std::vector<int>& data, const std::string& s);
extern int* base64TMXDecode(const std::string& s, const unsigned int size);
extern void base64TMXDecode(std::vector<int>& data, const std::string& s, const unsigned int size);
extern void base64TMXDecode(std::vector<unsigned int>& data, const std::string& s, const unsigned int size);
extern std::string base64_stringDecode(const std::string& s);
extern void base64_stringDecode(std::string& decodedString, const std::string& string);

#endif