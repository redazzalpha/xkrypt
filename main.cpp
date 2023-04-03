#include "files.h"
#include "mainwindow.h"
#include <QApplication>
#include <hex.h>
#include "base64.h"
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
//    string base = "AFF";
//    base[0] = static_cast <uint>(15);
//    base[1] = static_cast <uint>(6);
//    base[2] = static_cast <uint>(23);

//    CryptoPP::Base64Encoder encoderBase64(new CryptoPP::FileSink("/home/kyzer/Bureau/base64"));
//    CryptoPP::HexEncoder encoderHex(new CryptoPP::FileSink("/home/kyzer/Bureau/hex"));
//    CryptoPP::StringSource s(base.data(), true, new CryptoPP::FileSink("/home/kyzer/Bureau/bin"));
//    encoderBase64.Put((CryptoPP::byte*)base.data(), base.size());
//    encoderHex.Put((CryptoPP::byte*)base.data(), base.size());

//    string base64Decoded = "";
//    string hexDecoded = "";
//    string binDecoded;
//    CryptoPP::FileSource("/home/kyzer/Bureau/base64", true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(base64Decoded)));
//    CryptoPP::FileSource("/home/kyzer/Bureau/hex", true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(hexDecoded)));
//    CryptoPP::FileSource("/home/kyzer/Bureau/bin", true, new CryptoPP::StringSink(binDecoded));

//    std::cout << "-- base64 decoded: " << (int)base64Decoded[0] << std::endl;
//    std::cout << "-- hex decoded: " << (int)hexDecoded[1] << std::endl;
//    std::cout << "-- bin decoded: " << (int)binDecoded[2] << std::endl;


    using namespace CryptoPP;
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/assets/icon.ico"));
    MainWindow w;
    w.show();
    return a.exec();
}
