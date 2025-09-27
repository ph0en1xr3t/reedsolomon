# Reed-Solomon Error Correction Code Implementation

A complete C++ implementation of Reed-Solomon (RS) codes for error detection and correction, operating over the Galois Field GF(2^8).

## Overview

Reed-Solomon codes are widely used error-correcting codes that can detect and correct multiple symbol errors in data transmission and storage systems. This implementation provides a full encoder/decoder with advanced error correction capabilities including:

- Berlekamp-Massey algorithm for error locator polynomial calculation
- Chien search for error position finding
- Forney's algorithm for error magnitude calculation

## Features

- **Galois Field GF(2^8) Arithmetic**: Complete implementation with lookup tables for efficient operations
- **Polynomial Operations**: Addition, multiplication, evaluation, and division over finite fields
- **Systematic Encoding**: Message symbols appear unchanged in the encoded codeword
- **Multi-Error Correction**: Can correct up to `t = nsym/2` symbol errors
- **Robust Error Detection**: Detects uncorrectable error patterns beyond correction capability

## Code Structure

### Galois Field Operations
