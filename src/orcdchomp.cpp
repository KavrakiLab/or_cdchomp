#include <cstdio>
#include <cstring>
#include <boost/bind.hpp>

#include <openrave/config.h>
#include <openrave/openrave.h>
#include <openrave/plugin.h>

#include "orcdchomp_rdata.h"
#include "orcdchomp_mod.h"

/* globals: we maintain a single rdata xml reader instance */
namespace
{
   
static boost::shared_ptr<void> reg_reader;

static OpenRAVE::BaseXMLReaderPtr rdata_parser_maker(OpenRAVE::InterfaceBasePtr ptr, const OpenRAVE::AttributesList& atts)
{
   return OpenRAVE::BaseXMLReaderPtr(new orcdchomp::rdata_parser(boost::shared_ptr<orcdchomp::rdata>(),atts));
}

} /* anonymous namespace */


void GetPluginAttributesValidated(OpenRAVE::PLUGININFO& info)
{ 
   /* create the rdata xml parser interface if it does noet yet exit */
   if(!reg_reader)
      reg_reader = OpenRAVE::RaveRegisterXMLReader(OpenRAVE::PT_Robot,"orcdchomp",rdata_parser_maker);
   
   info.interfacenames[OpenRAVE::PT_Module].push_back("orcdchomp");
   
   return;
}


OpenRAVE::InterfaceBasePtr CreateInterfaceValidated(OpenRAVE::InterfaceType type, const std::string& interfacename, std::istream& sinput, OpenRAVE::EnvironmentBasePtr penv)
{
   if((type == OpenRAVE::PT_Module)&&(interfacename == "orcdchomp"))
      return OpenRAVE::InterfaceBasePtr(new orcdchomp::mod(penv));
      
   return OpenRAVE::InterfaceBasePtr();
}

OPENRAVE_PLUGIN_API void DestroyPlugin()
{
   RAVELOG_INFO("destroying plugin\n");
   return;
}
