# Password Manager (C++) — XOR Vault

CLI-based password manager in C++. Stores and retrieves credentials from a vault encrypted using XOR with a user-provided key.

## Features
- CLI menu interface
- Store/retrieve credentials
- Password generation
- Vault encryption/decryption using XOR with a user key

## Security Note
XOR is not secure cryptography. This project is for learning file handling + basic encryption concepts.

## Build & Run

```bash
g++ -std=c++17 -O2 -o password_manager src/password_manager.cpp
./password_manager
```

---

## Project Structure

```
password-manager-xor-cpp/
├── src/            # C++ source files
├── data/
│   └── sample_vault.txt   # Example encrypted vault (fake data)
└── README.md
```

---

## Future Improvements
- Replace XOR with AES-GCM for real encryption  
- Add key derivation (PBKDF2 / Argon2)  
- Add integrity checks for the vault  
- Add unit tests  
- Add better error handling and input validation
