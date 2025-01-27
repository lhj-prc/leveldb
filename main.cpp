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

    // r/w option
    ReadOptions read_option;
    WriteOptions write_option;

    // put, get, delete
    status = db->Put(write_option, "hello", "LevelDB");
    assert(status.ok());
    std::string value;
    status = db->Get(read_option, "hello", &value);
    assert(status.ok());
    std::cout << value << std::endl;
    status = db->Delete(write_option, "hello");
    assert(status.ok());

    // batch
    WriteBatch batch;
    batch.Delete("k1");
    batch.Put("k2", "v2");
    batch.Put("k3", "v3");
    status = db->Write(write_option, &batch);
    assert(status.ok());

    // iterator
    Iterator* it = db->NewIterator(read_option);
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;
    }
    for (it->SeekToLast(); it->Valid(); it->Prev()) {
        std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;
    }
    delete it;

    // snapshot
    const Snapshot* sp = db->GetSnapshot();
    read_option.snapshot = sp;
    db->ReleaseSnapshot(sp);

    delete db;
    return 0;
}
