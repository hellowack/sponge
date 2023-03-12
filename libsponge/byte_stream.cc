#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity): buffer(capacity), cap(capacity){}

size_t ByteStream::write(const string &data) {
    size_t write_num = 0;
    size_t n = data.length();
    if(n > cap - length)
    {
	    write_num = cap - length;
    }
    else
	    write_num = n;
    for(size_t i = 0; i < write_num; i++)
    {
	    tail %= cap;
	    buffer[tail] = data[i];
	    tail++;
    }
    length += write_num;
    total_write += write_num;
    return write_num;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t num = 0;
    if(len > length)
    {
	num = length;
    }
    else
	num = len;
    string str(num, 0);
    size_t p = head;
    for(size_t i = 0; i < num; i++)
    {
	str[i] = buffer[p];
	p = (p + 1)%cap;
    }
    return str;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) 
{
    if(len > length)
    {
	    head = this->tail;
	    total_read += length;
	    length = 0;
    }
    else
    {
	    head = (head + len)%cap;
	    total_read += len;
	    length -= len;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string str = peek_output(len);
    pop_output(len);
    return str;
}

void ByteStream::end_input() {end = true;}

bool ByteStream::input_ended() const {return end;}

size_t ByteStream::buffer_size() const { return length; }

bool ByteStream::buffer_empty() const { return length == 0; }

bool ByteStream::eof() const { return end && (length == 0); }

size_t ByteStream::bytes_written() const { return total_write; }

size_t ByteStream::bytes_read() const { return total_read; }

size_t ByteStream::remaining_capacity() const { return cap - length; }
