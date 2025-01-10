#pragma once

#include <string>
#include <istream>
#include <ostream>
#include <cstdint>
#include <cstring> // For std::memcpy

namespace wylma {
  namespace warden {

    class crypter {
    private:
      const std::string password;

    public:
      crypter(const std::string &_password) : password(_password) {
        if (password.empty()) {
          throw std::invalid_argument("Password cannot be empty.");
        }
      }

      void crypt(std::istream &is, std::ostream &os) {
        size_t password_len = password.size();
        size_t password_idx = 0;

        char buffer;
        while (is.get(buffer)) {
          // XOR the input character with the current password character
          char encrypted_char = buffer ^ password[password_idx];
          os.put(encrypted_char);

          // Move to the next character in the password
          password_idx = (password_idx + 1) % password_len;
        }
      }

      void decrypt(std::istream &is, std::ostream &os) {
        // Decryption is the same as encryption with XOR
        crypt(is, os);
      }
    };

  } // namespace warden
} // namespace wylma
