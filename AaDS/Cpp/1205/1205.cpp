#include <iostream>
#include <fstream>
#include <string>


#define LOGIC_RESULTS_COUNT 4
#define WORD_LEN 32

unsigned logic_tool_box(unsigned  image_word1, unsigned image_word2, std::string& logic_results) {
    if (logic_results == "0000") return 0;
    else if (logic_results == "0001") return image_word1 & image_word2;
    else if (logic_results == "0010") return image_word1 & ~image_word2;
    else if (logic_results == "0100") return image_word2 & ~image_word1;
    else if (logic_results == "1000") return ~(image_word1 | image_word2);

    else if (logic_results == "0110") return image_word1 ^ image_word2;
    else if (logic_results == "1100") return ~image_word1;
    else if (logic_results == "0011") return image_word1;
    else if (logic_results == "1001") return image_word1 == image_word2;
    else if (logic_results == "1010") return ~image_word2;
    else if (logic_results == "0101") return image_word2;

    else if (logic_results == "1110") return ~(image_word1 & image_word2);
    else if (logic_results == "0111") return image_word1 | image_word2;
    else if (logic_results == "1101") return ~image_word1 | image_word2;
    else if (logic_results == "1011") return ~image_word2 | image_word1;
    else if (logic_results == "1111") return 1;
    else return 2;
}

unsigned *mix_two_images(unsigned *uint_arr1, unsigned *uint_arr2, std::string logic_results) {
    unsigned size = uint_arr1[0];
    auto *result = new unsigned [size];
    result[0] = size;
    for (unsigned i = 1; i < size; i++){
        result[i] = logic_tool_box(uint_arr1[i], uint_arr2[i], logic_results);
    }
    return result;
}

unsigned word_to_uint(const std::string& word) {
    unsigned result = 0;
    for(char bit: word) {
        result <<= 1;
        result += bit & 1;
    }
    return result;
}

unsigned* image_to_uint_arr(std::string& image) {
    int not_fully_word_len = int(image.length()) % WORD_LEN;
    int words_count = int(image.length()) / WORD_LEN + (not_fully_word_len & 1);
    auto* uint_arr = new unsigned [words_count + 1];
    uint_arr[0] = words_count + 1;
    int i;
    for (i = 1; i < uint_arr[0]; ++i) {
        uint_arr[i] = word_to_uint(image.substr((i - 1) * WORD_LEN, WORD_LEN));
    }
    return uint_arr;
}

std::string uint_to_substr(unsigned uint_word) {
    std::string result;
    result = "";
    for (int i = 0; i < WORD_LEN; i++) {
        result.insert(0, 1, (uint_word & 1) + '0');
        uint_word >>= 1;
    }
    return result;
}

std::string uint_arr_to_image(unsigned* image_in_uint_arr, int image_size) {
    std::string image;
    std::string substr;
    image = "";
    unsigned uint_arr_size = image_in_uint_arr[0];
    int not_fully_word_len = image_size % WORD_LEN;
    for (unsigned i = 1; i < uint_arr_size; i++) {
        substr = uint_to_substr(image_in_uint_arr[i]);
        if (not_fully_word_len != 0 and i == uint_arr_size - 1) {
            image += substr.substr(WORD_LEN - not_fully_word_len, not_fully_word_len);
        }
        else{
            image += substr;
        }
    }
    return image;
}



int main () {
    std::fstream input("input.txt");
    std::ofstream output("output.txt");

    std::string image1, image2, tmp, all_info;
    int w, h;
    all_info = "";
    while (input) {
        getline(input, tmp);
        all_info += tmp;
    }
    w = all_info[0] - '0';
    h = all_info[2] - '0';
    image1 = all_info.substr(3, w * h);
    image2 = all_info.substr(3 + w * h, w * h);
    tmp = all_info.substr(all_info.length() - LOGIC_RESULTS_COUNT);

    unsigned *image1_in_uint_arr = image_to_uint_arr(image1);
    unsigned *image2_in_uint_arr = image_to_uint_arr(image2);
    unsigned *result_image = mix_two_images(image1_in_uint_arr, image2_in_uint_arr, tmp);
    all_info = uint_arr_to_image(result_image, w * h);
    for (int i = 0; i < h; i++) {
        output << all_info.substr(i * w, w) << std::endl;
    }




}