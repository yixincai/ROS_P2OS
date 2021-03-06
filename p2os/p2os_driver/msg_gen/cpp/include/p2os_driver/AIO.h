/* Auto-generated by genmsg_cpp for file /home/jfasola/fuerte_workspace/sandbox/p2os/p2os_driver/msg/AIO.msg */
#ifndef P2OS_DRIVER_MESSAGE_AIO_H
#define P2OS_DRIVER_MESSAGE_AIO_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace p2os_driver
{
template <class ContainerAllocator>
struct AIO_ {
  typedef AIO_<ContainerAllocator> Type;

  AIO_()
  : voltages_count(0)
  , voltages()
  {
  }

  AIO_(const ContainerAllocator& _alloc)
  : voltages_count(0)
  , voltages(_alloc)
  {
  }

  typedef uint8_t _voltages_count_type;
  uint8_t voltages_count;

  typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _voltages_type;
  std::vector<float, typename ContainerAllocator::template rebind<float>::other >  voltages;


  typedef boost::shared_ptr< ::p2os_driver::AIO_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::p2os_driver::AIO_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct AIO
typedef  ::p2os_driver::AIO_<std::allocator<void> > AIO;

typedef boost::shared_ptr< ::p2os_driver::AIO> AIOPtr;
typedef boost::shared_ptr< ::p2os_driver::AIO const> AIOConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::p2os_driver::AIO_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::p2os_driver::AIO_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace p2os_driver

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::p2os_driver::AIO_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::p2os_driver::AIO_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::p2os_driver::AIO_<ContainerAllocator> > {
  static const char* value() 
  {
    return "80e4ca5770a3db29064af246946ff4fe";
  }

  static const char* value(const  ::p2os_driver::AIO_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x80e4ca5770a3db29ULL;
  static const uint64_t static_value2 = 0x064af246946ff4feULL;
};

template<class ContainerAllocator>
struct DataType< ::p2os_driver::AIO_<ContainerAllocator> > {
  static const char* value() 
  {
    return "p2os_driver/AIO";
  }

  static const char* value(const  ::p2os_driver::AIO_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::p2os_driver::AIO_<ContainerAllocator> > {
  static const char* value() 
  {
    return "uint8 voltages_count\n\
float32[] voltages\n\
\n\
";
  }

  static const char* value(const  ::p2os_driver::AIO_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::p2os_driver::AIO_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.voltages_count);
    stream.next(m.voltages);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct AIO_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::p2os_driver::AIO_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::p2os_driver::AIO_<ContainerAllocator> & v) 
  {
    s << indent << "voltages_count: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.voltages_count);
    s << indent << "voltages[]" << std::endl;
    for (size_t i = 0; i < v.voltages.size(); ++i)
    {
      s << indent << "  voltages[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.voltages[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // P2OS_DRIVER_MESSAGE_AIO_H

