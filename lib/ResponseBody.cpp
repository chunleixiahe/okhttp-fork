//
// Created by Good_Pudge.
//

#include <iostream>
#include <cstring>
#include <iterator>
#include <ohf/ResponseBody.hpp>
#include "util/util.hpp"

namespace ohf {
    ResponseBody::ResponseBody(const MediaType &mediaType, const char *content, size_t count) :
            mediaType(mediaType),
            mContent(std::vector<Int8>(content, content + count))
    {
        std::copy(mContent.begin(), mContent.end(), std::ostream_iterator<char>(ss));
    }

    ResponseBody::ResponseBody(const MediaType &mediaType, const std::vector<Int8> &content) :
            mediaType(mediaType),
            mContent(content)
    {
        std::copy(mContent.begin(), mContent.end(), std::ostream_iterator<char>(ss));
    }

    ResponseBody::ResponseBody(const MediaType &mediaType, const std::string &content) :
            mediaType(mediaType),
            mContent(content.begin(), content.end())
    {
        std::copy(mContent.begin(), mContent.end(), std::ostream_iterator<char>(ss));
    }

    ResponseBody::ResponseBody(const MediaType &mediaType, std::istream &stream) :
            mediaType(mediaType),
            mContent(util::readStream(stream))
    {
        std::copy(mContent.begin(), mContent.end(), std::ostream_iterator<char>(ss));
    }

    std::vector<Int8> ResponseBody::bytes() {
        return mContent;
    }

    std::istream &ResponseBody::stream() {
        return ss;
    }

    unsigned int ResponseBody::contentLength() {
        return mContent.size();
    }

    MediaType ResponseBody::contentType() {
        return mediaType;
    }

    std::string ResponseBody::string() {
        return std::string(mContent.begin(), mContent.end());
    }
}