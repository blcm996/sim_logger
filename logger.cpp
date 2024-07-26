#include"logger.h"
using namespace blcm::utility;

#include<time.h>
#include<cstring>
#include<stdarg.h>
#include<stdexcept>
#include<iostream>

const char * Logger::s_level[LEVEL_COUNT] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};
Logger::Logger(): m_max(0), m_len(0), m_level(DEBUG){}
Logger::~Logger(){close();}

Logger * Logger::m_instance = NULL;

Logger * Logger::instance(){
    if(m_instance == NULL){
        m_instance = new Logger();
    }
    return m_instance;
}

void Logger::open(const std::string & filename){
    m_filename = filename;
    m_fout.open(filename, std::ios::app);
    if(m_fout.fail()){
        throw std::logic_error("opening " + filename + "failed");
    }

    m_fout.seekp(0, std::ios::end);
    m_len = m_fout.tellp();
}

void Logger::close(){
    m_fout.close(); 
}

void Logger::log(Level level, const char * file, int line, const char * format, ...){
    if(m_fout.fail()){
        throw std::logic_error("open file failed" + m_filename);
    }
    
    time_t ticks = time(NULL);
    struct tm * ptm = localtime(&ticks);
    char timestamp[32];
    memset(timestamp, 0, sizeof(timestamp));
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ptm);
    const char * fmt = "%s %s %s:%d ";
    int size = snprintf(NULL, 0, fmt, timestamp, s_level[level], file, __ORDER_LITTLE_ENDIAN__);
    if(size > 0){
        char * buffer = new char[size+1];
        snprintf(buffer, size + 1, fmt, timestamp, s_level[level], file, line);
        buffer[size] = 0;
        m_fout << buffer;
        m_len += size;
        delete buffer;
    }

    va_list arg_ptr;
    va_start(arg_ptr, format);
    size = vsnprintf(NULL, 0, format, arg_ptr);
    va_end(arg_ptr);
    if(size > 0){
        char * content = new char[size+1];
        va_start(arg_ptr, format);
        vsnprintf(content, size+1, format, arg_ptr);
        va_end(arg_ptr);
        m_fout << content;
        m_len += size;
        delete content;
    }
    
    m_fout << '\n';
    m_fout.flush();

    if(m_len >= m_max && m_max > 0){
        rotate();
    }
}

void Logger::rotate(){
    close();
 
    time_t ticks = time(NULL);
    struct tm * ptm = localtime(&ticks);
    char timestamp[32];
    memset(timestamp, 0, sizeof(timestamp));
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ptm);
    
    std::string filename = m_filename + timestamp;
    if(rename(m_filename.c_str(), filename.c_str()) != 0){
        throw std::logic_error("rename log filaed" );
    }
    open(m_filename);
}

