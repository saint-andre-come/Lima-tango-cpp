/*************************************************************************
/*! 
 *  \file   UserData.h
 *  \brief  class UserData
 *  \author Arafat NOUREDDINE
 */
/*************************************************************************/

#ifndef USER_DATA_H
#define USER_DATA_H
#include <yat/threading/Mutex.h>

#include <tango.h>
#define MAX_ATTRIBUTE_STRING_LENGTH 255
namespace Xspress3_ns
{
class DoubleUserData
{
public:
    DoubleUserData(const std::string& stat_name);
    ~DoubleUserData();
    const Tango::DevDouble& get_value();
    void set_value(Tango::DevDouble value);
private:
    yat::Mutex m_lock;
    std::string m_name;
    Tango::DevDouble m_value;
};

//----------------------------------------------------------------------------------------------------------------------
//	
//----------------------------------------------------------------------------------------------------------------------
class ULongUserData
{
public:
    ULongUserData(const std::string& stat_name);
    ~ULongUserData();
    const Tango::DevULong& get_value();
    void set_value(Tango::DevULong value);
private:
    yat::Mutex m_lock;
    std::string m_name;
    Tango::DevULong m_value;
};

//----------------------------------------------------------------------------------------------------------------------
//	
//----------------------------------------------------------------------------------------------------------------------
class LongUserData
{
public:
    LongUserData(const std::string& stat_name);
    ~LongUserData();
    const Tango::DevLong& get_value();
    void set_value(Tango::DevLong value);
private:
    yat::Mutex m_lock;
    std::string m_name;
    Tango::DevLong m_value;
};

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
class BooleanUserData
{
public:
    BooleanUserData(const std::string& stat_name);
    ~BooleanUserData();
    const Tango::DevBoolean& get_value();
    void set_value(Tango::DevBoolean value);
private:
    yat::Mutex m_lock;
    std::string m_name;
    Tango::DevBoolean m_value;
};

//----------------------------------------------------------------------------------------------------------------------
//	
//----------------------------------------------------------------------------------------------------------------------
class StringUserData
{
public:
    StringUserData(const std::string& stat_name);
    ~StringUserData();
    const Tango::DevString* get_value();
    void set_value(std::string value);
private:
    yat::Mutex m_lock;
    std::string m_name;
    Tango::DevString* m_value;
};

//----------------------------------------------------------------------------------------------------------------------
//	
//----------------------------------------------------------------------------------------------------------------------
class ChannelUserData
{
public:
    ChannelUserData(const std::string& name, int nb_bins);
    ~ChannelUserData();
    const std::vector<Tango::DevDouble>& get_value();
    void set_value(std::vector<Tango::DevDouble> value);
private:
    yat::Mutex m_lock;
    std::string m_name;
    std::vector<Tango::DevDouble> m_data;
};

} // namespace

#endif // USER_DATA_H
