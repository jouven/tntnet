/* generator.h
   Copyright (C) 2003-2005 Tommi Maekitalo

This file is part of tntnet.

Tntnet is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Tntnet is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with tntnet; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330,
Boston, MA  02111-1307  USA
*/

#ifndef TNT_ECPP_GENERATOR_H
#define TNT_ECPP_GENERATOR_H

#include <tnt/ecpp/parser.h>
#include <sstream>
#include <list>
#include <functional>
#include <tnt/datachunks_creator.h>
#include "tnt/ecppc/variable.h"
#include "tnt/ecppc/component.h"
#include "tnt/ecppc/subcomponent.h"
#include <map>

namespace tnt
{
  namespace ecppc
  {

    ////////////////////////////////////////////////////////////////////////
    // generator
    //
    class generator : public tnt::ecpp::parser
    {
        bool singleton;
        bool raw;
        std::string mimetype;
        std::string componentclass;
        std::string baseclass;

        typedef std::list<tnt::ecppc::variable> variable_declarations;

        variable_declarations configs;

        std::string pre;
        std::string declare;
        std::string init;
        std::string cleanup;
        std::string shared;
        std::string declare_shared;

        tnt::ecppc::component maincomp;

        typedef std::list<tnt::ecppc::subcomponent> subcomps_type;
        subcomps_type subcomps;

        tnt::ecppc::component* currentComp;

        typedef std::map<std::string, std::string> attr_type;
        attr_type attr;

        tnt::datachunks_creator data;

        enum filter_enum
        {
          filter_null,
          filter_html,
          filter_css,
          filter_js
        };
        filter_enum filter;
        bool compress;
        bool externData;

        time_t c_time;
        const char* gentime;

      public:
        generator(const std::string& classname, const std::string& ns);

        void setSingleton(bool sw)                   { singleton = sw; }
        bool isSingleton() const                     { return singleton; }

        void setMimetype(const std::string& type)    { mimetype = type; }
        const std::string& getMimetype()             { return mimetype; }

        void setComponentclass(const std::string& c) { componentclass = c; }
        const std::string& getComponentclass()       { return componentclass; }

        void setBaseclass(const std::string& c)      { baseclass = c; }
        const std::string& getBaseclass()            { return baseclass; }

        void setRawMode(bool sw = true)              { raw = sw; }
        bool isRawMode() const                       { return raw; }

        void setHtmlCompress(bool sw = true)         { filter = sw ? filter_html : filter_null; }
        bool isHtmlCompress()                        { return filter == filter_html; }

        void setCssCompress(bool sw = true)          { filter = sw ? filter_css : filter_null; }
        bool isCssCompress()                         { return filter == filter_css; }

        void setJsCompress(bool sw = true)           { filter = sw ? filter_js : filter_null; }
        bool isJsCompress()                          { return filter == filter_js; }

        void setCompress(bool sw = true)             { compress = sw; }
        bool isCompress() const                      { return compress; }

        void setExternData(bool sw = true)           { externData = sw; }
        bool isExternData() const                    { return externData; }

        void setLastModifiedTime(time_t t)           { c_time = t; }
        time_t getLastModifiedTime() const           { return c_time; }

        virtual void processHtml(const std::string& html);
        virtual void processExpression(const std::string& expr);
        virtual void processCpp(const std::string& cpp);
        virtual void processPre(const std::string& code);
        virtual void processDeclare(const std::string& code);
        virtual void processInit(const std::string& code);
        virtual void processCleanup(const std::string& code);
        virtual void processArg(const std::string& name,
          const std::string& value);
        virtual void processAttr(const std::string& name,
          const std::string& value);
        virtual void processCall(const std::string& comp,
          const comp_args_type& args, const std::string&  pass_cgi,
          const std::string& cppargs);
        virtual void processDeclareShared(const std::string& code);
        virtual void processShared(const std::string& code);
        virtual void startComp(const std::string& name, const cppargs_type& cppargs);
        virtual void processComp(const std::string& code);
        virtual void processCondExpr(const std::string& cond, const std::string& expr);
        virtual void processConfig(const std::string& name, const std::string& value);

        std::string getHeader(const std::string& basename) const;
        std::string getCpp(const std::string& basename) const;
        std::string getDataCpp(const std::string& basename) const;
    };

  }
}

#endif // TNT_ECPP_GENERATOR_H
