// #include <iostream>
// #include <map>
// #include <vector>
// #include <unordered_map>

// std::map<int, std::string> bytes_to_unicode() {
//     std::map<int, std::string> byte_encoder;
//     for (int b = static_cast<int>('!'); b <= static_cast<int>('~'); ++b) {
//         byte_encoder[b] = static_cast<char>(b);
//     }
//     for (int b = static_cast<int>('¡'); b <= static_cast<int>('¬'); ++b) {
//         byte_encoder[b] = static_cast<char>(b);
//     }
//     for (int b = static_cast<int>('®'); b <= static_cast<int>('ÿ'); ++b) {
//         byte_encoder[b] = static_cast<char>(b);
//     }
//     int n = 0;
//     for (int b = 0; b < 256; ++b) {
//         if (byte_encoder.find(b) == byte_encoder.end()) {
//             byte_encoder[b] = static_cast<char>(256 + n);
//             n += 1;
//         }
//     }
//     return byte_encoder;
// }

// int main() {
//     std::map<int, std::string> byte_to_unicode_map = bytes_to_unicode();
//     for (const auto& pair : byte_to_unicode_map) {
//         //std::cout << pair.first << ": " << pair.second << std::endl;
//     }
//     std::cout << byte_to_unicode_map.size() << std::endl;
//     return 0;
// }

// GET_PAIRS FUNCTION TRANSLATION 1
// #include <iostream>
// #include <vector>
// #include <unordered_set>
// #include <tuple>
// // Define a custom hash function for std::tuple<char, char>
// struct TupleHash {
//     template <class T1, class T2>
//     std::size_t operator () (const std::tuple<T1, T2>& p) const {
//         auto hash1 = std::hash<T1>{}(std::get<0>(p));
//         auto hash2 = std::hash<T2>{}(std::get<1>(p));
//         return hash1 ^ hash2;
//     }
// };
// std::unordered_set<std::tuple<char, char>, TupleHash> get_pairs(const std::vector<char>& word) {
//     std::unordered_set<std::tuple<char, char>, TupleHash> pairs;
//     char prev_char = word[0];
//     for (size_t i = 1; i < word.size(); ++i) {
//         char current_char = word[i];
//         pairs.insert(std::make_tuple(prev_char, current_char));
//         prev_char = current_char;
//     }
//     return pairs;
// }
// int main() {
//     std::vector<char> word = {'f', 'a', 'v', 'o', 'r'};
//     auto pairs = get_pairs(word);
//     for (const auto& pair : pairs) {
//         std::cout << "(" << std::get<0>(pair) << ", " << std::get<1>(pair) << ")" << std::endl;
//     }
//     return 0;
// }
#include <locale>
#include <codecvt>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <regex>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <climits>

