#include <systemc.h>

#include <cstdint>

template <class T, size_t N> SC_MODULE(delay_pipe)
{
  public:
    sc_in_clk m_clk;
    sc_export<sc_signal_inout_if<T>> m_in;
    sc_export<sc_signal_in_if<T>> m_out;

  public:
    SC_CTOR(delay_pipe)
    {
        m_in(m_pipe[0]);
        m_out(m_pipe[N - 1]);
        SC_METHOD(run);
        sensitive << m_clk.pos();
    }

  private:
    sc_signal<T> m_pipe[N];

  private:
    void run()
    {
        for (size_t i = 1; i < N; i++)
        {
            m_pipe[i].write(m_pipe[i - 1].read());
        }
    }
};

using atom = uint32_t;

SC_MODULE(Reader)
{
  public:
    sc_in_clk m_clk;
    sc_in<atom> m_from_pipe;

  public:
    SC_CTOR(Reader)
    {
        SC_METHOD(extract)
        sensitive << m_clk.pos();
        dont_initialize();
    }

  private:
    void extract() { cout << sc_time_stamp().to_double() << ": " << m_from_pipe.read() << endl; }
};

SC_MODULE(Writer)
{
  public:
    sc_in_clk m_clk;
    sc_inout<atom> m_to_pipe;

  public:
    SC_CTOR(Writer)
    {
        SC_METHOD(insert)
        sensitive << m_clk.pos();
        m_counter = 0;
    }

  private:
    atom m_counter;

  private:
    void insert()
    {
        m_to_pipe.write(m_counter);
        m_counter++;
    }
};

int sc_main(int, char *[])
{
    sc_clock clock("clk", {1, SC_NS});
    delay_pipe<atom, 4> delay("pipe");
    Reader reader("reader");
    Writer writer("writer");

    delay.m_clk(clock);

    reader.m_clk(clock);
    reader.m_from_pipe(delay.m_out);

    writer.m_clk(clock);
    writer.m_to_pipe(delay.m_in);

    sc_start(10, SC_NS);

    return 0;
}
