#include "mainwindow.h"
#include "modes.h"
#include <QApplication>
#include <hex.h>
#include <fstream>
#include <sstream>

using namespace std;
using namespace CryptoPP;

int main(int argc, char *argv[])
{


    KeyGen keygen;
    keygen.generateKey();
    std::string plain = "salut";
    std::string cipher = "";
    std::string recover = "";
    const SecByteBlock& key = keygen.getKey();
    const SecByteBlock& iv = keygen.getIv();



    StringSink* ss = new StringSink(cipher);
    CBC_Mode<AES>::Encryption e;
    StreamTransformationFilter* stf = new StreamTransformationFilter(e, ss);
    e.SetKeyWithIV(key, key.size(), iv);
    StringSource(plain, true, stf);

    StringSink* sk = new StringSink(recover);
    CBC_Mode<AES>::Decryption d;
    StreamTransformationFilter* stf1 = new StreamTransformationFilter(d, sk);
    d.SetKeyWithIV(key, key.size(), iv);
    StringSource(cipher, true, stf1);

    std::cout << "-------- plain: " << plain << std::endl;
    std::cout << "-------- cipher: " << cipher << std::endl;
    std::cout << "-------- recover: " << recover << std::endl;




    using namespace CryptoPP;
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/assets/icon.ico"));
    MainWindow w;
    w.show();
    return a.exec();
}