// Define a custom hash function for std::tuple<char, char>
struct TupleHash {
    template <class T1, class T2>
    std::size_t operator () (const std::tuple<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(std::get<0>(p));
        auto hash2 = std::hash<T2>{}(std::get<1>(p));
        return hash1 ^ hash2;
    }
};
std::unordered_set<std::tuple<std::string, std::string>, TupleHash> get_pairs(const std::vector<std::string>& word) {
    std::unordered_set<std::tuple<std::string, std::string>, TupleHash> pairs;
    std::string prev_char = word[0];
    for (size_t i = 1; i < word.size(); ++i) {
        std::string current_char = word[i];
        pairs.insert(std::make_tuple(prev_char, current_char));
        prev_char = current_char;
    }
    return pairs;
}
int utf_to_int(std::string utf8String) {
    // Convert UTF-8 to wide string (UTF-32)
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;
    std::u32string utf32String = utf32conv.from_bytes(utf8String);

    // Convert UTF-32 to integers
    int intValue;
    for (char32_t codePoint : utf32String) {
        intValue = static_cast<int>(codePoint);
        break;
    }
    return intValue;
}
std::string codePointToUTF8(int codePoint) {
    std::string utf8String;

    if (codePoint <= 0x7F) {
        // Single-byte character
        utf8String += static_cast<char>(codePoint);
    } else if (codePoint <= 0x7FF) {
        // Two-byte character
        utf8String += static_cast<char>(0xC0 | ((codePoint >> 6) & 0x1F));
        utf8String += static_cast<char>(0x80 | (codePoint & 0x3F));
    } else if (codePoint <= 0xFFFF) {
        // Three-byte character
        utf8String += static_cast<char>(0xE0 | ((codePoint >> 12) & 0x0F));
        utf8String += static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F));
        utf8String += static_cast<char>(0x80 | (codePoint & 0x3F));
    } else if (codePoint <= 0x10FFFF) {
        // Four-byte character
        utf8String += static_cast<char>(0xF0 | ((codePoint >> 18) & 0x07));
        utf8String += static_cast<char>(0x80 | ((codePoint >> 12) & 0x3F));
        utf8String += static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F));
        utf8String += static_cast<char>(0x80 | (codePoint & 0x3F));
    } else {
        // Invalid code point
        std::cerr << "Invalid Unicode code point: " << codePoint << std::endl;
    }
    return utf8String;
}
std::map<int, std::string> bytes_to_unicode() {
        std::map<int, std::string> byte_encoder;
        std::string string1;
        std::string string2;
        for (int b = utf_to_int("!"); b <= utf_to_int("~"); ++b) {
            byte_encoder[b] = codePointToUTF8(b);
        }
        for (int b = utf_to_int("¡"); b <= utf_to_int("¬"); ++b) {
            byte_encoder[b] = codePointToUTF8(b);
        }
        for (int b = utf_to_int("®"); b <= utf_to_int("ÿ"); ++b) {
            byte_encoder[b] = codePointToUTF8(b);
        }
        int n = 0;
        for (int b = 0; b < 256; ++b) {
            if (byte_encoder.find(b) == byte_encoder.end()) {
                byte_encoder[b] = codePointToUTF8(n+256);
                n += 1;
            }
        }
        return byte_encoder;
    }
std::map<std::string, int> load_json(const std::string& file_path) {
        // Load JSON file and return map
        std::map<std::string, int> result; // Dummy implementation
        return result;
    }
class MyTokenizer {
private:
    std::map<std::string, int> encoder;
    std::map<int, std::string> decoder;
    std::map<int, std::string> byte_encoder;
    std::map<int, std::string> byte_decoder;
    std::regex pat;
    std::unordered_map<std::pair<char, char>, int> bpe_ranks;
    std::unordered_map<std::string, std::string> cache;
    std::string unk_token;
    std::string errors;

public:
    MyTokenizer(const std::string& file_path, const std::string& merges_file) {
        encoder = load_json(file_path);
        for (const auto& pair : encoder) {
            decoder[pair.second] = pair.first;
        }
        byte_encoder = bytes_to_unicode();
        for (const auto& pair : byte_encoder) {
            byte_decoder[pair.first] = pair.second;
        }
        // pat = std::regex(R"('s|'t|'re|'ve|'m|'ll|'d| ?\p{L}+| ?\p{N}+| ?[^\s\p{L}\p{N}]+|\s+(?!\S)|\s+)");
        pat = std::regex(R"('s|'t|'re|'ve|'m|'ll|'d|[\p{L}]+|[\p{N}]+|[^\s\p{L}\p{N}]+|\s+(?!\S)|\s+)");
        load_bpe_ranks(merges_file);
        unk_token = "";
        errors = "replace";
    }
    std::vector<std::pair<char, char>> get_pairs(const std::vector<char>& word) {
        std::vector<std::pair<char, char>> pairs;
        for (size_t i = 0; i < word.size() - 1; ++i) {
            pairs.push_back(std::make_pair(word[i], word[i + 1]));
        }
        return pairs;
    }

