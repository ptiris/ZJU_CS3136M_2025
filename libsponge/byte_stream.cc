#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) { this->_capacity = capacity; }

size_t ByteStream::write(const string &data) {

    size_t original_size = this->_write_bytes;
    for (char ch : data) {
        if (ch == EOF){
            this->end_input();
            break;
        } else if (this->remaining_capacity() > 0) {
            this->_buffer.push_back(ch);
            this->_write_bytes++;
        } else {
            break;
        }
    }
    return this->_write_bytes - original_size;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    if(len > this->buffer_size()){
        return this->_buffer;
    }
    else if(len == 0){
        return "";
    } else return this->_buffer.substr(0, len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    if(len > this->buffer_size()){
        this->_read_bytes += this->buffer_size();
        this->_buffer.clear();
    } else {
        this->_buffer.erase(0, len);
        this->_read_bytes += len;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string result = this->peek_output(len);
    this->pop_output(len);
    return result;
}

void ByteStream::end_input() {
    this->_input_ended = true;
}

bool ByteStream::input_ended() const { return this->_input_ended; }

size_t ByteStream::buffer_size() const { return this->_write_bytes - this->_read_bytes; }

bool ByteStream::buffer_empty() const { return this->_buffer.empty(); }

bool ByteStream::eof() const { return this->input_ended() && this->buffer_empty(); }

size_t ByteStream::bytes_written() const { return this->_write_bytes; }

size_t ByteStream::bytes_read() const { return this->_read_bytes; }

size_t ByteStream::remaining_capacity() const { return this->_capacity - this->buffer_size(); }
