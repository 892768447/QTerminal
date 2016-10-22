#include <QApplication>
#include <KGL/Dialogs/QTerminal.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    kgl::QTerminal t(NULL);
    t.setWindowTitle("QTerminal Test");
    t.writeString("This is a ");
    t.setCurrentState(kgl::TextState::Success, false);
    t.writeString("green ");
    t.setCurrentState(kgl::TextState::Normal, false);
    t.writeString("string.\n");
    t.show();

    while (t.readLine() != "exit")
    {
        t.readHex();
    }
}
