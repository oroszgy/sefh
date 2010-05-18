#pragma once

//#include <gcj/cni.h>
//#include <java/lang/System.h>
//#include <java/lang/Throwable.h>
//#include "../misc/com/weblib/linguist/Humor.h"
#include <string>
#include <vector>
#include <iconv.h>
#include "stem2005_export.h"
#include "stem2005_options.h"

namespace com
{
  namespace weblib
  {
    namespace linguist
    {
    class HumorCPP
    {
            public:
                    static void initialize(std::string directory);
                    static bool isInitialized();
                    static int close();
                    static std::vector<std::string> getStem(std::string word);
                    //static std::vector<std::string>* getAnalyze(std::string word);
                    //static std::vector<std::string>* getWordGenerate(std::string word);
                    //static std::vector<std::string>* getWordForms(std::string word, int limit);
                    static std::vector<std::string> getSyns(std::string word);
                    static std::string getInitString();
                    //void TestError(std::string word, int limit);
                    //static std::string* getStrFromJava(java::lang::String* jStr);
                    //static java::lang::String* convertToJavaStr(std::string* str);
            private:
                    //static std::vector<std::string>* javaStrArraytoVector(JArray<java::lang::String*>* array);
                    HumorCPP();
                    static iconv_t utc;
                    static iconv_t ctu;
                    static int morphId;
                    static int stemOptions;
                    static int synOptions;
                    static std::vector<std::string> split(std::string str);

                    static iconv_t openCpToUtf();
                    static void closeDesc (iconv_t conv_desc);
                    static std::string convert (iconv_t desc, std::string fromStr);
                    static iconv_t openUtfToCp ();

    };

    }
  }
}
