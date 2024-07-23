#include"logger.h"
using namespace blcm::utilty;

const char * Logger::s_level[LEVEL_COUNT] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
}
Logger::Logger(){}
Logger::~Logger(){}

Logger * Logger::instance(){
    if(m_instance == NULL){
        m_instance = new Logger();
    }
    return m_instance;
}

void Logger::open(const string & filename){
    m_filename = filename;
    m_fout.open(filename, ios::app);
    if(m_fout.fail()){
        throw std::logic_error("opening " + filename + "failed");
    }

}

void Logger::close(){
    m_fout.close(); 
}