#pragma once

class BinarySaveFile;
class BinaryLoadFile;

class Serializable
{
public:
    virtual void serialize(BinarySaveFile& file) = 0;
    virtual void deserialize(BinaryLoadFile& file) = 0;
};
