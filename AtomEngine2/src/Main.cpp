#include <Atom.hpp>
#include <TestGame.hpp>

using namespace atom;

int main(int argc, char* argv[])
{
    CoreEngine engine(1240, 720, new TestGame());
    engine.Run();
    
    return 0;
}
