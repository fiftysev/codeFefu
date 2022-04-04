#include <cstdint>
#include <memory>

class BufferedReader {
 public:
    explicit BufferedReader(PackageStream* stream) {
        buffer_stream_ = stream;
        buffer_ = new char[buffer_stream_->PackageLen()];
        pos_ = 0;
        buffer_size_ = 0;
    }
    int32_t Read(char* output_buffer, int32_t buffer_len) {
        int32_t buffer_len_ = buffer_len;
        int32_t current_strpos = 0;
        while (buffer_len > 0) {
            if (pos_ == buffer_size_) {
                buffer_size_ = buffer_stream_->ReadPackage(buffer_);
                pos_ = 0;
                if (buffer_size_ == 0) {
                    delete[] buffer_;
                    return buffer_len_ - buffer_len;
                }
            }
            if (buffer_size_ - pos_ < buffer_len) {
                memcpy(output_buffer + current_strpos, \
                       buffer_ + pos_, buffer_size_ - pos_);
                buffer_len -= (buffer_size_ - pos_);
                current_strpos += buffer_size_ - pos_;
                buffer_size_ = buffer_stream_->ReadPackage(buffer_);
                pos_ = 0;
                if (buffer_size_ == 0) {
                    delete[] buffer_;
                    return buffer_len_ - buffer_len;
                }
            } else {
                memcpy(output_buffer + current_strpos, \
                       buffer_ + pos_, buffer_len);
                pos_ += buffer_len;
                buffer_len = 0;
            }
        }
        return buffer_len_;
    }

 private:
    char* buffer_;
    PackageStream* buffer_stream_;
    int32_t pos_;
    int32_t buffer_size_;
};
