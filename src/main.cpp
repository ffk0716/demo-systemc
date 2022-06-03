// All systemc modules should include systemc.h header file
#include "systemc.h"
// Hello_world is module name

class hello_world : sc_module
{
  public:
    sc_in<unsigned> in;
    sc_in<unsigned> in2;
    sc_in<unsigned> in3;
    hello_world(std::string a) : sc_module(a), in("in"), in2("in2")
    {
        // SC_THREAD(say_hello);
        sensitive << in;
        in3(in2);
        // Nothing in constructor
    }
    void say_hello()
    {
        // Print "Hello World" to the console.
        while (1)
        {
            cout << in.read() << endl;
            cout << in2.read() << endl;
            wait();
        }
    }
};

SC_MODULE(B)
{
    sc_out<unsigned> out;
    sc_in<bool> clk;
    SC_CTOR(B)
    {
        SC_THREAD(main);
        sensitive << clk.pos();
        // Nothing in constructor
    }
    void main()
    {
        // Print "Hello World" to the console.
        cout << "B." << endl;
        out.write(9);
        out.write(8);
        wait();
        out.write(8);
        wait();
        out.write(9);
        wait();
        sc_stop();
    }
};

// sc_main in top level function like in C++ main
int sc_main(int argc, char *argv[])
{
    // sc_clock TestClk("TestClock", 2, SC_NS,0.5);
    // B b("b");

    hello_world hello("HELLO");
    sc_signal<unsigned> s;
    sc_signal<unsigned> s2;
    // b.clk(TestClk);
    hello.in(s);
    hello.in2(s);
    // b.out(s);
    bool i = 0;
    s.write(i);
    i = !i;
    s.write(i);
    i = !i;
    s.write(i);
    i = !i;

    sc_start();
    s.write(i);
    i = !i;
    sc_start();
    s.write(i);
    i = !i;
    sc_start();
    return 0;
}
