#include "IFileManager.h"

class MpdFileManager : public IFileManager
{
public:
   MpdFileManager();
   virtual bool read(std::string to, std::string& fileData) override;
   virtual bool save(std::string fileData) override;
};
