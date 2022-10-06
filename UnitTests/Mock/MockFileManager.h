#include "../MediaServerLib/src/IFileManager.h"

#include <gmock/gmock.h>

class MockFileManager : public IFileManager
{
public:
//    MockFileManager(){}
    MOCK_METHOD1(read, bool(QString& fileData));
    MOCK_METHOD1(save, bool(const QString fileData));
};
