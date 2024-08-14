#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include "addressbook.pb.h"

using namespace std;
int main()
{
        xpilot::sr2_0::proto::Config addrBook;
        int fd = open("./cfg/pb.cfg", O_RDONLY);
        google::protobuf::io::FileInputStream f_in(fd);
        f_in.SetCloseOnDelete(true);
        google::protobuf::TextFormat::Parse(&f_in, &addrBook);

        addrBook.PrintDebugString();
        return 0;
}