    std::vector<int> generate(const std::string& text) {
        assert(!text.empty());
        auto tokenized_text = _tokenize(text);
        //auto token_ids = _convert_tokens_to_ids(tokenized_text);
        //return token_ids;
        std::vector<int> something;
        return something;
    }

//     std::string decode(const std::vector<int>& input_ids) {
//         std::string text;
//         for (int id : input_ids) {
//             text += decoder[id];
//         }
//         std::string decoded_text;
//         for (char c : text) {
//             decoded_text += byte_decoder[c];
//         }
//         return decoded_text;
//     }

// private:
    std::vector<std::string> _tokenize(const std::string& text) {
        std::vector<std::string> bpe_tokens;
        for (std::sregex_iterator it(text.begin(), text.end(), pat), end; it != end; ++it) {
            std::string token = it->str();
            std::string utf8_token;
            for (char b : token) {
                utf8_token += byte_encoder[b];
            }
            auto bpe_result = bpe(utf8_token);
            for (const auto& bpe_token : bpe_result) {
                bpe_tokens.push_back(bpe_token);
            }
        }
        return bpe_tokens;
    }

    std::string bpe(const std::string& token) {
            if (cache.find(token) != cache.end()) {
                return cache[token];
            }
            std::vector<char> word(token.begin(), token.end());
            std::vector<std::pair<char, char>> pairs = get_pairs(word);
            if (pairs.empty()) {
                return token;
            }
            while (true) {
                auto compare_function = [this](const std::pair<char, char>& pair) {
                    return bpe_ranks.find(pair) == bpe_ranks.end() ? INT_MAX : bpe_ranks[pair];
                };
                auto bigram = std::min_element(pairs.begin(), pairs.end(), compare_function);
                if (bpe_ranks.find(*bigram) == bpe_ranks.end()) {
                    break;
                }
                char first = bigram->first;
                char second = bigram->second;
                std::vector<char> new_word;
                size_t i = 0;
                while (i < word.size()) {
                    try {
                        size_t j = std::distance(word.begin(), std::find(word.begin() + i, word.end(), first));
                        if (j == word.size()) {
                            new_word.insert(new_word.end(), word.begin() + i, word.end());
                            break;
                        } else {
                            new_word.insert(new_word.end(), word.begin() + i, word.begin() + j);
                            i = j;
                        }
                    } catch (std::exception& e) {
                        new_word.insert(new_word.end(), word.begin() + i, word.end());
                        break;
                    }

                    if (word[i] == first && i < word.size() - 1 && word[i + 1] == second) {
                        new_word.push_back(first);
                        new_word.push_back(second);
                        i += 2;
                    } else {
                        new_word.push_back(word[i]);
                        i += 1;
                    }
                }
                word = new_word;
                if (word.size() == 1) {
                    break;
                } else {
                    pairs = get_pairs(word);
                }
            }
            std::string result(word.begin(), word.end());
            cache[token] = result;
            return result;
        }

    // std::vector<int> _convert_tokens_to_ids(const std::vector<std::string>& tokens) {
    //     std::vector<int> ids;
    //     for (const auto& token : tokens) {
    //         auto it = encoder.find(token);
    //         if (it != encoder.end()) {
    //             ids.push_back(it->second);
    //         } else {
    //             ids.push_back(encoder[unk_token]);
    //         }
    //     }
    //     return ids;
    // }

    void load_bpe_ranks(const std::string& merges_file) {
        std::ifstream file(merges_file);
        if (file.is_open()) {
            std::string line;
            int rank = 0;
            while (std::getline(file, line)) {
                std::istringstream tokenStream(line);
                std::string token1, token2;
                tokenStream >> token1 >> token2;
                if (!token1.empty() && !token2.empty()) {
                    bpe_ranks[{token1, token2}] = rank++;
                }
            }
            file.close();
        }
    }
};

int main() {
    std::string file_path = "vocab.json";
    std::string merges_file = "merges.txt";
    MyTokenizer tokenizer(file_path, merges_file);
    auto token_ids = tokenizer.generate("example text");
    // Do something with token_ids
    //auto decoded_text = tokenizer.decode(token_ids);
    //std::cout << "Decoded text: " << decoded_text << std::endl;
    return 0;
}





