#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "../buffer/buffer.h"
#include <cstddef>
#include <string>
#include <sys/stat.h>
#include <unordered_map>
class HttpResponse
{
  public:
    HttpResponse ();
    ~HttpResponse ();

  public:
    void Init (const std::string &srcDir, std::string &path, bool isKeepAlive = false, int code = -1);
    void MakeResponse (Buffer &buff);

    char  *File ();
    size_t FileLen () const;
    void   UnmapFile ();

    void ErrorContent (Buffer &buff, std::string message);
    int
    Code () const
    {
        return code_;
    }

  private:
    void AddStateLine_ (Buffer &buff);
    void AddHeader_ (Buffer &buff);
    void AddContent_ (Buffer &buff);

    void        ErrorHtml_ ();
    std::string GetFileType_ ();

  private:
    int  code_;
    bool isKeepAlive_;

    std::string path_;
    std::string srcDir_;

    // memory map file & file status
    char       *mmFile_;
    struct stat mmFileStat_;

  private:
    // init see in .cpp head
    static const std::unordered_map<std::string, std::string> SUFFIX_TYPE;
    static const std::unordered_map<int, std::string>         CODE_STATUS;
    static const std::unordered_map<int, std::string>         CODE_PATH;
};


#endif