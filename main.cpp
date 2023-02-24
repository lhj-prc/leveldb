#include <assert.h>
#include <cstring>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include <iostream>
using namespace leveldb;

int main(int argc, char* argv[])
{
    DB* db;
    Options options;
    options.create_if_missing = true;
    Status status = DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());

    // put, get, delete
    status = db->Put(WriteOptions(), "hello", "LevelDB");
    assert(status.ok());
    std::string value;
    status = db->Get(ReadOptions(), "hello", &value);
    assert(status.ok());
    std::cout << value << std::endl;
    status = db->Delete(WriteOptions(), "hello");
    assert(status.ok());

    // batch
    WriteBatch batch;
    batch.Delete("k1");
    batch.Put("k2", "v2");
    batch.Put("k3", "v3");
    status = db->Write(WriteOptions(), &batch);
    assert(status.ok());

    // iterator
    ReadOptions option;
    Iterator* it = db->NewIterator(option);
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;
    }
    for (it->SeekToLast(); it->Valid(); it->Prev()) {
        std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;
    }
    delete it;

    delete db;
    return 0;
}
