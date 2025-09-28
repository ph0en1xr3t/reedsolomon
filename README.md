![alt text](doc/images/reedsolomon.png)

# Reed-Solomon Error Correction Code Implementation

A C++ implementation framework for Reed-Solomon (RS) error correction codes, designed for educational and development purposes.

## Project Status

**Development Phase**: This project currently provides a foundational framework with stub implementations. The actual Reed-Solomon algorithms are not yet implemented.

## Features

### Current Implementation
- **Modern C++ Framework**: C++20 standards with CMake build system
- **Comprehensive Testing**: Google Test (GTest) and Google Mock (GMock) integration
- **Development Tools**: VS Code devcontainer, clangd integration, GitHub Actions CI/CD
- **Google Style Guide**: Enforced coding standards with automated formatting
- **Cross-Platform**: Builds on Linux, macOS, and Windows (via devcontainer)

### Planned Reed-Solomon Features
- **Galois Field GF(2^8) Arithmetic**: Lookup tables for efficient operations
- **Polynomial Operations**: Addition, multiplication, evaluation, and division over finite fields
- **Systematic Encoding**: Message symbols appear unchanged in the encoded codeword
- **Multi-Error Correction**: Can correct up to `t = nsym/2` symbol errors
- **Advanced Algorithms**: Berlekamp-Massey, Chien search, Forney's algorithm

## Project Structure

```
reedsolomon/
├── include/
│   └── reedsolomon.h          # Main header with API definitions
├── src/
│   └── reedsolomon.cc         # Implementation (stub functions)
├── examples/
│   └── main.cpp               # Example usage and demonstrations
├── tests/
│   ├── test_reedsolomon.cpp   # Main test suite
│   ├── test_galois_field.cpp  # Galois field tests
│   ├── test_encoder.cpp       # Encoder tests
│   └── test_decoder.cpp       # Decoder tests
├── .devcontainer/             # VS Code development container
├── .github/workflows/         # CI/CD pipelines
├── CMakeLists.txt             # Build configuration
└── .clangd                    # Language server configuration
```

## API Reference

The current API provides a simple C-style interface:

### Functions

```cpp
// Encode data with Reed-Solomon error correction
std::vector<unsigned char> rs_encode(const std::vector<unsigned char>& data, int parity_len);

// Decode data and correct errors
bool rs_decode(std::vector<unsigned char>& data, int parity_len, const std::vector<int>& erasures);
```

### Parameters

- `data`: Input data to encode/decode
- `parity_len`: Number of parity/check bytes to generate
- `erasures`: Known positions of erased/missing bytes (for rs_decode)

### Return Values

- `rs_encode`: Returns vector containing parity bytes
- `rs_decode`: Returns `true` if decoding was successful, `false` otherwise

## Building the Project

### Prerequisites

- **C++ Compiler**: GCC 9+ or Clang 10+ with C++20 support
- **CMake**: Version 3.16 or higher
- **Git**: For cloning and dependencies

### Quick Start

1. **Clone the repository**:
   ```bash
   git clone https://github.com/ph0en1xr3t/reedsolomon.git
   cd reedsolomon
   ```

2. **Build with CMake**:
   ```bash
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
   ```

3. **Run the example**:
   ```bash
   ./example
   ```

4. **Run tests**:
   ```bash
   ctest --output-on-failure
   # or directly:
   ./tests
   ```

### Build Options

```bash
# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build (default)
cmake -DCMAKE_BUILD_TYPE=Release ..

# Disable examples
cmake -DBUILD_EXAMPLES=OFF ..

# Disable tests
cmake -DBUILD_TESTS=OFF ..

# Use specific compiler
cmake -DCMAKE_CXX_COMPILER=clang++ ..
```

## Development Environment

### VS Code Devcontainer

The project includes a complete VS Code devcontainer setup:

1. **Open in VS Code**
2. **Install Dev Containers extension**
3. **Ctrl+Shift+P** → "Reopen in Container"

The container includes:
- Ubuntu 22.04 with C++ build tools
- CMake, Make, Clang toolchain
- Google Test pre-installed
- VS Code extensions for C++ development

### Manual Development Setup

Install dependencies on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install -y cmake make g++ clang clang-tidy clang-format
```

On macOS:
```bash
brew install cmake llvm
```

### Code Quality Tools

- **Formatting**: `clang-format` with Google C++ Style
- **Static Analysis**: `clang-tidy` with comprehensive rules
- **Language Server**: `clangd` for VS Code IntelliSense

## Testing

The project uses Google Test framework with comprehensive test suites:

### Test Categories

- **Unit Tests**: Individual function testing (`test_reedsolomon.cpp`)
- **Galois Field Tests**: Mathematical operations (`test_galois_field.cpp`)
- **Encoder Tests**: Encoding functionality (`test_encoder.cpp`)
- **Decoder Tests**: Decoding and error correction (`test_decoder.cpp`)

### Running Tests

```bash
# Build and run all tests
cd build
make tests
ctest --verbose

# Run specific test categories
./tests --gtest_filter="ReedSolomonTest.*"
./tests --gtest_filter="EncoderTest.*"
```

## Continuous Integration

GitHub Actions workflows provide:

- **Multi-platform builds**: Ubuntu, macOS
- **Multi-compiler support**: GCC, Clang
- **Code quality checks**: Formatting, linting, static analysis
- **Memory sanitizers**: AddressSanitizer, ThreadSanitizer, UBSanitizer
- **Automated releases**: Version tagging and artifact generation
- **Dependency updates**: Automated PR creation

## Contributing

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/amazing-feature`
3. **Make your changes** following the Google C++ Style Guide
4. **Run tests**: `make tests && ctest`
5. **Commit changes**: `git commit -m 'Add amazing feature'`
6. **Push to branch**: `git push origin feature/amazing-feature`
7. **Open a Pull Request**

### Development Notes

- Follow Google C++ Style Guide (automatically enforced)
- Add tests for new functionality
- Update documentation for API changes
- Use meaningful commit messages
- Ensure CI passes before submitting PR

## License

This project is licensed under the APACHE 2.0 Licence - see the [LICENSE.md](LICENSE.md) file for details.

## Roadmap

### Phase 1: Foundation (Complete)
- [x] Project structure and build system
- [x] Testing framework integration
- [x] Development environment setup
- [x] CI/CD pipeline implementation

### Phase 2: Core Implementation (In Progress)
- [ ] Galois Field GF(2^8) arithmetic operations
- [ ] Polynomial arithmetic in finite fields
- [ ] Generator polynomial calculation
- [ ] Basic Reed-Solomon encoder implementation

### Phase 3: Advanced Features (Planned)
- [ ] Berlekamp-Massey algorithm for error locator polynomial
- [ ] Chien search for error position finding
- [ ] Forney's algorithm for error magnitude calculation
- [ ] Erasure correction capabilities

### Phase 4: Optimization (Planned)
- [ ] Performance optimizations and benchmarking
- [ ] Memory usage optimization
- [ ] SIMD acceleration where applicable
- [ ] Comprehensive documentation and examples

## References

- Reed, I. S., & Solomon, G. (1960). Polynomial codes over certain finite fields
- Lin, S., & Costello, D. J. (2004). Error control coding
- Wicker, S. B. (1995). Error control systems for digital communication and storage

---

**Note**: This is a development framework. The actual Reed-Solomon encoding/decoding algorithms are not yet implemented. Contributions are welcome!
