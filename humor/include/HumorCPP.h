#ifndef HUMORCPP
#define HUMORCPP

#include <gcj/cni.h>
#include <java/lang/System.h>
#include <java/lang/Throwable.h>
#include "../misc/com/weblib/linguist/Humor.h"
#include <string>
#include <vector>

namespace com
{
  namespace weblib
  {
    namespace linguist
    {
    class HumorCPP
    {
            public:
                    static void initialize(std::string directory, int langCode);
                    static bool isInitialized();
                    static int close();
                    static std::vector<std::string>* getStem(std::string word);
                    static std::vector<std::string>* getAnalyze(std::string word);
                    static std::vector<std::string>* getWordGenerate(std::string word);
                    static std::vector<std::string>* getWordForms(std::string word, int limit);
                    static std::vector<std::string>* getSyns(std::string word, int contextSize);
                    void TestError(std::string word, int limit);
            private:
                    static std::string* getStrFromJava(java::lang::String* jStr);
                    static java::lang::String* convertToJavaStr(std::string* str);
                    static std::vector<std::string>* javaStrArraytoVector(JArray<java::lang::String*>* array);
                    HumorCPP();


    };
    }
  }
}


#endif /*HUMORCPP*/

